//
// ServiceRegistryWrapper.cpp
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/JS/ServiceRegistryWrapper.h"
#include "Poco/OSP/JS/ServiceRefWrapper.h"
#include "Poco/OSP/JS/ServiceListenerWrapper.h"


namespace Poco {
namespace OSP {
namespace JS {


ServiceRegistryWrapper::ServiceRegistryWrapper()
{
}


ServiceRegistryWrapper::~ServiceRegistryWrapper()
{
}


v8::Handle<v8::ObjectTemplate> ServiceRegistryWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::ObjectTemplate> serviceRegistryTemplate = v8::ObjectTemplate::New(pIsolate);
	serviceRegistryTemplate->SetInternalFieldCount(1);
	serviceRegistryTemplate->Set(v8::String::NewFromUtf8(pIsolate, "find"), v8::FunctionTemplate::New(pIsolate, find));
	serviceRegistryTemplate->Set(v8::String::NewFromUtf8(pIsolate, "findByName"), v8::FunctionTemplate::New(pIsolate, findByName));
	serviceRegistryTemplate->Set(v8::String::NewFromUtf8(pIsolate, "createListener"), v8::FunctionTemplate::New(pIsolate, createListener));
	return handleScope.Escape(serviceRegistryTemplate);
}


void ServiceRegistryWrapper::findByName(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope handleScope(args.GetIsolate());
	Poco::OSP::ServiceRegistry* pServiceRegistry = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::ServiceRegistry>(args);

	try
	{
		if (args.Length() == 1)
		{
			std::string serviceName = toString(args[0]);
			Poco::OSP::ServiceRef::Ptr pServiceRef = pServiceRegistry->findByName(serviceName);
			if (pServiceRef)
			{
				ServiceRefWrapper wrapper;
				v8::Persistent<v8::Object>& serviceRefObject(wrapper.wrapNativePersistent(args.GetIsolate(), pServiceRef));
				args.GetReturnValue().Set(serviceRefObject);
				return;
			}
			args.GetReturnValue().Set(v8::Null(args.GetIsolate()));
		}
		else
		{
			returnException(args, std::string("bad arguments - service name required"));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ServiceRegistryWrapper::find(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope handleScope(args.GetIsolate());
	Poco::OSP::ServiceRegistry* pServiceRegistry = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::ServiceRegistry>(args);

	try
	{
		if (args.Length() == 1)
		{
			ServiceRefWrapper wrapper;
			std::string serviceQuery = toString(args[0]);
			std::vector<Poco::OSP::ServiceRef::Ptr> services;
			v8::Local<v8::Array> result = v8::Array::New(args.GetIsolate());
			if (!result.IsEmpty())
			{
				int i = 0;
				if (pServiceRegistry->find(serviceQuery, services))
				{
					for (std::vector<Poco::OSP::ServiceRef::Ptr>::iterator it = services.begin(); it != services.end(); ++it)
					{
						v8::Persistent<v8::Object>& serviceRefObject(wrapper.wrapNativePersistent(args.GetIsolate(), *it));
						v8::Local<v8::Object> localServiceRefObject = v8::Local<v8::Object>::New(args.GetIsolate(), serviceRefObject);
						result->Set(i++, localServiceRefObject);
					}
				}
			}
			args.GetReturnValue().Set(result);
		}
		else
		{
			returnException(args, std::string("bad arguments - service query required"));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ServiceRegistryWrapper::createListener(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope handleScope(args.GetIsolate());
	Poco::OSP::ServiceRegistry* pServiceRegistry = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::ServiceRegistry>(args);

	try
	{
		if (args.Length() == 3 && args[1]->IsFunction() && args[2]->IsFunction())
		{
			std::string query = toString(args[0]);

			ServiceListenerWrapper wrapper;
			ServiceListenerHolder::Ptr pHolder = new ServiceListenerHolder(
				args.GetIsolate(),
				Poco::JS::Core::JSExecutor::current(),
				*pServiceRegistry,
				query,
				args[1].As<v8::Function>(),
				args[2].As<v8::Function>());

			v8::Persistent<v8::Object>& serviceListenerObject(wrapper.wrapNativePersistent(args.GetIsolate(), pHolder));
			v8::Local<v8::Object> localListenerObject = v8::Local<v8::Object>::New(args.GetIsolate(), serviceListenerObject);
			args.GetReturnValue().Set(localListenerObject);
		}
		else
		{
			returnException(args, std::string("bad arguments - service query, registered callback and unregistered callback required"));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


} } } // namespace Poco::OSP::JS
