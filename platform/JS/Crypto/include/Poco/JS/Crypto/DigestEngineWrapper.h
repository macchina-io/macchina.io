//
// DigestEngineWrapper.h
//
// Library: JS/Crypto
// Package: Wrappers
// Module:  DigestEngineWrapper
//
// Definition of the DigestEngineWrapper class.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Crypto_DigestEngineWrapper_INCLUDED
#define JS_Crypto_DigestEngineWrapper_INCLUDED


#include "Poco/JS/Crypto/Crypto.h"
#include "Poco/JS/Core/Wrapper.h"


namespace Poco {
namespace JS {
namespace Crypto {


class JSCrypto_API DigestEngineWrapper: public Core::Wrapper
	/// JavaScript wrapper for Poco::DigestEngine.
{
public:
	DigestEngineWrapper();
		/// Creates the DigestEngineWrapper.

	~DigestEngineWrapper();
		/// Destroys the DigestEngineWrapper.

	v8::Handle<v8::FunctionTemplate> constructor(v8::Isolate* pIsolate);
		/// Creates and returns a V8 FunctionTemplate for the constructor function.

	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);

protected:
	static void isDigestEngine(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void update(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void digest(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void reset(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::JS::Crypto


#endif // JS_Crypto_DigestEngineWrapper_INCLUDED
