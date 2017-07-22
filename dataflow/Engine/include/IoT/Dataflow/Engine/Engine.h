//
// Engine.h
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: Engine
// Module:  Engine
//
// Basic definitions for the IoT Dataflow library.
// This file must be the first file included by every other Dataflow
// header file.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Engine_Engine_INCLUDED
#define IoT_Dataflow_Engine_Engine_INCLUDED


#include "Poco/Poco.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the IoTDataflowEngine_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// IoTDataflowEngine_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(IoTDataflowEngine_EXPORTS)
		#define IoTDataflowEngine_API __declspec(dllexport)
	#else
		#define IoTDataflowEngine_API __declspec(dllimport)
	#endif
#endif


#if !defined(IoTDataflowEngine_API)
	#define IoTDataflowEngine_API
#endif


//
// Automatically link IoTDataflowEngine library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(IoTDataflowEngine_EXPORTS)
		#pragma comment(lib, "IoTDataflowEngine" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // IoT_Dataflow_Engine_Engine_INCLUDED
