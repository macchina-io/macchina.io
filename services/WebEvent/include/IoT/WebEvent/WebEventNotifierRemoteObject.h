//
// WebEventNotifierRemoteObject.h
//
// Library: IoT/WebEvent
// Package: Generated
// Module:  WebEventNotifierRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_WebEvent_WebEventNotifierRemoteObject_INCLUDED
#define IoT_WebEvent_WebEventNotifierRemoteObject_INCLUDED


#include "IoT/WebEvent/IWebEventNotifier.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace WebEvent {


class WebEventNotifierRemoteObject: public IoT::WebEvent::IWebEventNotifier, public Poco::RemotingNG::RemoteObject
	/// A simplified Remoting-capable interface to the
	/// Poco::OSP::WebEvent::WebEventService,
	/// usable from both C++ and JavaScript.
{
public:
	using Ptr = Poco::AutoPtr<WebEventNotifierRemoteObject>;

	WebEventNotifierRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::WebEvent::WebEventNotifier> pServiceObject);
		/// Creates a WebEventNotifierRemoteObject.

	virtual ~WebEventNotifierRemoteObject();
		/// Destroys the WebEventNotifierRemoteObject.

	virtual void clearEventFilter(const std::string& subscriberURI);
		/// Clears any event filter that has been set with setEventSubjectFilter().

	virtual void notify(const std::string& subjectName, const std::string& data);
		/// Notify all registered subscribers to the given subject, using
		/// the given data, which is typically a serialized JSON or
		/// XML document in UTF-8 encoding.
		///
		/// Sending the notification is done asynchronously. If a notification cannot be
		/// delivered to a subscriber due to a network issue, the subscriber will be removed
		/// and its WebSocket closed.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void setEventSubjectNameFilter(const std::string& subscriberURI, const std::string& subjectName);
		/// Sets a filter on the event to only report events with
		/// the given subjectName.

	virtual void setEventSubjectRegexFilter(const std::string& subscriberURI, const std::string& regex);
		/// Sets a filter on the event to only report events with
		/// the subjectName matching the specified regex.

protected:
	void event__event(const IoT::WebEvent::EventNotification& data);

private:
	Poco::SharedPtr<IoT::WebEvent::WebEventNotifier> _pServiceObject;
};


inline void WebEventNotifierRemoteObject::clearEventFilter(const std::string& subscriberURI)
{
	_pServiceObject->clearEventFilter(subscriberURI);
}


inline void WebEventNotifierRemoteObject::notify(const std::string& subjectName, const std::string& data)
{
	_pServiceObject->notify(subjectName, data);
}


inline const Poco::RemotingNG::Identifiable::TypeId& WebEventNotifierRemoteObject::remoting__typeId() const
{
	return IWebEventNotifier::remoting__typeId();
}


inline void WebEventNotifierRemoteObject::setEventSubjectNameFilter(const std::string& subscriberURI, const std::string& subjectName)
{
	_pServiceObject->setEventSubjectNameFilter(subscriberURI, subjectName);
}


inline void WebEventNotifierRemoteObject::setEventSubjectRegexFilter(const std::string& subscriberURI, const std::string& regex)
{
	_pServiceObject->setEventSubjectRegexFilter(subscriberURI, regex);
}


} // namespace WebEvent
} // namespace IoT


#endif // IoT_WebEvent_WebEventNotifierRemoteObject_INCLUDED

