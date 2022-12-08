//
// WebEventServiceImpl.cpp
//
// Library: OSP/WebEvent
// Package: WebEvent
// Module:  WebEventServiceImpl
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/WebEvent/WebEventServiceImpl.h"
#include "Poco/Net/HTTPServerResponse.h"
#include "Poco/Buffer.h"
#include <algorithm>


namespace Poco {
namespace OSP {
namespace WebEvent {


const std::string WebEventServiceImpl::SUBSCRIBE("SUBSCRIBE");
const std::string WebEventServiceImpl::UNSUBSCRIBE("UNSUBSCRIBE");
const std::string WebEventServiceImpl::NOTIFY("NOTIFY");
const std::string WebEventServiceImpl::VERSION("WebEvent/1.0");
const std::string WebEventServiceImpl::SYSTEM_PING("system.ping");
const std::string WebEventServiceImpl::SYSTEM_PONG("system.pong");


class TaskNotification: public Poco::Notification
{
public:
	using Ptr = Poco::AutoPtr<TaskNotification>;

	TaskNotification(WebEventServiceImpl& service):
		_service(service)
	{
	}

	~TaskNotification()
	{
	}

	virtual void execute() = 0;

protected:
	WebEventServiceImpl& _service;
};


class AddSubscriberNotification: public TaskNotification
{
public:
	AddSubscriberNotification(WebEventServiceImpl& service, Poco::SharedPtr<Poco::Net::WebSocket> pWS):
		TaskNotification(service),
		_pWS(pWS)
	{
	}

	void execute()
	{
		_service.addSubscriberImpl(_pWS);
	}

private:
	Poco::SharedPtr<Poco::Net::WebSocket> _pWS;
};


class RemoveSubscriberNotification: public TaskNotification
{
public:
	RemoveSubscriberNotification(WebEventServiceImpl& service, Poco::SharedPtr<Poco::Net::WebSocket> pWS, bool clientShutdown):
		TaskNotification(service),
		_pWS(pWS),
		_clientShutdown(clientShutdown)
	{
	}

	void execute()
	{
		_service.removeSubscriberImpl(_pWS, _clientShutdown);
	}

private:
	Poco::SharedPtr<Poco::Net::WebSocket> _pWS;
	bool _clientShutdown;
};


class SubscribeNotification: public TaskNotification
{
public:
	SubscribeNotification(WebEventServiceImpl& service, Poco::SharedPtr<Poco::Net::WebSocket> pWS, const std::set<std::string>& subjectNames):
		TaskNotification(service),
		_pWS(pWS),
		_subjectNames(subjectNames)
	{
	}

	void execute()
	{
		_service.subscribeImpl(_pWS, _subjectNames);
	}

private:
	Poco::SharedPtr<Poco::Net::WebSocket> _pWS;
	std::set<std::string> _subjectNames;
};


class UnsubscribeNotification: public TaskNotification
{
public:
	UnsubscribeNotification(WebEventServiceImpl& service, Poco::SharedPtr<Poco::Net::WebSocket> pWS, const std::set<std::string>& subjectNames):
		TaskNotification(service),
		_pWS(pWS),
		_subjectNames(subjectNames)
	{
	}

	void execute()
	{
		_service.unsubscribeImpl(_pWS, _subjectNames);
	}

private:
	Poco::SharedPtr<Poco::Net::WebSocket> _pWS;
	std::set<std::string> _subjectNames;
};


class NotifyNotification: public TaskNotification
{
public:
	NotifyNotification(WebEventServiceImpl& service, const std::string& subjectName, const std::string& data):
		TaskNotification(service),
		_subjectName(subjectName),
		_data(data)
	{
	}

	void execute()
	{
		_service.notifyImpl(_subjectName, _data);
	}

private:
	std::string _subjectName;
	std::string _data;
};


class SendNotification: public TaskNotification
{
public:
	SendNotification(WebEventServiceImpl& service, Poco::SharedPtr<Poco::Net::WebSocket> pWS, const std::string& message):
		TaskNotification(service),
		_pWS(pWS),
		_message(message)
	{
	}

