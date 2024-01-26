//
// HTTPRequestWrapper.cpp
//
// Library: JS/Net
// Package: Wrappers
// Module:  HTTPRequestWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Net/HTTPRequestWrapper.h"
#include "Poco/JS/Net/HTTPResponseWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/JS/Core/JSExecutor.h"
#include "Poco/JS/Core/BufferWrapper.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPSessionFactory.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPBasicCredentials.h"
#include "Poco/Net/OAuth20Credentials.h"
#include "Poco/Net/HTMLForm.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/URI.h"
#include "Poco/SharedPtr.h"
#include "Poco/StreamCopier.h"
#include "Poco/MemoryStream.h"
#include "Poco/ThreadPool.h"
#include "Poco/Exception.h"
#include "Poco/String.h"
#include <sstream>
#include <atomic>


using namespace std::string_literals;


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
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::FunctionTemplate> funcTemplate = v8::FunctionTemplate::New(pIsolate, construct);
	funcTemplate->Set(toV8Internalized(pIsolate, "isHTTPRequest"s), v8::FunctionTemplate::New(pIsolate, isHTTPRequest));
	funcTemplate->Set(toV8Internalized(pIsolate, "get"s), v8::FunctionTemplate::New(pIsolate, get));
	funcTemplate->Set(toV8Internalized(pIsolate, "post"s), v8::FunctionTemplate::New(pIsolate, post));
	funcTemplate->Set(toV8Internalized(pIsolate, "put"s), v8::FunctionTemplate::New(pIsolate, put));
	funcTemplate->Set(toV8Internalized(pIsolate, "patch"s), v8::FunctionTemplate::New(pIsolate, patch));
	funcTemplate->Set(toV8Internalized(pIsolate, "delete"s), v8::FunctionTemplate::New(pIsolate, delete_));
	return handleScope.Escape(funcTemplate);
}


v8::Handle<v8::ObjectTemplate> HTTPRequestWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Net.HTTPRequest"s));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "method"s), getMethod, setMethod);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "uri"s), getURI, setURI);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "version"s), getVersion, setVersion);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "contentType"s), getContentType, setContentType);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "content"s), getContent, setContent);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "buffer"s), getBuffer, setBuffer);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "timeout"s), getTimeout, setTimeout);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "cookies"s), getCookies);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "headers"s), getHeaders);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "credentials"s), getCredentials, setCredentials);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "parameters"s), getParameters, setParameters);

		objectTemplate->Set(toV8Internalized(pIsolate, "has"s), v8::FunctionTemplate::New(pIsolate, hasHeader));
		objectTemplate->Set(toV8Internalized(pIsolate, "get"s), v8::FunctionTemplate::New(pIsolate, getHeader));
		objectTemplate->Set(toV8Internalized(pIsolate, "set"s), v8::FunctionTemplate::New(pIsolate, setHeader));
		objectTemplate->Set(toV8Internalized(pIsolate, "add"s), v8::FunctionTemplate::New(pIsolate, addHeader));
		objectTemplate->Set(toV8Internalized(pIsolate, "authenticate"s), v8::FunctionTemplate::New(pIsolate, authenticate));
		objectTemplate->Set(toV8Internalized(pIsolate, "send"s), v8::FunctionTemplate::New(pIsolate, send));
		objectTemplate->Set(toV8Internalized(pIsolate, "cancel"s), v8::FunctionTemplate::New(pIsolate, cancel));

		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> requestTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(requestTemplate);
}


void HTTPRequestWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	RequestHolder* pRequestHolder = new RequestHolderImpl;

	try
	{
		if (args.Length() > 0)
			pRequestHolder->request().setMethod(toString(pIsolate, args[0]));
		if (args.Length() > 1)
			pRequestHolder->request().setURI(toString(pIsolate, args[1]));
		if (args.Length() > 2)
			pRequestHolder->request().setVersion(toString(pIsolate, args[2]));
		else
			pRequestHolder->request().setVersion(Poco::Net::HTTPMessage::HTTP_1_1);

		HTTPRequestWrapper wrapper;
		v8::Persistent<v8::Object>& requestObject(wrapper.wrapNativePersistent(pIsolate, pRequestHolder));
		args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, requestObject));
	}
	catch (Poco::Exception& exc)
	{
		delete pRequestHolder;
		returnException(args, exc);
	}
}


