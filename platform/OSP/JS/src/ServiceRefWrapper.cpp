//
// ServiceRefWrapper.cpp
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/JS/ServiceRefWrapper.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/JS/Bridge/BridgeWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/Format.h"


namespace Poco {
namespace OSP {
namespace JS {


ServiceRefWrapper::ServiceRefWrapper()
{
}


ServiceRefWrapper::~ServiceRefWrapper()
{
}


v8::Handle<v8::ObjectTemplate> ServiceRefWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("OSP.ServiceRef"));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetNamedPropertyHandler(getProperty);
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "instance"), v8::FunctionTemplate::New(pIsolate, instance));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "toJSON"), v8::FunctionTemplate::New(pIsolate, toJSON));
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> serviceRefTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(serviceRefTemplate);
}


void ServiceRefWrapper::getProperty(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::ServiceRef* pServiceRef = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::ServiceRef>(info);

	try
	{
		std::string nm(toString(name));
		if (pServiceRef->properties().has(nm))
		{
			returnString(info, pServiceRef->properties().get(nm));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
}


void ServiceRefWrapper::instance(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Poco::OSP::ServiceRef* pServiceRef = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::ServiceRef>(args);
	Poco::JS::Bridge::BridgeHolder::Ptr pHolder;
	try
	{
		if (pServiceRef->properties().has("jsbridge"))
		{
			pHolder = new Poco::JS::Bridge::BridgeHolder(pServiceRef->properties().get("jsbridge"));
			Poco::JS::Bridge::BridgeWrapper wrapper;
			v8::Persistent<v8::Object>& bridgeObject(wrapper.wrapNativePersistent(args.GetIsolate(), pHolder));
			pHolder->setPersistent(bridgeObject);
			args.GetReturnValue().Set(bridgeObject);
			return;
		}
		returnException(args, Poco::format("service instance for %s not accessible from JavaScript", pServiceRef->name()));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ServiceRefWrapper::toJSON(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());
	Poco::OSP::ServiceRef* pServiceRef = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::ServiceRef>(args);
	const Poco::OSP::Properties& props = pServiceRef->properties();

	try
	{
		std::vector<std::string> keys;
		props.keys(keys);

		v8::Local<v8::Object> object = v8::Object::New(args.GetIsolate());

		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string value = props.get(*it);
			object->Set(
				v8::String::NewFromUtf8(args.GetIsolate(), it->c_str(), v8::String::kNormalString, static_cast<int>(it->size())),
				v8::String::NewFromUtf8(args.GetIsolate(), value.c_str(), v8::String::kNormalString, static_cast<int>(value.size()))
			);
		}

		args.GetReturnValue().Set(object);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


} } } // namespace Poco::OSP::JS
