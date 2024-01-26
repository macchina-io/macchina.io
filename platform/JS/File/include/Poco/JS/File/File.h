//
// File.h
//
// Library: JS/File
// Package: File
// Module:  File
//
// Basic definitions for the Poco JS File library.
// This file must be the first file included by every other File
// header file.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_File_File_INCLUDED
#define JS_File_File_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the JSFile_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// JSFile_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(JSFile_EXPORTS)
		#define JSFile_API __declspec(dllexport)
	#else
		#define JSFile_API __declspec(dllimport)
	#endif
#endif


#if !defined(JSFile_API)
	#define JSFile_API
#endif


//
// Automatically link JSFile library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(JSFile_EXPORTS)
		#pragma comment(lib, "PocoJSFile" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // JS_File_File_INCLUDED
