//
// LoggerWrapper.h
//
// $Id: //poco/1.4/JS/Core/include/Poco/JS/Core/LoggerWrapper.h#4 $
//
// Library: JSCore
// Package: JSCore
// Module:  LoggerWrapper
//
// Definition of the LoggerWrapper interface.
//
// Copyright (c) 2013-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_Core_LoggerWrapper_INCLUDED
#define JS_Core_LoggerWrapper_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/Message.h"


namespace Poco {
namespace JS {
namespace Core {


class JSCore_API LoggerWrapper: public Wrapper
	/// JavaScript wrapper for Poco::Logger.
{
public:
	LoggerWrapper();
		/// Creates the LoggerWrapper for the root logger.
	
	~LoggerWrapper();
		/// Destroys the LoggerWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);
		
protected:
	static void log(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void format(int prio, const v8::FunctionCallbackInfo<v8::Value>& args, int firstArgIndex = 0, const std::string& prefix = "");
	static void trace(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void debug(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void information(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void notice(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void warning(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void error(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void critical(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void fatal(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void dump(const v8::FunctionCallbackInfo<v8::Value>& args);
	
	friend class ConsoleWrapper;
};


} } } // namespace Poco::JS::Core


#endif // JS_Core_LoggerWrapper_INCLUDED
