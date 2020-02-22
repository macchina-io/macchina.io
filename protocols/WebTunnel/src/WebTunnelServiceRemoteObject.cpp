//
// WebTunnelServiceRemoteObject.cpp
//
// Library: IoT/WebTunnel
// Package: Generated
// Module:  WebTunnelServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2019-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/WebTunnel/WebTunnelServiceRemoteObject.h"
#include "IoT/WebTunnel/WebTunnelServiceEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace WebTunnel {


WebTunnelServiceRemoteObject::WebTunnelServiceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::WebTunnel::WebTunnelService> pServiceObject):
	IoT::WebTunnel::IWebTunnelService(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->connected += Poco::delegate(this, &WebTunnelServiceRemoteObject::event__connected);
	_pServiceObject->disconnected += Poco::delegate(this, &WebTunnelServiceRemoteObject::event__disconnected);
}


WebTunnelServiceRemoteObject::~WebTunnelServiceRemoteObject()
{
	try
	{
		_pServiceObject->connected -= Poco::delegate(this, &WebTunnelServiceRemoteObject::event__connected);
		_pServiceObject->disconnected -= Poco::delegate(this, &WebTunnelServiceRemoteObject::event__disconnected);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string WebTunnelServiceRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void WebTunnelServiceRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new WebTunnelServiceEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool WebTunnelServiceRemoteObject::remoting__hasEvents() const
{
	return true;
}


void WebTunnelServiceRemoteObject::event__connected()
{
	connected(this);
}


void WebTunnelServiceRemoteObject::event__disconnected()
{
	disconnected(this);
}


} // namespace WebTunnel
} // namespace IoT