void HTTPRequestWrapper::construct(const std::string& method, const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	RequestHolder* pRequestHolder = new RequestHolderImpl;

	try
	{
		pRequestHolder->request().setMethod(method);
		if (args.Length() > 0)
			pRequestHolder->request().setURI(toString(pIsolate, args[0]));
		if (args.Length() > 1)
			pRequestHolder->request().setVersion(toString(pIsolate, args[1]));
		else
			pRequestHolder->request().setVersion(Poco::Net::HTTPMessage::HTTP_1_1);

		HTTPRequestWrapper wrapper;
		v8::Persistent<v8::Object>& requestObject(wrapper.wrapNativePersistent(pIsolate, pRequestHolder));
		args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, requestObject));
	}
	catch (Poco::Exception& exc)
	{
		delete pRequestHolder;
		returnException(args, exc);
	}
}


void HTTPRequestWrapper::isHTTPRequest(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() > 0)
	{
		args.GetReturnValue().Set(Wrapper::isWrapper<RequestHolder>(args.GetIsolate(), args[0]));
	}
	else
	{
		args.GetReturnValue().Set(false);
	}
}


void HTTPRequestWrapper::get(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	construct(Poco::Net::HTTPRequest::HTTP_GET, args);
}


void HTTPRequestWrapper::post(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	construct(Poco::Net::HTTPRequest::HTTP_POST, args);
}


void HTTPRequestWrapper::put(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	construct(Poco::Net::HTTPRequest::HTTP_PUT, args);
}


void HTTPRequestWrapper::patch(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	construct(Poco::Net::HTTPRequest::HTTP_PATCH, args);
}


void HTTPRequestWrapper::delete_(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	construct(Poco::Net::HTTPRequest::HTTP_DELETE, args);
}


void HTTPRequestWrapper::getMethod(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	returnString(info, pRequestHolder->request().getMethod());
}


void HTTPRequestWrapper::setMethod(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	pRequestHolder->request().setMethod(toString(info.GetIsolate(), value));
}


void HTTPRequestWrapper::getURI(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	returnString(info, pRequestHolder->request().getURI());
}


void HTTPRequestWrapper::setURI(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	pRequestHolder->request().setURI(toString(info.GetIsolate(), value));
}


void HTTPRequestWrapper::getVersion(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	returnString(info, pRequestHolder->request().getVersion());
}


void HTTPRequestWrapper::setVersion(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	pRequestHolder->request().setVersion(toString(info.GetIsolate(), value));
}


void HTTPRequestWrapper::getContentType(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	returnString(info, pRequestHolder->request().getContentType());
}


void HTTPRequestWrapper::setContentType(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	pRequestHolder->request().setContentType(toString(info.GetIsolate(), value));
}


void HTTPRequestWrapper::getContent(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	returnString(info, pRequestHolder->content());
}


void HTTPRequestWrapper::setContent(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	pRequestHolder->content() = toString(info.GetIsolate(), value);
}


void HTTPRequestWrapper::getBuffer(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	Poco::JS::Core::BufferWrapper::Buffer* pBuffer = new Poco::JS::Core::BufferWrapper::Buffer(pRequestHolder->content().data(), pRequestHolder->content().size());
	Poco::JS::Core::BufferWrapper wrapper;
	v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(info.GetIsolate(), pBuffer));
	info.GetReturnValue().Set(v8::Local<v8::Object>::New(info.GetIsolate(), bufferObject));
}


void HTTPRequestWrapper::setBuffer(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	if (Poco::JS::Core::Wrapper::isWrapper<Poco::JS::Core::BufferWrapper::Buffer>(info.GetIsolate(), value))
	{
		Poco::JS::Core::BufferWrapper::Buffer* pBuffer = Poco::JS::Core::Wrapper::unwrapNativeObject<Poco::JS::Core::BufferWrapper::Buffer>(value);
		pRequestHolder->content().assign(pBuffer->begin(), pBuffer->size());
	}
	else returnException(info, Poco::InvalidArgumentException("argument must be a Buffer"));
}


