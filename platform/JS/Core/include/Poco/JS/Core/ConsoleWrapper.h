//
// ConsoleWrapper.h
//
// Library: JS/Core
// Package: Wrappers
// Module:  ConsoleWrapper
//
// Definition of the ConsoleWrapper interface.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Core_ConsoleWrapper_INCLUDED
#define JS_Core_ConsoleWrapper_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/Message.h"


namespace Poco {
namespace JS {
namespace Core {


class JSCore_API ConsoleWrapper: public Wrapper
	/// JavaScript wrapper for Poco::Logger, presenting
	/// a Console-style interface as known from web browsers.
{
public:
	ConsoleWrapper();
		/// Creates the ConsoleWrapper for the root logger.

	~ConsoleWrapper();
		/// Destroys the ConsoleWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);

protected:
	static void trace(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void xassert(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void log(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void debug(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void info(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void error(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void warn(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void dump(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::JS::Core


#endif // JS_Core_ConsoleWrapper_INCLUDED
