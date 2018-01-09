//
// TriggerRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  TriggerRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/TriggerRemoteObject.h"
#include "IoT/Devices/TriggerEventDispatcher.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


TriggerRemoteObject::TriggerRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Trigger> pServiceObject):
	IoT::Devices::ITrigger(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
}


TriggerRemoteObject::~TriggerRemoteObject()
{
	try
	{
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string TriggerRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void TriggerRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new TriggerEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool TriggerRemoteObject::remoting__hasEvents() const
{
	return true;
}


} // namespace Devices
} // namespace IoT

