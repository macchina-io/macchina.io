//
// CANEndpointRemoteObject.cpp
//
// Library: IoT/CAN
// Package: Generated
// Module:  CANEndpointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/CAN/CANEndpointRemoteObject.h"
#include "IoT/CAN/CANEndpointEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace CAN {


CANEndpointRemoteObject::CANEndpointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::CAN::CANEndpoint> pServiceObject):
	IoT::CAN::ICANEndpoint(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->frameReceived += Poco::delegate(this, &CANEndpointRemoteObject::event__frameReceived);
}


CANEndpointRemoteObject::~CANEndpointRemoteObject()
{
	try
	{
		_pServiceObject->frameReceived -= Poco::delegate(this, &CANEndpointRemoteObject::event__frameReceived);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string CANEndpointRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void CANEndpointRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new CANEndpointEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool CANEndpointRemoteObject::remoting__hasEvents() const
{
	return true;
}


void CANEndpointRemoteObject::event__frameReceived(const IoT::CAN::CANFDFrame& data)
{
	frameReceived(this, data);
}


} // namespace CAN
} // namespace IoT

