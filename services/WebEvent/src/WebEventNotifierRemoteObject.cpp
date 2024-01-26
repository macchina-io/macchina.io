//
// WebEventNotifierRemoteObject.cpp
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


#include "IoT/WebEvent/WebEventNotifierRemoteObject.h"
#include "IoT/WebEvent/WebEventNotifierEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace WebEvent {


WebEventNotifierRemoteObject::WebEventNotifierRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::WebEvent::WebEventNotifier> pServiceObject):
	IoT::WebEvent::IWebEventNotifier(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->event += Poco::delegate(this, &WebEventNotifierRemoteObject::event__event);
}


WebEventNotifierRemoteObject::~WebEventNotifierRemoteObject()
{
	try
	{
		_pServiceObject->event -= Poco::delegate(this, &WebEventNotifierRemoteObject::event__event);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string WebEventNotifierRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void WebEventNotifierRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new WebEventNotifierEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool WebEventNotifierRemoteObject::remoting__hasEvents() const
{
	return true;
}


void WebEventNotifierRemoteObject::event__event(const IoT::WebEvent::EventNotification& data)
{
	event(this, data);
}


} // namespace WebEvent
} // namespace IoT

