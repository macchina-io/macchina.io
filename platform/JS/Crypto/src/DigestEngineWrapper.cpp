//
// DigestEngineWrapper.cpp
//
// Library: JS/Crypto
// Package: Wrappers
// Module:  DigestEngineWrapper
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Crypto/DigestEngineWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/JS/Core/BufferWrapper.h"
#include "Poco/Crypto/DigestEngine.h"
#include "Poco/Base64Encoder.h"
#include "Poco/String.h"
#include <sstream>


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Crypto {


DigestEngineWrapper::DigestEngineWrapper()
{
}


DigestEngineWrapper::~DigestEngineWrapper()
{
}


v8::Handle<v8::FunctionTemplate> DigestEngineWrapper::constructor(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::FunctionTemplate> funcTemplate = v8::FunctionTemplate::New(pIsolate, construct);
	funcTemplate->Set(toV8Internalized(pIsolate, "isDigestEngine"), v8::FunctionTemplate::New(pIsolate, isDigestEngine));
	return handleScope.Escape(funcTemplate);
}


v8::Handle<v8::ObjectTemplate> DigestEngineWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	Core::PooledIsolate* pPooledIso = Core::PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Crypto.DigestEngine"s));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->Set(toV8Internalized(pIsolate, "update"), v8::FunctionTemplate::New(pIsolate, update));
		objectTemplate->Set(toV8Internalized(pIsolate, "digest"), v8::FunctionTemplate::New(pIsolate, digest));
		objectTemplate->Set(toV8Internalized(pIsolate, "reset"), v8::FunctionTemplate::New(pIsolate, reset));
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> uuidTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(uuidTemplate);
}


void DigestEngineWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::EscapableHandleScope handleScope(pIsolate);

	Poco::DigestEngine* pDigestEngine = nullptr;
	try
	{
		
		if (args.Length() == 0)
		{
			returnException(args, "Digest algorithm must be specified when creating a DigestEngine"s);
		}
		else
		{
			if (args[0]->IsString())
			{
				const std::string algo = toString(pIsolate, args[0]);
				pDigestEngine = new Poco::Crypto::DigestEngine(algo);
				DigestEngineWrapper wrapper;
				v8::Persistent<v8::Object>& digestEngineObject(wrapper.wrapNativePersistent(pIsolate, pDigestEngine));
				args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, digestEngineObject));
			}
			else
			{
				returnException(args, "Digest algorithm must be a string"s);
			}
		}
	}
	catch (Poco::Exception& exc)
	{
		delete pDigestEngine;
		returnException(args, exc);
	}
}


void DigestEngineWrapper::isDigestEngine(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() > 0)
	{
		args.GetReturnValue().Set(Wrapper::isWrapper<Poco::DigestEngine>(args.GetIsolate(), args[0]));
	}
	else
	{
		args.GetReturnValue().Set(false);
	}
}


void DigestEngineWrapper::update(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	Poco::DigestEngine* pDigestEngine = Wrapper::unwrapNative<Poco::DigestEngine>(args);
	if (args.Length() > 0)
	{
		if (Poco::JS::Core::Wrapper::isWrapper<Poco::JS::Core::BufferWrapper::Buffer>(args.GetIsolate(), args[0]))
		{
			Poco::JS::Core::BufferWrapper::Buffer* pBuffer = Poco::JS::Core::Wrapper::unwrapNativeObject<Poco::JS::Core::BufferWrapper::Buffer>(args[0]);
			pDigestEngine->update(pBuffer->begin(), pBuffer->size());
		}
		else
		{
			const std::string data = toString(pIsolate, args[0]);
			pDigestEngine->update(data);
		}
	}
}


void DigestEngineWrapper::digest(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	Poco::DigestEngine* pDigestEngine = Wrapper::unwrapNative<Poco::DigestEngine>(args);
	if (args.Length() > 0)
	{
		const std::string encoding = toString(pIsolate, args[0]);
		if (Poco::icompare(encoding, "hex"s) == 0 || Poco::icompare(encoding, "hexbin"s) == 0)
		{
			const std::string hex = Poco::DigestEngine::digestToHex(pDigestEngine->digest());
			returnString(args, hex);
		}
		else if (Poco::icompare(encoding, "base64"s) == 0 || Poco::icompare(encoding, "base64url"s) == 0)
		{
			int options = 0;
			if (encoding.length() == "base64url"s.length()) options |= BASE64_URL_ENCODING | BASE64_NO_PADDING;

			const auto digest = pDigestEngine->digest();
			std::ostringstream ostr;
			Poco::Base64Encoder base64(ostr, options);
			base64.rdbuf()->setLineLength(0);
			base64.write(reinterpret_cast<const char*>(digest.data()), digest.size());
			base64.close();
			returnString(args, ostr.str());
		}
		else
		{
			returnException(args, "Invalid encoding parameter specified"s);
		}
	}
	else
	{
		const auto digest = pDigestEngine->digest();
		Poco::JS::Core::BufferWrapper::Buffer* pBuffer = new Poco::JS::Core::BufferWrapper::Buffer(reinterpret_cast<const char*>(digest.data()), digest.size());
		Poco::JS::Core::BufferWrapper wrapper;
		v8::Persistent<v8::Object>& bufferObject(wrapper.wrapNativePersistent(args.GetIsolate(), pBuffer));
		args.GetReturnValue().Set(v8::Local<v8::Object>::New(args.GetIsolate(), bufferObject));
	}
}


void DigestEngineWrapper::reset(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Poco::DigestEngine* pDigestEngine = Wrapper::unwrapNative<Poco::DigestEngine>(args);
	pDigestEngine->reset();
}


} } } // namespace Poco::JS::Crypto
