//
// WebTunnel.h
//
// Library: IoT/WebTunnel
// Package: WebTunnel
// Module:  WebTunnel
//
// Basic definitions for the IoT WebTunnel library.
// This file must be the first file included by every other WebTunnel
// header file.
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_WebTunnel_WebTunnel_INCLUDED
#define IoT_WebTunnel_WebTunnel_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTWebTunnel_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTWebTunnel_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTWebTunnel_EXPORTS)
		#define IoTWebTunnel_API __declspec(dllexport)
	#else
		#define IoTWebTunnel_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTWebTunnel_API)
	#define IoTWebTunnel_API
#endif


//
// Automatically link Devices library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTWebTunnel_EXPORTS)
		#pragma comment(lib, "IoTWebTunnel" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_WebTunnel_WebTunnel_INCLUDED
