//
// Runner.h
//
// $Id$
//
// Library: IoT/Dataflow/Runner
// Package: Dataflow
// Module:  Dataflow
//
// Basic definitions for the IoT Dataflow Runner Parser library.
// This file must be the first file included by every other Dataflow
// Runner Parser header file.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Runner_Runner_INCLUDED
#define IoT_Dataflow_Runner_Runner_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTDataflowRunner_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTDataflowRunner_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTDataflowRunner_EXPORTS)
		#define IoTDataflowRunner_API __declspec(dllexport)
	#else
		#define IoTDataflowRunner_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTDataflowRunner_API)
	#define IoTDataflowRunner_API
#endif


//
// Automatically link IoTDataflowEngine library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTDataflowRunner_EXPORTS)
		#pragma comment(lib, "IoTDataflowRunner" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_Dataflow_Runner_Runner_INCLUDED
