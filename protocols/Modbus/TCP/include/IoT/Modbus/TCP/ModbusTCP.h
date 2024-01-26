//
// ModbusTCP.h
//
// Library: IoT/Modbus/TCP
// Package: TCP
// Module:  ModbusTCP
//
// Basic definitions for the IoT Modbus TCP library.
// This file must be the first file included by every other Modbus
// TCP header file.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Modbus_TCP_ModbusTCP_INCLUDED
#define IoT_Modbus_TCP_ModbusTCP_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTModbusTCP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTModbusTCP_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTModbusTCP_EXPORTS)
		#define IoTModbusTCP_API __declspec(dllexport)
	#else
		#define IoTModbusTCP_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTModbusTCP_API)
	#define IoTModbusTCP_API
#endif


//
// Automatically link IoTModbusTCP library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTModbusTCP_EXPORTS)
		#pragma comment(lib, "IoTModbusTCP" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_Modbus_TCP_ModbusTCP_INCLUDED
