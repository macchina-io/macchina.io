//
// MQTT.h
//
// $Id$
//
// Library: IoT/MQTT
// Package: MQTT
// Module:  MQTT
//
// Basic definitions for the IoT MQTT library.
// This file must be the first file included by every other MQTT
// header file.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MQTT_MQTT_INCLUDED
#define IoT_MQTT_MQTT_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTMQTT_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTMQTT_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTMQTT_EXPORTS)
		#define IoTMQTT_API __declspec(dllexport)
	#else
		#define IoTMQTT_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTMQTT_API)
	#define IoTMQTT_API
#endif


//
// Automatically link Devices library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTMQTT_EXPORTS)
		#pragma comment(lib, "IoTMQTT" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_MQTT_MQTT_INCLUDED
