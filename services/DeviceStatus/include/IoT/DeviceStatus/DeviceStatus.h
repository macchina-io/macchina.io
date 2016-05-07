//
// DeviceStatus.h
//
// $Id$
//
// Library: IoT/DeviceStatuss
// Package: DeviceStatus
// Module:  DeviceStatus
//
// Basic definitions for the IoT DeviceStatus library.
// This file must be the first file included by every other Core
// header file.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_DeviceStatus_DeviceStatus_INCLUDED
#define IoT_DeviceStatus_DeviceStatus_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTDeviceStatus_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTDeviceStatus_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTDeviceStatus_EXPORTS)
		#define IoTDeviceStatus_API __declspec(dllexport)
	#else
		#define IoTDeviceStatus_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTDeviceStatus_API)
	#define IoTDeviceStatus_API
#endif


//
// Automatically link Devices library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTDeviceStatus_EXPORTS)
		#pragma comment(lib, "IoTDeviceStatus" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_DeviceStatus_DeviceStatus_INCLUDED
