//
// Timer.h
//
// Library: JS/Core
// Package: Execution
// Module:  JSExecutor
//
// Definition of the Timer class.
//
// Copyright (c) 2021, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Core_JSTimer_INCLUDED
#define JS_Core_JSTimer_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/TimedNotificationQueue.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include <atomic>


namespace Poco {
namespace JS {
namespace Core {


class TimedJSExecutor;


class JSCore_API JSTimer: protected Poco::Runnable
	/// A JSTimer allows to schedule tasks (Poco::Util::TimerTask objects) for future execution
	/// in a background thread. Tasks may be scheduled for one-time execution,
	/// or for repeated execution at regular intervals.
	///
	/// The JSTimer object creates a thread that executes all scheduled tasks
	/// sequentially. Therefore, tasks should complete their work as quickly
	/// as possible, otherwise subsequent tasks may be delayed.
	///
	/// JSTimer is safe for multithreaded use - multiple threads can schedule
	/// new tasks simultaneously.
	///
	/// JSTimer is a slightly adapted version of the Poco::Util::Timer class for
	/// use with JSTimedExecutor.
{
public:
	JSTimer();
		/// Creates the Timer.

	~JSTimer();
		/// Destroys the Timer, cancelling all pending tasks.

	void cancel(TimedJSExecutor* pExecutor);
		/// Cancels all pending tasks.
		///
		/// If a task is currently running, it is allowed to finish,
		/// however, any JavaScript executing is interrupted.

	void cancelAsync(TimedJSExecutor* pExecutor);
		/// Cancels all pending tasks.
		///
		/// If a task is currently running, it is allowed to finish,
		/// however, any JavaScript executing is interrupted.
		///
		/// Unlike cancel(), does not wait for the current task to finish.

	void schedule(Poco::Util::TimerTask::Ptr pTask, Poco::Timestamp time);
		/// Schedules a task for execution at the specified time.
		///
		/// If the time lies in the past, the task is executed
		/// immediately.
		///
		/// Note: the relative time the task will be executed
		/// won't change if the system's time changes. If the
		/// given time is 10 seconds in the future at the point
		/// schedule() is called, the task will be executed 10
		/// seconds later, even if the system time changes in
		/// between.

	void schedule(Poco::Util::TimerTask::Ptr pTask, Poco::Clock clock);
		/// Schedules a task for execution at the specified time.
		///
		/// If the time lies in the past, the task is executed
		/// immediately.

	void schedule(Poco::Util::TimerTask::Ptr pTask, long delay, long interval);
		/// Schedules a task for periodic execution.
		///
		/// The task is first executed after the given delay.
		/// Subsequently, the task is executed periodically with
		/// the given interval in milliseconds between invocations.

	void schedule(Poco::Util::TimerTask::Ptr pTask, Poco::Timestamp time, long interval);
		/// Schedules a task for periodic execution.
		///
		/// The task is first executed at the given time.
		/// Subsequently, the task is executed periodically with
		/// the given interval in milliseconds between invocations.
		///
		/// Note: the relative time the task will be executed
		/// won't change if the system's time changes. If the
		/// given time is 10 seconds in the future at the point
		/// schedule() is called, the task will be executed 10
		/// seconds later, even if the system time changes in
		/// between.

	void schedule(Poco::Util::TimerTask::Ptr pTask, Poco::Clock clock, long interval);
		/// Schedules a task for periodic execution.
		///
		/// The task is first executed at the given time.
		/// Subsequently, the task is executed periodically with
		/// the given interval in milliseconds between invocations.

	void scheduleAtFixedRate(Poco::Util::TimerTask::Ptr pTask, long delay, long interval);
		/// Schedules a task for periodic execution at a fixed rate.
		///
		/// The task is first executed after the given delay.
		/// Subsequently, the task is executed periodically
		/// every number of milliseconds specified by interval.
		///
		/// If task execution takes longer than the given interval,
		/// further executions are delayed.

	void scheduleAtFixedRate(Poco::Util::TimerTask::Ptr pTask, Poco::Timestamp time, long interval);
		/// Schedules a task for periodic execution at a fixed rate.
		///
		/// The task is first executed at the given time.
		/// Subsequently, the task is executed periodically
		/// every number of milliseconds specified by interval.
		///
		/// If task execution takes longer than the given interval,
		/// further executions are delayed.
		///
		/// Note: the relative time the task will be executed
		/// won't change if the system's time changes. If the
		/// given time is 10 seconds in the future at the point
		/// scheduleAtFixedRate() is called, the task will be executed 10
		/// seconds later, even if the system time changes in
		/// between.

	void scheduleAtFixedRate(Poco::Util::TimerTask::Ptr pTask, Poco::Clock clock, long interval);
		/// Schedules a task for periodic execution at a fixed rate.
		///
		/// The task is first executed at the given time.
		/// Subsequently, the task is executed periodically
		/// every number of milliseconds specified by interval.
		///
		/// If task execution takes longer than the given interval,
		/// further executions are delayed.

protected:
	void run();
	static void validateTask(const Poco::Util::TimerTask::Ptr& pTask);

private:
	JSTimer(const JSTimer&);
	JSTimer& operator = (const JSTimer&);

	Poco::TimedNotificationQueue _queue;
	Poco::Thread _thread;
	std::atomic<bool> _cancelled;
};


} } } // namespace Poco::JS::Core


#endif // JS_Core_JSTimer_INCLUDED
