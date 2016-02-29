//
// CodeGeneration.h
//
// $Id: //poco/1.7/CodeGeneration/include/Poco/CodeGeneration/CodeGeneration.h#1 $
//
// Library: CodeGeneration
// Package: CodeGeneration
// Module:  CodeGeneration
//
// Basic definitions for the Poco CodeGeneration library.
// This file must be the first file included by every other CodeGeneration
// header file.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef CodeGeneration_CodeGeneration_INCLUDED
#define CodeGeneration_CodeGeneration_INCLUDED


#ifndef Foundation_Foundation_INCLUDED
#include "Poco/Foundation.h"
#endif


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the CodeGeneration_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// CodeGeneration_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(CodeGeneration_EXPORTS)
		#define CodeGeneration_API __declspec(dllexport)
	#else
		#define CodeGeneration_API __declspec(dllimport)
	#endif
#endif


#if !defined(CodeGeneration_API)
	#define CodeGeneration_API
#endif


//
// Automatically link CodeGeneration library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(CodeGeneration_EXPORTS)
		#pragma comment(lib, "PocoCodeGeneration" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // CodeGeneration_CodeGeneration_INCLUDED