void HTTPRequestWrapper::getTimeout(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	info.GetReturnValue().Set(pRequestHolder->getTimeout().totalMilliseconds()/1000.0);
}


void HTTPRequestWrapper::setTimeout(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	if (value->IsNumber())
	{
		double timeout = value->NumberValue(context).FromMaybe(0.0);
		pRequestHolder->setTimeout(static_cast<Poco::Timespan::TimeDiff>(timeout*1000000));
	}
}


void HTTPRequestWrapper::getCookies(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);

	Poco::Net::NameValueCollection cookies;
	pRequestHolder->request().getCookies(cookies);
	v8::Local<v8::Object> result(v8::Object::New(pIsolate));
	if (!result.IsEmpty())
	{
		for (auto it = cookies.begin(); it != cookies.end(); ++it)
		{
			V8_CHECK_SET_RESULT(result->Set(context, toV8String(pIsolate, it->first), toV8String(pIsolate, it->second)));
		}
	}
	info.GetReturnValue().Set(result);
}


void HTTPRequestWrapper::getHeaders(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);

	const Poco::Net::HTTPRequest& request = pRequestHolder->request();
	v8::Local<v8::Object> result(v8::Object::New(pIsolate));
	if (!result.IsEmpty())
	{
		for (auto it = request.begin(); it != request.end(); ++it)
		{
			V8_CHECK_SET_RESULT(result->Set(context, toV8String(pIsolate, it->first), toV8String(pIsolate, it->second)));
		}
	}
	info.GetReturnValue().Set(result);
}


void HTTPRequestWrapper::getCredentials(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);

	if (pRequestHolder->request().hasCredentials())
	{
		std::string scheme;
		std::string authInfo;
		pRequestHolder->request().getCredentials(scheme, authInfo);
		if (Poco::icompare(scheme, "Basic"s) == 0)
		{
			Poco::Net::HTTPBasicCredentials creds(authInfo);
			v8::Local<v8::Object> result(v8::Object::New(pIsolate));
			if (!result.IsEmpty())
			{
				V8_CHECK_SET_RESULT(result->Set(context, toV8String(pIsolate, "username"s), toV8String(pIsolate, creds.getUsername())));
				V8_CHECK_SET_RESULT(result->Set(context, toV8String(pIsolate, "password"), toV8String(pIsolate, creds.getPassword())));
			}
			info.GetReturnValue().Set(result);
			return;
		}
		else if (Poco::icompare(scheme, "Bearer"s) == 0)
		{
			v8::Local<v8::Object> result(v8::Object::New(pIsolate));
			if (!result.IsEmpty())
			{
				V8_CHECK_SET_RESULT(result->Set(context, toV8String(pIsolate, "bearer"s), toV8String(pIsolate, authInfo)));
			}
			info.GetReturnValue().Set(result);
			return;
		}
	}
	info.GetReturnValue().Set(v8::Null(pIsolate));
}


void HTTPRequestWrapper::setCredentials(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);

	if (value->IsObject())
	{
		v8::Local<v8::Object> credentials = value.As<v8::Object>();
		v8::Local<v8::String> usernameProp = toV8String(pIsolate, "username"s);
		v8::Local<v8::String> passwordProp = toV8String(pIsolate, "password"s);
		v8::Local<v8::String> bearerProp = toV8String(pIsolate, "bearer"s);

		if (credentials->Has(context, usernameProp).FromMaybe(false) && credentials->Has(context, passwordProp).FromMaybe(false))
		{
			const std::string username = toString(pIsolate, credentials->Get(context, usernameProp));
			const std::string password = toString(pIsolate, credentials->Get(context, passwordProp));
			Poco::Net::HTTPBasicCredentials basicCredentials(username, password);
			basicCredentials.authenticate(pRequestHolder->request());
		}
		else if (credentials->Has(context, bearerProp).FromMaybe(false))
		{
			const std::string bearer = toString(pIsolate, credentials->Get(context, bearerProp));
			Poco::Net::OAuth20Credentials oauthCreds(bearer);
			oauthCreds.authenticate(pRequestHolder->request());
		}
		else
		{
			returnException(info, "Invalid credentials object"s);
		}
	}
}


