//
// Wrapper.h
//
// Library: JS/Core
// Package: Wrappers
// Module:  Wrapper
//
// Definition of the Wrapper interface.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Core_Wrapper_INCLUDED
#define JS_Core_Wrapper_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/SharedPtr.h"
#include "Poco/AutoPtr.h"
#include "Poco/Exception.h"
#include "Poco/Mutex.h"
#include <typeinfo>
#include <map>
#include <set>
#include "v8.h"


// Helper macro to check the result of Object/Array->Set(), which must not be ignored,
// but apparently no (except maybe the V8 devs) knows what to do with either. 
// So we just write a message to cerr and be done with it.
#define V8_CHECK_SET_RESULT(expr) Poco::JS::Core::Wrapper::checkSetResult(expr, __FILE__, __LINE__)


namespace Poco {
namespace JS {
namespace Core {


namespace Internal {


template <class T>
class DeletePolicy
{
public:
	static void release(T pObject)
	{
		delete pObject;
	}
};


template <class T>
class NoReleasePolicy
{
public:
	static void release(T pObject)
	{
	}
};


} // namespace Internal


class JSCore_API WeakPersistentWrapperBase
	/// A common base class for all WeakPersistentWrapper template
	/// instantiations that defines a virtual destructor.
{
public:
	virtual ~WeakPersistentWrapperBase() = 0;
};


class JSCore_API WeakPersistentWrapperRegistry
	/// This class maintains references to all active WeakPersistentWrapper instances.
	///
	/// The V8 engine won't properly garbage-collect any remaining objects when a script's
	/// context is disposed. This is not an issue for pure JavaScript objects, as they
	/// reside in the JavaScript heap, which will eventually be freed when the Isolate
	/// is disposed. This is, however, an issue for wrapped, heap-allocated native
	/// objects. If they're not garbage collected, the destructors of the wrapped
	/// C++ objects will never be called.
	///
	/// Therefore, we register each WeakPersistentWrapper wrapper in a Isolate-specific
	/// registry. If at the time we dispose of the Isolate any wrappers for that Isolate
	/// remain in the registry, we can safely delete them, ensuring that all wrapped
	/// C++ objects are properly deleted.
{
public:
	using Ptr = Poco::SharedPtr<WeakPersistentWrapperRegistry>;

	WeakPersistentWrapperRegistry();
		/// Creates a new WeakPersistentWrapperRegistry.

	~WeakPersistentWrapperRegistry();
		/// Destroys the WeakPersistentWrapperRegistry and
		/// deletes any WeakPersistentWrapper instances still registered.

	void registerWrapper(WeakPersistentWrapperBase* pWrapper);
		/// Registers a WeakPersistentWrapper instance.

	void unregisterWrapper(WeakPersistentWrapperBase* pWrapper);
		/// Unregisters a WeakPersistentWrapper instance.

	static WeakPersistentWrapperRegistry& forIsolate(v8::Isolate* pIsolate);
		/// Returns the WeakPersistentWrapperRegistry for the given Isolate.
		/// If no WeakPersistentWrapperRegistry for that Isolate exists, a new
		/// one is created, otherwise the existing instance is returned.

	static void cleanupIsolate(v8::Isolate* pIsolate);
		/// Destroys the WeakPersistentWrapperRegistry instance for the
		/// given Isolate, if one exists.

protected:
	void cleanup();
		/// Deletes all registered wrappers.

private:
	using WrapperSet = std::set<WeakPersistentWrapperBase*>;
	using RegistryMap = std::map<v8::Isolate*, WeakPersistentWrapperRegistry::Ptr>;

	WrapperSet _wrappers;

	static RegistryMap _registry;
	static Poco::Mutex _registryMutex;
};


template <class T, class RP>
class WeakPersistentWrapper: public WeakPersistentWrapperBase
	/// Helper for wrapping native types in weak persistent handles.
	///
	/// Takes ownership of the native object and makes sure both
	/// the native object and the wrapping JS object are properly
	/// destroyed when garbage collected.
{
public:
	WeakPersistentWrapper(v8::Isolate* pIsolate, const v8::Local<v8::Object>& jsObject, T pNative):
		_pIsolate(pIsolate),
		_pNative(pNative)
	{
		_persistent.Reset(pIsolate, jsObject);

		WeakPersistentWrapperRegistry::forIsolate(_pIsolate).registerWrapper(this);
	}

	WeakPersistentWrapper(v8::Isolate* pIsolate, const v8::MaybeLocal<v8::Object>& maybeJSObject, T pNative):
		_pIsolate(pIsolate),
		_pNative(pNative)
	{
		v8::Local<v8::Object> jsObject;
		if (maybeJSObject.ToLocal(&jsObject))
		{
			_persistent.Reset(pIsolate, jsObject);
		}

		WeakPersistentWrapperRegistry::forIsolate(_pIsolate).registerWrapper(this);
	}

	~WeakPersistentWrapper()
	{
		WeakPersistentWrapperRegistry::forIsolate(_pIsolate).unregisterWrapper(this);

		_persistent.Reset();
		RP::release(_pNative);
	}

	v8::Persistent<v8::Object>& persistent()
	{
		return _persistent;
	}

	static void destruct(const v8::WeakCallbackInfo<WeakPersistentWrapper>& info)
	{
		delete info.GetParameter();
	}

private:
	WeakPersistentWrapper();
	WeakPersistentWrapper(const WeakPersistentWrapper&);
	WeakPersistentWrapper& operator = (const WeakPersistentWrapper&);

	v8::Isolate* _pIsolate;
	v8::Persistent<v8::Object> _persistent;
	T _pNative;
};


class JSCore_API Wrapper
	/// Interface for JavaScript V8 Engine Wrapper classes.
{
public:
	Wrapper();
		/// Creates the Wrapper.

	virtual ~Wrapper();
		/// Destroys the Wrapper.

	virtual v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate) = 0;
		/// Creates and returns a V8 ObjectTemplate.

