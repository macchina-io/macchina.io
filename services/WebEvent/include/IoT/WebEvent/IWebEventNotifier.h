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
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_WebEvent_IWebEventNotifier_INCLUDED
#define IoT_WebEvent_IWebEventNotifier_INCLUDED


#include "IoT/WebEvent/WebEventNotifier.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"


namespace IoT {
namespace WebEvent {


class IWebEventNotifier: public Poco::OSP::Service
	/// A simplified Remoting-capable interface to the 
	/// Poco::OSP::WebEvent::WebEventService,
	/// usable from both C++ and JavaScript.
{
public:
	typedef Poco::AutoPtr<IWebEventNotifier> Ptr;

	IWebEventNotifier();
		/// Creates a IWebEventNotifier.

	virtual ~IWebEventNotifier();
		/// Destroys the IWebEventNotifier.

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

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

};


} // namespace WebEvent
} // namespace IoT


#endif // IoT_WebEvent_IWebEventNotifier_INCLUDED

