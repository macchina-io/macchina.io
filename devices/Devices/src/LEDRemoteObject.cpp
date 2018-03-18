//
// LEDRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  LEDRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/LEDRemoteObject.h"
#include "IoT/Devices/LEDEventDispatcher.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


LEDRemoteObject::LEDRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::LED> pServiceObject):
	IoT::Devices::ILED(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
}


LEDRemoteObject::~LEDRemoteObject()
{
	try
	{
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string LEDRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void LEDRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new LEDEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool LEDRemoteObject::remoting__hasEvents() const
{
	return true;
}


} // namespace Devices
} // namespace IoT

