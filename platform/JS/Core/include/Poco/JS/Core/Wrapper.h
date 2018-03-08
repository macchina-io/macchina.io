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
// SPDX-License-Identifier: Apache-2.0
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
	typedef Poco::SharedPtr<WeakPersistentWrapperRegistry> Ptr;

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
	typedef std::set<WeakPersistentWrapperBase*> WrapperSet;
	typedef std::map<v8::Isolate*, WeakPersistentWrapperRegistry::Ptr> RegistryMap;

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

	~WeakPersistentWrapper()
	{
		WeakPersistentWrapperRegistry::forIsolate(_pIsolate).unregisterWrapper(this);

		if (!_persistent.IsEmpty())
		{
			_persistent.ClearWeak();
			_persistent.Reset();
		}
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
	v8::Local<v8::Object> wrapNative(v8::Isolate* pIsolate, T* pNative)
	{
	 	v8::EscapableHandleScope handleScope(pIsolate);
		v8::Local<v8::ObjectTemplate> wrapperTempl = objectTemplate(pIsolate);
		poco_assert (!wrapperTempl.IsEmpty());
		v8::Local<v8::Object> wrapper = wrapperTempl->NewInstance();
		if (!wrapper.IsEmpty())
		{
			v8::Local<v8::External> ext = v8::External::New(pIsolate, pNative);
			poco_assert (wrapper->InternalFieldCount() > 0);
			wrapper->SetInternalField(0, ext);
			wrapper->SetPrivate(
				pIsolate->GetCurrentContext(),
				v8::Private::New(pIsolate, v8::String::NewFromUtf8(pIsolate, "Poco::nativeType")),
				v8::String::NewFromUtf8(pIsolate, typeid(T).name()));
		}
		return handleScope.Escape(wrapper);
	}

	v8::Handle<v8::Object> wrapNative(v8::Isolate* pIsolate)
	{
	 	v8::EscapableHandleScope handleScope(pIsolate);
		v8::Local<v8::ObjectTemplate> wrapperTempl = objectTemplate(pIsolate);
		poco_assert (!wrapperTempl.IsEmpty());
		v8::Local<v8::Object> wrapper = wrapperTempl->NewInstance();
		return handleScope.Escape(wrapper);
	}

	template <typename T>
	v8::Persistent<v8::Object>& wrapNativePersistent(v8::Isolate* pIsolate, T* pNative)
	{
		typedef WeakPersistentWrapper<T*, Internal::DeletePolicy<T*> > WPW;

		WPW* pWPW = new WPW(pIsolate, wrapNative(pIsolate, pNative), pNative);
		if (!pWPW->persistent().IsEmpty())
		{
			pWPW->persistent().SetWeak(pWPW, WPW::destruct, v8::WeakCallbackType::kParameter);
			pWPW->persistent().MarkIndependent();
		}
		return pWPW->persistent();
	}

	template <typename T>
	v8::Persistent<v8::Object>& wrapNativePersistent(v8::Isolate* pIsolate, Poco::SharedPtr<T> pNative)
	{
		typedef WeakPersistentWrapper<Poco::SharedPtr<T>, Internal::NoReleasePolicy<Poco::SharedPtr<T> > > WPW;

		WPW* pWPW = new WPW(pIsolate, wrapNative(pIsolate, pNative.get()), pNative);
		if (!pWPW->persistent().IsEmpty())
		{
			pWPW->persistent().SetWeak(pWPW, WPW::destruct, v8::WeakCallbackType::kParameter);
			pWPW->persistent().MarkIndependent();
		}
		return pWPW->persistent();
	}

	template <typename T>
	v8::Persistent<v8::Object>& wrapNativePersistent(v8::Isolate* pIsolate, Poco::AutoPtr<T> pNative)
	{
		typedef WeakPersistentWrapper<Poco::AutoPtr<T>, Internal::NoReleasePolicy<Poco::AutoPtr<T> > > WPW;

		WPW* pWPW = new WPW(pIsolate, wrapNative(pIsolate, pNative.get()), pNative);
		if (!pWPW->persistent().IsEmpty())
		{
			pWPW->persistent().SetWeak(pWPW, WPW::destruct, v8::WeakCallbackType::kParameter);
			pWPW->persistent().MarkIndependent();
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
		if (!value.IsEmpty() && value->IsObject())
		{
			v8::Local<v8::Object> object = v8::Local<v8::Object>::Cast(value);
			if (object->InternalFieldCount() > 0)
			{
				v8::MaybeLocal<v8::Value> maybeNativeType = object->GetPrivate(pIsolate->GetCurrentContext(), v8::Private::New(pIsolate, v8::String::NewFromUtf8(pIsolate, "Poco::nativeType")));
				if (!maybeNativeType.IsEmpty())
				{
					v8::Local<v8::Value> nativeType = maybeNativeType.ToLocalChecked();
					if (nativeType->IsString() && toString(nativeType) == typeid(T).name())
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
		if (!value.IsEmpty() && value->IsObject())
		{
			v8::Local<v8::Object> object = v8::Local<v8::Object>::Cast(value);
			if (object->InternalFieldCount() > 0)
			{
				v8::MaybeLocal<v8::Value> maybeNativeType = object->GetPrivate(pIsolate->GetCurrentContext(), v8::Private::New(pIsolate, v8::String::NewFromUtf8(pIsolate, "Poco::nativeType")));
				if (!maybeNativeType.IsEmpty())
				{
					v8::Local<v8::Value> nativeType = maybeNativeType.ToLocalChecked();
					if (nativeType->IsString())
					{
						return toString(nativeType) == typeid(T).name();
					}
				}
			}
		}
		return false;
	}

	static std::string toString(v8::Local<v8::Value> value);

	template <typename T>
	static void returnString(const T& info, const std::string& value)
	{
		info.GetReturnValue().Set(v8::String::NewFromUtf8(
			info.GetIsolate(),
			value.c_str(),
			v8::String::kNormalString,
			static_cast<int>(value.length())));
	}

	template <typename T>
	static void returnException(const T& info, const Poco::Exception& exc)
	{
		std::string displayText = exc.displayText();
		info.GetReturnValue().Set(
			info.GetIsolate()->ThrowException(
				v8::Exception::Error(
					v8::String::NewFromUtf8(
						info.GetIsolate(),
						displayText.c_str(),
						v8::String::kNormalString,
						static_cast<int>(displayText.length())
					)
				)
			)
		);
	}

	template <typename T>
	static void returnException(const T& info, const std::string& displayText)
	{
		info.GetReturnValue().Set(
			info.GetIsolate()->ThrowException(
				v8::Exception::Error(
					v8::String::NewFromUtf8(
						info.GetIsolate(),
						displayText.c_str(),
						v8::String::kNormalString,
						static_cast<int>(displayText.length())
					)
				)
			)
		);
	}

private:
	Wrapper(const Wrapper&);
	Wrapper& operator = (const Wrapper&);
};


} } } // namespace Poco::JS::Core


#endif // JS_Core_Wrapper_INCLUDED
