//
// XBee.h
//
// $Id$
//
// Library: IoT/XBee
// Package: XBee
// Module:  XBee
//
// Basic definitions for the IoT XBee library.
// This file must be the first file included by every other XBee
// header file.
//
// Copyright (c) 2013-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_XBee_XBee_INCLUDED
#define IoT_XBee_XBee_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTXBee_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTXBee_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTXBee_EXPORTS)
		#define IoTXBee_API __declspec(dllexport)
	#else
		#define IoTXBee_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTXBee_API)
	#define IoTXBee_API
#endif


//
// Automatically link IOZB library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTXBee_EXPORTS)
		#pragma comment(lib, "IoTXBee" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_XBee_XBee_INCLUDED
