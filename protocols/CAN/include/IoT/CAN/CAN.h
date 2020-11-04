//
// CAN.h
//
// Library: IoT/CAN
// Package: CAN
// Module:  CAN
//
// Basic definitions for the IoT CAN library.
// This file must be the first file included by every other CAN
// header file.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_CAN_CAN_INCLUDED
#define IoT_CAN_CAN_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTCAN_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTCAN_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTCAN_EXPORTS)
		#define IoTCAN_API __declspec(dllexport)
	#else
		#define IoTCAN_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTCAN_API)
	#define IoTCAN_API
#endif


//
// Automatically link IoTCAN library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTCAN_EXPORTS)
		#pragma comment(lib, "IoTCAN" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_CAN_CAN_INCLUDED
