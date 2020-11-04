//
// Data.h
//
// Library: JS/Data
// Package: Data
// Module:  Data
//
// Basic definitions for the Poco JS Data library.
// This file must be the first file included by every other Data
// header file.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Data_Data_INCLUDED
#define JS_Data_Data_INCLUDED


#include "Poco/JS/Core/Core.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the JSData_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// JSData_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(JSData_EXPORTS)
		#define JSData_API __declspec(dllexport)
	#else
		#define JSData_API __declspec(dllimport)
	#endif
#endif


#if !defined(JSData_API)
	#define JSData_API
#endif


//
// Automatically link JSData library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(JSData_EXPORTS)
		#pragma comment(lib, "PocoJSData" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // JS_Data_Data_INCLUDED
