//
// WebEvent.h
//
// Library: OSP/WebEvent
// Package: WebEvent
// Module:  WebEvent
//
// Basic definitions for the Poco OSP WebEvent library.
// This file must be the first file included by every other OSP WebEvent
// header file.
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_WebEvent_WebEvent_INCLUDED
#define OSP_WebEvent_WebEvent_INCLUDED


#include "Poco/OSP/OSP.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the WebEvent_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// WebEvent_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(OSPWebEvent_EXPORTS)
		#define OSPWebEvent_API __declspec(dllexport)
	#else
		#define OSPWebEvent_API __declspec(dllimport)
	#endif
#endif


#if !defined(OSPWebEvent_API)
	#define OSPWebEvent_API
#endif


//
// Automatically link OSP WebEvent library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(OSPWebEvent_EXPORTS)
		#pragma comment(lib, "PocoOSPWebEvent" POCO_LIB_SUFFIX)
	#endif
#endif


// Turn off some annoying warnings
#if defined(_MSC_VER)
	#pragma warning(disable:4503) // decorated name length exceeded, name was truncated
#endif


#endif // OSP_WebEvent_WebEvent_INCLUDED
