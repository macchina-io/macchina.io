//
// OPC.h
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  OPC
//
// Basic definitions for the Poco OPC library.
// This file must be the first file included by every other OPC
// header file.
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef OPC_OPC_INCLUDED
#define OPC_OPC_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the OPC_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// OPC_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(OPC_EXPORTS)
		#define OPC_API __declspec(dllexport)
	#else
		#define OPC_API __declspec(dllimport)
	#endif
#endif


#if !defined(OPC_API)
	#define OPC_API
#endif


//
// Automatically link OPC library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(OPC_EXPORTS)
		#pragma comment(lib, "PocoOPC" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // OPC_OPC_INCLUDED
