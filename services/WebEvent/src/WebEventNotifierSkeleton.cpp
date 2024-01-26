//
// WebEventNotifierSkeleton.cpp
//
// Library: IoT/WebEvent
// Package: Generated
// Module:  WebEventNotifierSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/WebEvent/WebEventNotifierSkeleton.h"
#include "Poco/RemotingNG/Deserializer.h"
#include "Poco/RemotingNG/MethodHandler.h"
#include "Poco/RemotingNG/RemotingException.h"
#include "Poco/RemotingNG/Serializer.h"
#include "Poco/RemotingNG/ServerTransport.h"
#include "Poco/RemotingNG/TypeDeserializer.h"
#include "Poco/RemotingNG/TypeSerializer.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace WebEvent {


class WebEventNotifierClearEventFilterMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"clearEventFilter"s,"subscriberURI"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string subscriberURI;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, subscriberURI);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::WebEvent::WebEventNotifierRemoteObject* remoting__pCastedRO = static_cast<IoT::WebEvent::WebEventNotifierRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->clearEventFilter(subscriberURI);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("clearEventFilterReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::WebEvent::WebEventNotifier::clearEventFilter"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::WebEvent::WebEventNotifier::clearEventFilter"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::WebEvent::WebEventNotifier::clearEventFilter"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class WebEventNotifierNotifyMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"notify"s,"subjectName"s,"data"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string subjectName;
			std::string data;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, subjectName);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, remoting__deser, data);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::WebEvent::WebEventNotifierRemoteObject* remoting__pCastedRO = static_cast<IoT::WebEvent::WebEventNotifierRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->notify(subjectName, data);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("notifyReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::WebEvent::WebEventNotifier::notify"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::WebEvent::WebEventNotifier::notify"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::WebEvent::WebEventNotifier::notify"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class WebEventNotifierSetEventSubjectNameFilterMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"setEventSubjectNameFilter"s,"subscriberURI"s,"subjectName"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string subscriberURI;
			std::string subjectName;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, subscriberURI);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, remoting__deser, subjectName);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::WebEvent::WebEventNotifierRemoteObject* remoting__pCastedRO = static_cast<IoT::WebEvent::WebEventNotifierRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->setEventSubjectNameFilter(subscriberURI, subjectName);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("setEventSubjectNameFilterReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::WebEvent::WebEventNotifier::setEventSubjectNameFilter"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::WebEvent::WebEventNotifier::setEventSubjectNameFilter"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::WebEvent::WebEventNotifier::setEventSubjectNameFilter"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


class WebEventNotifierSetEventSubjectRegexFilterMethodHandler: public Poco::RemotingNG::MethodHandler
{
public:
	void invoke(Poco::RemotingNG::ServerTransport& remoting__trans, Poco::RemotingNG::Deserializer& remoting__deser, Poco::RemotingNG::RemoteObject::Ptr remoting__pRemoteObject)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"setEventSubjectRegexFilter"s,"subscriberURI"s,"regex"s};
		bool remoting__requestSucceeded = false;
		try
		{
			std::string subscriberURI;
			std::string regex;
			remoting__deser.deserializeMessageBegin(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, remoting__deser, subscriberURI);
			Poco::RemotingNG::TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, remoting__deser, regex);
			remoting__deser.deserializeMessageEnd(REMOTING__NAMES[0], Poco::RemotingNG::SerializerBase::MESSAGE_REQUEST);
			IoT::WebEvent::WebEventNotifierRemoteObject* remoting__pCastedRO = static_cast<IoT::WebEvent::WebEventNotifierRemoteObject*>(remoting__pRemoteObject.get());
			remoting__pCastedRO->setEventSubjectRegexFilter(subscriberURI, regex);
			remoting__requestSucceeded = true;
			Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			static const std::string REMOTING__REPLY_NAME("setEventSubjectRegexFilterReply");
			remoting__ser.serializeMessageBegin(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
			remoting__ser.serializeMessageEnd(REMOTING__REPLY_NAME, Poco::RemotingNG::SerializerBase::MESSAGE_REPLY);
		}
		catch (const Poco::Exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				remoting__trans.reportException("IoT::WebEvent::WebEventNotifier::setEventSubjectRegexFilter"s, e);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], e);
			}
		}
		catch (const std::exception& e)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc(e.what());
				remoting__trans.reportException("IoT::WebEvent::WebEventNotifier::setEventSubjectRegexFilter"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
		catch (...)
		{
			if (!remoting__requestSucceeded)
			{
				const Poco::Exception exc("Unknown Exception"s);
				remoting__trans.reportException("IoT::WebEvent::WebEventNotifier::setEventSubjectRegexFilter"s, exc);
				Poco::RemotingNG::Serializer& remoting__ser = remoting__trans.sendReply(Poco::RemotingNG::SerializerBase::MESSAGE_FAULT);
				remoting__ser.serializeFaultMessage(REMOTING__NAMES[0], exc);
			}
		}
	}

};


WebEventNotifierSkeleton::WebEventNotifierSkeleton():
	Poco::RemotingNG::Skeleton()

{
	using namespace std::string_literals;
	
	addMethodHandler("clearEventFilter"s, new IoT::WebEvent::WebEventNotifierClearEventFilterMethodHandler);
	addMethodHandler("notify"s, new IoT::WebEvent::WebEventNotifierNotifyMethodHandler);
	addMethodHandler("setEventSubjectNameFilter"s, new IoT::WebEvent::WebEventNotifierSetEventSubjectNameFilterMethodHandler);
	addMethodHandler("setEventSubjectRegexFilter"s, new IoT::WebEvent::WebEventNotifierSetEventSubjectRegexFilterMethodHandler);
}


WebEventNotifierSkeleton::~WebEventNotifierSkeleton()
{
}


const std::string WebEventNotifierSkeleton::DEFAULT_NS;
} // namespace WebEvent
} // namespace IoT

