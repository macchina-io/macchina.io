//
// UUIDWrapper.cpp
//
// Library: JS/Core
// Package: Wrappers
// Module:  UUIDWrapper
//
// Copyright (c) 2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/UUIDWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/UUID.h"


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Core {


UUIDWrapper::UUIDWrapper()
{
}


UUIDWrapper::~UUIDWrapper()
{
}


v8::Handle<v8::FunctionTemplate> UUIDWrapper::constructor(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::FunctionTemplate> funcTemplate = v8::FunctionTemplate::New(pIsolate, construct);
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "isUUID"), v8::FunctionTemplate::New(pIsolate, isUUID));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "create"), v8::FunctionTemplate::New(pIsolate, create));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "createRandom"), v8::FunctionTemplate::New(pIsolate, createRandom));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "createTimeBased"), v8::FunctionTemplate::New(pIsolate, createTimeBased));
	return handleScope.Escape(funcTemplate);
}


v8::Handle<v8::ObjectTemplate> UUIDWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	PooledIsolate* pPooledIso = PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Core.UUID"s));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "version"), version);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "variant"), variant);

		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "toString"), v8::FunctionTemplate::New(pIsolate, toString));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "toJSON"), v8::FunctionTemplate::New(pIsolate, toString));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "equals"), v8::FunctionTemplate::New(pIsolate, equals));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "isNull"), v8::FunctionTemplate::New(pIsolate, isNull));
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> dateTimeTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(dateTimeTemplate);
}


void UUIDWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Poco::UUID* pUUID = 0;
	try
	{
		if (args.Length() == 0)
		{
			pUUID = new Poco::UUID;
		}
		else
		{
			if (args[0]->IsString())
			{
				pUUID = new Poco::UUID(Wrapper::toString(args[0]));
			}
			else throw Poco::InvalidArgumentException("Invalid arguments to construct UUID");
		}
		UUIDWrapper wrapper;
		v8::Persistent<v8::Object>& uuidObject(wrapper.wrapNativePersistent(args.GetIsolate(), pUUID));
		args.GetReturnValue().Set(uuidObject);
	}
	catch (Poco::Exception& exc)
	{
		delete pUUID;
		returnException(args, exc);
	}
}


void UUIDWrapper::isUUID(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() > 0)
	{
		args.GetReturnValue().Set(Wrapper::isWrapper<Poco::UUID>(args.GetIsolate(), args[0]));
	}
	else
	{
		args.GetReturnValue().Set(false);
	}
}


void UUIDWrapper::createRandom(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Poco::UUID* pUUID = nullptr;
	try
	{
		pUUID = new Poco::UUID(Poco::UUIDGenerator().createRandom());
		UUIDWrapper wrapper;
		v8::Persistent<v8::Object>& uuidObject(wrapper.wrapNativePersistent(args.GetIsolate(), pUUID));
		args.GetReturnValue().Set(uuidObject);
	}
	catch (Poco::Exception& exc)
	{
		delete pUUID;
		returnException(args, exc);
	}
}


void UUIDWrapper::createTimeBased(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Poco::UUID* pUUID = nullptr;
	try
	{
		pUUID = new Poco::UUID(Poco::UUIDGenerator().create());
		UUIDWrapper wrapper;
		v8::Persistent<v8::Object>& uuidObject(wrapper.wrapNativePersistent(args.GetIsolate(), pUUID));
		args.GetReturnValue().Set(uuidObject);
	}
	catch (Poco::Exception& exc)
	{
		delete pUUID;
		returnException(args, exc);
	}
}


void UUIDWrapper::create(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Poco::UUID* pUUID = nullptr;
	try
	{
		pUUID = new Poco::UUID(Poco::UUIDGenerator().createOne());
		UUIDWrapper wrapper;
		v8::Persistent<v8::Object>& uuidObject(wrapper.wrapNativePersistent(args.GetIsolate(), pUUID));
		args.GetReturnValue().Set(uuidObject);
	}
	catch (Poco::Exception& exc)
	{
		delete pUUID;
		returnException(args, exc);
	}
}


void UUIDWrapper::version(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::UUID* pUUID = Wrapper::unwrapNative<Poco::UUID>(info);
	info.GetReturnValue().Set(static_cast<int>(pUUID->version()));
}


void UUIDWrapper::variant(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::UUID* pUUID = Wrapper::unwrapNative<Poco::UUID>(info);
	info.GetReturnValue().Set(pUUID->variant());
}


void UUIDWrapper::toString(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());
	Poco::UUID* pUUID = Wrapper::unwrapNative<Poco::UUID>(args);

	try
	{
		returnString(args, pUUID->toString());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void UUIDWrapper::equals(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() > 0)
	{
		if (args[0]->IsObject())
		{
			if (Wrapper::isWrapper<Poco::UUID>(args.GetIsolate(), args[0]))
			{
				Poco::UUID* pThisUUID = Wrapper::unwrapNative<Poco::UUID>(args);
				Poco::UUID* pOtherUUID = Wrapper::unwrapNativeObject<Poco::UUID>(args[0]);
				args.GetReturnValue().Set(*pThisUUID == *pOtherUUID);
				return;
			}
		}
	}
}


void UUIDWrapper::isNull(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());
	Poco::UUID* pUUID = Wrapper::unwrapNative<Poco::UUID>(args);

	try
	{
		args.GetReturnValue().Set(pUUID->isNull());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


} } } // namespace Poco::JS::Core
