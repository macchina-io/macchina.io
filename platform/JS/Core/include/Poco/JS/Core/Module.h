//
// Module.h
//
// Library: JS/Core
// Package: Execution
// Module:  Module
//
// Definition of the Module interface.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Core_Module_INCLUDED
#define JS_Core_Module_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "v8.h"


namespace Poco {
namespace JS {
namespace Core {


class JSCore_API Module: public Poco::RefCountedObject
	/// A JavaScript native module, implemented in C++.
{
public:
	using Ptr = Poco::AutoPtr<Module>;

	Module();
		/// Creates the Module.

	virtual ~Module();
		/// Destroys the Module.

	virtual v8::Local<v8::Object> exportIt(v8::Isolate* pIsolate) = 0;
		/// Creates a the JavaScript Object or Function this
		/// module exports.
		///
		/// A typical implementation uses a wrapper class to create a
		/// constructor function, and then exports that function:
		///
		///     v8::EscapableHandleScope handleScope(pIsolate);
		///     SomeWrapper someWrapper;
		///     v8::Local<v8::Function> ctor = someWrapper.constructor(pIsolate);
		///     return handleScope.escape(ctor);
};


} } } // namespace Poco::JS::Core


#endif // JS_Core_Module_INCLUDED
