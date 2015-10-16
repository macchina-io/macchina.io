//
// BtLE.h
//
// $Id$
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  BtLE
//
// Basic definitions for the IoT BtLE library.
// This file must be the first file included by every other BtLE
// header file.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_BtLE_INCLUDED
#define IoT_BtLE_BtLE_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTBtLE_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTBtLE_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTBtLE_EXPORTS)
		#define IoTBtLE_API __declspec(dllexport)
	#else
		#define IoTBtLE_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTBtLE_API)
	#define IoTBtLE_API
#endif


//
// Automatically link IOZB library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTBtLE_EXPORTS)
		#pragma comment(lib, "IoTBtLE" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_BtLE_BtLE_INCLUDED
