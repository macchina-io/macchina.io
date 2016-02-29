//
// TCP.h
//
// $Id: //poco/1.7/RemotingNG/TCP/include/Poco/RemotingNG/TCP/TCP.h#1 $
//
// Library: RemotingNG/TCP
// Package: TCP
// Module:  TCP
//
// Basic definitions for the RemotingNG TCP library.
// This file must be the first file included by every other TCP
// header file.
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemotingNG_TCP_TCP_INCLUDED
#define RemotingNG_TCP_TCP_INCLUDED


#include "Poco/Foundation.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the RemotingNGTCP_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// RemotingNGTCP_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(RemotingNGTCP_EXPORTS)
		#define RemotingNGTCP_API __declspec(dllexport)
	#else
		#define RemotingNGTCP_API __declspec(dllimport)
	#endif
#endif


#if !defined(RemotingNGTCP_API)
	#define RemotingNGTCP_API
#endif


//
// Automatically link RemotingNGTCP library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(RemotingNGTCP_EXPORTS)
		#pragma comment(lib, "PocoRemotingNGTCP" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // RemotingNG_TCP_TCP_INCLUDED
