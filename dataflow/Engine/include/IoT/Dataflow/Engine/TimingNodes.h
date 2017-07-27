//
// TimingNodes.h
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: LogicalNodes
// Module:  LogicalNodes
//
// Definition of timing node class templates.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Engine_TimingNodes_INCLUDED
#define IoT_Dataflow_Engine_TimingNodes_INCLUDED


#include "IoT/Dataflow/Engine/Node.h"
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTask.h"
#include <limits>
#include <cmath>


namespace IoT {
namespace Dataflow {
namespace Engine {


template <typename T>
class Stopwatch: public Node
{
public:
	typedef Poco::AutoPtr<Stopwatch> Ptr;
	
	Stopwatch(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		Node(id, attrs),
		_pEnable(new Inlet<bool>("enable")),
		_pStart(new Inlet<void>("start")),
		_pStop(new Inlet<void>("stop")),
		_pElapsed(new Outlet<T>("elapsed", scheduler))
	{
		addInlet(_pEnable);
		addInlet(_pStart);
		addInlet(_pStop);
		addOutlet(_pElapsed);
		
		_pEnable->updated += Poco::delegate(this, &Stopwatch::enable);
		_pStart->updated += Poco::delegate(this, &Stopwatch::start);
		_pStop->updated += Poco::delegate(this, &Stopwatch::stop);
	}
	
	void enable(const bool& flag)
	{
		if (flag)
			start();
		else
			stop();
	}
	
	void start()
	{
		_timestamp.update();
	}
	
	void stop()
	{
		_pElapsed->update(static_cast<T>(_timestamp.elapsed()));
	}
	
private:
	Inlet<bool>::Ptr _pEnable;
	Inlet<void>::Ptr _pStart;
	Inlet<void>::Ptr _pStop;
	typename Outlet<T>::Ptr _pElapsed;
	Poco::Timestamp _timestamp;
};


class IoTDataflowEngine_API AbstractClock: public Node
{
public:
	typedef Poco::AutoPtr<AbstractClock> Ptr;

	AbstractClock(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler);
		/// Creates the AbstractClock.
	
	~AbstractClock();
		/// Destroys the AbstractClock.
		
	void enable(const bool& flag);
		/// Handles the enable inlet.
		
	virtual void reset() = 0;
		/// Handles the reset inlet.

	virtual void tick() = 0;
		/// Advances the clock.

protected:	
	void startFlow();
	void stopFlow();

private:
	Scheduler& _scheduler;
	Inlet<bool>::Ptr _pEnable;
	Inlet<void>::Ptr _pReset;
	Inlet<double>::Ptr _pInterval;
	Outlet<void>::Ptr _pTick;
	SchedulerTask::Ptr _pTickTask;
};


template <typename T>
class Clock: public AbstractClock
{
public:
	typedef Poco::AutoPtr<Clock> Ptr;

	Clock(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
		AbstractClock(id, attrs, scheduler),
		_ticks(),
		_pTicks(new Outlet<T>("ticks", scheduler))
	{
		addOutlet(_pTicks);
	}
	
	void tick()
	{
		_ticks++;
		_pTicks->update(_ticks);
	}
	
	void reset()
	{
		_ticks = 0;
	}

private:
	T _ticks;
	typename Outlet<T>::Ptr _pTicks;
};


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Engine_TimingNodes_INCLUDED
