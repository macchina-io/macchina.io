//
// TimingNodes.cpp
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: LogicalNodes
// Module:  LogicalNodes
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Engine/TimingNodes.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


class TickTask: public SchedulerTask
{
public:
	TickTask(AbstractClock& clock):
		_clock(clock)
	{
	}
	
	void run()
	{
		_clock.tick();
	}
	
private:
	AbstractClock& _clock;
};


AbstractClock::AbstractClock(const std::string& id, const AttributedObject& attrs, Scheduler& scheduler):
	Node(id, attrs),
	_scheduler(scheduler),
	_pEnable(new Inlet<bool>("enable", attrs.getBoolAttribute("enable", false))),
	_pReset(new Inlet<void>("reset")),
	_pInterval(new Inlet<double>("interval", attrs.getAttribute<double>("interval", 0))),
	_pTick(new Outlet<void>("tick", scheduler))
{
	addInlet(_pEnable);
	addInlet(_pReset);
	addInlet(_pInterval);
	addOutlet(_pTick);

	_pEnable->updated += Poco::delegate(this, &AbstractClock::enable);
	_pReset->updated += Poco::delegate(this, &AbstractClock::reset);
	
	_scheduler.started += Poco::delegate(this, &AbstractClock::startFlow);
	_scheduler.stopped += Poco::delegate(this, &AbstractClock::stopFlow);
}


AbstractClock::~AbstractClock()
{
	_scheduler.started -= Poco::delegate(this, &AbstractClock::startFlow);
	_scheduler.stopped -= Poco::delegate(this, &AbstractClock::stopFlow);
}


void AbstractClock::enable(const bool& flag)
{
	if (flag && !_pTickTask)
	{
		_pTickTask = new TickTask(*this);
		_scheduler.scheduleAtFixedRate(_pTickTask, 0, _pInterval->value());
	}
	else if (!flag && _pTickTask)
	{
		_pTickTask->cancel();
		_pTickTask = 0;
	}
}


void AbstractClock::startFlow()
{
	enable(_pEnable->value());
}


void AbstractClock::stopFlow()
{
	enable(false);
}


} } } // namespace IoT::Dataflow::Engine
