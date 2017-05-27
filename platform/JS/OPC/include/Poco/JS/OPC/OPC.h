//
// OPC.h
//
// $Id: //poco/1.4/JS/OPC/include/Poco/JS/OPC/OPC.h#3 $
//
// Library: JS/OPC
// Package: OPC
// Module:  OPC
//
// Basic definitions for the Poco JS OPC library.
// This file must be the first file included by every other OPC
// header file.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_OPC_OPC_INCLUDED
#define JS_OPC_OPC_INCLUDED


#include "Poco/JS/Core/Core.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the JSOPC_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// JSOPC_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(JSOPC_EXPORTS)
		#define JSOPC_API __declspec(dllexport)
	#else
		#define JSOPC_API __declspec(dllimport)
	#endif
#endif


#if !defined(JSOPC_API)
	#define JSOPC_API
#endif


//
// Automatically link JSOPC library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(JSOPC_EXPORTS)
		#pragma comment(lib, "PocoJSOPC" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // JS_OPC_OPC_INCLUDED
