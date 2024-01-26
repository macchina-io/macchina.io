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
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Net_HTTPRequestWrapper_INCLUDED
#define JS_Net_HTTPRequestWrapper_INCLUDED


#include "Poco/JS/Net/Net.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/Net/HTTPServerRequest.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Timespan.h"
#include "Poco/SharedPtr.h"


namespace Poco {
namespace JS {
namespace Net {


class JSNet_API CancelHandler: public Poco::RefCountedObject
{
public:
	using Ptr = Poco::AutoPtr<CancelHandler>;

	virtual void cancelRequest() = 0;
	virtual ~CancelHandler() = default;
};


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

	void setCancelHandler(CancelHandler::Ptr pCancelHandler)
	{
		_pCancelHandler = pCancelHandler;
	}

	CancelHandler::Ptr getCancelHandler() const
	{
		return _pCancelHandler;
	}

	void cancelRequest()
	{
		if (_pCancelHandler)
		{
			_pCancelHandler->cancelRequest();
			_pCancelHandler.reset();
		}
	}

private:
	std::string _content;
	Poco::Timespan _timeout;
	CancelHandler::Ptr _pCancelHandler;
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

	static void construct(const std::string& method, const v8::FunctionCallbackInfo<v8::Value>& args);
		/// Constructor function, used by get(), post(), etc.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);

protected:
	static void isHTTPRequest(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void get(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void post(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void put(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void patch(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void delete_(const v8::FunctionCallbackInfo<v8::Value>& args);
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
	static void getHeaders(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void getCredentials(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setCredentials(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getParameters(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setParameters(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void hasHeader(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getHeader(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void setHeader(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void addHeader(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void authenticate(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void send(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void sendBlocking(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void sendAsync(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void cancel(const v8::FunctionCallbackInfo<v8::Value>& args);	
};


} } } // namespace Poco::JS::Net


#endif // JS_Net_HTTPRequestWrapper_INCLUDED
