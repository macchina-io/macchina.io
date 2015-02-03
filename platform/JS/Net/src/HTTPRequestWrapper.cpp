//
// HTTPRequestWrapper.cpp
//
// $Id: //poco/1.4/JS/Net/src/HTTPRequestWrapper.cpp#7 $
//
// Library: JSNet
// Package: HTTP
// Module:  HTTPRequestWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Net/HTTPRequestWrapper.h"
#include "Poco/JS/Net/HTTPResponseWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPSessionFactory.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPBasicCredentials.h"
#include "Poco/URI.h"
#include "Poco/SharedPtr.h"
#include "Poco/StreamCopier.h"


namespace Poco {
namespace JS {
namespace Net {


RequestHolder::RequestHolder():
	_timeout(30, 0)
{
}


RequestHolder::~RequestHolder()
{
}


HTTPRequestWrapper::HTTPRequestWrapper()
{
}


HTTPRequestWrapper::~HTTPRequestWrapper()
{
}


v8::Handle<v8::FunctionTemplate> HTTPRequestWrapper::constructor(v8::Isolate* pIsolate)
{
	return v8::FunctionTemplate::New(pIsolate, construct);
}


v8::Handle<v8::ObjectTemplate> HTTPRequestWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Net.HTTPRequest"));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New();
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "method"), getMethod, setMethod);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "uri"), getURI, setURI);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "version"), getVersion, setVersion);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "contentType"), getContentType, setContentType);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "content"), getContent, setContent);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "timeout"), getTimeout, setTimeout);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "cookies"), getCookies);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "credentials"), getCredentials);

		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "hasHeader"), v8::FunctionTemplate::New(pIsolate, hasHeader));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getHeader"), v8::FunctionTemplate::New(pIsolate, getHeader));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "setHeader"), v8::FunctionTemplate::New(pIsolate, setHeader));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "authenticate"), v8::FunctionTemplate::New(pIsolate, authenticate));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "send"), v8::FunctionTemplate::New(pIsolate, send));
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> requestTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(requestTemplate);
}
	

void HTTPRequestWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	RequestHolder* pRequestHolder = new RequestHolderImpl();
	
	if (args.Length() > 0) 
		pRequestHolder->request().setMethod(toString(args[0]));
	if (args.Length() > 1) 
		pRequestHolder->request().setURI(toString(args[1]));
	if (args.Length() > 2) 
		pRequestHolder->request().setVersion(toString(args[2]));
	else
		pRequestHolder->request().setVersion(Poco::Net::HTTPMessage::HTTP_1_1);
	
	HTTPRequestWrapper wrapper;
	v8::Persistent<v8::Object>& requestObject(wrapper.wrapNativePersistent(args.GetIsolate(), pRequestHolder));
	args.GetReturnValue().Set(requestObject);
}


void HTTPRequestWrapper::getMethod(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	returnString(info, pRequestHolder->request().getMethod());
}


void HTTPRequestWrapper::setMethod(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	pRequestHolder->request().setMethod(toString(value));
}


void HTTPRequestWrapper::getURI(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	returnString(info, pRequestHolder->request().getURI());
}


void HTTPRequestWrapper::setURI(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	pRequestHolder->request().setURI(toString(value));
}


void HTTPRequestWrapper::getVersion(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	returnString(info, pRequestHolder->request().getVersion());
}


void HTTPRequestWrapper::setVersion(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	pRequestHolder->request().setVersion(toString(value));
}


void HTTPRequestWrapper::getContentType(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	returnString(info, pRequestHolder->request().getContentType());
}


void HTTPRequestWrapper::setContentType(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	pRequestHolder->request().setContentType(toString(value));
}


void HTTPRequestWrapper::getContent(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	returnString(info, pRequestHolder->content());
}


void HTTPRequestWrapper::setContent(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	pRequestHolder->content() = toString(value);
}


void HTTPRequestWrapper::getTimeout(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	info.GetReturnValue().Set(pRequestHolder->getTimeout().totalMilliseconds()/1000.0);
}


void HTTPRequestWrapper::setTimeout(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	if (value->IsNumber())
	{
		double timeout = value->NumberValue();
		pRequestHolder->setTimeout(timeout*1000000);
	}
}


