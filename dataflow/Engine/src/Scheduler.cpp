//
// Scheduler.cpp
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: Scheduler
// Module:  Scheduler
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Dataflow/Engine/Scheduler.h"
#include "Poco/ErrorHandler.h"
#include "Poco/Exception.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


SchedulerTask::SchedulerTask():
	_isCancelled(false)
{
}


SchedulerTask::~SchedulerTask()
{
}


void SchedulerTask::cancel()
{
	_isCancelled = true;
}


class SchedulerNotification: public Poco::Notification
{
public:
	SchedulerNotification(Poco::TimedNotificationQueue& queue):
		_queue(queue)
	{
	}
	
	~SchedulerNotification()
	{
	}
	
	virtual bool execute() = 0;
	
	Poco::TimedNotificationQueue& queue()
	{
		return _queue;
	}
	
private:
	Poco::TimedNotificationQueue& _queue;
};


class StopNotification: public SchedulerNotification
{
public:
	StopNotification(Poco::TimedNotificationQueue& queue):
		SchedulerNotification(queue)
	{
	}
	
	~StopNotification()
	{
	}
	
	bool execute()
	{
		queue().clear();
		return false;
	}
};


class CancelNotification: public SchedulerNotification
{
public:
	CancelNotification(Poco::TimedNotificationQueue& queue):
		SchedulerNotification(queue)
	{
	}
	
	~CancelNotification()
	{
	}
	
	bool execute()
	{
		queue().clear();
		_finished.set();
		return true;
	}
	
	void wait()
	{
		_finished.wait();
	}
	
private:
	Poco::Event _finished;
};


class TaskNotification: public SchedulerNotification
{
public:
	TaskNotification(Poco::TimedNotificationQueue& queue, SchedulerTask::Ptr pTask):
		SchedulerNotification(queue),
		_pTask(pTask)
	{
	}
	
	~TaskNotification()
	{
	}
	
	SchedulerTask::Ptr task()
	{
		return _pTask;	
	}
	
	bool execute()
	{
		if (!_pTask->isCancelled())
		{
			try
			{
				_pTask->run();
			}
			catch (Poco::Exception& exc)
			{
				Poco::ErrorHandler::handle(exc);
			}
			catch (std::exception& exc)
			{
				Poco::ErrorHandler::handle(exc);
			}
			catch (...)
			{
				Poco::ErrorHandler::handle();
			}
		}
		return true;
	}
			
private:
	SchedulerTask::Ptr _pTask;
};


class FixedRateTaskNotification: public TaskNotification
{
public:
	FixedRateTaskNotification(Poco::TimedNotificationQueue& queue, SchedulerTask::Ptr pTask, long interval, Poco::Clock clock):
		TaskNotification(queue, pTask),
		_interval(interval),
		_nextExecution(clock)
	{
	}
	
	~FixedRateTaskNotification()
	{
	}
	
	bool execute()
	{	
		TaskNotification::execute();

		if (!task()->isCancelled())
		{
			Poco::Clock now;
			_nextExecution += static_cast<Poco::Clock::ClockDiff>(_interval)*1000;
			if (_nextExecution < now) _nextExecution = now;
			queue().enqueueNotification(this, _nextExecution);
			duplicate();
		}
		return true;			
	}
	
private:
	long _interval;
	Poco::Clock _nextExecution;
};


Scheduler::Scheduler()
{
}


Scheduler::~Scheduler()
{
	try
	{
		stop();
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void Scheduler::start()
{
	if (_thread.isRunning()) throw Poco::IllegalStateException("Scheduler is already running");

	_thread.start(*this);
	
	started(this);
}


void Scheduler::stop()
{
	if (_thread.isRunning())
	{
		stopped(this);
	
		_queue.enqueueNotification(new StopNotification(_queue), Poco::Clock(0));
		_thread.join();
	}
}

	
void Scheduler::cancel(bool wait)
{
	Poco::AutoPtr<CancelNotification> pNf = new CancelNotification(_queue);
	_queue.enqueueNotification(pNf, Poco::Clock(0));
	if (wait)
	{
		pNf->wait();
	}
}


void Scheduler::scheduleImmediately(SchedulerTask::Ptr pTask)
{
	_queue.enqueueNotification(new TaskNotification(_queue, pTask), Poco::Clock());
}


void Scheduler::scheduleAtFixedRate(SchedulerTask::Ptr pTask, long delay, long interval)
{
	Poco::Clock time;
	time += static_cast<Poco::Clock::ClockDiff>(delay)*1000;
	_queue.enqueueNotification(new FixedRateTaskNotification(_queue, pTask, interval, time), time);
}


void Scheduler::run()
{
	bool cont = true;
	while (cont)
	{
		Poco::AutoPtr<SchedulerNotification> pNf = static_cast<SchedulerNotification*>(_queue.waitDequeueNotification());
		cont = pNf->execute();
	}
}


} } } // namespace IoT::Dataflow::Engine
