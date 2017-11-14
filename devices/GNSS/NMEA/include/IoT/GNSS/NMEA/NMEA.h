//
// NMEA.h
//
// Library: IoT/GNSS/NMEA
// Package: NMEA
// Module:  NMEA
//
// Basic definitions for the IoT GNSS NMEA library.
// This file must be the first file included by every other NMEA
// header file.
//
// Copyright (c) 2010-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef NMEA_NMEA_INCLUDED
#define NMEA_NMEA_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the NMEA_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// NMEA_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(NMEA_EXPORTS)
		#define NMEA_API __declspec(dllexport)
	#else
		#define NMEA_API __declspec(dllimport)
	#endif
#endif


#if !defined(NMEA_API)
	#define NMEA_API
#endif


//
// Automatically link NMEA library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(NMEA_EXPORTS)
		#pragma comment(lib, "IoTGNSSNMEA" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // NMEA_NMEA_INCLUDED
