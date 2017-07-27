//
// Scheduler.h
//
// $Id$
//
// Library: IoT/Dataflow/Engine
// Package: Scheduler
// Module:  Scheduler
//
// Definition of the Scheduler class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Dataflow_Engine_Scheduler_INCLUDED
#define IoT_Dataflow_Engine_Scheduler_INCLUDED


#include "IoT/Dataflow/Engine/Engine.h"
#include "Poco/TimedNotificationQueue.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Dataflow {
namespace Engine {


class IoTDataflowEngine_API SchedulerTask: public Poco::RefCountedObject, public Poco::Runnable
	/// A task that can be scheduled for one-time or 
	/// repeated execution by the Scheduler.
	///
	/// This is an abstract class. Subclasses must override the run() member
	/// function to implement the actual task logic.
{
public:
	typedef Poco::AutoPtr<SchedulerTask> Ptr;
	
	SchedulerTask();
		/// Creates the SchedulerTask.
		
	void cancel();
		/// Cancels the execution of the scheduler.
		///
		/// If the task has been scheduled for one-time execution and has 
		/// not yet run, or has not yet been scheduled, it will never run. 
		/// If the task has been scheduled for repeated execution, it will never 
		/// run again. If the task is running when this call occurs, the task 
		/// will run to completion, but will never run again.	
	
	bool isCancelled() const;
		/// Returns true iff the SchedulerTask has been cancelled by a call
		/// to cancel().
	
protected:
	~SchedulerTask();
		/// Destroys the SchedulerTask.
	
private:
	SchedulerTask(const SchedulerTask&);
	SchedulerTask& operator = (const SchedulerTask&);
	
	bool _isCancelled;
	
	friend class TaskNotification;
};


class IoTDataflowEngine_API Scheduler: public Poco::Runnable
	/// The Scheduler drives the data flow.
	///
	/// It does this by scheduling tasks (SchedulerTask objects) for future execution 
	/// in its thread. Tasks may be scheduled for one-time execution, 
	/// or for repeated execution at regular intervals. 
	///
	/// The Scheduler object creates a thread that executes all scheduled tasks
	/// sequentially. Therefore, tasks should complete their work as quickly
	/// as possible, otherwise subsequent tasks may be delayed.
	///
	/// Scheduler is save for multithreaded use - multiple threads can schedule
	/// new tasks simultaneously.
{
public:
	Poco::BasicEvent<void> started;
		/// Fired after the Scheduler has been started.
		
	Poco::BasicEvent<void> stopped;
		/// Fired after the Scheduler has been stopped.	
		
	Scheduler();
		/// Creates a Scheduler with a given name.
	
	~Scheduler();
		/// Destroys the Scheduler, cancelling all pending tasks.

	void start();
		/// Starts the Scheduler.
		
	void stop();
		/// Cancels all pending tasks (see cancel) and stops the Scheduler.	
		
	void cancel(bool wait = false);
		/// Cancels all pending tasks.
		///
		/// If a task is currently running, it is allowed to finish.
		///
		/// Task cancellation is done asynchronously. If wait
		/// is false, cancel() returns immediately and the
		/// task queue will be purged as soon as the currently
		/// running task finishes. If wait is true, waits
		/// until the queue has been purged.
		
	void scheduleImmediately(SchedulerTask::Ptr pTask);
		/// Schedules a task for immediate execution.

	void scheduleAtFixedRate(SchedulerTask::Ptr pTask, long delay, long interval);
		/// Schedules a task for periodic execution at a fixed rate.
		///
		/// The task is first executed after the given delay.
		/// Subsequently, the task is executed periodically 
		/// every number of milliseconds specified by interval.
		
protected:
	void run();
		
private:
	Scheduler(const Scheduler&);
	Scheduler& operator = (const Scheduler&);
	
	Poco::TimedNotificationQueue _queue;
	Poco::Thread _thread;
};


//
// inlines
//
inline bool SchedulerTask::isCancelled() const
{
	return _isCancelled;
}


} } } // namespace IoT::Dataflow::Engine


#endif // IoT_Dataflow_Engine_Scheduler_INCLUDED
