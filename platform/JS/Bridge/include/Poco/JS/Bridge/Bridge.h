//
// Bridge.h
//
// Library: JS/Bridge
// Package: Bridging
// Module:  Bridge
//
// Basic definitions for the Poco JS Bridge library.
// This file must be the first file included by every other Bridge
// header file.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Bridge_Bridge_INCLUDED
#define JS_Bridge_Bridge_INCLUDED


#include "Poco/JS/Core/Core.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the JSBridge_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// JSBridge_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(JSBridge_EXPORTS)
		#define JSBridge_API __declspec(dllexport)
	#else
		#define JSBridge_API __declspec(dllimport)
	#endif
#endif


#if !defined(JSBridge_API)
	#define JSBridge_API
#endif


//
// Automatically link JSBridge library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(JSBridge_EXPORTS)
		#pragma comment(lib, "PocoJSBridge" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // JS_Bridge_Bridge_INCLUDED