	template <typename T>
	v8::MaybeLocal<v8::Object> wrapNative(v8::Isolate* pIsolate, T* pNative)
	{
		using namespace std::string_literals;

	 	v8::EscapableHandleScope handleScope(pIsolate);
		v8::Local<v8::ObjectTemplate> wrapperTempl = objectTemplate(pIsolate);
		poco_assert (!wrapperTempl.IsEmpty());
		v8::MaybeLocal<v8::Object> maybeWrapper = wrapperTempl->NewInstance(pIsolate->GetCurrentContext());
		v8::Local<v8::Object> wrapper;
		if (maybeWrapper.ToLocal(&wrapper))
		{
			v8::Local<v8::External> ext = v8::External::New(pIsolate, pNative);
			poco_assert (wrapper->InternalFieldCount() > 0);
			wrapper->SetInternalField(0, ext);
			wrapper->SetPrivate(
				pIsolate->GetCurrentContext(),
				v8::Private::ForApi(pIsolate, toV8Internalized(pIsolate, "Poco::nativeType"s)),
				toV8String(pIsolate, typeid(T).name()));
			return handleScope.Escape(wrapper);
		}
		else return maybeWrapper;
	}

	v8::MaybeLocal<v8::Object> wrapNative(v8::Isolate* pIsolate)
	{
	 	v8::EscapableHandleScope handleScope(pIsolate);
		v8::Local<v8::ObjectTemplate> wrapperTempl = objectTemplate(pIsolate);
		poco_assert (!wrapperTempl.IsEmpty());
		v8::MaybeLocal<v8::Object> maybeWrapper = wrapperTempl->NewInstance(pIsolate->GetCurrentContext());
		v8::Local<v8::Object> wrapper;
		if (maybeWrapper.ToLocal(&wrapper))
		{
			return handleScope.Escape(wrapper);
		}
		else return maybeWrapper;
	}

	template <typename T>
	v8::Persistent<v8::Object>& wrapNativePersistent(v8::Isolate* pIsolate, T* pNative)
	{
		using WPW = WeakPersistentWrapper<T*, Internal::DeletePolicy<T*>>;

		WPW* pWPW = new WPW(pIsolate, wrapNative(pIsolate, pNative), pNative);
		if (!pWPW->persistent().IsEmpty())
		{
			pWPW->persistent().SetWeak(pWPW, WPW::destruct, v8::WeakCallbackType::kParameter);
		}
		return pWPW->persistent();
	}

	template <typename T>
	v8::Persistent<v8::Object>& wrapNativePersistent(v8::Isolate* pIsolate, Poco::SharedPtr<T> pNative)
	{
		using WPW = WeakPersistentWrapper<Poco::SharedPtr<T>, Internal::NoReleasePolicy<Poco::SharedPtr<T>>>;

		WPW* pWPW = new WPW(pIsolate, wrapNative(pIsolate, pNative.get()), pNative);
		if (!pWPW->persistent().IsEmpty())
		{
			pWPW->persistent().SetWeak(pWPW, WPW::destruct, v8::WeakCallbackType::kParameter);
		}
		return pWPW->persistent();
	}

	template <typename T>
	v8::Persistent<v8::Object>& wrapNativePersistent(v8::Isolate* pIsolate, Poco::AutoPtr<T> pNative)
	{
		using WPW = WeakPersistentWrapper<Poco::AutoPtr<T>, Internal::NoReleasePolicy<Poco::AutoPtr<T>>>;

		WPW* pWPW = new WPW(pIsolate, wrapNative(pIsolate, pNative.get()), pNative);
		if (!pWPW->persistent().IsEmpty())
		{
			pWPW->persistent().SetWeak(pWPW, WPW::destruct, v8::WeakCallbackType::kParameter);
		}
		return pWPW->persistent();
	}

