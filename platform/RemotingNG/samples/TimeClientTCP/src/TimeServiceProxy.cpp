//
// TimeServiceProxy.cpp
//
// Package: Generated
// Module:  TimeServiceProxy
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2015, Applied Informatics Software Engineering GmbH.
//


#include "TimeServiceProxy.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "TimeServiceEventSubscriber.h"


namespace Services {


TimeServiceProxy::TimeServiceProxy(const Poco::RemotingNG::Identifiable::ObjectId& oid):
	Services::ITimeService(),
	Poco::RemotingNG::Proxy(oid),
	_currentTimeRet(),
	_pEventListener(),
	_pEventSubscriber()
{
}


TimeServiceProxy::~TimeServiceProxy()
{
	if (_pEventListener)
	{
		try
		{
			_pEventListener->unsubscribeFromEvents(_pEventSubscriber);
		}
		catch (...)
		{
		}
		_pEventSubscriber = 0;
		_pEventListener = 0;
	}
}


Poco::DateTime TimeServiceProxy::currentTime() const
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"currentTime"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("currentTimeReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	Poco::RemotingNG::TypeDeserializer<Poco::DateTime >::deserialize(Poco::RemotingNG::SerializerBase::RETURN_PARAM, true, remoting__deser, _currentTimeRet);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__trans.endRequest();
	return _currentTimeRet;
}


void TimeServiceProxy::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	if ((_pEventListener && !enable) || (!_pEventListener && enable))
	{
		Poco::RemotingNG::EventListener::Ptr pEventListener = pListener.cast<Poco::RemotingNG::EventListener>();
		if (pEventListener)
		{
			if (enable)
			{
				std::string eventURI = remoting__getEventURI().empty() ? remoting__getURI().toString() : remoting__getEventURI().toString();
				_pEventSubscriber = new TimeServiceEventSubscriber(eventURI, this);
				pEventListener->subscribeToEvents(_pEventSubscriber);
				_pEventListener = pEventListener;
			}
			else if (_pEventListener == pEventListener)
			{
				try
				{
					_pEventListener->unsubscribeFromEvents(_pEventSubscriber);
				}
				catch (...)
				{
					_pEventSubscriber = 0;
					_pEventListener = 0;
					throw;
				}
				_pEventSubscriber = 0;
				_pEventListener = 0;
			}
			else throw Poco::RemotingNG::RemotingException("EventListener mismatch");
		}
		else throw Poco::RemotingNG::RemotingException("Listener is not an EventListener");
	}
}


void TimeServiceProxy::wakeMeUp(const Poco::DateTime& time, const std::string& message)
{
	remoting__staticInitBegin(REMOTING__NAMES);
	static const std::string REMOTING__NAMES[] = {"wakeMeUp","time","message"};
	remoting__staticInitEnd(REMOTING__NAMES);
	Poco::RemotingNG::Transport& remoting__trans = remoting__transport();
	Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.beginRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__ser.serializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::TypeSerializer<Poco::DateTime >::serialize(REMOTING__NAMES[1], time, remoting__ser);
	Poco::RemotingNG::TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], message, remoting__ser);
	remoting__ser.serializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	Poco::RemotingNG::Deserializer& remoting__deser = remoting__trans.sendRequest(remoting__objectId(), remoting__typeId(), REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
	remoting__staticInitBegin(REMOTING__REPLY_NAME);
	static const std::string REMOTING__REPLY_NAME("wakeMeUpReply");
	remoting__staticInitEnd(REMOTING__REPLY_NAME);
	remoting__deser.deserializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__deser.deserializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
	remoting__trans.endRequest();
}


const std::string TimeServiceProxy::DEFAULT_NS("");
} // namespace Services

