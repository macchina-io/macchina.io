//
// SocketDispatcher.cpp
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


#include "Poco/WebTunnel/SocketDispatcher.h"
#include "Poco/Net/NetException.h"
#include "Poco/Event.h"


namespace Poco {
namespace WebTunnel {


class AutoSetEvent
{
public:
	AutoSetEvent(Poco::Event& event):
		_event(event)
	{
	}

	~AutoSetEvent()
	{
		try
		{
			_event.set();
		}
		catch (...)
		{
			poco_unexpected();
		}
	}

private:
	Poco::Event& _event;
};


class TaskNotification: public Poco::Notification
{
public:
	typedef Poco::AutoPtr<TaskNotification> Ptr;

	enum
	{
		TASK_WAIT_TIMEOUT = 30000
	};

	TaskNotification(SocketDispatcher& dispatcher):
		_dispatcher(dispatcher)
	{
	}

	~TaskNotification()
	{
	}

	void wait()
	{
		_done.wait(TASK_WAIT_TIMEOUT);
	}

	virtual void execute() = 0;

protected:
	SocketDispatcher& _dispatcher;
	Poco::Event _done;
};


class ReadableNotification: public TaskNotification
{
public:
	typedef Poco::AutoPtr<ReadableNotification> Ptr;

	ReadableNotification(SocketDispatcher& dispatcher, const Poco::Net::StreamSocket& socket, const SocketDispatcher::SocketInfo::Ptr& pInfo):
		TaskNotification(dispatcher),
		_socket(socket),
		_pInfo(pInfo)
	{
	}

	void execute()
	{
		AutoSetEvent ase(_done);

		_dispatcher.readableImpl(_socket, _pInfo);
	}

private:
	Poco::Net::StreamSocket _socket;
	SocketDispatcher::SocketInfo::Ptr _pInfo;
};


class ExceptionNotification: public TaskNotification
{
public:
	typedef Poco::AutoPtr<ExceptionNotification> Ptr;

	ExceptionNotification(SocketDispatcher& dispatcher, const Poco::Net::StreamSocket& socket, const SocketDispatcher::SocketInfo::Ptr& pInfo):
		TaskNotification(dispatcher),
		_socket(socket),
		_pInfo(pInfo)
	{
	}

	void execute()
	{
		AutoSetEvent ase(_done);

		_dispatcher.exceptionImpl(_socket, _pInfo);
	}

private:
	Poco::Net::StreamSocket _socket;
	SocketDispatcher::SocketInfo::Ptr _pInfo;
};


class TimeoutNotification: public TaskNotification
{
public:
	typedef Poco::AutoPtr<TimeoutNotification> Ptr;

	TimeoutNotification(SocketDispatcher& dispatcher, const Poco::Net::StreamSocket& socket, const SocketDispatcher::SocketInfo::Ptr& pInfo):
		TaskNotification(dispatcher),
		_socket(socket),
		_pInfo(pInfo)
	{
	}

	void execute()
	{
		AutoSetEvent ase(_done);

		_dispatcher.timeoutImpl(_socket, _pInfo);
	}

private:
	Poco::Net::StreamSocket _socket;
	SocketDispatcher::SocketInfo::Ptr _pInfo;
};


class AddSocketNotification: public TaskNotification
{
public:
	typedef Poco::AutoPtr<AddSocketNotification> Ptr;

	AddSocketNotification(SocketDispatcher& dispatcher, const Poco::Net::StreamSocket& socket, const SocketDispatcher::SocketHandler::Ptr& pHandler, Poco::Timespan timeout):
		TaskNotification(dispatcher),
		_socket(socket),
		_pHandler(pHandler),
		_timeout(timeout)
	{
	}

	void execute()
	{
		AutoSetEvent ase(_done);

		_dispatcher.addSocketImpl(_socket, _pHandler, _timeout);
	}

private:
	Poco::Net::StreamSocket _socket;
	SocketDispatcher::SocketHandler::Ptr _pHandler;
	Poco::Timespan _timeout;
};


class RemoveSocketNotification: public TaskNotification
{
public:
	typedef Poco::AutoPtr<RemoveSocketNotification> Ptr;

	RemoveSocketNotification(SocketDispatcher& dispatcher, const Poco::Net::StreamSocket& socket):
		TaskNotification(dispatcher),
		_socket(socket)
	{
	}

	void execute()
	{
		AutoSetEvent ase(_done);

		_dispatcher.removeSocketImpl(_socket);
	}

private:
	Poco::Net::StreamSocket _socket;
};


class CloseSocketNotification: public TaskNotification
{
public:
	typedef Poco::AutoPtr<CloseSocketNotification> Ptr;

	CloseSocketNotification(SocketDispatcher& dispatcher, const Poco::Net::StreamSocket& socket):
		TaskNotification(dispatcher),
		_socket(socket)
	{
	}