void HTTPRequestWrapper::getParameters(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);

	Poco::MemoryInputStream bodyStream(pRequestHolder->content().data(), pRequestHolder->content().size());
	Poco::Net::HTMLForm form(pRequestHolder->request(), bodyStream);
	v8::Local<v8::Object> result(v8::Object::New(pIsolate));
	for (const auto& p: form)
	{
		v8::Local<v8::String> name = toV8String(pIsolate, p.first.c_str());
		v8::Local<v8::String> value = toV8String(pIsolate, p.second.c_str());
		V8_CHECK_SET_RESULT(result->Set(context, name, value));
	}
	info.GetReturnValue().Set(result);
}


void HTTPRequestWrapper::setParameters(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);

	if (value->IsObject())
	{
		if (pRequestHolder->request().getMethod() == Poco::Net::HTTPRequest::HTTP_GET)
		{
			Poco::URI uri(pRequestHolder->request().getURI());
			uri.setRawQuery(""s);
			pRequestHolder->request().setURI(uri.toString());
		}
		Poco::Net::HTMLForm form;
		v8::Local<v8::Object> params = value.As<v8::Object>();
		v8::MaybeLocal<v8::Array> maybeNames = params->GetOwnPropertyNames(pIsolate->GetCurrentContext());
		if (!maybeNames.IsEmpty())
		{
			v8::Local<v8::Array> names = maybeNames.ToLocalChecked();
			std::size_t length = names->Length();
			for (std::size_t i = 0; i < length; i++)
			{
				v8::Local<v8::Value> v8Name = names->Get(context, i).ToLocalChecked();
				const std::string name = toString(pIsolate, v8Name);
				const std::string value = toString(pIsolate, params->Get(context, v8Name));
				form.set(name, value);
			}
			form.prepareSubmit(pRequestHolder->request());
			if (pRequestHolder->request().getMethod() != Poco::Net::HTTPRequest::HTTP_GET)
			{
				std::ostringstream contentStream;
				form.write(contentStream);
				pRequestHolder->content() = contentStream.str();
			}
		}
	}
}


void HTTPRequestWrapper::hasHeader(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(args);
	std::string name = toString(args.GetIsolate(), args[0]);
	bool result = pRequestHolder->request().has(name);
	args.GetReturnValue().Set(result);
}


void HTTPRequestWrapper::getHeader(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(args);
	std::string name = toString(pIsolate, args[0]);
	std::string deflt;
	if (args.Length() > 1) deflt = toString(pIsolate, args[1]);
	std::string value = pRequestHolder->request().get(name, deflt);
	returnString(args, value);
}


