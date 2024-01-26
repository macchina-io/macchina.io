//
// Datapoints.h
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  Datapoints
//
// Basic definitions for the IoT Datapoints library.
// This file must be the first file included by every other Core
// header file.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_Datapoints_INCLUDED
#define IoT_Datapoints_Datapoints_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTDatapoints_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTDatapoints_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTDatapoints_EXPORTS)
		#define IoTDatapoints_API __declspec(dllexport)
	#else
		#define IoTDatapoints_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTDatapoints_API)
	#define IoTDatapoints_API
#endif


//
// Automatically link Datapoints library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTDatapoints_EXPORTS)
		#pragma comment(lib, "IoTDatapoints" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_Datapoints_Datapoints_INCLUDED
