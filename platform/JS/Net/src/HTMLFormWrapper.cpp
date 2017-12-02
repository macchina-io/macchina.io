//
// HTMLFormWrapper.cpp
//
// Library: JS/Net
// Package: Wrappers
// Module:  HTMLFormWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Net/HTMLFormWrapper.h"
#include "Poco/JS/Net/HTTPResponseWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"


namespace Poco {
namespace JS {
namespace Net {


HTMLFormWrapper::HTMLFormWrapper()
{
}


HTMLFormWrapper::~HTMLFormWrapper()
{
}


v8::Handle<v8::ObjectTemplate> HTMLFormWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Net.HTMLForm"));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "has"), v8::FunctionTemplate::New(pIsolate, hasField));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "get"), v8::FunctionTemplate::New(pIsolate, getField));

		// deprecated - for backwards compatibility, will be removed eventually
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "hasField"), v8::FunctionTemplate::New(pIsolate, hasField));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getField"), v8::FunctionTemplate::New(pIsolate, getField));

		objectTemplate->SetNamedPropertyHandler(getProperty);
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> formTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(formTemplate);
}


void HTMLFormWrapper::hasField(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	Poco::Net::HTMLForm* pForm = Wrapper::unwrapNative<Poco::Net::HTMLForm>(args);
	std::string name = toString(args[0]);
	bool result = pForm->has(name);
	args.GetReturnValue().Set(result);
}


void HTMLFormWrapper::getField(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	Poco::Net::HTMLForm* pForm = Wrapper::unwrapNative<Poco::Net::HTMLForm>(args);
	std::string name = toString(args[0]);
	std::string deflt;
	if (args.Length() > 1) deflt = toString(args[1]);
	std::string value = pForm->get(name, deflt);
	returnString(args, value);
}


void HTMLFormWrapper::getProperty(v8::Local<v8::String> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Local<v8::Object> object = info.Holder();
	if (object->HasRealNamedProperty(property))
	{
		v8::MaybeLocal<v8::Value> prop = object->GetRealNamedProperty(info.GetIsolate()->GetCurrentContext(), property);
		if (!prop.IsEmpty())
		{
			info.GetReturnValue().Set(prop.ToLocalChecked());
		}
	}
	else
	{
		Poco::Net::HTMLForm* pForm = Wrapper::unwrapNative<Poco::Net::HTMLForm>(info);
		std::string name = toString(property);
		if (pForm->has(name))
		{
			std::string value = pForm->get(name);
			returnString(info, value);
		}
	}
}


} } } // namespace Poco::JS::Net
