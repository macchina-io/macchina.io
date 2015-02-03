//
// BundleWrapper.cpp
//
// $Id: //poco/1.4/OSP/JS/src/BundleWrapper.cpp#4 $
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "BundleWrapper.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/StreamCopier.h"
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
	v8::Local<v8::ObjectTemplate> bundleTemplate = v8::ObjectTemplate::New();
	bundleTemplate->SetInternalFieldCount(1);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "name"), name);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "symbolicName"), symbolicName);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "version"), version);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "state"), state);
	bundleTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "active"), active);
	bundleTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getResource"), v8::FunctionTemplate::New(pIsolate, getResource));
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


void BundleWrapper::getResource(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::HandleScope scope(args.GetIsolate());
	Poco::OSP::Bundle* pBundle = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::Bundle>(args);
	std::string name = toString(args[0]);
	std::string data;
	try
	{
		std::auto_ptr<std::istream> pStream(pBundle->getResource(name));
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


} } } // namespace Poco::OSP::JS
