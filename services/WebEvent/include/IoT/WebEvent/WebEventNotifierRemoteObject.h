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
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace WebEvent {


class WebEventNotifierRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::WebEvent::IWebEventNotifier
	/// A simplified Remoting-capable interface to the 
	/// Poco::OSP::WebEvent::WebEventService,
	/// usable from both C++ and JavaScript.
{
public:
	typedef Poco::AutoPtr<WebEventNotifierRemoteObject> Ptr;

	WebEventNotifierRemoteObject();
		/// Creates a WebEventNotifierRemoteObject.

	virtual ~WebEventNotifierRemoteObject();
		/// Destroys the WebEventNotifierRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& WebEventNotifierRemoteObject::remoting__typeId() const
{
	return IWebEventNotifier::remoting__typeId();
}


} // namespace WebEvent
} // namespace IoT


#endif // IoT_WebEvent_WebEventNotifierRemoteObject_INCLUDED

