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
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
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
	typedef Poco::AutoPtr<WebEventNotifierRemoteObject> Ptr;

	WebEventNotifierRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::WebEvent::WebEventNotifier> pServiceObject);
		/// Creates a WebEventNotifierRemoteObject.

	virtual ~WebEventNotifierRemoteObject();
		/// Destroys the WebEventNotifierRemoteObject.

	virtual void notify(const std::string& subjectName, const std::string& data);
		/// Notify all registered subscribers to the given subject, using
		/// the given data, which is typically a serialized JSON or
		/// XML document in UTF-8 encoding.
		/// 
		/// Sending the notification is done asynchronously. If a notification cannot be
		/// delivered to a subscriber due to a network issue, the subscriber will be removed 
		/// and its WebSocket closed.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	Poco::SharedPtr<IoT::WebEvent::WebEventNotifier> _pServiceObject;
};


inline void WebEventNotifierRemoteObject::notify(const std::string& subjectName, const std::string& data)
{
	_pServiceObject->notify(subjectName, data);
}


inline const Poco::RemotingNG::Identifiable::TypeId& WebEventNotifierRemoteObject::remoting__typeId() const
{
	return IWebEventNotifier::remoting__typeId();
}


} // namespace WebEvent
} // namespace IoT


#endif // IoT_WebEvent_WebEventNotifierRemoteObject_INCLUDED