	template <typename T, typename A>
	static T* unwrapNative(const A& args)
	{
		v8::Local<v8::Object> holder = args.Holder();
		if (holder->InternalFieldCount() > 0)
		{
			v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(holder->GetInternalField(0));
			void* pRaw = wrap->Value();
			return static_cast<T*>(pRaw);
		}
		else return 0;
	}

	template <typename T>
	static T* unwrapNativeObject(const v8::Local<v8::Value>& value)
	{
		if (!value.IsEmpty() && value->IsObject())
		{
			v8::Local<v8::Object> object = v8::Local<v8::Object>::Cast(value);
			if (object->InternalFieldCount() > 0)
			{
				v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(object->GetInternalField(0));
				void* pRaw = wrap->Value();
				return static_cast<T*>(pRaw);
			}
		}
		return 0;
	}

	template <typename T>
	static T* safeUnwrapNative(v8::Isolate* pIsolate, v8::Local<v8::Value>& value)
	{
		using namespace std::string_literals;

		if (!value.IsEmpty() && value->IsObject())
		{
			v8::Local<v8::Object> object = v8::Local<v8::Object>::Cast(value);
			if (object->InternalFieldCount() > 0)
			{
				v8::MaybeLocal<v8::Value> maybeNativeType = object->GetPrivate(
					pIsolate->GetCurrentContext(),
					v8::Private::ForApi(pIsolate, toV8Internalized(pIsolate, "Poco::nativeType"s)));
				v8::Local<v8::Value> nativeType;
				if (maybeNativeType.ToLocal(&nativeType))
				{
					if (nativeType->IsString() && toString(pIsolate, nativeType) == typeid(T).name())
					{
						v8::Local<v8::External> wrap = v8::Local<v8::External>::Cast(object->GetInternalField(0));
						void* pRaw = wrap->Value();
						return static_cast<T*>(pRaw);
					}
				}
			}
		}
		return 0;
	}

	template <typename T>
	static bool isWrapper(v8::Isolate* pIsolate, const v8::Local<v8::Value>& value)
	{
		using namespace std::string_literals;

		if (!value.IsEmpty() && value->IsObject())
		{
			v8::Local<v8::Object> object = v8::Local<v8::Object>::Cast(value);
			if (object->InternalFieldCount() > 0)
			{
				v8::MaybeLocal<v8::Value> maybeNativeType = object->GetPrivate(
					pIsolate->GetCurrentContext(),
					v8::Private::ForApi(pIsolate, toV8Internalized(pIsolate, "Poco::nativeType"s)));
				v8::Local<v8::Value> nativeType;
				if (maybeNativeType.ToLocal(&nativeType))
				{
					if (nativeType->IsString())
					{
						return toString(pIsolate, nativeType) == typeid(T).name();
					}
				}
			}
		}
		return false;
	}

	static std::string toString(v8::Isolate* pIsolate, v8::Local<v8::Value> value);
	static std::string toString(v8::Isolate* pIsolate, v8::Local<v8::String> value);
	static std::string toString(v8::Isolate* pIsolate, v8::Local<v8::Name> value);
	static std::string toString(v8::Isolate* pIsolate, v8::MaybeLocal<v8::Value> maybeValue);
	static std::string toString(v8::Isolate* pIsolate, v8::MaybeLocal<v8::String> maybeValue);
	static v8::Local<v8::String> toV8String(v8::Isolate* pIsolate, const std::string& value, v8::NewStringType type = v8::NewStringType::kNormal);
	static v8::Local<v8::String> toV8Internalized(v8::Isolate* pIsolate, const std::string& value);
	static v8::Local<v8::String> toV8String(v8::Isolate* pIsolate, const char* value);

	template <typename T>
	static void returnString(const T& info, const std::string& value)
	{
		info.GetReturnValue().Set(toV8String(info.GetIsolate(), value));
	}

	template <typename T>
	static void returnException(const T& info, const Poco::Exception& exc)
	{
		std::string displayText = exc.displayText();
		info.GetReturnValue().Set(
			info.GetIsolate()->ThrowException(
				v8::Exception::Error(toV8String(info.GetIsolate(), displayText))
			)
		);
	}

	template <typename T>
	static void returnException(const T& info, const std::string& displayText)
	{
		info.GetReturnValue().Set(
			info.GetIsolate()->ThrowException(
				v8::Exception::Error(toV8String(info.GetIsolate(), displayText))
			)
		);
	}

	static void checkSetResult(const v8::Maybe<bool>& result, const char* file, int line);

protected:
	static void reportEmptySetResult(const char* file, int line);

private:
	Wrapper(const Wrapper&);
	Wrapper& operator = (const Wrapper&);
};


//
// inlines
//


inline void Wrapper::checkSetResult(const v8::Maybe<bool>& result, const char* file, int line)
{
	if (result.IsNothing())
	{
		reportEmptySetResult(file, line);
	}
}


} } } // namespace Poco::JS::Core


#endif // JS_Core_Wrapper_INCLUDED
