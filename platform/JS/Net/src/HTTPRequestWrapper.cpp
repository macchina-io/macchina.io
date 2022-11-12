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


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Net {


static Poco::AtomicCounter _cnt;


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
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "isHTTPRequest"), v8::FunctionTemplate::New(pIsolate, isHTTPRequest));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "get"), v8::FunctionTemplate::New(pIsolate, get));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "post"), v8::FunctionTemplate::New(pIsolate, post));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "put"), v8::FunctionTemplate::New(pIsolate, put));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "patch"), v8::FunctionTemplate::New(pIsolate, patch));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "delete"), v8::FunctionTemplate::New(pIsolate, delete_));
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
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "method"), getMethod, setMethod);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "uri"), getURI, setURI);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "version"), getVersion, setVersion);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "contentType"), getContentType, setContentType);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "content"), getContent, setContent);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "buffer"), getBuffer, setBuffer);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "timeout"), getTimeout, setTimeout);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "cookies"), getCookies);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "headers"), getHeaders);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "credentials"), getCredentials, setCredentials);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "parameters"), getParameters, setParameters);

		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "isHTTPRequest"), v8::FunctionTemplate::New(pIsolate, isHTTPRequest));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "has"), v8::FunctionTemplate::New(pIsolate, hasHeader));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "get"), v8::FunctionTemplate::New(pIsolate, getHeader));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "set"), v8::FunctionTemplate::New(pIsolate, setHeader));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "add"), v8::FunctionTemplate::New(pIsolate, addHeader));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "authenticate"), v8::FunctionTemplate::New(pIsolate, authenticate));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "send"), v8::FunctionTemplate::New(pIsolate, send));

		// deprecated - for backwards, will be removed eventually
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "hasHeader"), v8::FunctionTemplate::New(pIsolate, hasHeader));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getHeader"), v8::FunctionTemplate::New(pIsolate, getHeader));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "setHeader"), v8::FunctionTemplate::New(pIsolate, setHeader));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "addHeader"), v8::FunctionTemplate::New(pIsolate, addHeader));

		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> requestTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(requestTemplate);
}


void HTTPRequestWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	RequestHolder* pRequestHolder = new RequestHolderImpl;

	try
	{
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
	catch (Poco::Exception& exc)
	{
		delete pRequestHolder;
		returnException(args, exc);
	}
}


void HTTPRequestWrapper::construct(const std::string& method, const v8::FunctionCallbackInfo<v8::Value>& args)
{
	RequestHolder* pRequestHolder = new RequestHolderImpl;

	try
	{
		pRequestHolder->request().setMethod(method);
		if (args.Length() > 0)
			pRequestHolder->request().setURI(toString(args[0]));
		if (args.Length() > 1)
			pRequestHolder->request().setVersion(toString(args[1]));
		else
			pRequestHolder->request().setVersion(Poco::Net::HTTPMessage::HTTP_1_1);

		HTTPRequestWrapper wrapper;
		v8::Persistent<v8::Object>& requestObject(wrapper.wrapNativePersistent(args.GetIsolate(), pRequestHolder));
		args.GetReturnValue().Set(requestObject);
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
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);
	if (value->IsNumber())
	{
		double timeout = value->NumberValue();
		pRequestHolder->setTimeout(static_cast<Poco::Timespan::TimeDiff>(timeout*1000000));
	}
}


void HTTPRequestWrapper::getCookies(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::HandleScope handleScope(info.GetIsolate());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);

	Poco::Net::NameValueCollection cookies;
	pRequestHolder->request().getCookies(cookies);
	v8::Local<v8::Object> result(v8::Object::New(info.GetIsolate()));
	if (!result.IsEmpty())
	{
		for (auto it = cookies.begin(); it != cookies.end(); ++it)
		{
			result->Set(v8::String::NewFromUtf8(info.GetIsolate(), it->first.c_str()), v8::String::NewFromUtf8(info.GetIsolate(),it->second.c_str()));
		}
	}
	info.GetReturnValue().Set(result);
}


void HTTPRequestWrapper::getHeaders(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::HandleScope handleScope(info.GetIsolate());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);

	const Poco::Net::HTTPRequest& request = pRequestHolder->request();
	v8::Local<v8::Object> result(v8::Object::New(info.GetIsolate()));
	if (!result.IsEmpty())
	{
		for (auto it = request.begin(); it != request.end(); ++it)
		{
			result->Set(v8::String::NewFromUtf8(info.GetIsolate(), it->first.c_str()), v8::String::NewFromUtf8(info.GetIsolate(),it->second.c_str()));
		}
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
			if (!result.IsEmpty())
			{
				result->Set(v8::String::NewFromUtf8(info.GetIsolate(), "username"), v8::String::NewFromUtf8(info.GetIsolate(), creds.getUsername().c_str()));
				result->Set(v8::String::NewFromUtf8(info.GetIsolate(), "password"), v8::String::NewFromUtf8(info.GetIsolate(), creds.getPassword().c_str()));
			}
			info.GetReturnValue().Set(result);
			return;
		}
		else if (scheme == "Bearer")
		{
			v8::Local<v8::Object> result(v8::Object::New(info.GetIsolate()));
			if (!result.IsEmpty())
			{
				result->Set(v8::String::NewFromUtf8(info.GetIsolate(), "bearer"), v8::String::NewFromUtf8(info.GetIsolate(), authInfo.c_str()));
			}
			info.GetReturnValue().Set(result);
			return;
		}
	}
	info.GetReturnValue().Set(v8::Null(info.GetIsolate()));
}


