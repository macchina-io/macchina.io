//
// UDPEndpointStub.cpp
//
// Library: IoT/UDP
// Package: Generated
// Module:  UDPEndpointStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/UDP/UDPEndpointStub.h"
#include "IoT/UDP/UDPEndpointEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace UDP {


UDPEndpointStub::UDPEndpointStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::UDP::UDPEndpoint> pServiceObject):
	IoT::UDP::UDPEndpointRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->packetReceived += Poco::delegate(this, &UDPEndpointStub::event__packetReceived);
}


UDPEndpointStub::~UDPEndpointStub()
{
	try
	{
		_pServiceObject->packetReceived -= Poco::delegate(this, &UDPEndpointStub::event__packetReceived);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string UDPEndpointStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void UDPEndpointStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new UDPEndpointEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool UDPEndpointStub::remoting__hasEvents() const
{
	return true;
}


void UDPEndpointStub::event__packetReceived(const IoT::UDP::Packet& data)
{
	packetReceived(this, data);
}


} // namespace UDP
} // namespace IoT

