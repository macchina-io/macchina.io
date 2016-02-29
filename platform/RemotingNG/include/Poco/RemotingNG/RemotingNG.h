//
// RemotingNG.h
//
// $Id: //poco/1.7/RemotingNG/include/Poco/RemotingNG/RemotingNG.h#1 $
//
// Library: RemotingNG
// Package: RemotingNG
// Module:  RemotingNG
//
// Basic definitions for the Applied Informatics RemotingNG library.
// This file must be the first file included by every other RemotingNG
// header file.
//
// Copyright (c) 2006-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef RemotingNG_RemotingNG_INCLUDED
#define RemotingNG_RemotingNG_INCLUDED


#include "Poco/Foundation.h"


//
// The following block is the standard way of creating macros which make exporting
// from a DLL simpler. All files within this DLL are compiled with the RemotingNG_EXPORTS
// symbol defined on the command line. this symbol should not be defined on any project
// that uses this DLL. This way any other project whose source files include this file see
// RemotingNG_API functions as being imported from a DLL, wheras this DLL sees symbols
// defined with this macro as being exported.
//
#if defined(_WIN32) && defined(POCO_DLL)
	#if defined(RemotingNG_EXPORTS)
		#define RemotingNG_API __declspec(dllexport)
	#else
		#define RemotingNG_API __declspec(dllimport)
	#endif
#endif


#if !defined(RemotingNG_API)
	#define RemotingNG_API
#endif


#if defined(_WIN32)
#pragma warning(disable: 4503) // decorated name length exceeded, name was truncated.
#endif


//
// Automatically link RemotingNG library.
//
#if defined(_MSC_VER)
	#if !defined(POCO_NO_AUTOMATIC_LIBS) && !defined(RemotingNG_EXPORTS)
		#pragma comment(lib, "PocoRemotingNG" POCO_LIB_SUFFIX)
	#endif
#endif


//
// StaticInitGuard
//
// Generated serializers, deserializers and other classes use
// static local variables. On some compilers, most notably,
// Visual C++, initialization of static locals is not threadsafe.
// Note that C++11 requires that compilers make this threadsafe,
// so eventually this hack can go away.
//
// Following helper class and macros wrap the static declarations
// in code making it thread safe.
//


#if !defined(POCO_LOCAL_STATIC_INIT_IS_THREADSAFE)


#include "Poco/Mutex.h"


namespace Poco {
namespace RemotingNG {


class RemotingNG_API StaticInitGuard
{
public:
	StaticInitGuard():
		_pMutex(&_mutex)
	{
		_mutex.lock();
	}
	
	~StaticInitGuard()
	{
		try
		{
			release();
		}
		catch (...)
		{
			poco_unexpected();
		}
	}
	
	void release()
	{
		if (_pMutex)
		{
			_pMutex->unlock();
			_pMutex = 0;
		}
	}
	
private:
	StaticInitGuard(const StaticInitGuard&);
	StaticInitGuard& operator = (const StaticInitGuard&);

	Poco::FastMutex* _pMutex;
	static Poco::FastMutex _mutex;
};


} } // namespace Poco::RemotingNG


#define remoting__staticInitBegin(var) Poco::RemotingNG::StaticInitGuard var##__GUARD
#define remoting__staticInitEnd(var) var##__GUARD.release()


#else // local static initialization is thread safe


#define remoting__staticInitBegin(var)
#define remoting__staticInitEnd(var)


#endif // !defined(POCO_LOCAL_STATIC_INIT_IS_THREADSAFE)


#endif // RemotingNG_RemotingNG_INCLUDED
