//
// HTTPResponseWrapper.h
//
// Library: JS/Net
// Package: Wrappers
// Module:  HTTPResponseWrapper
//
// Definition of the HTTPResponseWrapper interface.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_Net_HTTPResponseWrapper_INCLUDED
#define JS_Net_HTTPResponseWrapper_INCLUDED


#include "Poco/JS/Net/Net.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/SharedPtr.h"


namespace Poco {
namespace JS {
namespace Net {


class JSNet_API ResponseHolder
	/// Base class for ResponseHolder classes.
{
public:
	ResponseHolder();
		/// Creates the ResponseHolder.
	
	virtual ~ResponseHolder();
		/// Destroys the ResponseHolder.
		
	virtual Poco::Net::HTTPResponse& response() = 0;

	std::string& content()
	{
		return _content;
	}
	
	const std::string& content() const
	{
		return _content;
	}

private:
	std::string _content;
};


class JSNet_API ResponseHolderImpl: public ResponseHolder
{
public:
	ResponseHolderImpl()
	{
	}
	
	ResponseHolderImpl(const Poco::Net::HTTPResponse& response):
		_response(response.getVersion(), response.getStatus(), response.getReason())
	{
		static_cast<Poco::Net::MessageHeader>(_response) = response;
	}
	
	~ResponseHolderImpl()
	{
	}
	
	Poco::Net::HTTPResponse& response()
	{
		return _response;
	}
	
private:
	Poco::Net::HTTPResponse _response;
};


template <class C>
class ResponseRefHolderImpl: public ResponseHolder
{
public:
	ResponseRefHolderImpl(C& response):
		_response(response)
	{
	}
	
	~ResponseRefHolderImpl()
	{
	}
	
	Poco::Net::HTTPResponse& response()
	{
		return _response;
	}
	
private:
	C& _response;
};


template <class C>
class ResponsePtrHolderImpl: public ResponseHolder
{
public:
	ResponsePtrHolderImpl(Poco::SharedPtr<C> pResponse):
		_pResponse(pResponse)
	{
	}
	
	~ResponsePtrHolderImpl()
	{
	}
	
	Poco::Net::HTTPResponse& response()
	{
		return *_pResponse;
	}
	
private:
	Poco::SharedPtr<C> _pResponse;
};


class JSNet_API HTTPResponseWrapper: public JS::Core::Wrapper
	/// JavaScript wrapper for Poco::HTTPResponse.
{
public:
	HTTPResponseWrapper();
		/// Creates the HTTPResponseWrapper for the root logger.
	
	~HTTPResponseWrapper();
		/// Destroys the HTTPResponseWrapper.

	v8::Handle<v8::FunctionTemplate> constructor(v8::Isolate* pIsolate);
		/// Creates and returns a V8 FunctionTemplate for the constructor function.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);
		
protected:
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void destruct(const v8::WeakCallbackInfo<ResponseHolder>& data);
	static void getStatus(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setStatus(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getReason(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setReason(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getVersion(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setVersion(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getContentType(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setContentType(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getContent(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setContent(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void getBuffer(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void setBuffer(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info);
	static void hasHeader(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getHeader(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void setHeader(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void setStatus(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void write(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeln(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void writeHTML(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void htmlize(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void send(const v8::FunctionCallbackInfo<v8::Value>& args);
	
	friend class HTTPRequestWrapper;
};


} } } // namespace Poco::JS::Net


#endif // JS_Net_HTTPResponseWrapper_INCLUDED
