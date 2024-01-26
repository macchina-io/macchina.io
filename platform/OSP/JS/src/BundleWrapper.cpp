//
// BundleWrapper.cpp
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/JS/BundleWrapper.h"
#include "Poco/JS/Core/BufferWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/StreamCopier.h"
#include "Poco/SharedPtr.h"
#include <memory>


using Poco::JS::Core::Wrapper;
using namespace std::string_literals;


namespace Poco {
namespace OSP {
namespace JS {


BundleWrapper::BundleWrapper()
{
}


BundleWrapper::~BundleWrapper()
{
}


v8::Handle<v8::ObjectTemplate> BundleWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("OSP.Bundle"s));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Local<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "name"s), name);
		objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "symbolicName"s), symbolicName);
		objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "version"s), version);
		objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "vendor"s), vendor);
		objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "copyright"s), copyright);
		objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "path"s), path);
		objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "runLevel"s), runLevel);
		objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "state"s), state);
		objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "active"s), active);
		objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "lazyStart"s), lazyStart);
		objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "sealed"s), sealed);
		objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "preventUninstall"s), preventUninstall);
		objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "requiredBundles"s), requiredBundles);
		objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "requiredModules"s), requiredModules);
		objectTemplate->SetAccessor(Wrapper::toV8Internalized(pIsolate, "providedModules"s), providedModules);
		objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "getResourceString"s), v8::FunctionTemplate::New(pIsolate, getResourceString));
		objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "getResourceBuffer"s), v8::FunctionTemplate::New(pIsolate, getResourceBuffer));
		objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "getLocalizedResourceString"s), v8::FunctionTemplate::New(pIsolate, getLocalizedResourceString));
		objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "getLocalizedResourceBuffer"s), v8::FunctionTemplate::New(pIsolate, getLocalizedResourceBuffer));
		objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "getResource"s), v8::FunctionTemplate::New(pIsolate, getResourceString)); // deprecated
		objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "getLocalizedResource"s), v8::FunctionTemplate::New(pIsolate, getLocalizedResourceString)); // deprecated
		objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "getBinaryResource"s), v8::FunctionTemplate::New(pIsolate, getResourceBuffer)); // deprecated
		objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "getLocalizedBinaryResource"s), v8::FunctionTemplate::New(pIsolate, getLocalizedResourceBuffer)); // deprecated
		objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "equals"s), v8::FunctionTemplate::New(pIsolate, equals));
		objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "toJSON"s), v8::FunctionTemplate::New(pIsolate, toJSON));
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> bundleTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(bundleTemplate);
}


void BundleWrapper::name(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	returnString(info, pBundle->name());
}


void BundleWrapper::symbolicName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	returnString(info, pBundle->symbolicName());
}


void BundleWrapper::version(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	returnString(info, pBundle->version().toString());
}


void BundleWrapper::vendor(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	returnString(info, pBundle->vendor());
}


void BundleWrapper::copyright(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	returnString(info, pBundle->copyright());
}


void BundleWrapper::path(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	returnString(info, pBundle->path());
}


void BundleWrapper::runLevel(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	returnString(info, pBundle->runLevel());
}


void BundleWrapper::state(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	returnString(info, pBundle->stateString());
}


void BundleWrapper::active(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	info.GetReturnValue().Set(pBundle->isActive());
}


void BundleWrapper::lazyStart(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	info.GetReturnValue().Set(pBundle->lazyStart());
}


void BundleWrapper::sealed(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	info.GetReturnValue().Set(pBundle->sealed());
}


void BundleWrapper::preventUninstall(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	info.GetReturnValue().Set(pBundle->preventUninstall());
}


void BundleWrapper::requiredBundles(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	info.GetReturnValue().Set(dependencies(info.GetIsolate(), pBundle->requiredBundles()));
}


void BundleWrapper::requiredModules(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	info.GetReturnValue().Set(dependencies(info.GetIsolate(), pBundle->requiredModules()));
}


void BundleWrapper::providedModules(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	info.GetReturnValue().Set(modules(info.GetIsolate(), pBundle->providedModules()));
}


