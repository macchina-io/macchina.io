//
// HTTPResponseWrapper.cpp
//
// Library: JS/Net
// Package: Wrappers
// Module:  HTTPResponseWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Net/HTTPResponseWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/JS/Core/BufferWrapper.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/NumberParser.h"


namespace Poco {
namespace JS {
namespace Net {


std::string htmlize(const std::string& str)
{
	std::string::const_iterator it(str.begin());
	std::string::const_iterator end(str.end());
	std::string html;
	for (; it != end; ++it)
	{
		switch (*it)
		{
		case '<': html += "&lt;"; break;
		case '>': html += "&gt;"; break;
		case '"': html += "&quot;"; break;
		case '&': html += "&amp;"; break;
		default:  html += *it; break;
		}
	}
	return html;
}


ResponseHolder::ResponseHolder()
{
}


ResponseHolder::~ResponseHolder()
{
}


HTTPResponseWrapper::HTTPResponseWrapper()
{
}


HTTPResponseWrapper::~HTTPResponseWrapper()
{
}


v8::Handle<v8::FunctionTemplate> HTTPResponseWrapper::constructor(v8::Isolate* pIsolate)
{
	return v8::FunctionTemplate::New(pIsolate, construct);
}


v8::Handle<v8::ObjectTemplate> HTTPResponseWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Poco::JS::Core::PooledIsolate* pPooledIso = Poco::JS::Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Net.HTTPResponse"));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "status"), getStatus, setStatus);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "reason"), getReason, setReason);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "version"), getVersion, setVersion);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "contentType"), getContentType, setContentType);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "content"), getContent, setContent);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "buffer"), getBuffer, setBuffer);

		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "has"), v8::FunctionTemplate::New(pIsolate, hasHeader));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "get"), v8::FunctionTemplate::New(pIsolate, getHeader));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "set"), v8::FunctionTemplate::New(pIsolate, setHeader));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "setStatus"), v8::FunctionTemplate::New(pIsolate, setStatus));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "write"), v8::FunctionTemplate::New(pIsolate, write));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "writeln"), v8::FunctionTemplate::New(pIsolate, writeln));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "writeHTML"), v8::FunctionTemplate::New(pIsolate, writeHTML));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "htmlize"), v8::FunctionTemplate::New(pIsolate, writeHTML));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "send"), v8::FunctionTemplate::New(pIsolate, send));

		// deprecated - for backwards compatibility only, will be removed in future version
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "hasHeader"), v8::FunctionTemplate::New(pIsolate, hasHeader));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getHeader"), v8::FunctionTemplate::New(pIsolate, getHeader));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "setHeader"), v8::FunctionTemplate::New(pIsolate, setHeader));

		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> responseTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(responseTemplate);
}


void HTTPResponseWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	ResponseHolder* pResponseHolder = new ResponseHolderImpl();
	try
	{
		HTTPResponseWrapper wrapper;
		v8::Persistent<v8::Object> responseObject(args.GetIsolate(), wrapper.wrapNative(args.GetIsolate(), pResponseHolder));
		responseObject.SetWeak(pResponseHolder, destruct, v8::WeakCallbackType::kParameter);
		args.GetReturnValue().Set(responseObject);
	}
	catch (Poco::Exception& exc)
	{
		delete pResponseHolder;
		returnException(args, exc);
	}
}


void HTTPResponseWrapper::destruct(const v8::WeakCallbackInfo<ResponseHolder>& data)
{
	delete data.GetParameter();
}


void HTTPResponseWrapper::getStatus(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	info.GetReturnValue().Set(static_cast<int>(pResponseHolder->response().getStatus()));
}


