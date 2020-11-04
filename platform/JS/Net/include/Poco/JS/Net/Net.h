//
// Net.h
//
// Library: JS/Net
// Package: Net
// Module:  Net
//
// Basic definitions for the Poco JS Net library.
// This file must be the first file included by every other Net
// header file.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Net_Net_INCLUDED
#define JS_Net_Net_INCLUDED


#include "Poco/JS/Core/Core.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the JSNet_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// JSNet_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(JSNet_EXPORTS)
		#define JSNet_API __declspec(dllexport)
	#else
		#define JSNet_API __declspec(dllimport)
	#endif
#endif


#if !defined(JSNet_API)
	#define JSNet_API
#endif


//
// Automatically link JSNet library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(JSNet_EXPORTS)
		#pragma comment(lib, "PocoJSNet" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // JS_Net_Net_INCLUDED
