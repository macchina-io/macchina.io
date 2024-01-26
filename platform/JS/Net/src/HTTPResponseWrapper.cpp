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
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Net/HTTPResponseWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/JS/Core/BufferWrapper.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/NumberParser.h"


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Net {


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
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::FunctionTemplate> funcTemplate = v8::FunctionTemplate::New(pIsolate, construct);
	funcTemplate->Set(toV8Internalized(pIsolate, "isHTTPResponse"s), v8::FunctionTemplate::New(pIsolate, isHTTPResponse));
	return handleScope.Escape(funcTemplate);
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
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "status"s), getStatus, setStatus);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "reason"s), getReason, setReason);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "version"s), getVersion, setVersion);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "contentType"s), getContentType, setContentType);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "content"s), getContent, setContent);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "buffer"s), getBuffer, setBuffer);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "headers"s), getHeaders);

		objectTemplate->Set(toV8Internalized(pIsolate, "has"s), v8::FunctionTemplate::New(pIsolate, hasHeader));
		objectTemplate->Set(toV8Internalized(pIsolate, "get"s), v8::FunctionTemplate::New(pIsolate, getHeader));
		objectTemplate->Set(toV8Internalized(pIsolate, "set"s), v8::FunctionTemplate::New(pIsolate, setHeader));
		objectTemplate->Set(toV8Internalized(pIsolate, "setStatus"s), v8::FunctionTemplate::New(pIsolate, setStatus));
		objectTemplate->Set(toV8Internalized(pIsolate, "write"s), v8::FunctionTemplate::New(pIsolate, write));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeln"s), v8::FunctionTemplate::New(pIsolate, writeln));
		objectTemplate->Set(toV8Internalized(pIsolate, "writeHTML"s), v8::FunctionTemplate::New(pIsolate, writeHTML));
		objectTemplate->Set(toV8Internalized(pIsolate, "htmlize"s), v8::FunctionTemplate::New(pIsolate, writeHTML));
		objectTemplate->Set(toV8Internalized(pIsolate, "send"s), v8::FunctionTemplate::New(pIsolate, send));
		objectTemplate->Set(toV8Internalized(pIsolate, "sendFile"s), v8::FunctionTemplate::New(pIsolate, sendFile));
		objectTemplate->Set(toV8Internalized(pIsolate, "redirect"s), v8::FunctionTemplate::New(pIsolate, redirect));

		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> responseTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(responseTemplate);
}


void HTTPResponseWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::EscapableHandleScope handleScope(pIsolate);

	ResponseHolder* pResponseHolder = new ResponseHolderImpl();
	try
	{
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


void HTTPResponseWrapper::destruct(const v8::WeakCallbackInfo<ResponseHolder>& data)
{
	delete data.GetParameter();
}


void HTTPResponseWrapper::isHTTPResponse(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() > 0)
	{
		args.GetReturnValue().Set(Wrapper::isWrapper<ResponseHolder>(args.GetIsolate(), args[0]));
	}
	else
	{
		args.GetReturnValue().Set(false);
	}
}


void HTTPResponseWrapper::getStatus(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	info.GetReturnValue().Set(static_cast<int>(pResponseHolder->response().getStatus()));
}


void HTTPResponseWrapper::setStatus(v8::Local<v8::Name> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	try
	{
		pResponseHolder->response().setStatus(toString(info.GetIsolate(), value));
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
}


void HTTPResponseWrapper::getReason(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	returnString(info, pResponseHolder->response().getReason());
}


void HTTPResponseWrapper::setReason(v8::Local<v8::Name> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	pResponseHolder->response().setReason(toString(info.GetIsolate(), value));
}


void HTTPResponseWrapper::getVersion(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	returnString(info, pResponseHolder->response().getVersion());
}


void HTTPResponseWrapper::setVersion(v8::Local<v8::Name> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	pResponseHolder->response().setVersion(toString(info.GetIsolate(), value));
}


void HTTPResponseWrapper::getContentType(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	returnString(info, pResponseHolder->response().getContentType());
}


void HTTPResponseWrapper::setContentType(v8::Local<v8::Name> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	pResponseHolder->response().setContentType(toString(info.GetIsolate(), value));
}


void HTTPResponseWrapper::getContent(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	returnString(info, pResponseHolder->content());
}


void HTTPResponseWrapper::setContent(v8::Local<v8::Name> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	pResponseHolder->content() = toString(info.GetIsolate(), value);
}


void HTTPResponseWrapper::getBuffer(v8::Local<v8::Name> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	Poco::JS::Core::BufferWrapper::Buffer* pBuffer = new Poco::JS::Core::BufferWrapper::Buffer(pResponseHolder->content().data(), pResponseHolder->content().size());
	Poco::JS::Core::BufferWrapper wrapper;
	v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(info.GetIsolate(), pBuffer));
	info.GetReturnValue().Set(v8::Local<v8::Object>::New(info.GetIsolate(), bufferObject));
}


