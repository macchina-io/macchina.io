//
// Tf.h
//
// $Id: //iot/Main/Tf/include/IoT/Tf/Tf.h#2 $
//
// Library: Tf
// Package: Tf
// Module:  Tf
//
// Basic definitions for the IoT Tinkerforge library.
// This file must be the first file included by every other Core
// header file.
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Tf_Tf_INCLUDED
#define IoT_Tf_Tf_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTTf_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTTf_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTTf_EXPORTS)
		#define IoTTf_API __declspec(dllexport)
	#else
		#define IoTTf_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTTf_API)
	#define IoTTf_API
#endif


//
// Automatically link Tf library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTTf_EXPORTS)
		#pragma comment(lib, "IoTTf" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_Tf_Tf_INCLUDED