void BundleWrapper::getResourceString(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(args);
	std::string name = toString(pIsolate, args[0]);
	std::string data;
	try
	{
		std::unique_ptr<std::istream> pStream(pBundle->getResource(name));
		if (pStream.get())
		{
			Poco::StreamCopier::copyToString(*pStream, data);
			returnString(args, data);
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void BundleWrapper::getResourceBuffer(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(args);
	std::string name = toString(pIsolate, args[0]);
	std::string data;
	try
	{
		std::unique_ptr<std::istream> pStream(pBundle->getResource(name));
		if (pStream.get())
		{
			Poco::StreamCopier::copyToString(*pStream, data);
			Poco::JS::Core::BufferWrapper::Buffer* pBuffer = new Poco::JS::Core::BufferWrapper::Buffer(data.data(), data.size());
			Poco::JS::Core::BufferWrapper wrapper;
			v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(args.GetIsolate(), pBuffer));
			args.GetReturnValue().Set(v8::Local<v8::Object>::New(args.GetIsolate(), bufferObject));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void BundleWrapper::getLocalizedResourceString(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(args);
	std::string name = toString(pIsolate, args[0]);
	std::string data;
	try
	{
		Poco::SharedPtr<std::istream> pStream;
		if (args.Length() > 1)
		{
			std::string language = toString(pIsolate, args[1]);
			Poco::OSP::LanguageTag languageTag(language);
			pStream = pBundle->getLocalizedResource(name, languageTag);
		}
		else
		{
			pStream = pBundle->getLocalizedResource(name);
		}

		if (pStream)
		{
			Poco::StreamCopier::copyToString(*pStream, data);
			returnString(args, data);
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void BundleWrapper::getLocalizedResourceBuffer(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(args);
	std::string name = toString(pIsolate, args[0]);
	std::string data;
	try
	{
		Poco::SharedPtr<std::istream> pStream;
		if (args.Length() > 1)
		{
			std::string language = toString(pIsolate, args[1]);
			Poco::OSP::LanguageTag languageTag(language);
			pStream = pBundle->getLocalizedResource(name, languageTag);
		}
		else
		{
			pStream = pBundle->getLocalizedResource(name);
		}

		if (pStream)
		{
			Poco::StreamCopier::copyToString(*pStream, data);
			Poco::JS::Core::BufferWrapper::Buffer* pBuffer = new Poco::JS::Core::BufferWrapper::Buffer(data.data(), data.size());
			Poco::JS::Core::BufferWrapper wrapper;
			v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(args.GetIsolate(), pBuffer));
			args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, bufferObject));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void BundleWrapper::equals(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	bool result = false;
	if (args.Length() > 0 && args[0]->IsObject())
	{
		if (Wrapper::isWrapper<Poco::OSP::Bundle>(args.GetIsolate(), args[0]))
		{
			Poco::OSP::Bundle* pThisBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(args);
			Poco::OSP::Bundle* pOtherBundle = Poco::JS::Core::Wrapper::unwrapNativeObject<Poco::OSP::Bundle>(args[0]);
			result = pThisBundle == pOtherBundle;
		}
	}
	args.GetReturnValue().Set(result);
}


void BundleWrapper::toJSON(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(args);
	try
	{
		v8::Local<v8::Object> object = v8::Object::New(pIsolate);
		V8_CHECK_SET_RESULT(object->Set(context, Wrapper::toV8String(pIsolate, "id"s), v8::Int32::New(pIsolate, pBundle->id())));
		V8_CHECK_SET_RESULT(object->Set(context, Wrapper::toV8String(pIsolate, "symbolicName"s), Wrapper::toV8String(pIsolate, pBundle->symbolicName())));
		V8_CHECK_SET_RESULT(object->Set(context, Wrapper::toV8String(pIsolate, "name"s), Wrapper::toV8String(pIsolate, pBundle->name())));
		V8_CHECK_SET_RESULT(object->Set(context, Wrapper::toV8String(pIsolate, "version"s), Wrapper::toV8String(pIsolate, pBundle->version().toString())));
		V8_CHECK_SET_RESULT(object->Set(context, Wrapper::toV8String(pIsolate, "vendor"s), Wrapper::toV8String(pIsolate, pBundle->vendor())));
		V8_CHECK_SET_RESULT(object->Set(context, Wrapper::toV8String(pIsolate, "copyright"s), Wrapper::toV8String(pIsolate, pBundle->copyright())));
		V8_CHECK_SET_RESULT(object->Set(context, Wrapper::toV8String(pIsolate, "runLevel"s), Wrapper::toV8String(pIsolate, pBundle->runLevel())));
		V8_CHECK_SET_RESULT(object->Set(context, Wrapper::toV8String(pIsolate, "state"s), Wrapper::toV8String(pIsolate, pBundle->stateString())));
		V8_CHECK_SET_RESULT(object->Set(context, Wrapper::toV8String(pIsolate, "path"s), Wrapper::toV8String(pIsolate, pBundle->path())));
		V8_CHECK_SET_RESULT(object->Set(context, Wrapper::toV8String(pIsolate, "lazyStart"s), v8::Boolean::New(pIsolate, pBundle->lazyStart())));
		V8_CHECK_SET_RESULT(object->Set(context, Wrapper::toV8String(pIsolate, "sealed"s), v8::Boolean::New(pIsolate, pBundle->sealed())));
		V8_CHECK_SET_RESULT(object->Set(context, Wrapper::toV8String(pIsolate, "preventUninstall"s), v8::Boolean::New(pIsolate, pBundle->preventUninstall())));
		V8_CHECK_SET_RESULT(object->Set(context, Wrapper::toV8String(pIsolate, "requiredBundles"s), dependencies(pIsolate, pBundle->requiredBundles())));
		V8_CHECK_SET_RESULT(object->Set(context, Wrapper::toV8String(pIsolate, "requiredModules"s), dependencies(pIsolate, pBundle->requiredModules())));
		V8_CHECK_SET_RESULT(object->Set(context, Wrapper::toV8String(pIsolate, "providedModules"s), modules(pIsolate, pBundle->providedModules())));
		args.GetReturnValue().Set(object);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


v8::Local<v8::Array> BundleWrapper::dependencies(v8::Isolate* pIsolate, const Poco::OSP::Bundle::Dependencies& deps)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	v8::Local<v8::Array> depsArray = v8::Array::New(pIsolate, static_cast<int>(deps.size()));
	if (!depsArray.IsEmpty())
	{
		for (unsigned i = 0; i < static_cast<unsigned>(deps.size()); i++)
		{
			v8::Local<v8::Object> depObject = v8::Object::New(pIsolate);
			V8_CHECK_SET_RESULT(depObject->Set(context, Wrapper::toV8String(pIsolate, "symbolicName"s), Wrapper::toV8String(pIsolate, deps[i].symbolicName)));
			V8_CHECK_SET_RESULT(depObject->Set(context, Wrapper::toV8String(pIsolate, "versions"s), Wrapper::toV8String(pIsolate, deps[i].versions.toString())));
			V8_CHECK_SET_RESULT(depsArray->Set(context, i, v8::Local<v8::Object>::New(pIsolate, depObject)));
		}
	}
	return handleScope.Escape(depsArray);
}


v8::Local<v8::Array> BundleWrapper::modules(v8::Isolate* pIsolate, const Poco::OSP::Bundle::Modules& mods)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	v8::Local<v8::Array> modsArray = v8::Array::New(pIsolate, static_cast<int>(mods.size()));
	if (!modsArray.IsEmpty())
	{
		for (unsigned i = 0; i < static_cast<unsigned>(mods.size()); i++)
		{
			v8::Local<v8::Object> modObject = v8::Object::New(pIsolate);
			V8_CHECK_SET_RESULT(modObject->Set(context, Wrapper::toV8String(pIsolate, "symbolicName"s), Wrapper::toV8String(pIsolate, mods[i].symbolicName)));
			V8_CHECK_SET_RESULT(modObject->Set(context, Wrapper::toV8String(pIsolate, "version"s), Wrapper::toV8String(pIsolate, mods[i].version.toString())));
			V8_CHECK_SET_RESULT(modsArray->Set(context, i, v8::Local<v8::Object>::New(pIsolate, modObject)));
		}
	}
	return handleScope.Escape(modsArray);
}


} } } // namespace Poco::OSP::JS
