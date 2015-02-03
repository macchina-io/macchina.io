//
// Devices.h
//
// $Id: //iot/Main/Devices/include/IoT/Devices/Devices.h#2 $
//
// Library: IoT/Devices
// Package: Devices
// Module:  Devices
//
// Basic definitions for the IoT Devices library.
// This file must be the first file included by every other Core
// header file.
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_Devices_INCLUDED
#define IoT_Devices_Devices_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTDevices_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTDevices_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTDevices_EXPORTS)
		#define IoTDevices_API __declspec(dllexport)
	#else
		#define IoTDevices_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTDevices_API)
	#define IoTDevices_API
#endif


//
// Automatically link Devices library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTDevices_EXPORTS)
		#pragma comment(lib, "IoTDevices" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_Devices_Devices_INCLUDED
