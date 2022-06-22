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
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/TriggerRemoteObject.h"
#include "IoT/Devices/TriggerEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


TriggerRemoteObject::TriggerRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Trigger> pServiceObject):
	IoT::Devices::ITrigger(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->stateChanged += Poco::delegate(this, &TriggerRemoteObject::event__stateChanged);
	_pServiceObject->statusChanged += Poco::delegate(this, &TriggerRemoteObject::event__statusChanged);
}


TriggerRemoteObject::~TriggerRemoteObject()
{
	try
	{
		_pServiceObject->stateChanged -= Poco::delegate(this, &TriggerRemoteObject::event__stateChanged);
		_pServiceObject->statusChanged -= Poco::delegate(this, &TriggerRemoteObject::event__statusChanged);
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


void TriggerRemoteObject::event__stateChanged(const bool& data)
{
	stateChanged(this, data);
}


void TriggerRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


} // namespace Devices
} // namespace IoT