	void execute()
	{
		AutoSetEvent ase(_done);

		_dispatcher.closeSocketImpl(_socket);
	}

private:
	Poco::Net::StreamSocket _socket;
};


class ResetNotification: public TaskNotification
{
public:
	typedef Poco::AutoPtr<ResetNotification> Ptr;

	ResetNotification(SocketDispatcher& dispatcher):
		TaskNotification(dispatcher)
	{
	}

	void execute()
	{
		AutoSetEvent ase(_done);

		_dispatcher.resetImpl();
	}
};


SocketDispatcher::SocketDispatcher(int threadCount, Poco::Timespan timeout, int maxReadsPerWorker):
	_timeout(timeout),
	_maxReadsPerWorker(maxReadsPerWorker),
	_mainRunnable(*this, &SocketDispatcher::runMain),
	_workerRunnable(*this, &SocketDispatcher::runWorker),
	_stopped(false),
	_logger(Poco::Logger::get("WebTunnel.SocketDispatcher"))
{
	for (int i = 0; i < threadCount; i++)
	{
		ThreadPtr pThread = new Poco::Thread;
		pThread->start(_workerRunnable);
		_workerThreads.push_back(pThread);
	}
	_mainThread.start(_mainRunnable);
}


SocketDispatcher::~SocketDispatcher()
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


void SocketDispatcher::stop()
{
	if (!stopped())
	{
		{
			Poco::FastMutex::ScopedLock lock(_stoppedMtx);

			_stopped = true;
		}
		_mainQueue.wakeUpAll();
		_workerQueue.wakeUpAll();
		_mainThread.join();
		for (ThreadVec::iterator it = _workerThreads.begin(); it != _workerThreads.end(); ++it)
		{
			(*it)->join();
		}
		_socketMap.clear();
		_pollSet.clear();
	}
}


void SocketDispatcher::reset()
{
	ResetNotification::Ptr pNf = new ResetNotification(*this);
	_mainQueue.enqueueNotification(pNf);
	pNf->wait();
}


void SocketDispatcher::addSocket(const Poco::Net::StreamSocket& socket, SocketHandler::Ptr pHandler, Poco::Timespan timeout)
{
	AddSocketNotification::Ptr pNf = new AddSocketNotification(*this, socket, pHandler, timeout);
	_mainQueue.enqueueNotification(pNf);
	pNf->wait();
}


void SocketDispatcher::removeSocket(const Poco::Net::StreamSocket& socket)
{
	RemoveSocketNotification::Ptr pNf = new RemoveSocketNotification(*this, socket);
	_mainQueue.enqueueNotification(pNf);
	pNf->wait();
}


void SocketDispatcher::closeSocket(const Poco::Net::StreamSocket& socket)
{
	CloseSocketNotification::Ptr pNf = new CloseSocketNotification(*this, socket);
	_mainQueue.enqueueNotification(pNf);
	pNf->wait();
}


void SocketDispatcher::runMain()
{
	Poco::Timespan currentTimeout(_timeout);
	while (!stopped())
	{
		try
		{
			for (SocketMap::iterator it = _socketMap.begin(); it != _socketMap.end(); ++it)
			{
				if (it->second->wantRead && it->second->timeout != 0 && it->second->timeout < it->second->activity.elapsed())
				{
					it->second->wantRead = false;
					it->second->activity.update();
					timeout(it->first, it->second);
				}
				if (it->second->wantRead)
				{
					if (!it->second->polling)
					{
						it->second->polling = true;
						_pollSet.update(it->first, Poco::Net::PollSet::POLL_READ | Poco::Net::PollSet::POLL_ERROR);
					}
				}
				else
				{
					if (it->second->polling)
					{
						it->second->polling = false;
						_pollSet.update(it->first, 0);
					}
					// reset timeout clock
					it->second->activity.update();
				}
			}

			Poco::Net::PollSet::SocketModeMap socketModeMap = _pollSet.poll(currentTimeout);
			if (!socketModeMap.empty())
			{
				currentTimeout = _timeout;
				for (Poco::Net::PollSet::SocketModeMap::const_iterator it = socketModeMap.begin(); it != socketModeMap.end(); ++it)
				{
					SocketMap::iterator its = _socketMap.find(it->first);
					if (its != _socketMap.end() && its->second->wantRead)
					{
						its->second->wantRead = false;
						its->second->activity.update();
						if (it->second & Poco::Net::PollSet::POLL_READ)
						{
							readable(its->first, its->second);
						}
						if (it->second & Poco::Net::PollSet::POLL_ERROR)
						{
							exception(its->first, its->second);
						}
					}
				}
			}
			else
			{
				if (currentTimeout.totalMicroseconds() < 4*_timeout.totalMicroseconds()) currentTimeout += _timeout.totalMicroseconds()/2;
			}

			Poco::Notification::Ptr pNf = _socketMap.empty() ? _mainQueue.waitDequeueNotification(MAIN_QUEUE_TIMEOUT) : _mainQueue.dequeueNotification();
			while (pNf)
			{
				TaskNotification::Ptr pTaskNf = pNf.cast<TaskNotification>();
				if (pTaskNf)
				{
					pTaskNf->execute();
				}
				pNf = _socketMap.empty() ? _mainQueue.waitDequeueNotification(MAIN_QUEUE_TIMEOUT) : _mainQueue.dequeueNotification();
			}
		}
		catch (Poco::Net::NetException& exc)
		{
			if (exc.code() == POCO_ENOTCONN)
			{
				_logger.debug("A socket is no longer connected.");
			}
			else
			{
				_logger.error("Network exception in socket dispatcher: " + exc.displayText());
			}
		}
		catch (Poco::Exception& exc)
		{
			_logger.error("Exception in socket dispatcher: " + exc.displayText());
		}
	}
}


void SocketDispatcher::runWorker()
{
	while (!stopped())
	{
		try
		{
			Poco::Notification::Ptr pNf = _workerQueue.waitDequeueNotification(WORKER_QUEUE_TIMEOUT);
			if (pNf)
			{
				TaskNotification::Ptr pTaskNf = pNf.cast<TaskNotification>();
				if (pTaskNf)
				{
					pTaskNf->execute();
				}
			}
		}
		catch (Poco::Exception& exc)
		{
			_logger.error("Exception in worker thread: " + exc.displayText());
		}
	}
}


void SocketDispatcher::readable(const Poco::Net::StreamSocket& socket, const SocketDispatcher::SocketInfo::Ptr& pInfo)
{
	_workerQueue.enqueueNotification(new ReadableNotification(*this, socket, pInfo));
}


void SocketDispatcher::exception(const Poco::Net::StreamSocket& socket, const SocketDispatcher::SocketInfo::Ptr& pInfo)
{
	_workerQueue.enqueueNotification(new ExceptionNotification(*this, socket, pInfo));
}


void SocketDispatcher::timeout(const Poco::Net::StreamSocket& socket, const SocketDispatcher::SocketInfo::Ptr& pInfo)
{
	_workerQueue.enqueueNotification(new TimeoutNotification(*this, socket, pInfo));
}


void SocketDispatcher::readableImpl(Poco::Net::StreamSocket& socket, SocketDispatcher::SocketInfo::Ptr pInfo)
{
	try
	{
		int reads = 0;
		bool expectMore = false;
		do
		{
			if (socket.impl()->initialized())
			{
				expectMore = pInfo->pHandler->readable(*this, socket);
			}
		}
		while (socket.impl()->initialized() && (socket.available() > 0 || (expectMore && reads++ < _maxReadsPerWorker && socket.poll(_timeout, Poco::Net::Socket::SELECT_READ))));
	}
	catch (Poco::Exception& exc)
	{
		_logger.log(exc);
	}
	pInfo->wantRead = socket.impl()->initialized();
}


void SocketDispatcher::exceptionImpl(Poco::Net::StreamSocket& socket, SocketDispatcher::SocketInfo::Ptr pInfo)
{
	try
	{
		pInfo->pHandler->exception(*this, socket);
	}
	catch (Poco::Exception& exc)
	{
		_logger.log(exc);
	}
}


void SocketDispatcher::timeoutImpl(Poco::Net::StreamSocket& socket, SocketDispatcher::SocketInfo::Ptr pInfo)
{
	try
	{
		pInfo->pHandler->timeout(*this, socket);
	}
	catch (Poco::Exception& exc)
	{
		_logger.log(exc);
	}
	pInfo->wantRead = socket.impl()->initialized();
}


void SocketDispatcher::addSocketImpl(const Poco::Net::StreamSocket& socket, SocketHandler::Ptr pHandler, Poco::Timespan timeout)
{
	_socketMap[socket] = new SocketInfo(pHandler, timeout);
	_pollSet.add(socket, Poco::Net::PollSet::POLL_READ | Poco::Net::PollSet::POLL_ERROR);
}


void SocketDispatcher::removeSocketImpl(const Poco::Net::StreamSocket& socket)
{
	_socketMap.erase(socket);
	try
	{
		_pollSet.remove(socket);
	}
	catch (Poco::IOException&)
	{
	}
}


void SocketDispatcher::closeSocketImpl(Poco::Net::StreamSocket& socket)
{
	_socketMap.erase(socket);
	try
	{
		_pollSet.remove(socket);
	}
	catch (Poco::IOException&)
	{
	}
	socket.shutdown();
}


void SocketDispatcher::resetImpl()
{
	_socketMap.clear();
	_pollSet.clear();
}


} } // namespace Poco::WebTunnel