void HTTPRequestWrapper::setHeader(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(args);
	std::string name = toString(pIsolate, args[0]);
	std::string value = toString(pIsolate, args[1]);
	try
	{
		pRequestHolder->request().set(name, value);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void HTTPRequestWrapper::addHeader(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(args);
	std::string name = toString(pIsolate, args[0]);
	std::string value = toString(pIsolate, args[1]);
	try
	{
		pRequestHolder->request().add(name, value);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void HTTPRequestWrapper::authenticate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() != 2) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(args);
	std::string username = toString(pIsolate, args[0]);
	std::string password = toString(pIsolate, args[1]);
	try
	{
		Poco::Net::HTTPBasicCredentials creds(username, password);
		creds.authenticate(pRequestHolder->request());
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void HTTPRequestWrapper::send(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() > 0 && args[0]->IsFunction())
	{
		sendAsync(args);
	}
	else
	{
		sendBlocking(args);
	}
}


void HTTPRequestWrapper::cancel(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(args);
	try
	{
		pRequestHolder->cancelRequest();
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void HTTPRequestWrapper::sendBlocking(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(args);
	ResponseHolder* pResponseHolder = new ResponseHolderImpl;
	std::string uriString = pRequestHolder->request().getURI();
	try
	{
		Poco::URI uri(uriString);
		std::string uriPath = uri.getPathEtc();
		if (uriPath.empty()) uriPath = "/";
		Poco::Net::HTTPRequest request(pRequestHolder->request());
		request.setURI(uriPath);
		Poco::SharedPtr<Poco::Net::HTTPClientSession> pCS = Poco::Net::HTTPSessionFactory::defaultFactory().createClientSession(uri);
		if (request.getMethod() == Poco::Net::HTTPRequest::HTTP_PUT || request.getMethod() == Poco::Net::HTTPRequest::HTTP_POST || request.getMethod() == Poco::Net::HTTPRequest::HTTP_PATCH)
		{
			request.setContentLength(pRequestHolder->content().length());
		}
		pCS->setTimeout(pRequestHolder->getTimeout());
		pCS->sendRequest(request).write(pRequestHolder->content().data(), pRequestHolder->content().size());
		std::istream& istr = pCS->receiveResponse(pResponseHolder->response());
		std::streamsize contentLength = pResponseHolder->response().getContentLength();
		if (contentLength != Poco::Net::HTTPMessage::UNKNOWN_CONTENT_LENGTH)
		{
			pResponseHolder->content().reserve(static_cast<std::size_t>(contentLength));
		}
		Poco::StreamCopier::copyToString(istr, pResponseHolder->content());
		HTTPResponseWrapper wrapper;
		v8::Persistent<v8::Object>& responseObject(wrapper.wrapNativePersistent(pIsolate, pResponseHolder));
		args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, responseObject));
	}
	catch (Poco::Exception& exc)
	{
		delete pResponseHolder;
		returnException(args, exc);
	}
}


class AsyncCancelHandler: public CancelHandler
{
public:
	using Ptr = Poco::AutoPtr<AsyncCancelHandler>;

	AsyncCancelHandler(Poco::SharedPtr<Poco::Net::HTTPClientSession> pSession):
		_pSession(pSession)
	{
	}

	bool cancelled() const
	{
		return _cancelled;
	}

	void disarm()
	{
		Poco::FastMutex::ScopedLock lock(_mutex);
		_pSession.reset();
	}

	// CancelHandler
	void cancelRequest()
	{
		_cancelled = true;
		try
		{
			Poco::FastMutex::ScopedLock lock(_mutex);
		
			if (_pSession)
			{
				_pSession->abort();
				_pSession.reset();
			}
		}
		catch (...)
		{
		}
	}

private:
	Poco::SharedPtr<Poco::Net::HTTPClientSession> _pSession;
	Poco::FastMutex _mutex;
	std::atomic<bool> _cancelled{false};
};


class AsyncRequest: public Poco::Runnable
{
public:
	AsyncRequest(v8::Isolate* pIsolate, Poco::JS::Core::TimedJSExecutor::Ptr pExecutor, Poco::SharedPtr<Poco::Net::HTTPClientSession> pSession, Poco::SharedPtr<Poco::Net::HTTPRequest> pRequest, AsyncCancelHandler::Ptr pCancelHandler, const std::string& body, v8::Handle<v8::Function> function):
		_pIsolate(pIsolate),
		_pExecutor(pExecutor),
		_pSession(pSession),
		_pRequest(pRequest),
		_pCancelHandler(pCancelHandler),
		_body(body),
		_function(pIsolate, function)
	{
	}

	~AsyncRequest()
	{
	}

	v8::Persistent<v8::Function>& function()
	{
		return _function;
	}

	std::string& body()
	{
		return _body;
	}

	AsyncCancelHandler::Ptr cancelHandler() const
	{
		return _pCancelHandler;
	}

	void run();

private:
	v8::Isolate* _pIsolate;
	Poco::JS::Core::TimedJSExecutor::Ptr _pExecutor;
	Poco::SharedPtr<Poco::Net::HTTPClientSession> _pSession;
	Poco::SharedPtr<Poco::Net::HTTPRequest> _pRequest;
	AsyncCancelHandler::Ptr _pCancelHandler;
	std::string _body;
	v8::Persistent<v8::Function> _function;
};


class AsyncRequestCompletionTask: public Poco::Util::TimerTask
{
public:
	AsyncRequestCompletionTask(v8::Isolate* pIsolate, Poco::JS::Core::JSExecutor::Ptr pExecutor, Poco::SharedPtr<Poco::Net::HTTPResponse> pResponse, AsyncRequest* pAsyncRequest):
		_pIsolate(pIsolate),
		_pExecutor(pExecutor),
		_pResponse(pResponse),
		_pAsyncRequest(pAsyncRequest)
	{
	}

	~AsyncRequestCompletionTask()
	{
		delete _pAsyncRequest;
	}

	void run()
	{
		poco_assert (_pIsolate == _pExecutor->isolate());

		v8::Locker locker(_pIsolate);
		v8::Isolate::Scope isoScope(_pIsolate);
		v8::HandleScope handleScope(_pIsolate);

		v8::Local<v8::Context> context(v8::Local<v8::Context>::New(_pIsolate, _pExecutor->scriptContext()));
		v8::Context::Scope contextScope(context);

		ResponseHolder* pResponseHolder = new ResponsePtrHolderImpl<Poco::Net::HTTPResponse>(_pResponse);
		std::swap(pResponseHolder->content(), _pAsyncRequest->body());
		HTTPResponseWrapper wrapper;
		v8::Persistent<v8::Object>& responseObject(wrapper.wrapNativePersistent(_pIsolate, pResponseHolder));

		v8::Local<v8::Object> statusObject = v8::Object::New(_pIsolate);
		V8_CHECK_SET_RESULT(statusObject->Set(context, Core::Wrapper::toV8String(_pIsolate, "response"s), v8::Local<v8::Object>::New(_pIsolate, responseObject)));
		V8_CHECK_SET_RESULT(statusObject->Set(context, Core::Wrapper::toV8String(_pIsolate, "error"s), v8::Null(_pIsolate)));

		v8::Local<v8::Function> localFunction(v8::Local<v8::Function>::New(_pIsolate, _pAsyncRequest->function()));
		v8::Local<v8::Value> receiver(v8::Null(_pIsolate));
		_pAsyncRequest->function().Reset();

		if (!_pAsyncRequest->cancelHandler()->cancelled())
		{
			v8::Handle<v8::Value> args[1];
			args[0] = v8::Local<v8::Object>::New(_pIsolate, statusObject);

			_pExecutor->callInContext(_pIsolate, context, localFunction, receiver, 1, args);
		}
	}

private:
	v8::Isolate* _pIsolate;
	Poco::JS::Core::JSExecutor::Ptr _pExecutor;
	Poco::SharedPtr<Poco::Net::HTTPResponse> _pResponse;
	AsyncRequest* _pAsyncRequest;
};


class AsyncRequestFailedTask: public Poco::Util::TimerTask
{
public:
	AsyncRequestFailedTask(v8::Isolate* pIsolate, Poco::JS::Core::JSExecutor::Ptr pExecutor, Poco::SharedPtr<Poco::Exception> pException, AsyncRequest* pAsyncRequest):
		_pIsolate(pIsolate),
		_pExecutor(pExecutor, true),
		_pException(pException),
		_pAsyncRequest(pAsyncRequest)
	{
	}

	~AsyncRequestFailedTask()
	{
		delete _pAsyncRequest;
	}

	void run()
	{
		poco_assert (_pIsolate == _pExecutor->isolate());

		v8::Locker locker(_pIsolate);
		v8::Isolate::Scope isoScope(_pIsolate);
		v8::HandleScope handleScope(_pIsolate);

		v8::Local<v8::Context> context(v8::Local<v8::Context>::New(_pIsolate, _pExecutor->scriptContext()));
		v8::Context::Scope contextScope(context);

		v8::Local<v8::Object> statusObject = v8::Object::New(_pIsolate);
		V8_CHECK_SET_RESULT(statusObject->Set(context, Core::Wrapper::toV8String(_pIsolate, "response"s), v8::Null(_pIsolate)));
		V8_CHECK_SET_RESULT(statusObject->Set(context, Core::Wrapper::toV8String(_pIsolate, "error"s), Core::Wrapper::toV8String(_pIsolate, _pException->displayText())));

		v8::Local<v8::Function> localFunction(v8::Local<v8::Function>::New(_pIsolate, _pAsyncRequest->function()));
		v8::Local<v8::Value> receiver(v8::Null(_pIsolate));
		_pAsyncRequest->function().Reset();

		if (!_pAsyncRequest->cancelHandler()->cancelled())
		{
			v8::Handle<v8::Value> args[1];
			args[0] = v8::Local<v8::Object>::New(_pIsolate, statusObject);

			_pExecutor->callInContext(_pIsolate, context, localFunction, receiver, 1, args);
		}
	}

private:
	v8::Isolate* _pIsolate;
	Poco::JS::Core::JSExecutor::Ptr _pExecutor;
	Poco::SharedPtr<Poco::Exception> _pException;
	AsyncRequest* _pAsyncRequest;
};


void AsyncRequest::run()
{
	try
	{
		if (!_pCancelHandler->cancelled())
		{
			_pSession->sendRequest(*_pRequest).write(_body.data(), _body.size());
		}

		Poco::SharedPtr<Poco::Net::HTTPResponse> pResponse = new Poco::Net::HTTPResponse;
		if (!_pCancelHandler->cancelled())
		{
			std::istream& istr = _pSession->receiveResponse(*pResponse);
			std::streamsize contentLength = pResponse->getContentLength();
			_body.clear();
			if (contentLength != Poco::Net::HTTPMessage::UNKNOWN_CONTENT_LENGTH)
			{
				_body.reserve(static_cast<std::size_t>(contentLength));
			}
			if (!_pCancelHandler->cancelled())
			{
				Poco::StreamCopier::copyToString(istr, _body);
			}
		}
		if (!_pCancelHandler->cancelled())
		{
			_pExecutor->schedule(new AsyncRequestCompletionTask(_pIsolate, _pExecutor, pResponse, this));
		}
	}
	catch (Poco::Exception& exc)
	{
		if (!_pCancelHandler->cancelled())
		{
			_pExecutor->schedule(new AsyncRequestFailedTask(_pIsolate, _pExecutor, exc.clone(), this));
		}
	}
	catch (...)
	{
		poco_bugcheck();
	}
	_pCancelHandler->disarm();
}


void HTTPRequestWrapper::sendAsync(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Function> function = args[0].As<v8::Function>();
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(args);
	std::string uriString = pRequestHolder->request().getURI();
	try
	{
		Poco::JS::Core::JSExecutor::Ptr pExecutor = Poco::JS::Core::JSExecutor::current();
		Poco::JS::Core::TimedJSExecutor::Ptr pTimedJSExecutor = pExecutor.cast<Poco::JS::Core::TimedJSExecutor>();
		if (pTimedJSExecutor)
		{
			Poco::URI uri(uriString);
			std::string uriPath = uri.getPathEtc();
			if (uriPath.empty()) uriPath = "/";
			Poco::SharedPtr<Poco::Net::HTTPRequest> pRequest = new Poco::Net::HTTPRequest(pRequestHolder->request());
			pRequest->setURI(uriPath);
			Poco::SharedPtr<Poco::Net::HTTPClientSession> pCS = Poco::Net::HTTPSessionFactory::defaultFactory().createClientSession(uri);
			if (pRequest->getMethod() == Poco::Net::HTTPRequest::HTTP_PUT || pRequest->getMethod() == Poco::Net::HTTPRequest::HTTP_POST)
			{
				pRequest->setContentLength(pRequestHolder->content().length());
			}
			pCS->setTimeout(pRequestHolder->getTimeout());

			AsyncCancelHandler::Ptr pCancelHandler = new AsyncCancelHandler(pCS);
			pRequestHolder->setCancelHandler(pCancelHandler);
			AsyncRequest* pAsyncRequest = new AsyncRequest(pIsolate, pTimedJSExecutor, pCS, pRequest, pCancelHandler, pRequestHolder->content(), function);
			try
			{
				Poco::ThreadPool::defaultPool().start(*pAsyncRequest);
			}
			catch (...)
			{
				delete pAsyncRequest;
				throw Poco::RuntimeException("No thread available for async HTTPRequest");
			}
		}
		else throw Poco::RuntimeException("Async HTTP request not supported in this context");
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


} } } // namespace Poco::JS::Net
