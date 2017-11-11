//
// MobileConnection.h
//
// Library: IoT/MobileConnection
// Package: MobileConnection
// Module:  MobileConnection
//
// Basic definitions for the IoT MobileConnection library.
// This file must be the first file included by every other MobileConnection
// header file.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MobileConnection_MobileConnection_INCLUDED
#define IoT_MobileConnection_MobileConnection_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the OSPNetEnv_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTMobileConnection_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTMobileConnection_EXPORTS)
		#define IoTMobileConnection_API __declspec(dllexport)
	#else
		#define IoTMobileConnection_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTMobileConnection_API)
	#define IoTMobileConnection_API
#endif


//
// Automatically link IoTMobileConnection library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTMobileConnection_EXPORTS)
		#pragma comment(lib, "IoTMobileConnection" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_MobileConnection_MobileConnection_INCLUDED
