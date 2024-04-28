//
// IWebEventNotifier.h
//
// Library: IoT/WebEvent
// Package: Generated
// Module:  IWebEventNotifier
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_WebEvent_IWebEventNotifier_INCLUDED
#define IoT_WebEvent_IWebEventNotifier_INCLUDED


#include "IoT/WebEvent/WebEventNotifier.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace WebEvent {


class IWebEventNotifier: public Poco::OSP::Service
	/// A simplified Remoting-capable interface to the
	/// Poco::OSP::WebEvent::WebEventService,
	/// usable from both C++ and JavaScript.
{
public:
	using Ptr = Poco::AutoPtr<IWebEventNotifier>;

	IWebEventNotifier();
		/// Creates a IWebEventNotifier.

	virtual ~IWebEventNotifier();
		/// Destroys the IWebEventNotifier.

	virtual void clearEventFilter(const std::string& subscriberURI) = 0;
		/// Clears any event filter that has been set with setEventSubjectFilter().

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual void notify(const std::string& subjectName, const std::string& data) = 0;
		/// Notify all registered subscribers to the given subject, using
		/// the given data, which is typically a serialized JSON or
		/// XML document in UTF-8 encoding.
		///
		/// Sending the notification is done asynchronously. If a notification cannot be
		/// delivered to a subscriber due to a network issue, the subscriber will be removed
		/// and its WebSocket closed.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void setEventSubjectNameFilter(const std::string& subscriberURI, const std::string& subjectName) = 0;
		/// Sets a filter on the event to only report events with
		/// the given subjectName.

	virtual void setEventSubjectRegexFilter(const std::string& subscriberURI, const std::string& regex) = 0;
		/// Sets a filter on the event to only report events with
		/// the subjectName matching the specified regex.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent<const IoT::WebEvent::EventNotification> event;
};


} // namespace WebEvent
} // namespace IoT


#endif // IoT_WebEvent_IWebEventNotifier_INCLUDED

