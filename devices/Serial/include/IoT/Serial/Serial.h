//
// Serial.h
//
// $Id: //poco/1.4/IO/Serial/include/Poco/IO/Serial/Serial.h#1 $
//
// Library: IoT/Serial
// Package: Serial
// Module:  Serial
//
// Basic definitions for the IoT Serial library.
// This file must be the first file included by every other Serial
// header file.
//
// Copyright (c) 2013-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Serial_Serial_INCLUDED
#define IoT_Serial_Serial_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTSerial_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTSerial_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTSerial_EXPORTS)
		#define IoTSerial_API __declspec(dllexport)
	#else
		#define IoTSerial_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTSerial_API)
	#define IoTSerial_API
#endif


//
// Automatically link IOSerial library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTSerial_EXPORTS)
		#pragma comment(lib, "IoTSerial" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_Serial_Serial_INCLUDED