	void execute()
	{
		_service.sendImpl(_pWS, _message);
	}

private:
	Poco::SharedPtr<Poco::Net::WebSocket> _pWS;
	std::string _message;
};


class ReceiveNotification: public TaskNotification
{
public:
	ReceiveNotification(WebEventServiceImpl& service, Poco::SharedPtr<Poco::Net::WebSocket> pWS):
		TaskNotification(service),
		_pWS(pWS)
	{
	}

	void execute()
	{
		_service.receiveImpl(_pWS);
	}

private:
	Poco::SharedPtr<Poco::Net::WebSocket> _pWS;
};


class ShutdownNotification: public TaskNotification
{
public:
	ShutdownNotification(WebEventServiceImpl& service, Poco::SharedPtr<Poco::Net::WebSocket> pWS, Poco::UInt16 statusCode, const std::string& statusMessage, bool passive):
		TaskNotification(service),
		_pWS(pWS),
		_statusCode(statusCode),
		_statusMessage(statusMessage),
		_passive(passive)
	{
	}

	void execute()
	{
		_service.shutdownImpl(_pWS, _statusCode, _statusMessage, _passive);
	}

private:
	Poco::SharedPtr<Poco::Net::WebSocket> _pWS;
	Poco::UInt16 _statusCode;
	std::string _statusMessage;
	bool _passive;
};


class WatchSocketNotification: public TaskNotification
{
public:
	WatchSocketNotification(WebEventServiceImpl& service, const Poco::Net::Socket& socket):
		TaskNotification(service),
		_socket(socket)
	{
	}