void HTTPRequestWrapper::getCookies(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::HandleScope handleScope(info.GetIsolate());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	
	Poco::Net::NameValueCollection cookies;
	pRequestHolder->request().getCookies(cookies);
	v8::Local<v8::Object> result(v8::Object::New(info.GetIsolate()));
	for (Poco::Net::NameValueCollection::ConstIterator it = cookies.begin(); it != cookies.end(); ++it)
	{
		result->Set(v8::String::NewFromUtf8(info.GetIsolate(), it->first.c_str()), v8::String::NewFromUtf8(info.GetIsolate(),it->second.c_str()));
	}
	info.GetReturnValue().Set(result);
}


void HTTPRequestWrapper::getCredentials(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::HandleScope handleScope(info.GetIsolate());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	
	if (pRequestHolder->request().hasCredentials())
	{
		std::string scheme;
		std::string authInfo;
		pRequestHolder->request().getCredentials(scheme, authInfo);
		if (scheme == "Basic")
		{
			Poco::Net::HTTPBasicCredentials creds(authInfo);
			v8::Local<v8::Object> result(v8::Object::New(info.GetIsolate()));
			result->Set(v8::String::NewFromUtf8(info.GetIsolate(), "username"), v8::String::NewFromUtf8(info.GetIsolate(), creds.getUsername().c_str()));
			result->Set(v8::String::NewFromUtf8(info.GetIsolate(), "password"), v8::String::NewFromUtf8(info.GetIsolate(), creds.getPassword().c_str()));
			info.GetReturnValue().Set(result);
			return;
		}
	}
	info.GetReturnValue().Set(v8::Null(info.GetIsolate()));
}


void HTTPRequestWrapper::hasHeader(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(args);
	std::string name = toString(args[0]);
	bool result = pRequestHolder->request().has(name);
	args.GetReturnValue().Set(result);
}


void HTTPRequestWrapper::getHeader(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(args);
	std::string name = toString(args[0]);
	std::string deflt;
	if (args.Length() > 1) deflt = toString(args[1]);
	std::string value = pRequestHolder->request().get(name, deflt);
	returnString(args, value);
}


void HTTPRequestWrapper::setHeader(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(args);
	std::string name = toString(args[0]);
	std::string value = toString(args[1]);
	pRequestHolder->request().set(name, value);
}


void HTTPRequestWrapper::authenticate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() != 2) return;
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(args);
	std::string username = toString(args[0]);
	std::string password = toString(args[1]);
	Poco::Net::HTTPBasicCredentials creds(username, password);
	creds.authenticate(pRequestHolder->request());
}


void HTTPRequestWrapper::send(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(args);
	ResponseHolder* pResponseHolder = new ResponseHolderImpl;
	std::string uriString = pRequestHolder->request().getURI();
	try
	{
		Poco::URI uri(uriString);
		pRequestHolder->request().setURI(uri.getPathEtc());
		Poco::SharedPtr<Poco::Net::HTTPClientSession> pCS = Poco::Net::HTTPSessionFactory::defaultFactory().createClientSession(uri);
		if (pRequestHolder->request().getMethod() == Poco::Net::HTTPRequest::HTTP_PUT || pRequestHolder->request().getMethod() == Poco::Net::HTTPRequest::HTTP_POST)
		{
			pRequestHolder->request().setContentLength(pRequestHolder->content().length());
		}
		pCS->setTimeout(pRequestHolder->getTimeout());
		pCS->sendRequest(pRequestHolder->request()) << pRequestHolder->content();
		std::istream& istr = pCS->receiveResponse(pResponseHolder->response());
		Poco::StreamCopier::copyToString(istr, pResponseHolder->content());
		HTTPResponseWrapper wrapper;
		v8::Persistent<v8::Object>& responseObject(wrapper.wrapNativePersistent(args.GetIsolate(), pResponseHolder));
		args.GetReturnValue().Set(responseObject);
		pRequestHolder->request().setURI(uriString);
	}
	catch (Poco::Exception& exc)
	{
		delete pResponseHolder;
		pRequestHolder->request().setURI(uriString);
		returnException(args, exc);
	}
}


} } } // namespace Poco::JS::Net
