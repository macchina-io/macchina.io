//
// Settings.h
//
// Library: IoT/Settings
// Package: Settings
// Module:  Settings
//
// Basic definitions for the IoT Settings library.
// This file must be the first file included by every other Settings
// header file.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Settings_Settings_INCLUDED
#define IoT_Settings_Settings_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTSettings_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTSettings_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTSettings_EXPORTS)
		#define IoTSettings_API __declspec(dllexport)
	#else
		#define IoTSettings_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTSettings_API)
	#define IoTSettings_API
#endif


//
// Automatically link IoTSettings library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTSettings_EXPORTS)
		#pragma comment(lib, "IoTSettings" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_Settings_Settings_INCLUDED
