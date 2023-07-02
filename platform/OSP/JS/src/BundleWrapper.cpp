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
#include "Poco/OSP/Bundle.h"
#include "Poco/StreamCopier.h"
#include "Poco/SharedPtr.h"
#include <memory>


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
	v8::Local<v8::ObjectTemplate> bundleTemplate = v8::ObjectTemplate::New(pIsolate);
	bundleTemplate->SetInternalFieldCount(1);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "name"), name);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "symbolicName"), symbolicName);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "version"), version);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "path"), path);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "state"), state);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "active"), active);
	bundleTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getResourceString"), v8::FunctionTemplate::New(pIsolate, getResourceString));
	bundleTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getResourceBuffer"), v8::FunctionTemplate::New(pIsolate, getResourceBuffer));
	bundleTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getLocalizedResourceString"), v8::FunctionTemplate::New(pIsolate, getLocalizedResourceString));
	bundleTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getLocalizedResourceBuffer"), v8::FunctionTemplate::New(pIsolate, getLocalizedResourceBuffer));
	bundleTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getResource"), v8::FunctionTemplate::New(pIsolate, getResourceString)); // deprecated
	bundleTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getLocalizedResource"), v8::FunctionTemplate::New(pIsolate, getLocalizedResourceString)); // deprecated
	bundleTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getBinaryResource"), v8::FunctionTemplate::New(pIsolate, getResourceBuffer)); // deprecated
	bundleTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getLocalizedBinaryResource"), v8::FunctionTemplate::New(pIsolate, getLocalizedResourceBuffer)); // deprecated
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


void BundleWrapper::path(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	returnString(info, pBundle->path());
}


void BundleWrapper::state(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	returnString(info, pBundle->stateString());
}


void BundleWrapper::active(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(info);
	info.GetReturnValue().Set(pBundle->state() == Poco::OSP::Bundle::BUNDLE_ACTIVE);
}


void BundleWrapper::getResourceString(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::HandleScope scope(args.GetIsolate());
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(args);
	std::string name = toString(args[0]);
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
	v8::HandleScope scope(args.GetIsolate());
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(args);
	std::string name = toString(args[0]);
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
	v8::HandleScope scope(args.GetIsolate());
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(args);
	std::string name = toString(args[0]);
	std::string data;
	try
	{
		Poco::SharedPtr<std::istream> pStream;
		if (args.Length() > 1)
		{
			std::string language = toString(args[1]);
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
	v8::HandleScope scope(args.GetIsolate());
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(args);
	std::string name = toString(args[0]);
	std::string data;
	try
	{
		Poco::SharedPtr<std::istream> pStream;
		if (args.Length() > 1)
		{
			std::string language = toString(args[1]);
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
			args.GetReturnValue().Set(v8::Local<v8::Object>::New(args.GetIsolate(), bufferObject));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


} } } // namespace Poco::OSP::JS
