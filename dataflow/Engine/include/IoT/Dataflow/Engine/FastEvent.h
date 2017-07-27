//
// FastEvent.h
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: FastEvent
// Module:  FastEvent
//
// Definition of the FastEvent class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Engine_FastEvent_INCLUDED
#define IoT_Dataflow_Engine_FastEvent_INCLUDED


#include "IoT/Dataflow/Engine/Engine.h"
#include "Poco/AbstractDelegate.h"
#include "Poco/DefaultStrategy.h"
#include "Poco/Delegate.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


template <typename T>
class FastEvent
	/// FastEvent is a variant of Poco::BasicEvent optimized
	/// for performance. FastEvent is intended for use
	/// in single-threaded scenarios only.
{
public:
	typedef T TArgs;
	typedef Poco::AbstractDelegate<TArgs> TDelegate;
	typedef Poco::DefaultStrategy<TArgs, TDelegate> TStrategy;

	FastEvent()
	{
	}
	
	~FastEvent()
	{
	}

	void operator += (const TDelegate& aDelegate)
	{
		_strategy.add(aDelegate);
	}
	
	void operator -= (const TDelegate& aDelegate)
	{
		_strategy.remove(aDelegate);
	}
	
	void operator () (const void* pSender, TArgs& args)
	{
		_strategy.notify(pSender, args);
	}

private:
	FastEvent(const FastEvent&);
	FastEvent& operator = (const FastEvent&);

	TStrategy _strategy;
};


template <>
class FastEvent<void>
{
public:
	typedef Poco::AbstractDelegate<void> TDelegate;
	typedef Poco::DefaultStrategy<void, TDelegate> TStrategy;

	FastEvent()
	{
	}
	
	~FastEvent()
	{
	}

	void operator += (const TDelegate& aDelegate)
	{
		_strategy.add(aDelegate);
	}
	
	void operator -= (const TDelegate& aDelegate)
	{
		_strategy.remove(aDelegate);
	}
	
	void operator () (const void* pSender)
	{
		_strategy.notify(pSender);
	}

private:
	FastEvent(const FastEvent&);
	FastEvent& operator = (const FastEvent&);

	TStrategy _strategy;
};


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Engine_FastEvent_INCLUDED
