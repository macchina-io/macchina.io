//
// HTTPRequestWrapper.h
//
// Library: JS/Net
// Package: Wrappers
// Module:  HTTPRequestWrapper
//
// Definition of the HTTPRequestWrapper interface.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_Net_HTTPRequestWrapper_INCLUDED
#define JS_Net_HTTPRequestWrapper_INCLUDED


#include "Poco/JS/Net/Net.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/Timespan.h"
#include "Poco/SharedPtr.h"


namespace Poco {
namespace JS {
namespace Net {


class JSNet_API RequestHolder
	/// Base class for RequestHolder classes.
{
public:
	RequestHolder();
		/// Creates the RequestHolder.
	
	virtual ~RequestHolder();
		/// Destroys the RequestHolder.
		
	virtual Poco::Net::HTTPRequest& request() = 0;

	std::string& content()
	{
		return _content;
	}
	
	const std::string& content() const
	{
		return _content;
	}
	
	void setTimeout(const Poco::Timespan timeout)
	{
		_timeout = timeout;
	}
	
	const Poco::Timespan& getTimeout() const
	{
		return _timeout;
	}

private:
	std::string _content;
	Poco::Timespan _timeout;
};


class JSNet_API RequestHolderImpl: public RequestHolder
{
public:
	RequestHolderImpl()
	{
	}
	
	RequestHolderImpl(const Poco::Net::HTTPRequest& request):
		_request(request.getMethod(), request.getURI(), request.getVersion())
	{
		static_cast<Poco::Net::MessageHeader>(_request) = request;
	}
	
	~RequestHolderImpl()
	{
	}
	
	Poco::Net::HTTPRequest& request()
	{
		return _request;
	}
	
private:
	Poco::Net::HTTPRequest _request;
};


template <class C>
class RequestRefHolderImpl: public RequestHolder
{
public:
	RequestRefHolderImpl(C& request):
		_request(request)
	{
	}
	
	~RequestRefHolderImpl()
	{
	}
	
	Poco::Net::HTTPRequest& request()
	{
		return _request;
	}
	
private:
	C& _request;
};


template <class C>
class RequestPtrHolderImpl: public RequestHolder
{
public:
	RequestPtrHolderImpl(Poco::SharedPtr<C> pRequest):
		_pRequest(pRequest)
	{
	}
	
	~RequestPtrHolderImpl()
	{
	}
	
	Poco::Net::HTTPRequest& request()
	{
		return *_pRequest;
	}
	
private:
	Poco::SharedPtr<C> _pRequest;
};


class JSNet_API HTTPRequestWrapper: public JS::Core::Wrapper
	/// JavaScript wrapper for Poco::HTTPRequest.
{
public:
	HTTPRequestWrapper();
		/// Creates the HTTPRequestWrapper for the root logger.
	
	~HTTPRequestWrapper();
		/// Destroys the HTTPRequestWrapper.

	v8::Handle<v8::FunctionTemplate> constructor(v8::Isolate* pIsolate);
		/// Creates and returns a V8 FunctionTemplate for the constructor function.

	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
		/// Constructor function.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);
		
protected:
	static void getMethod(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setMethod(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getURI(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setURI(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getVersion(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setVersion(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getContentType(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setContentType(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getContent(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setContent(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getBuffer(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setBuffer(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getTimeout(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setTimeout(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getCookies(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getCredentials(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void hasHeader(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getHeader(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void setHeader(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void addHeader(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void authenticate(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void send(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void sendBlocking(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void sendAsync(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::JS::Net


#endif // JS_Net_HTTPRequestWrapper_INCLUDED
