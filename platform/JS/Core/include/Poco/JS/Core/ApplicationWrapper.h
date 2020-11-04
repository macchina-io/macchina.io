//
// ApplicationWrapper.h
//
// Library: JS/Core
// Package: Wrappers
// Module:  ApplicationWrapper
//
// Definition of the ApplicationWrapper interface.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Core_ApplicationWrapper_INCLUDED
#define JS_Core_ApplicationWrapper_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"


namespace Poco {
namespace JS {
namespace Core {


class JSCore_API ApplicationWrapper: public Wrapper
	/// JavaScript wrapper for Poco::Environment.
{
public:
	ApplicationWrapper();
		/// Creates the ApplicationWrapper.
	
	~ApplicationWrapper();
		/// Destroys the ApplicationWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);
		
protected:
	static void name(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void startTime(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void uptime(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void config(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void logger(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
};


} } } // namespace Poco::JS::Core


#endif // JS_Core_ApplicationWrapper_INCLUDED
