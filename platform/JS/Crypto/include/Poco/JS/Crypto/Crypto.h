//
// Crypto.h
//
// Library: JS/Crypto
// Package: Crypto
// Module:  Crypto
//
// Basic definitions for the Poco JS Crypto library.
// This file must be the first file included by every other Crypto
// header file.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Crypto_Crypto_INCLUDED
#define JS_Crypto_Crypto_INCLUDED


#include "Poco/JS/Core/Core.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the JSCrypto_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// JSCrypto_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(JSCrypto_EXPORTS)
		#define JSCrypto_API __declspec(dllexport)
	#else
		#define JSCrypto_API __declspec(dllimport)
	#endif
#endif


#if !defined(JSCrypto_API)
	#define JSCrypto_API
#endif


//
// Automatically link JSCrypto library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(JSCrypto_EXPORTS)
		#pragma comment(lib, "PocoJSCrypto" POCO_LIB_SUFFIX)
	#endif
#endif


#endif // JS_Crypto_Crypto_INCLUDED