	void execute()
	{
		_service.watchSocketImpl(_socket);
	}

private:
	Poco::Net::Socket _socket;
};


WebEventServiceImpl::WebEventServiceImpl(Poco::OSP::BundleContext::Ptr pContext, int maxSockets, int workerCount):
	_pContext(pContext),
	_maxSockets(maxSockets),
	_mainRunnable(*this, &WebEventServiceImpl::runMain),
	_workerRunnable(*this, &WebEventServiceImpl::runWorker),
	_stopped(false)
{
	for (unsigned i = 0; i < workerCount; i++)
	{
		ThreadPtr pThread = new Poco::Thread;
		pThread->start(_workerRunnable);
		_workerThreads.push_back(pThread);
	}
	_mainThread.start(_mainRunnable);
}


WebEventServiceImpl::~WebEventServiceImpl()
{
	try
	{
		_stopped = true;
		_mainQueue.wakeUpAll();
		_workerQueue.wakeUpAll();
		_mainThread.join();
		for (ThreadVec::iterator it = _workerThreads.begin(); it != _workerThreads.end(); ++it)
		{
			(*it)->join();
		}
	}
	catch (...)
	{
		poco_unexpected();
	}
}


Poco::BasicEvent<const WebEventService::NotificationEvent>& WebEventServiceImpl::subjectNotified(const std::string& subject)
{
	EventMap::iterator it = _eventMap.find(subject);
	if (it != _eventMap.end())
	{
		return *it->second;
	}
	else
	{
		EventPtr pEvent = new Event;
		_eventMap.insert(EventMap::value_type(subject, pEvent));
		return *pEvent;
	}
}


void WebEventServiceImpl::notify(const std::string& subjectName, const std::string& data)
{
	_mainQueue.enqueueNotification(new NotifyNotification(*this, subjectName, data));
}


const std::type_info& WebEventServiceImpl::type() const
{
	return typeid(WebEventServiceImpl);
}


bool WebEventServiceImpl::isA(const std::type_info& otherType) const
{
	std::string name(typeid(WebEventServiceImpl).name());
	return name == otherType.name() || WebEventService::isA(otherType);
}


void WebEventServiceImpl::runMain()
{
	while (!_stopped)
	{
		try
		{
			Poco::Net::Socket::SocketList readList(_socketList);
			Poco::Net::Socket::SocketList writeList;
			Poco::Net::Socket::SocketList exceptList(_socketList);

			Poco::Timespan timeout(5000);
			int n = Poco::Net::Socket::select(readList, writeList, exceptList, timeout);
			if (n > 0)
			{
				for (Poco::Net::Socket::SocketList::iterator it = readList.begin(); it != readList.end(); ++it)
				{
					SocketMap::iterator its = _socketMap.find(*it);
					if (its != _socketMap.end())
					{
						receive(its->second->pWebSocket);
						unwatchSocketImpl(*it);
					}
				}
				for (Poco::Net::Socket::SocketList::iterator it = exceptList.begin(); it != exceptList.end(); ++it)
				{
					SocketMap::iterator its = _socketMap.find(*it);
					if (its != _socketMap.end())
					{
						removeSubscriberImpl(its->second->pWebSocket, false);
					}
				}
			}

			Poco::Notification::Ptr pNf = _socketList.empty() ? _mainQueue.waitDequeueNotification() : _mainQueue.dequeueNotification();
			while (pNf)
			{
				TaskNotification::Ptr pTaskNf = pNf.cast<TaskNotification>();
				if (pTaskNf)
				{
					pTaskNf->execute();
				}
				pNf = _socketList.empty() ? _mainQueue.waitDequeueNotification() : _mainQueue.dequeueNotification();
			}
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error("Exception in main thread: " + exc.displayText());
		}
	}
}


void WebEventServiceImpl::runWorker()
{
	while (!_stopped)
	{
		try
		{
			Poco::Notification::Ptr pNf = _workerQueue.waitDequeueNotification();
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
			_pContext->logger().error("Exception in worker thread: " + exc.displayText());
		}
	}
}


void WebEventServiceImpl::addSubscriber(Poco::SharedPtr<Poco::Net::WebSocket> pWS)
{
	_mainQueue.enqueueNotification(new AddSubscriberNotification(*this, pWS));
}


void WebEventServiceImpl::removeSubscriber(Poco::SharedPtr<Poco::Net::WebSocket> pWS, bool clientShutdown)
{
	_mainQueue.enqueueNotification(new RemoveSubscriberNotification(*this, pWS, clientShutdown));
}


void WebEventServiceImpl::subscribe(Poco::SharedPtr<Poco::Net::WebSocket> pWS, const std::set<std::string>& subjectNames)
{
	_mainQueue.enqueueNotification(new SubscribeNotification(*this, pWS, subjectNames));
}


void WebEventServiceImpl::unsubscribe(Poco::SharedPtr<Poco::Net::WebSocket> pWS, const std::set<std::string>& subjectNames)
{
	_mainQueue.enqueueNotification(new UnsubscribeNotification(*this, pWS, subjectNames));
}


int WebEventServiceImpl::subscriberCount(const std::string& subject)
{
	int cnt = 0;
	auto er = _subjectMap.equal_range(subject);
	for (auto it = er.first; it != er.second; ++it) ++cnt;
	return cnt;
}


void WebEventServiceImpl::send(Poco::SharedPtr<Poco::Net::WebSocket> pWS, const std::string& message)
{
	_workerQueue.enqueueNotification(new SendNotification(*this, pWS, message));
}


void WebEventServiceImpl::receive(Poco::SharedPtr<Poco::Net::WebSocket> pWS)
{
	_workerQueue.enqueueNotification(new ReceiveNotification(*this, pWS));
}


void WebEventServiceImpl::shutdown(Poco::SharedPtr<Poco::Net::WebSocket> pWS, Poco::UInt16 statusCode, const std::string& statusMessage, bool passive)
{
	_workerQueue.enqueueNotification(new ShutdownNotification(*this, pWS, statusCode, statusMessage, passive));
}


void WebEventServiceImpl::notifyImpl(const std::string& subjectName, const std::string& data)
{
	NotificationEvent ev(subjectName, data);
	notificationSent(ev);

	std::string message(NOTIFY);
	message += ' ';
	message += subjectName;
	message += ' ';
	message += VERSION;
	message += "\r\n";
	message += data;

	std::string s(subjectName);
	std::string::size_type pos = std::string::npos;
	do
	{
		SubjectMap::const_iterator it = _subjectMap.find(s);
		while (it != _subjectMap.end() && it->first == s)
		{
			send(it->second->pWebSocket, message);
			++it;
		}
		EventMap::iterator itEv = _eventMap.find(s);
		while (itEv != _eventMap.end() && itEv->first == s)
		{
			(*itEv->second)(ev);
			++itEv;
		}
		pos = s.find_last_of('.');
		if (pos != std::string::npos)
		{
			s.resize(pos);
		}
	}
	while (pos != std::string::npos);
}


void WebEventServiceImpl::addSubscriberImpl(Poco::SharedPtr<Poco::Net::WebSocket> pWS)
{
	Subscriber::Ptr pSubscriber = new Subscriber;
	pSubscriber->pWebSocket = pWS;
	_socketMap[*pWS] = pSubscriber;
	watchSocketImpl(*pWS);
	pWS->setSendTimeout(Poco::Timespan(WEBEVENT_SEND_TIMEOUT, 0));
	pWS->setReceiveTimeout(Poco::Timespan(WEBEVENT_RECEIVE_TIMEOUT, 0));
}


void WebEventServiceImpl::removeSubscriberImpl(Poco::SharedPtr<Poco::Net::WebSocket> pWS, bool clientShutdown)
{
	SocketMap::iterator it = _socketMap.find(*pWS);
	if (it != _socketMap.end())
	{
		unsubscribeImpl(pWS, it->second->subjectNames);
		_socketMap.erase(it);
		unwatchSocketImpl(*pWS);
		try
		{
			shutdown(pWS, Poco::Net::WebSocket::WS_NORMAL_CLOSE, "", clientShutdown);
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().error("Exception while removing subscriber: " + exc.displayText());
		}
	}
}


void WebEventServiceImpl::subscribeImpl(Poco::SharedPtr<Poco::Net::WebSocket> pWS, const std::set<std::string>& subjectNames)
{
	SocketMap::iterator it = _socketMap.find(*pWS);
	if (it != _socketMap.end())
	{
		for (std::set<std::string>::const_iterator itSub = subjectNames.begin(); itSub != subjectNames.end(); ++itSub)
		{
			if (it->second->subjectNames.find(*itSub) == it->second->subjectNames.end())
			{
				it->second->subjectNames.insert(*itSub);
				_subjectMap.insert(SubjectMap::value_type(*itSub, it->second));
				subscriptionRequestReceived.notify(this, *itSub);
			}
		}
	}
}


void WebEventServiceImpl::unsubscribeImpl(Poco::SharedPtr<Poco::Net::WebSocket> pWS, const std::set<std::string>& subjectNames)
{
	SocketMap::iterator it = _socketMap.find(*pWS);
	if (it != _socketMap.end())
	{
		std::set<std::string> allSubjectNames;
		if (subjectNames.find("*") != subjectNames.end())
		{
			allSubjectNames = it->second->subjectNames;
		}
		else
		{
			allSubjectNames = subjectNames;
		}
		for (std::set<std::string>::const_iterator itSub = allSubjectNames.begin(); itSub != allSubjectNames.end(); ++itSub)
		{
			std::set<std::string>::iterator itFound = it->second->subjectNames.find(*itSub);
			if (itFound != it->second->subjectNames.end())
			{
				it->second->subjectNames.erase(itFound);
				SubjectMap::iterator itSM = _subjectMap.find(*itSub);
				while (itSM != _subjectMap.end() && itSM->first == *itSub)
				{
					if (itSM->second == it->second)
					{
						_subjectMap.erase(itSM);
						unsubscriptionRequestReceived.notify(this, *itSub);
						break;
					}
					++itSM;
				}
			}
		}
	}
}


void WebEventServiceImpl::sendImpl(Poco::SharedPtr<Poco::Net::WebSocket> pWS, const std::string& message)
{
	try
	{
		Poco::FastMutex::ScopedLock lock(_sendMutex);

		pWS->sendFrame(message.data(), static_cast<int>(message.size()));
	}
	catch (Poco::Exception& exc)
	{
		_pContext->logger().error("Error while sending frame: " + exc.displayText());
		removeSubscriber(pWS, false);
	}
}


void WebEventServiceImpl::receiveImpl(Poco::SharedPtr<Poco::Net::WebSocket> pWS)
{
	try
	{
		Poco::Buffer<char> buffer(4096);
		int flags;
		int n = pWS->receiveFrame(buffer.begin(), static_cast<int>(buffer.size()), flags);
		_pContext->logger().debug(Poco::format("Frame received (length=%d, flags=0x%x).", n, unsigned(flags)));

		if (flags & Poco::Net::WebSocket::FRAME_OP_PONG)
		{
			_pContext->logger().debug("Received unsolicited PONG frame - ignoring.");
			_mainQueue.enqueueNotification(new WatchSocketNotification(*this, *pWS));
			return;
		}

		if ((flags & Poco::Net::WebSocket::FRAME_OP_CLOSE) || n == 0)
		{
			removeSubscriber(pWS, true);
			return;
		}

		const char* it  = buffer.begin();
		const char* end = buffer.begin() + n;
		std::string verb;
		while (it != end && *it != ' ') verb += *it++;
		if (verb == SUBSCRIBE || verb == UNSUBSCRIBE || verb == NOTIFY)
		{
			while (it != end && *it == ' ') ++it;
			std::set<std::string> subjectNames;
			while (it != end && *it != ' ')
			{
				std::string subject;
				while (it != end && *it != ',' && *it != ' ') subject += *it++;
				if (it != end)
				{
					subjectNames.insert(subject);
					if (*it == ',') it++; // skip ','
				}
			}
			while (it != end && *it == ' ') ++it;
			std::string version;
			while (it != end && *it != '\r' && *it != '\n') version += *it++;
			if (it != end && *it == '\r') ++it;
			if (it != end && *it == '\n') ++it;
			if (version == VERSION)
			{
				if (verb == SUBSCRIBE)
				{
					subscribe(pWS, subjectNames);
				}
				else if (verb == UNSUBSCRIBE)
				{
					unsubscribe(pWS, subjectNames);
				}
				else if (verb == NOTIFY)
				{
					std::string data;
					while (it != end) data += *it++;
					for (std::set<std::string>::const_iterator it = subjectNames.begin(); it != subjectNames.end(); ++it)
					{
						if (*it == SYSTEM_PING)
						{
							std::string pong(NOTIFY);
							pong += ' ';
							pong += SYSTEM_PONG;
							pong += ' ';
							pong += VERSION;
							pong += "\r\n";
							pong += data;
							send(pWS, pong);
						}
						else
						{
							notify(*it, data);
						}
					}
				}
				_mainQueue.enqueueNotification(new WatchSocketNotification(*this, *pWS));
				return;
			}
		}
		_pContext->logger().notice("Client protocol violation. Closing WebSocket.");
	}
	catch (Poco::Exception& exc)
	{
		_pContext->logger().error("Error while receiving frame: " + exc.displayText());
	}
	removeSubscriber(pWS, false);
}


void WebEventServiceImpl::shutdownImpl(Poco::SharedPtr<Poco::Net::WebSocket> pWS, Poco::UInt16 statusCode, const std::string& statusMessage, bool passive)
{
	_pContext->logger().notice("Shutting down WebSocket.");
	try
	{
		pWS->shutdown(statusCode, statusMessage);
	}
	catch (Poco::Exception& exc)
	{
		_pContext->logger().notice("Error while shutting down WebSocket: " + exc.displayText());
		passive = true; // don't wait for client confirmation
	}
	if (!passive)
	{
		if (pWS->poll(Poco::Timespan(WEBEVENT_SHUTDOWN_TIMEOUT, 0), Poco::Net::Socket::SELECT_READ))
		{
			Poco::Buffer<char> buffer(4096);
			int flags;
			pWS->receiveFrame(buffer.begin(), static_cast<int>(buffer.size()), flags);
			if (flags & Poco::Net::WebSocket::FRAME_OP_CLOSE)
			{
				pWS->close();
				return;
			}
		}
		_pContext->logger().notice("Client failed to confirm shutdown.");
	}
	pWS->close();
}


void WebEventServiceImpl::watchSocketImpl(const Poco::Net::Socket& socket)
{
	_socketList.push_back(socket);
}


void WebEventServiceImpl::unwatchSocketImpl(const Poco::Net::Socket& socket)
{
	Poco::Net::Socket::SocketList::iterator itd = std::find(_socketList.begin(), _socketList.end(), socket);
	if (itd != _socketList.end())
	{
		_socketList.erase(itd);
	}
}


void WebEventServiceImpl::preflightRequest(Poco::Net::HTTPServerRequest& request)
{
	if (_maxSockets > 0 && _socketMap.size() >= _maxSockets)
	{
		request.response().setStatusAndReason(Poco::Net::HTTPResponse::HTTP_SERVICE_UNAVAILABLE);
	}
}


} } } // namespace Poco::OSP::WebEvent
