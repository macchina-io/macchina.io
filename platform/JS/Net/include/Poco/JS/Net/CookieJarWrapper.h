//
// CookieJarWrapper.h
//
// Library: JS/Net
// Package: Wrappers
// Module:  CookieJar
//
// Definition of the CookieJarWrapper class.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Net_CookieJarWrapper_INCLUDED
#define JS_Net_CookieJarWrapper_INCLUDED


#include "Poco/JS/Net/Net.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/UUID.h"


namespace Poco {
namespace JS {
namespace Net {


class JSNet_API CookieJarWrapper: public Core::Wrapper
	/// JavaScript wrapper for CookieJar.
{
public:
	CookieJarWrapper();
		/// Creates the CookieJarWrapper.

	~CookieJarWrapper();
		/// Destroys the CookieJarWrapper.

	v8::Handle<v8::FunctionTemplate> constructor(v8::Isolate* pIsolate);
		/// Creates and returns a V8 FunctionTemplate for the constructor function.

	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);

protected:
	static void isCookieJar(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void addCookies(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void updateCookies(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::JS::Net


#endif // JS_Net_CookieJarWrapper_INCLUDED
