//
// URIWrapper.cpp
//
// Library: JS/Core
// Package: Wrappers
// Module:  URIWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/URIWrapper.h"
#include "Poco/JS/Core/BufferWrapper.h"
#include "Poco/URIStreamOpener.h"
#include "Poco/StreamCopier.h"
#include <memory>


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Core {


URIWrapper::URIWrapper()
{
}


URIWrapper::~URIWrapper()
{
}


v8::Handle<v8::ObjectTemplate> URIWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::ObjectTemplate> uriTemplate = v8::ObjectTemplate::New(pIsolate);
	uriTemplate->Set(toV8Internalized(pIsolate, "loadString"s), v8::FunctionTemplate::New(pIsolate, loadString));
	uriTemplate->Set(toV8Internalized(pIsolate, "loadBuffer"s), v8::FunctionTemplate::New(pIsolate, loadBuffer));
	return handleScope.Escape(uriTemplate);
}


void URIWrapper::loadString(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	std::string uri = toString(pIsolate, args[0]);
	try
	{
		std::string data;
		std::unique_ptr<std::istream> pStream(Poco::URIStreamOpener::defaultOpener().open(uri));
		Poco::StreamCopier::copyToString(*pStream, data);
		returnString(args, data);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void URIWrapper::loadBuffer(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	std::string uri = toString(pIsolate, args[0]);
	try
	{
		std::string data;
		std::unique_ptr<std::istream> pStream(Poco::URIStreamOpener::defaultOpener().open(uri));
		Poco::StreamCopier::copyToString(*pStream, data);
		Poco::JS::Core::BufferWrapper::Buffer* pBuffer = new Poco::JS::Core::BufferWrapper::Buffer(data.data(), data.size());
		Poco::JS::Core::BufferWrapper wrapper;
		v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(pIsolate, pBuffer));
		args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, bufferObject));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


} } } // namespace Poco::JS::Core
