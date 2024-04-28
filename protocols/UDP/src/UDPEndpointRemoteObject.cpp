//
// UDPEndpointRemoteObject.cpp
//
// Library: IoT/UDP
// Package: Generated
// Module:  UDPEndpointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/UDP/UDPEndpointRemoteObject.h"
#include "IoT/UDP/UDPEndpointEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace UDP {


UDPEndpointRemoteObject::UDPEndpointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::UDP::UDPEndpoint> pServiceObject):
	IoT::UDP::IUDPEndpoint(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->packetReceived += Poco::delegate(this, &UDPEndpointRemoteObject::event__packetReceived);
}


UDPEndpointRemoteObject::~UDPEndpointRemoteObject()
{
	try
	{
		_pServiceObject->packetReceived -= Poco::delegate(this, &UDPEndpointRemoteObject::event__packetReceived);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string UDPEndpointRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void UDPEndpointRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new UDPEndpointEventDispatcher(this, remoting__objectId(), protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool UDPEndpointRemoteObject::remoting__hasEvents() const
{
	return true;
}


void UDPEndpointRemoteObject::event__packetReceived(const IoT::UDP::Packet& data)
{
	packetReceived(this, data);
}


} // namespace UDP
} // namespace IoT

