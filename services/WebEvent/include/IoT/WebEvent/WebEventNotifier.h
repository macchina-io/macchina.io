//
// WebEventNotifier.h
//
// $Id$
//
// Library: IoT/WebEvent
// Package: WebEventNotifier
// Module:  WebEventNotifier
//
// Definition of the WebEventNotifier interface.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_WebEvent_WebEventNotifier_INCLUDED
#define IoT_WebEvent_WebEventNotifier_INCLUDED


#include "IoT/WebEvent/WebEvent.h"
#include "Poco/AutoPtr.h"


namespace IoT {
namespace WebEvent {


//@ remote
class IoTWebEvent_API WebEventNotifier
	/// A simplified Remoting-capable interface to the 
	/// Poco::OSP::WebEvent::WebEventService,
	/// usable from both C++ and JavaScript.
{
public:
	typedef Poco::AutoPtr<WebEventNotifier> Ptr;

	WebEventNotifier();
		/// Creates the Device.
		
	virtual ~WebEventNotifier();
		/// Destroys the Device.
		
	virtual void notify(const std::string& subjectName, const std::string& data) = 0;
		/// Notify all registered subscribers to the given subject, using
		/// the given data, which is typically a serialized JSON or
		/// XML document in UTF-8 encoding.
		/// 
		/// Sending the notification is done asynchronously. If a notification cannot be
		/// delivered to a subscriber due to a network issue, the subscriber will be removed 
		/// and its WebSocket closed.
};


} } // namespace IoT::WebEvent


#endif // IoT_WebEvent_WebEventNotifier_INCLUDED
