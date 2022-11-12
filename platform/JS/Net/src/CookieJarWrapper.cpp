//
// CookieJarWrapper.cpp
//
// Library: JS/Net
// Package: Wrappers
// Module:  CookieJar
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Net/CookieJarWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/JS/Net/CookieJar.h"
#include "Poco/JS/Net/HTTPRequestWrapper.h"
#include "Poco/JS/Net/HTTPResponseWrapper.h"


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Net {


CookieJarWrapper::CookieJarWrapper()
{
}


CookieJarWrapper::~CookieJarWrapper()
{
}


v8::Handle<v8::FunctionTemplate> CookieJarWrapper::constructor(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::FunctionTemplate> funcTemplate = v8::FunctionTemplate::New(pIsolate, construct);
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "isCookieJar"), v8::FunctionTemplate::New(pIsolate, isCookieJar));
	return handleScope.Escape(funcTemplate);
}


v8::Handle<v8::ObjectTemplate> CookieJarWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Core::PooledIsolate* pPooledIso = Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Core.UUID"s));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "addCookies"), v8::FunctionTemplate::New(pIsolate, addCookies));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "updateCookies"), v8::FunctionTemplate::New(pIsolate, updateCookies));
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> uuidTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(uuidTemplate);
}


void CookieJarWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::EscapableHandleScope handleScope(args.GetIsolate());

	CookieJar* pCookieJar = new CookieJar;
	try
	{
		CookieJarWrapper wrapper;
		v8::Persistent<v8::Object>& cookieJarObject(wrapper.wrapNativePersistent(args.GetIsolate(), pCookieJar));
		args.GetReturnValue().Set(cookieJarObject);
	}
	catch (Poco::Exception& exc)
	{
		delete pCookieJar;
		returnException(args, exc);
	}
}


void CookieJarWrapper::isCookieJar(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() > 0)
	{
		args.GetReturnValue().Set(Wrapper::isWrapper<CookieJar>(args.GetIsolate(), args[0]));
	}
	else
	{
		args.GetReturnValue().Set(false);
	}
}


void CookieJarWrapper::addCookies(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() > 0)
	{
		if (args[0]->IsObject())
		{
			if (Wrapper::isWrapper<RequestHolder>(args.GetIsolate(), args[0]))
			{
				CookieJar* pCookieJar = Wrapper::unwrapNative<CookieJar>(args);
				RequestHolder* pRequestWrapper = Wrapper::unwrapNativeObject<RequestHolder>(args[0]);
				pCookieJar->addCookies(pRequestWrapper->request());
			}
		}
	}
}


void CookieJarWrapper::updateCookies(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() > 0)
	{
		if (args[0]->IsObject())
		{
			if (Wrapper::isWrapper<ResponseHolder>(args.GetIsolate(), args[0]))
			{
				CookieJar* pCookieJar = Wrapper::unwrapNative<CookieJar>(args);
				ResponseHolder* pResponseHolder = Wrapper::unwrapNativeObject<ResponseHolder>(args[0]);
				pCookieJar->updateCookies(pResponseHolder->response());
			}
		}
	}
}


} } } // namespace Poco::JS::Net