void HTTPRequestWrapper::setCredentials(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	v8::HandleScope handleScope(info.GetIsolate());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);

	if (value->IsObject())
	{
		v8::Local<v8::Object> credentials = value.As<v8::Object>();
		v8::Local<v8::String> usernameProp = v8::String::NewFromUtf8(info.GetIsolate(), "username");
		v8::Local<v8::String> passwordProp = v8::String::NewFromUtf8(info.GetIsolate(), "password");
		v8::Local<v8::String> bearerProp = v8::String::NewFromUtf8(info.GetIsolate(), "bearer");

		if (credentials->Has(usernameProp) && credentials->Has(passwordProp))
		{
			const std::string username = toString(credentials->Get(usernameProp));
			const std::string password = toString(credentials->Get(passwordProp));
			Poco::Net::HTTPBasicCredentials basicCredentials(username, password);
			basicCredentials.authenticate(pRequestHolder->request());
		}
		else if (credentials->Has(bearerProp))
		{
			const std::string bearer = toString(credentials->Get(bearerProp));
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
	v8::HandleScope handleScope(info.GetIsolate());
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(info);

	Poco::MemoryInputStream bodyStream(pRequestHolder->content().data(), pRequestHolder->content().size());
	Poco::Net::HTMLForm form(pRequestHolder->request(), bodyStream);
	v8::Local<v8::Object> result(v8::Object::New(info.GetIsolate()));
	for (const auto& p: form)
	{
		v8::Local<v8::String> name = v8::String::NewFromUtf8(info.GetIsolate(), p.first.c_str());
		v8::Local<v8::String> value = v8::String::NewFromUtf8(info.GetIsolate(), p.second.c_str());
		result->Set(name, value);
	}
	info.GetReturnValue().Set(result);
}


void HTTPRequestWrapper::setParameters(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	v8::HandleScope handleScope(info.GetIsolate());
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
		v8::MaybeLocal<v8::Array> maybeNames = params->GetOwnPropertyNames(info.GetIsolate()->GetCurrentContext());
		if (!maybeNames.IsEmpty())
		{
			v8::Local<v8::Array> names = maybeNames.ToLocalChecked();
			std::size_t length = names->Length();
			for (std::size_t i = 0; i < length; i++)
			{
				const std::string name = toString(names->Get(i));
				const std::string value = toString(params->Get(names->Get(i)));
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


void HTTPRequestWrapper::addHeader(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(args);
	std::string name = toString(args[0]);
	std::string value = toString(args[1]);
	pRequestHolder->request().add(name, value);
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
	if (args.Length() > 0 && args[0]->IsFunction())
	{
		sendAsync(args);
	}
	else
	{
		sendBlocking(args);
	}
}


void HTTPRequestWrapper::sendBlocking(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	RequestHolder* pRequestHolder = Wrapper::unwrapNative<RequestHolder>(args);
	ResponseHolder* pResponseHolder = new ResponseHolderImpl;
	std::string uriString = pRequestHolder->request().getURI();
	try
	{
		Poco::URI uri(uriString);
		std::string uriPath = uri.getPathEtc();
		if (uriPath.empty()) uriPath = "/";
		pRequestHolder->request().setURI(uriPath);
		Poco::SharedPtr<Poco::Net::HTTPClientSession> pCS = Poco::Net::HTTPSessionFactory::defaultFactory().createClientSession(uri);
		if (pRequestHolder->request().getMethod() == Poco::Net::HTTPRequest::HTTP_PUT || pRequestHolder->request().getMethod() == Poco::Net::HTTPRequest::HTTP_POST || pRequestHolder->request().getMethod() == Poco::Net::HTTPRequest::HTTP_PATCH)
		{
			pRequestHolder->request().setContentLength(pRequestHolder->content().length());
		}
		pCS->setTimeout(pRequestHolder->getTimeout());
		pCS->sendRequest(pRequestHolder->request()).write(pRequestHolder->content().data(), pRequestHolder->content().size());
		std::istream& istr = pCS->receiveResponse(pResponseHolder->response());
		std::streamsize contentLength = pResponseHolder->response().getContentLength();
		if (contentLength != Poco::Net::HTTPMessage::UNKNOWN_CONTENT_LENGTH)
		{
			pResponseHolder->content().reserve(static_cast<std::size_t>(contentLength));
		}
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


class AsyncRequest: public Poco::Runnable
{
public:
	AsyncRequest(v8::Isolate* pIsolate, Poco::JS::Core::TimedJSExecutor::Ptr pExecutor, Poco::SharedPtr<Poco::Net::HTTPClientSession> pSession, Poco::SharedPtr<Poco::Net::HTTPRequest> pRequest, const std::string& body, v8::Handle<v8::Function> function):
		_pIsolate(pIsolate),
		_pExecutor(pExecutor),
		_pSession(pSession),
		_pRequest(pRequest),
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

	void run();

private:
	v8::Isolate* _pIsolate;
	Poco::JS::Core::TimedJSExecutor::Ptr _pExecutor;
	Poco::SharedPtr<Poco::Net::HTTPClientSession> _pSession;
	Poco::SharedPtr<Poco::Net::HTTPRequest> _pRequest;
	std::string _body;
	v8::Persistent<v8::Function> _function;
};



class AsyncRequestCompletionTask: public Poco::Util::TimerTask
{
public:
	AsyncRequestCompletionTask(v8::Isolate* pIsolate, Poco::JS::Core::JSExecutor::Ptr pExecutor, Poco::SharedPtr<Poco::Net::HTTPResponse> pResponse, AsyncRequest* pAsyncRequest):
		_pIsolate(pIsolate),
		_pExecutor(pExecutor, true),
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
		pResponseHolder->content() = std::move(_pAsyncRequest->body());
		HTTPResponseWrapper wrapper;
		v8::Persistent<v8::Object>& responseObject(wrapper.wrapNativePersistent(_pIsolate, pResponseHolder));

		v8::Local<v8::Object> statusObject = v8::Object::New(_pIsolate);
		statusObject->Set(v8::String::NewFromUtf8(_pIsolate, "response"), v8::Local<v8::Object>::New(_pIsolate, responseObject));
		statusObject->Set(v8::String::NewFromUtf8(_pIsolate, "error"), v8::Null(_pIsolate));

		v8::Local<v8::Function> localFunction(v8::Local<v8::Function>::New(_pIsolate, _pAsyncRequest->function()));
		v8::Local<v8::Value> receiver(v8::Null(_pIsolate));
		_pAsyncRequest->function().Reset();

		v8::Handle<v8::Value> args[1];
		args[0] = v8::Local<v8::Object>::New(_pIsolate, statusObject);

		_pExecutor->callInContext(localFunction, receiver, 1, args);
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
		statusObject->Set(v8::String::NewFromUtf8(_pIsolate, "response"), v8::Null(_pIsolate));
		statusObject->Set(v8::String::NewFromUtf8(_pIsolate, "error"), v8::String::NewFromUtf8(_pIsolate, _pException->displayText().c_str()));

		v8::Local<v8::Function> localFunction(v8::Local<v8::Function>::New(_pIsolate, _pAsyncRequest->function()));
		v8::Local<v8::Value> receiver(v8::Null(_pIsolate));
		_pAsyncRequest->function().Reset();

		v8::Handle<v8::Value> args[1];
		args[0] = v8::Local<v8::Object>::New(_pIsolate, statusObject);

		_pExecutor->callInContext(localFunction, receiver, 1, args);
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
		_pSession->sendRequest(*_pRequest).write(_body.data(), _body.size());
		Poco::SharedPtr<Poco::Net::HTTPResponse> pResponse = new Poco::Net::HTTPResponse;
		std::istream& istr = _pSession->receiveResponse(*pResponse);
		std::streamsize contentLength = pResponse->getContentLength();
		_body.clear();
		if (contentLength != Poco::Net::HTTPMessage::UNKNOWN_CONTENT_LENGTH)
		{
			_body.reserve(static_cast<std::size_t>(contentLength));
		}
		Poco::StreamCopier::copyToString(istr, _body);
		_pExecutor->schedule(new AsyncRequestCompletionTask(_pIsolate, _pExecutor, pResponse, this));
	}
	catch (Poco::Exception& exc)
	{
		_pExecutor->schedule(new AsyncRequestFailedTask(_pIsolate, _pExecutor, exc.clone(), this));
	}
	catch (...)
	{
		poco_bugcheck();
	}
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
			pRequestHolder->request().setURI(uriPath);
			Poco::SharedPtr<Poco::Net::HTTPRequest> pRequest = new Poco::Net::HTTPRequest(pRequestHolder->request().getMethod(), uriPath, pRequestHolder->request().getVersion());
			static_cast<Poco::Net::MessageHeader&>(*pRequest) = pRequestHolder->request();
			Poco::SharedPtr<Poco::Net::HTTPClientSession> pCS = Poco::Net::HTTPSessionFactory::defaultFactory().createClientSession(uri);
			if (pRequest->getMethod() == Poco::Net::HTTPRequest::HTTP_PUT || pRequest->getMethod() == Poco::Net::HTTPRequest::HTTP_POST)
			{
				pRequest->setContentLength(pRequestHolder->content().length());
			}
			pCS->setTimeout(pRequestHolder->getTimeout());

			AsyncRequest* pAsyncRequest = new AsyncRequest(pIsolate, pTimedJSExecutor, pCS, pRequest, pRequestHolder->content(), function);
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