void HTTPResponseWrapper::setBuffer(v8::Local<v8::Name> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);
	if (Poco::JS::Core::Wrapper::isWrapper<Poco::JS::Core::BufferWrapper::Buffer>(info.GetIsolate(), value))
	{
		Poco::JS::Core::BufferWrapper::Buffer* pBuffer = Poco::JS::Core::Wrapper::unwrapNativeObject<Poco::JS::Core::BufferWrapper::Buffer>(value);
		pResponseHolder->content().assign(pBuffer->begin(), pBuffer->size());
	}
	else returnException(info, Poco::InvalidArgumentException("argument must be a Buffer"));
}


void HTTPResponseWrapper::getHeaders(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(info);

	const Poco::Net::HTTPResponse& response = pResponseHolder->response();
	v8::Local<v8::Object> result(v8::Object::New(pIsolate));
	if (!result.IsEmpty())
	{
		for (auto it = response.begin(); it != response.end(); ++it)
		{
			V8_CHECK_SET_RESULT(result->Set(context, toV8String(pIsolate, it->first), toV8String(pIsolate, it->second)));
		}
	}
	info.GetReturnValue().Set(result);
}


void HTTPResponseWrapper::hasHeader(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	std::string name = toString(args.GetIsolate(), args[0]);
	bool result = pResponseHolder->response().has(name);
	args.GetReturnValue().Set(result);
}


void HTTPResponseWrapper::getHeader(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	std::string name = toString(pIsolate, args[0]);
	std::string deflt;
	if (args.Length() > 1) deflt = toString(pIsolate, args[1]);
	std::string value = pResponseHolder->response().get(name, deflt);
	returnString(args, value);
}


void HTTPResponseWrapper::setHeader(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	std::string name = toString(pIsolate, args[0]);
	std::string value = toString(pIsolate, args[1]);
	pResponseHolder->response().set(name, value);
}


void HTTPResponseWrapper::setStatus(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	std::string status = toString(pIsolate, args[0]);
	try
	{
		if (args.Length() > 1)
		{
			std::string reason = toString(pIsolate, args[1]);
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
		pResponseHolder->content().append(toString(args.GetIsolate(), args[i]));
	}
}


void HTTPResponseWrapper::writeln(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	for (int i = 0; i < args.Length(); i++)
	{
		pResponseHolder->content().append(toString(args.GetIsolate(), args[i]));
	}
	pResponseHolder->content().append("\n");
}


void HTTPResponseWrapper::writeHTML(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	for (int i = 0; i < args.Length(); i++)
	{
		pResponseHolder->content().append(Poco::Net::htmlize(toString(args.GetIsolate(), args[i])));
	}
}


void HTTPResponseWrapper::send(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	Poco::Net::HTTPResponse* pResponse = &pResponseHolder->response();
	Poco::Net::HTTPServerResponse* pServerResponse = dynamic_cast<Poco::Net::HTTPServerResponse*>(pResponse);
	if (pServerResponse)
	{
		try
		{
			pServerResponse->sendBuffer(pResponseHolder->content().data(), pResponseHolder->content().size());
		}
		catch (Poco::Exception& exc)
		{
			returnException(args, exc);
		}
	}
}


void HTTPResponseWrapper::sendFile(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	Poco::Net::HTTPResponse* pResponse = &pResponseHolder->response();
	Poco::Net::HTTPServerResponse* pServerResponse = dynamic_cast<Poco::Net::HTTPServerResponse*>(pResponse);
	if (pServerResponse)
	{
		std::string contentType;
		if (args.Length() > 1)
		{
			contentType = toString(args.GetIsolate(), args[1]);
		}
		else
		{
			contentType = pServerResponse->getContentType();
		}
		if (args.Length() > 0)
		{
			const std::string path = toString(args.GetIsolate(), args[0]);
			try
			{
				pServerResponse->sendFile(path, contentType);
			}
			catch (Poco::Exception& exc)
			{
				returnException(args, exc);
			}
		}
		else
		{
			returnException(args, "No path specified"s);
		}
	}
}


void HTTPResponseWrapper::redirect(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	ResponseHolder* pResponseHolder = Wrapper::unwrapNative<ResponseHolder>(args);
	Poco::Net::HTTPResponse* pResponse = &pResponseHolder->response();
	Poco::Net::HTTPServerResponse* pServerResponse = dynamic_cast<Poco::Net::HTTPServerResponse*>(pResponse);
	if (pServerResponse)
	{
		if (args.Length() > 0)
		{
			int status = Poco::Net::HTTPResponse::HTTP_FOUND;
			std::string location = toString(args.GetIsolate(), args[0]);
			if (args.Length() > 1)
			{
				status = args[1]->Int32Value(context).FromMaybe(status);
				switch (status)
				{
				case 301:
				case 302:
				case 303:
				case 307:
				case 308:
					break;
				default:
					returnException(args, "Invalid status code for redirect"s);
					return;
				}
			}
			try
			{			
				pServerResponse->redirect(location, static_cast<Poco::Net::HTTPResponse::HTTPStatus>(status));
			}
			catch (Poco::Exception& exc)
			{
				returnException(args, exc);
			}
		}
		else
		{
			returnException(args, "No location specified"s);
		}
	}
}


void HTTPResponseWrapper::htmlize(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	std::string result;
	for (int i = 0; i < args.Length(); i++)
	{
		result += Poco::Net::htmlize(toString(args.GetIsolate(), args[i]));
	}
	returnString(args, result);
}


} } } // namespace Poco::JS::Net
