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
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Net/HTMLFormWrapper.h"
#include "Poco/JS/Net/HTTPResponseWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"


using namespace std::string_literals;


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
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Net.HTMLForm"s));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->Set(toV8Internalized(pIsolate, "has"s), v8::FunctionTemplate::New(pIsolate, hasField));
		objectTemplate->Set(toV8Internalized(pIsolate, "get"s), v8::FunctionTemplate::New(pIsolate, getField));
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "fields"s), getFields);

		// deprecated - for backwards compatibility, will be removed eventually
		objectTemplate->Set(toV8Internalized(pIsolate, "hasField"s), v8::FunctionTemplate::New(pIsolate, hasField));
		objectTemplate->Set(toV8Internalized(pIsolate, "getField"s), v8::FunctionTemplate::New(pIsolate, getField));

		v8::NamedPropertyHandlerConfiguration nph(getProperty);
		nph.flags = v8::PropertyHandlerFlags::kOnlyInterceptStrings;
		objectTemplate->SetHandler(nph);

		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> formTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(formTemplate);
}


void HTMLFormWrapper::hasField(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	Poco::Net::HTMLForm* pForm = Wrapper::unwrapNative<Poco::Net::HTMLForm>(args);
	std::string name = toString(pIsolate, args[0]);
	bool result = pForm->has(name);
	args.GetReturnValue().Set(result);
}


void HTMLFormWrapper::getField(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	Poco::Net::HTMLForm* pForm = Wrapper::unwrapNative<Poco::Net::HTMLForm>(args);
	std::string name = toString(pIsolate, args[0]);
	std::string deflt;
	if (args.Length() > 1) deflt = toString(pIsolate, args[1]);
	std::string value = pForm->get(name, deflt);
	returnString(args, value);
}


void HTMLFormWrapper::getFields(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Poco::Net::HTMLForm* pForm = Wrapper::unwrapNative<Poco::Net::HTMLForm>(info);

	v8::Local<v8::Object> result(v8::Object::New(pIsolate));
	if (!result.IsEmpty())
	{
		for (auto it = pForm->begin(); it != pForm->end(); ++it)
		{
			V8_CHECK_SET_RESULT(result->Set(context, toV8String(pIsolate, it->first), toV8String(pIsolate, it->second)));
		}
	}
	info.GetReturnValue().Set(result);
}


void HTMLFormWrapper::getProperty(v8::Local<v8::Name> property, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	v8::Local<v8::Object> object = info.Holder();
	if (object->HasRealNamedProperty(context, property).FromMaybe(false))
	{
		v8::MaybeLocal<v8::Value> maybeProp = object->GetRealNamedProperty(context, property);
		v8::Local<v8::Value> prop;
		if (maybeProp.ToLocal(&prop))
		{
			info.GetReturnValue().Set(prop);
		}
	}
	else
	{
		Poco::Net::HTMLForm* pForm = Wrapper::unwrapNative<Poco::Net::HTMLForm>(info);
		std::string name = toString(pIsolate, property);
		if (pForm->has(name))
		{
			std::string value = pForm->get(name);
			returnString(info, value);
		}
	}
}


} } } // namespace Poco::JS::Net
