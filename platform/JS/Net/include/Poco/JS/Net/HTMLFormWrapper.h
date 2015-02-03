//
// HTMLFormWrapper.h
//
// $Id: //poco/1.4/JS/Net/include/Poco/JS/Net/HTMLFormWrapper.h#3 $
//
// Library: JSNet
// Package: HTTP
// Module:  HTMLFormWrapper
//
// Definition of the HTMLFormWrapper interface.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_Net_HTMLFormWrapper_INCLUDED
#define JS_Net_HTMLFormWrapper_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/Net/HTMLForm.h"


namespace Poco {
namespace JS {
namespace Net {


class JSCore_API HTMLFormWrapper: public JS::Core::Wrapper
	/// JavaScript wrapper for Poco::HTMLForm.
{
public:
	HTMLFormWrapper();
		/// Creates the HTMLFormWrapper for the root logger.
	
	~HTMLFormWrapper();
		/// Destroys the HTMLFormWrapper.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);
		
protected:
	static void hasField(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void getField(const v8::FunctionCallbackInfo<v8::Value>& args);
};


} } } // namespace Poco::JS::Net


#endif // JS_Net_HTMLFormWrapper_INCLUDED
