//
// UnitsOfMeasure.h
//
// Library: IoT/UnitsOfMeasure
// Package: UnitsOfMeasure
// Module:  UnitsOfMeasure
//
// Basic definitions for the IoT UnitsOfMeasure library.
// This file must be the first file included by every other UnitsOfMeasure
// header file.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_UnitsOfMeasure_UnitsOfMeasure_INCLUDED
#define IoT_UnitsOfMeasure_UnitsOfMeasure_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTUnitsOfMeasure_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTUnitsOfMeasure_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTUnitsOfMeasure_EXPORTS)
		#define IoTUnitsOfMeasure_API __declspec(dllexport)
	#else
		#define IoTUnitsOfMeasure_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTUnitsOfMeasure_API)
	#define IoTUnitsOfMeasure_API
#endif


//
// Automatically link IoTUnitsOfMeasure library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTUnitsOfMeasure_EXPORTS)
		#pragma comment(lib, "IoTUnitsOfMeasure" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_UnitsOfMeasure_UnitsOfMeasure_INCLUDED
