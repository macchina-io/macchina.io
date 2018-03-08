//
// WebTunnel.h
//
// Library: WebTunnel
// Package: WebTunnel
// Module:  WebTunnel
//
// Basic definitions for the Poco WebTunnel library.
// This file must be the first file included by every other WebTunnel
// header file.
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef WebTunnel_WebTunnel_INCLUDED
#define WebTunnel_WebTunnel_INCLUDED


#include "Poco/Net/Net.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the WebTunnel_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// WebTunnel_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(WebTunnel_EXPORTS)
		#define WebTunnel_API __declspec(dllexport)
	#else
		#define WebTunnel_API __declspec(dllimport)
	#endif
#endif


#if !defined(WebTunnel_API)
	#define WebTunnel_API
#endif


//
// Automatically link WebTunnel library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(WebTunnel_EXPORTS)
		#pragma comment(lib, "PocoWebTunnel" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // WebTunnel_WebTunnel_INCLUDED
