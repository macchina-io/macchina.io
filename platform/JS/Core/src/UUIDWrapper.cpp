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
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/UUIDWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/JS/Core/BufferWrapper.h"
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
	funcTemplate->Set(toV8Internalized(pIsolate, "isUUID"s), v8::FunctionTemplate::New(pIsolate, isUUID));
	funcTemplate->Set(toV8Internalized(pIsolate, "create"s), v8::FunctionTemplate::New(pIsolate, create));
	funcTemplate->Set(toV8Internalized(pIsolate, "createRandom"s), v8::FunctionTemplate::New(pIsolate, createRandom));
	funcTemplate->Set(toV8Internalized(pIsolate, "createTimeBased"s), v8::FunctionTemplate::New(pIsolate, createTimeBased));
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
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "version"s), version);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "variant"s), variant);

		objectTemplate->Set(toV8Internalized(pIsolate, "toString"s), v8::FunctionTemplate::New(pIsolate, toString));
		objectTemplate->Set(toV8Internalized(pIsolate, "toBuffer"s), v8::FunctionTemplate::New(pIsolate, toBuffer));
		objectTemplate->Set(toV8Internalized(pIsolate, "toJSON"s), v8::FunctionTemplate::New(pIsolate, toString));
		objectTemplate->Set(toV8Internalized(pIsolate, "equals"s), v8::FunctionTemplate::New(pIsolate, equals));
		objectTemplate->Set(toV8Internalized(pIsolate, "isNull"s), v8::FunctionTemplate::New(pIsolate, isNull));
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> uuidTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(uuidTemplate);
}


void UUIDWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
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
				pUUID = new Poco::UUID(Wrapper::toString(pIsolate, args[0]));
			}
			else if (args[0]->IsObject() && Wrapper::isWrapper<Poco::JS::Core::BufferWrapper::Buffer>(pIsolate, args[0]))
			{
				Poco::JS::Core::BufferWrapper::Buffer* pBuffer = Wrapper::unwrapNativeObject<Poco::JS::Core::BufferWrapper::Buffer>(args[0]);
				if (pBuffer->size() >= 16)
				{
					pUUID = new Poco::UUID;
					pUUID->copyFrom(pBuffer->begin());
				}
				else throw Poco::InvalidAccessException("Buffer used to construct UUID must have a size of at least 16 bytes");
			}
			else throw Poco::InvalidArgumentException("Invalid arguments to construct UUID");
		}
		UUIDWrapper wrapper;
		v8::Persistent<v8::Object>& uuidObject(wrapper.wrapNativePersistent(pIsolate, pUUID));
		args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, uuidObject));
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
	v8::Isolate* pIsolate(args.GetIsolate());
	Poco::UUID* pUUID = nullptr;
	try
	{
		pUUID = new Poco::UUID(Poco::UUIDGenerator().createRandom());
		UUIDWrapper wrapper;
		v8::Persistent<v8::Object>& uuidObject(wrapper.wrapNativePersistent(pIsolate, pUUID));
		args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, uuidObject));
	}
	catch (Poco::Exception& exc)
	{
		delete pUUID;
		returnException(args, exc);
	}
}


void UUIDWrapper::createTimeBased(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	Poco::UUID* pUUID = nullptr;
	try
	{
		pUUID = new Poco::UUID(Poco::UUIDGenerator().create());
		UUIDWrapper wrapper;
		v8::Persistent<v8::Object>& uuidObject(wrapper.wrapNativePersistent(pIsolate, pUUID));
		args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, uuidObject));
	}
	catch (Poco::Exception& exc)
	{
		delete pUUID;
		returnException(args, exc);
	}
}


void UUIDWrapper::create(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	Poco::UUID* pUUID = nullptr;
	try
	{
		pUUID = new Poco::UUID(Poco::UUIDGenerator().createOne());
		UUIDWrapper wrapper;
		v8::Persistent<v8::Object>& uuidObject(wrapper.wrapNativePersistent(pIsolate, pUUID));
		args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, uuidObject));
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


void UUIDWrapper::toBuffer(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());
	Poco::UUID* pUUID = Wrapper::unwrapNative<Poco::UUID>(args);

	std::unique_ptr<Poco::JS::Core::BufferWrapper::Buffer> pBuffer = std::make_unique<Poco::JS::Core::BufferWrapper::Buffer>(16);
	pUUID->copyTo(pBuffer->begin());

	Poco::JS::Core::BufferWrapper wrapper;
	v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(args.GetIsolate(), pBuffer.release()));
	args.GetReturnValue().Set(v8::Local<v8::Object>::New(args.GetIsolate(), bufferObject));
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
