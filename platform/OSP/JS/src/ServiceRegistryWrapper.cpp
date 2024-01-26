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


using Poco::JS::Core::Wrapper;
using namespace std::string_literals;


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
	serviceRegistryTemplate->Set(Wrapper::toV8Internalized(pIsolate, "find"s), v8::FunctionTemplate::New(pIsolate, find));
	serviceRegistryTemplate->Set(Wrapper::toV8Internalized(pIsolate, "findByName"s), v8::FunctionTemplate::New(pIsolate, findByName));
	serviceRegistryTemplate->Set(Wrapper::toV8Internalized(pIsolate, "createListener"s), v8::FunctionTemplate::New(pIsolate, createListener));
	return handleScope.Escape(serviceRegistryTemplate);
}


void ServiceRegistryWrapper::findByName(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	Poco::OSP::ServiceRegistry* pServiceRegistry = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::ServiceRegistry>(args);

	try
	{
		if (args.Length() == 1)
		{
			std::string serviceName = toString(pIsolate, args[0]);
			Poco::OSP::ServiceRef::Ptr pServiceRef = pServiceRegistry->findByName(serviceName);
			if (pServiceRef)
			{
				ServiceRefWrapper wrapper;
				v8::Persistent<v8::Object>& serviceRefObject(wrapper.wrapNativePersistent(args.GetIsolate(), pServiceRef));
				args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, serviceRefObject));
				return;
			}
			args.GetReturnValue().Set(v8::Null(args.GetIsolate()));
		}
		else
		{
			returnException(args, "bad arguments - service name required"s);
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ServiceRegistryWrapper::find(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	Poco::OSP::ServiceRegistry* pServiceRegistry = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::ServiceRegistry>(args);
	try
	{
		if (args.Length() == 1)
		{
			ServiceRefWrapper wrapper;
			std::string serviceQuery = toString(pIsolate, args[0]);
			std::vector<Poco::OSP::ServiceRef::Ptr> services;
			v8::Local<v8::Array> result = v8::Array::New(args.GetIsolate());
			if (!result.IsEmpty())
			{
				int i = 0;
				if (pServiceRegistry->find(serviceQuery, services))
				{
					for (std::vector<Poco::OSP::ServiceRef::Ptr>::iterator it = services.begin(); it != services.end(); ++it)
					{
						v8::Persistent<v8::Object>& serviceRefObject(wrapper.wrapNativePersistent(pIsolate, *it));
						v8::Local<v8::Object> localServiceRefObject = v8::Local<v8::Object>::New(pIsolate, serviceRefObject);
						V8_CHECK_SET_RESULT(result->Set(context, i++, localServiceRefObject));
					}
				}
			}
			args.GetReturnValue().Set(result);
		}
		else
		{
			returnException(args, "bad arguments - service query required"s);
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ServiceRegistryWrapper::createListener(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope handleScope(pIsolate);

	Poco::OSP::ServiceRegistry* pServiceRegistry = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::ServiceRegistry>(args);
	try
	{
		if (args.Length() == 3 && args[1]->IsFunction() && args[2]->IsFunction())
		{
			std::string query = toString(pIsolate, args[0]);

			ServiceListenerWrapper wrapper;
			ServiceListenerHolder::Ptr pHolder = new ServiceListenerHolder(
				args.GetIsolate(),
				Poco::JS::Core::JSExecutor::current(),
				*pServiceRegistry,
				query,
				args[1].As<v8::Function>(),
				args[2].As<v8::Function>());

			v8::Persistent<v8::Object>& serviceListenerObject(wrapper.wrapNativePersistent(pIsolate, pHolder));
			args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, serviceListenerObject));
		}
		else
		{
			returnException(args, "bad arguments - service query, registered callback and unregistered callback required"s);
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


} } } // namespace Poco::OSP::JS
