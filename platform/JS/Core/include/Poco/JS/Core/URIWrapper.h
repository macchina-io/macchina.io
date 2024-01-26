//
// URIWrapper.h
//
// Library: JS/Core
// Package: Wrappers
// Module:  URIWrapper
//
// Definition of the URIWrapper interface.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Core_URIWrapper_INCLUDED
#define JS_Core_URIWrapper_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"


namespace Poco {
namespace JS {
namespace Core {


class JSCore_API URIWrapper: public Wrapper
	/// JavaScript wrapper for Poco::AbstractURI.
{
public:
	URIWrapper();
		/// Creates the URIWrapper for the root logger.
	
	~URIWrapper();
		/// Destroys the URIWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);
		
protected:
	static void loadString(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void loadStringAsync(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void loadBuffer(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void loadBufferAsync(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::JS::Core


#endif // JS_Core_URIWrapper_INCLUDED
