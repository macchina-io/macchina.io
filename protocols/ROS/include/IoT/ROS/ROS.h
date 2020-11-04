//
// ROS.h
//
// Library: IoT/ROS
// Package: ROS
// Module:  ROS
//
// Basic definitions for the IoT ROS library.
// This file must be the first file included by every other ROS
// header file.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_ROS_ROS_INCLUDED
#define IoT_ROS_ROS_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTROS_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTROS_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTROS_EXPORTS)
		#define IoTROS_API __declspec(dllexport)
	#else
		#define IoTROS_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTROS_API)
	#define IoTROS_API
#endif


//
// Automatically link Devices library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTROS_EXPORTS)
		#pragma comment(lib, "IoTROS" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_ROS_ROS_INCLUDED
