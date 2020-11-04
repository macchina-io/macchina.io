//
// JS.h
//
// Library: OSP/JS
// Package: JS
// Module:  JS
//
// Basic definitions for the Poco OSP JS library.
// This file must be the first file included by every other OSP JS
// header file.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JS_JS_INCLUDED
#define OSP_JS_JS_INCLUDED


#include "Poco/OSP/OSP.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the JSServer_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// JSServer_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(OSPJS_EXPORTS)
		#define OSPJS_API __declspec(dllexport)
	#else
		#define OSPJS_API __declspec(dllimport)
	#endif
#endif


#if !defined(OSPJS_API)
	#define OSPJS_API
#endif


//
// Automatically link OSP JS library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(OSPJS_EXPORTS)
		#pragma comment(lib, "PocoOSPJS" POCO_LIB_SUFFIX)
	#endif
#endif


// Turn off some annoying warnings
#if defined(_MSC_VER)
	#pragma warning(disable:4503) // decorated name length exceeded, name was truncated
#endif


#endif // OSP_JS_JS_INCLUDED
