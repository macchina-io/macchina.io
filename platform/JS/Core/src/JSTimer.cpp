//
// JSTimer.cpp
//
// Library: JS/Core
// Package: Execution
// Module:  JSTimer
//
// Copyright (c) 2021, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/JSTimer.h"
#include "Poco/JS/Core/JSExecutor.h"
#include "Poco/Notification.h"
#include "Poco/ErrorHandler.h"
#include "Poco/Event.h"


using Poco::ErrorHandler;


namespace Poco {
namespace JS {
namespace Core {


class TimerNotification: public Poco::Notification
{
public:
	TimerNotification(Poco::TimedNotificationQueue& queue):
		_queue(queue)
	{
	}

	~TimerNotification()
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


class StopNotification: public TimerNotification
{
public:
	StopNotification(Poco::TimedNotificationQueue& queue):
		TimerNotification(queue)
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


class CancelNotification: public TimerNotification
{
public:
	CancelNotification(Poco::TimedNotificationQueue& queue, TimedJSExecutor* pExecutor):
		TimerNotification(queue),
		_pExecutor(pExecutor)
	{
	}

	~CancelNotification()
	{
	}

	bool execute()
	{
		// Check if there's a StopNotification pending.
		Poco::AutoPtr<TimerNotification> pNf = static_cast<TimerNotification*>(queue().dequeueNotification());
		while (pNf)
		{
			if (pNf.cast<StopNotification>())
			{
				queue().clear();
				_finished.set();
				return false;
			}
			pNf = static_cast<TimerNotification*>(queue().dequeueNotification());
		}

		queue().clear();
		_finished.set();
		return true;
	}

	void wait()
	{
		_pExecutor->terminate();
		while (!_finished.tryWait(200))
		{
			_pExecutor->terminate();
		}
	}

private:
	Poco::Event _finished;
	JSExecutor* _pExecutor;
};


class TaskNotification: public TimerNotification
{
public:
	TaskNotification(Poco::TimedNotificationQueue& queue, Poco::Util::TimerTask::Ptr pTask):
		TimerNotification(queue),
		_pTask(pTask)
	{
	}

	~TaskNotification()
	{
	}

	Poco::Util::TimerTask::Ptr task()
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
			catch (Exception& exc)
			{
				ErrorHandler::handle(exc);
			}
			catch (std::exception& exc)
			{
				ErrorHandler::handle(exc);
			}
			catch (...)
			{
				ErrorHandler::handle();
			}
		}
		return true;
	}

private:
	Poco::Util::TimerTask::Ptr _pTask;
};


class PeriodicTaskNotification: public TaskNotification
{
public:
	PeriodicTaskNotification(Poco::TimedNotificationQueue& queue, Poco::Util::TimerTask::Ptr pTask, long interval):
		TaskNotification(queue, pTask),
		_interval(interval)
	{
	}

	~PeriodicTaskNotification()
	{
	}

	bool execute()
	{
		TaskNotification::execute();

		if (!task()->isCancelled())
		{
			Poco::Clock now;
			Poco::Clock nextExecution;
			nextExecution += static_cast<Poco::Clock::ClockDiff>(_interval)*1000;
			if (nextExecution < now) nextExecution = now;
			queue().enqueueNotification(this, nextExecution);
			duplicate();
		}
		return true;
	}

private:
	long _interval;
};


class FixedRateTaskNotification: public TaskNotification
{
public:
	FixedRateTaskNotification(Poco::TimedNotificationQueue& queue, Poco::Util::TimerTask::Ptr pTask, long interval, Poco::Clock clock):
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


JSTimer::JSTimer():
	_cancelled(false)
{
	_thread.start(*this);
}


JSTimer::~JSTimer()
{
	try
	{
		_queue.enqueueNotification(new StopNotification(_queue), Poco::Clock(0));
		_thread.join();
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void JSTimer::cancel(TimedJSExecutor* pExecutor)
{
	if (!_cancelled.exchange(true))
	{
		Poco::AutoPtr<CancelNotification> pNf = new CancelNotification(_queue, pExecutor);
		_queue.enqueueNotification(pNf, Poco::Clock(0));
		pNf->wait();
		_cancelled = false;
	}
}


void JSTimer::cancelAsync(TimedJSExecutor* pExecutor)
{
	if (!_cancelled.exchange(true))
	{
		Poco::AutoPtr<CancelNotification> pNf = new CancelNotification(_queue, pExecutor);
		_queue.enqueueNotification(pNf, Poco::Clock(0));
	}
}


void JSTimer::schedule(Poco::Util::TimerTask::Ptr pTask, Poco::Timestamp time)
{
	if (_cancelled) return;

	validateTask(pTask);
	_queue.enqueueNotification(new TaskNotification(_queue, pTask), time);
}


void JSTimer::schedule(Poco::Util::TimerTask::Ptr pTask, Poco::Clock clock)
{
	if (_cancelled) return;

	validateTask(pTask);
	_queue.enqueueNotification(new TaskNotification(_queue, pTask), clock);
}


void JSTimer::schedule(Poco::Util::TimerTask::Ptr pTask, long delay, long interval)
{
	if (_cancelled) return;

	Poco::Clock clock;
	clock += static_cast<Poco::Clock::ClockDiff>(delay)*1000;
	schedule(pTask, clock, interval);
}


void JSTimer::schedule(Poco::Util::TimerTask::Ptr pTask, Poco::Timestamp time, long interval)
{
	if (_cancelled) return;

	validateTask(pTask);
	_queue.enqueueNotification(new PeriodicTaskNotification(_queue, pTask, interval), time);
}


void JSTimer::schedule(Poco::Util::TimerTask::Ptr pTask, Poco::Clock clock, long interval)
{
	if (_cancelled) return;

	validateTask(pTask);
	_queue.enqueueNotification(new PeriodicTaskNotification(_queue, pTask, interval), clock);
}


void JSTimer::scheduleAtFixedRate(Poco::Util::TimerTask::Ptr pTask, long delay, long interval)
{
	if (_cancelled) return;

	Poco::Clock clock;
	clock += static_cast<Poco::Clock::ClockDiff>(delay)*1000;
	scheduleAtFixedRate(pTask, clock, interval);
}


void JSTimer::scheduleAtFixedRate(Poco::Util::TimerTask::Ptr pTask, Poco::Timestamp time, long interval)
{
	if (_cancelled) return;

	validateTask(pTask);
	Poco::Timestamp tsNow;
	Poco::Clock clock;
	Poco::Timestamp::TimeDiff diff = time - tsNow;
	clock += diff;
	_queue.enqueueNotification(new FixedRateTaskNotification(_queue, pTask, interval, clock), clock);
}


void JSTimer::scheduleAtFixedRate(Poco::Util::TimerTask::Ptr pTask, Poco::Clock clock, long interval)
{
	if (_cancelled) return;

	validateTask(pTask);
	_queue.enqueueNotification(new FixedRateTaskNotification(_queue, pTask, interval, clock), clock);
}


void JSTimer::run()
{
	bool cont = true;
	while (cont)
	{
		Poco::AutoPtr<TimerNotification> pNf = static_cast<TimerNotification*>(_queue.waitDequeueNotification());
		cont = pNf->execute();
	}
}


void JSTimer::validateTask(const Poco::Util::TimerTask::Ptr& pTask)
{
	if (pTask->isCancelled())
	{
		throw Poco::IllegalStateException("A cancelled task must not be rescheduled");
	}
}


} } } // namespace Poco::JS::Core
