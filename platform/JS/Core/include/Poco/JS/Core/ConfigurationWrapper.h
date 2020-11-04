//
// ConfigurationWrapper.h
//
// Library: JS/Core
// Package: Wrappers
// Module:  ConfigurationWrapper
//
// Definition of the ConfigurationWrapper interface.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Core_ConfigurationWrapper_INCLUDED
#define JS_Core_ConfigurationWrapper_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"


namespace Poco {
namespace JS {
namespace Core {


class JSCore_API ConfigurationWrapper: public Wrapper
	/// JavaScript wrapper for Poco::AbstractConfiguration.
{
public:
	ConfigurationWrapper();
		/// Creates the ConfigurationWrapper for the root logger.
	
	~ConfigurationWrapper();
		/// Destroys the ConfigurationWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);
		
protected:
	static void getInt(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getDouble(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getBool(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getObject(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void has(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void set(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void keys(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::JS::Core


#endif // JS_Core_ConfigurationWrapper_INCLUDED
