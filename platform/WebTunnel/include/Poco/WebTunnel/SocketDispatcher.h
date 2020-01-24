//
// SocketDispatcher.h
//
// Library: WebTunnel
// Package: WebTunnel
// Module:  SocketDispatcher
//
// Definition of the SocketDispatcher class.
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef WebTunnel_SocketDispatcher_INCLUDED
#define WebTunnel_SocketDispatcher_INCLUDED


#include "Poco/WebTunnel/WebTunnel.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/PollSet.h"
#include "Poco/NotificationQueue.h"
#include "Poco/Thread.h"
#include "Poco/RunnableAdapter.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/SharedPtr.h"
#include "Poco/Clock.h"
#include "Poco/Logger.h"
#include <map>


namespace Poco {
namespace WebTunnel {


class WebTunnel_API SocketDispatcher
	/// SocketDispatcher implements a multi-threaded variant of the
	/// Reactor pattern, optimized for forwarding data from one
	/// socket to another.
	///
	/// The SocketDispatcher runs a select() loop in a separate thread.
	/// As soon as a socket becomes readable, it will be put into a work
	/// queue. A number of worker threads dequeue work queue items and
	/// process the data received over the socket, using registered
	/// SocketHandler instances.
{
public:
	class SocketHandler: public Poco::RefCountedObject
	{
	public:
		using Ptr = Poco::AutoPtr<SocketHandler>;

		virtual bool readable(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket) = 0;
		virtual void exception(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket) = 0;
		virtual void timeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket) = 0;
	};

	SocketDispatcher(int threadCount, Poco::Timespan timeout = Poco::Timespan(5000), int maxReadsPerWorker = 10);
		/// Creates the SocketDispatcher, using the given number of worker threads.
		///
		/// The given timeout is used for the main select loop, as well as
		/// by workers to poll if more reads are possible, up to the given
		/// maximum number of reads per worker.

	~SocketDispatcher();
		/// Destroys the SocketDispatcher.

	void addSocket(const Poco::Net::StreamSocket& socket, SocketHandler::Ptr pHandler, Poco::Timespan timeout = 0);
		/// Adds a socket and its handler to the SocketDispatcher.

	void removeSocket(const Poco::Net::StreamSocket& socket);
		/// Removes a socket and its associated handler from the SocketDispatcher.

	void closeSocket(const Poco::Net::StreamSocket& socket);
		/// Closes and removes a socket and its associated handler from the SocketDispatcher.

	void stop();
		/// Stops the SocketDispatcher and removes all sockets.

	void reset();
		/// Removes all sockets but does not stop the SocketDispatcher.

protected:
	struct SocketInfo: public Poco::RefCountedObject
	{
		using Ptr = Poco::AutoPtr<SocketInfo>;

		SocketInfo(SocketHandler::Ptr pHnd, Poco::Timespan tmo):
			pHandler(pHnd),
			timeout(tmo),
			wantRead(true),
			polling(true)
		{
		}

		SocketHandler::Ptr pHandler;
		Poco::Timespan timeout;
		Poco::Clock activity;
		bool wantRead;
		bool polling;
	};

	using SocketMap = std::map<Poco::Net::Socket, SocketInfo::Ptr>;
	using ThreadPtr = Poco::SharedPtr<Poco::Thread>;
	using ThreadVec = std::vector<ThreadPtr>;

	enum
	{
		MAIN_QUEUE_TIMEOUT = 1000,
		WORKER_QUEUE_TIMEOUT = 2500
	};

	void runMain();
	void runWorker();
	void readable(const Poco::Net::StreamSocket& socket, const SocketInfo::Ptr& pInfo);
	void exception(const Poco::Net::StreamSocket& socket, const SocketInfo::Ptr& pInfo);
	void timeout(const Poco::Net::StreamSocket& socket, const SocketInfo::Ptr& pInfo);
	void readableImpl(Poco::Net::StreamSocket& socket, SocketInfo::Ptr pInfo);
	void exceptionImpl(Poco::Net::StreamSocket& socket, SocketInfo::Ptr pInfo);
	void timeoutImpl(Poco::Net::StreamSocket& socket, SocketInfo::Ptr pInfo);
	void addSocketImpl(const Poco::Net::StreamSocket& socket, SocketHandler::Ptr pHandler, Poco::Timespan timeout);
	void removeSocketImpl(const Poco::Net::StreamSocket& socket);
	void closeSocketImpl(Poco::Net::StreamSocket& socket);
	void resetImpl();
	bool stopped();

private:
	Poco::Timespan _timeout;
	int _maxReadsPerWorker;
	SocketMap _socketMap;
	Poco::Net::PollSet _pollSet;
	Poco::Thread _mainThread;
	ThreadVec _workerThreads;
	Poco::RunnableAdapter<SocketDispatcher> _mainRunnable;
	Poco::RunnableAdapter<SocketDispatcher> _workerRunnable;
	Poco::NotificationQueue _mainQueue;
	Poco::NotificationQueue _workerQueue;
	bool _stopped;
	Poco::FastMutex _stoppedMtx;
	Poco::Logger& _logger;

	friend class ReadableNotification;
	friend class ExceptionNotification;
	friend class TimeoutNotification;
	friend class AddSocketNotification;
	friend class RemoveSocketNotification;
	friend class CloseSocketNotification;
	friend class ResetNotification;
};


//
// inlines
//
inline bool SocketDispatcher::stopped()
{
	Poco::FastMutex::ScopedLock lock(_stoppedMtx);

	return _stopped;
}


} } // namespace Poco::WebTunnel


#endif // WebTunnel_SocketDispatcher_INCLUDED
