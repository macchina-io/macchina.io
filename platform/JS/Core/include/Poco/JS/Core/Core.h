//
// Core.h
//
// Library: JS/Core
// Package: Core
// Module:  Core
//
// Basic definitions for the Poco JS Core library.
// This file must be the first file included by every other Core
// header file.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_Core_Core_INCLUDED
#define JS_Core_Core_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the JSCore_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// JSCore_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(JSCore_EXPORTS)
		#define JSCore_API __declspec(dllexport)
	#else
		#define JSCore_API __declspec(dllimport)
	#endif
#endif


#if !defined(JSCore_API)
	#define JSCore_API
#endif


//
// Automatically link JSCore library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(JSCore_EXPORTS)
		#pragma comment(lib, "PocoJSCore" POCO_LIB_SUFFIX)
	#endif
#endif


namespace Poco {
namespace JS {
namespace Core {


void JSCore_API initialize();
	/// Initializes the JavaScript engine.


void JSCore_API uninitialize();
	/// Uninitialize the JavaScript engine.
	

} } } // namespace Poco::JS::Core


#endif // JS_Core_Core_INCLUDED
