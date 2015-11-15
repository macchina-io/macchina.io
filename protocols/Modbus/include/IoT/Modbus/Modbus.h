//
// Modbus.h
//
// $Id$
//
// Library: IoT/Modbus
// Package: Modbus
// Module:  Modbus
//
// Basic definitions for the IoT Modbus library.
// This file must be the first file included by every other Modbus
// header file.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Modbus_Modbus_INCLUDED
#define IoT_Modbus_Modbus_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTModbus_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTModbus_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTModbus_EXPORTS)
		#define IoTModbus_API __declspec(dllexport)
	#else
		#define IoTModbus_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTModbus_API)
	#define IoTModbus_API
#endif


//
// Automatically link IOZB library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTModbus_EXPORTS)
		#pragma comment(lib, "IoTModbus" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_Modbus_Modbus_INCLUDED
