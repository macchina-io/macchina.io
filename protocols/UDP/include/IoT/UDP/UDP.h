//
// UDP.h
//
// $Id$
//
// Library: IoT/UDP
// Package: UDP
// Module:  UDP
//
// Basic definitions for the IoT UDP library.
// This file must be the first file included by every other UDP
// header file.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_UDP_UDP_INCLUDED
#define IoT_UDP_UDP_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTUDP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTUDP_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTUDP_EXPORTS)
		#define IoTUDP_API __declspec(dllexport)
	#else
		#define IoTUDP_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTUDP_API)
	#define IoTUDP_API
#endif


//
// Automatically link IoTUDP library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTUDP_EXPORTS)
		#pragma comment(lib, "IoTUDP" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_UDP_UDP_INCLUDED
