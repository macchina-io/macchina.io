//
// TimerWrapper.h
//
// Library: JS/Core
// Package: Wrappers
// Module:  TimerWrapper
//
// Definition of the TimerWrapper interface.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Core_TimerWrapper_INCLUDED
#define JS_Core_TimerWrapper_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"


namespace Poco {
namespace JS {
namespace Core {


class JSCore_API TimerWrapper: public Poco::JS::Core::Wrapper
	/// JavaScript wrapper for TimedJSExecutor-based timers.
{
public:
	TimerWrapper();
		/// Creates the TimerWrapper.
	
	~TimerWrapper();
		/// Destroys the TimerWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);
		
protected:
	static void cancel(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void cancelled(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);

	friend class TimedJSExecutor;
};


} } } // namespace Poco::JS::Core


#endif // JS_Core_TimerWrapper_INCLUDED
