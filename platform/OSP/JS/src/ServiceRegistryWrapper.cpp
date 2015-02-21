//
// ServiceRegistryWrapper.cpp
//
// $Id: //poco/1.4/OSP/JS/src/ServiceRegistryWrapper.cpp#4 $
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "ServiceRegistryWrapper.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "ServiceRefWrapper.h"


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
	return handleScope.Escape(serviceRegistryTemplate);
}


void ServiceRegistryWrapper::findByName(const v8::FunctionCallbackInfo<v8::Value>& args)
{
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
				v8::Persistent<v8::Object> serviceRefObject(args.GetIsolate(), wrapper.wrapNativePersistent(args.GetIsolate(), pServiceRef));
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
	Poco::OSP::ServiceRegistry* pServiceRegistry = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::ServiceRegistry>(args);

	try
	{
		if (args.Length() == 1)
		{
			ServiceRefWrapper wrapper;
			std::string serviceQuery = toString(args[0]);
			std::vector<Poco::OSP::ServiceRef::Ptr> services;
			v8::Local<v8::Array> result = v8::Array::New(args.GetIsolate());
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


} } } // namespace Poco::OSP::JS
