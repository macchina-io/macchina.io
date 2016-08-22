//
// NetworkEnvironment.h
//
// $Id$
//
// Library: IoT/NetworkEnvironment
// Package: NetworkEnvironment
// Module:  NetworkEnvironment
//
// Basic definitions for the IoT NetworkEnvironment library.
// This file must be the first file included by every other NetworkEnvironment
// header file.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_NetworkEnvironment_NetworkEnvironment_INCLUDED
#define IoT_NetworkEnvironment_NetworkEnvironment_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the OSPNetEnv_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// OSPNetEnv_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTNetworkEnvironment_EXPORTS)
		#define IoTNetworkEnvironment_API __declspec(dllexport)
	#else
		#define IoTNetworkEnvironment_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTNetworkEnvironment_API)
	#define IoTNetworkEnvironment_API
#endif


//
// Automatically link IoTNetworkEnvironment library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTNetworkEnvironment_EXPORTS)
		#pragma comment(lib, "IoTNetworkEnvironment" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_NetworkEnvironment_NetworkEnvironment_INCLUDED
