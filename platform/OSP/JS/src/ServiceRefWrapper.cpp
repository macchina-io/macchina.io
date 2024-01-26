//
// ServiceRefWrapper.cpp
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/JS/ServiceRefWrapper.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/JS/Bridge/BridgeWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/Format.h"


using Poco::JS::Core::Wrapper;
using namespace std::string_literals;


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
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("OSP.ServiceRef"s));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);

		v8::NamedPropertyHandlerConfiguration nph(getProperty);
		nph.flags = static_cast<v8::PropertyHandlerFlags>(static_cast<int>(v8::PropertyHandlerFlags::kOnlyInterceptStrings) | static_cast<int>(v8::PropertyHandlerFlags::kNonMasking));
		objectTemplate->SetHandler(nph);

		objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "instance"s), v8::FunctionTemplate::New(pIsolate, instance));
		objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "equals"s), v8::FunctionTemplate::New(pIsolate, equals));
		objectTemplate->Set(Wrapper::toV8Internalized(pIsolate, "toJSON"s), v8::FunctionTemplate::New(pIsolate, toJSON));
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> serviceRefTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(serviceRefTemplate);
}


void ServiceRefWrapper::getProperty(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::OSP::ServiceRef* pServiceRef = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::ServiceRef>(info);

	try
	{
		std::string nm(toString(info.GetIsolate(), name));
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
	v8::Isolate* pIsolate(args.GetIsolate());
	Poco::OSP::ServiceRef* pServiceRef = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::ServiceRef>(args);
	Poco::JS::Bridge::BridgeHolder::Ptr pHolder;
	try
	{
		if (pServiceRef->properties().has("jsbridge"))
		{
			pHolder = new Poco::JS::Bridge::BridgeHolder(pServiceRef->properties().get("jsbridge"s));
			Poco::JS::Bridge::BridgeWrapper wrapper;
			v8::Persistent<v8::Object>& bridgeObject(wrapper.wrapNativePersistent(pIsolate, pHolder));
			pHolder->setPersistent(bridgeObject);
			args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, bridgeObject));
			return;
		}
		returnException(args, Poco::format("service instance for %s not accessible from JavaScript"s, pServiceRef->name()));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ServiceRefWrapper::toJSON(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	Poco::OSP::ServiceRef* pServiceRef = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::ServiceRef>(args);
	const Poco::OSP::Properties& props = pServiceRef->properties();

	try
	{
		std::vector<std::string> keys;
		props.keys(keys);

		v8::Local<v8::Object> object = v8::Object::New(pIsolate);

		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string value = props.get(*it);
			V8_CHECK_SET_RESULT(object->Set(
				context,
				Wrapper::toV8String(pIsolate, *it),
				Wrapper::toV8String(pIsolate, value)
			));
		}

		args.GetReturnValue().Set(object);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ServiceRefWrapper::equals(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	bool result = false;
	if (args.Length() > 0 && args[0]->IsObject())
	{
		if (Wrapper::isWrapper<Poco::OSP::ServiceRef>(args.GetIsolate(), args[0]))
		{
			Poco::OSP::ServiceRef* pThisServiceRef = Poco::JS::Core::Wrapper::unwrapNative<Poco::OSP::ServiceRef>(args);
			Poco::OSP::ServiceRef* pOtherServiceRef = Poco::JS::Core::Wrapper::unwrapNativeObject<Poco::OSP::ServiceRef>(args[0]);
			result = pThisServiceRef == pOtherServiceRef;
		}
	}
	args.GetReturnValue().Set(result);
}


} } } // namespace Poco::OSP::JS