void HTTPResponseWrapper::setStatus(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	try
	{
		pResponseHolder->response().setStatus(toString(value));
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
}


void HTTPResponseWrapper::getReason(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	returnString(info, pResponseHolder->response().getReason());
}


void HTTPResponseWrapper::setReason(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	pResponseHolder->response().setReason(toString(value));
}


void HTTPResponseWrapper::getVersion(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	returnString(info, pResponseHolder->response().getVersion());
}


void HTTPResponseWrapper::setVersion(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	pResponseHolder->response().setVersion(toString(value));
}


void HTTPResponseWrapper::getContentType(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	returnString(info, pResponseHolder->response().getContentType());
}


void HTTPResponseWrapper::setContentType(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	pResponseHolder->response().setContentType(toString(value));
}


void HTTPResponseWrapper::getContent(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	returnString(info, pResponseHolder->content());
}


void HTTPResponseWrapper::setContent(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	pResponseHolder->content() = toString(value);
}


void HTTPResponseWrapper::getBuffer(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	Poco::JS::Core::BufferWrapper::Buffer* pBuffer = new Poco::JS::Core::BufferWrapper::Buffer(pResponseHolder->content().data(), pResponseHolder->content().size());
	Poco::JS::Core::BufferWrapper wrapper;
	v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(info.GetIsolate(), pBuffer));
	info.GetReturnValue().Set(v8::Local<v8::Object>::New(info.GetIsolate(), bufferObject));
}


void HTTPResponseWrapper::setBuffer(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	if (Poco::JS::Core::Wrapper::isWrapper<Poco::JS::Core::BufferWrapper::Buffer>(info.GetIsolate(), value))
	{
		Poco::JS::Core::BufferWrapper::Buffer* pBuffer = Poco::JS::Core::Wrapper::unwrapNativeObject<Poco::JS::Core::BufferWrapper::Buffer>(value);
		pResponseHolder->content().assign(pBuffer->begin(), pBuffer->size());
	}
	else returnException(info, Poco::InvalidArgumentException("argument must be a Buffer"));
}


void HTTPResponseWrapper::hasHeader(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	std::string name = toString(args[0]);
	bool result = pResponseHolder->response().has(name);
	args.GetReturnValue().Set(result);
}


void HTTPResponseWrapper::getHeader(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	std::string name = toString(args[0]);
	std::string deflt;
	if (args.Length() > 1) deflt = toString(args[1]);
	std::string value = pResponseHolder->response().get(name, deflt);
	returnString(args, value);
}


void HTTPResponseWrapper::setHeader(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	std::string name = toString(args[0]);
	std::string value = toString(args[1]);
	pResponseHolder->response().set(name, value);
}


void HTTPResponseWrapper::setStatus(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	std::string status = toString(args[0]);
	try
	{
		if (args.Length() > 1)
		{
			std::string reason = toString(args[1]);
			pResponseHolder->response().setStatusAndReason(static_cast<Poco::Net::HTTPResponse::HTTPStatus>(Poco::NumberParser::parse(status)), reason);
		}
		else
		{
			pResponseHolder->response().setStatusAndReason(static_cast<Poco::Net::HTTPResponse::HTTPStatus>(Poco::NumberParser::parse(status)));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void HTTPResponseWrapper::write(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	for (int i = 0; i < args.Length(); i++)
	{
		pResponseHolder->content().append(toString(args[i]));
	}
}


void HTTPResponseWrapper::writeln(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	for (int i = 0; i < args.Length(); i++)
	{
		pResponseHolder->content().append(toString(args[i]));
	}
	pResponseHolder->content().append("\n");
}


void HTTPResponseWrapper::writeHTML(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	for (int i = 0; i < args.Length(); i++)
	{
		pResponseHolder->content().append(Poco::JS::Net::htmlize(toString(args[i])));
	}
}


void HTTPResponseWrapper::send(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	Poco::Net::HTTPResponse* pResponse = &pResponseHolder->response();
	Poco::Net::HTTPServerResponse* pServerResponse = dynamic_cast<Poco::Net::HTTPServerResponse*>(pResponse);
	if (pServerResponse)
	{
		pServerResponse->sendBuffer(pResponseHolder->content().data(), pResponseHolder->content().size());
	}
}


void HTTPResponseWrapper::htmlize(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	std::string result;
	for (int i = 0; i < args.Length(); i++)
	{
		result += Poco::JS::Net::htmlize(toString(args[i]));
	}
	returnString(args, result);
}


} } } // namespace Poco::JS::Net
