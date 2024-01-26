//
// SystemWrapper.h
//
// Library: JS/Core
// Package: Wrappers
// Module:  SystemWrapper
//
// Definition of the SystemWrapper interface.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Core_SystemWrapper_INCLUDED
#define JS_Core_SystemWrapper_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"


namespace Poco {
namespace JS {
namespace Core {


class JSCore_API SystemWrapper: public Wrapper
	/// JavaScript wrapper for Poco::Environment.
{
public:
	SystemWrapper();
		/// Creates the SystemWrapper.
	
	~SystemWrapper();
		/// Destroys the SystemWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);
		
protected:
	static void exec(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void execAsync(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void sleep(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void get(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void has(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void set(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void osName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void osDisplayName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void osVersion(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void osArchitecture(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void nodeName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void nodeId(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void processorCount(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void clock(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
};


} } } // namespace Poco::JS::Core


#endif // JS_Core_SystemWrapper_INCLUDED
