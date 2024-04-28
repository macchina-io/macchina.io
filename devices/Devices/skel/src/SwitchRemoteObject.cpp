//
// SwitchRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  SwitchRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/SwitchRemoteObject.h"
#include "IoT/Devices/SwitchEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


SwitchRemoteObject::SwitchRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Switch> pServiceObject):
	IoT::Devices::ISwitch(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->stateChanged += Poco::delegate(this, &SwitchRemoteObject::event__stateChanged);
	_pServiceObject->statusChanged += Poco::delegate(this, &SwitchRemoteObject::event__statusChanged);
}


SwitchRemoteObject::~SwitchRemoteObject()
{
	try
	{
		_pServiceObject->stateChanged -= Poco::delegate(this, &SwitchRemoteObject::event__stateChanged);
		_pServiceObject->statusChanged -= Poco::delegate(this, &SwitchRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string SwitchRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void SwitchRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new SwitchEventDispatcher(this, remoting__objectId(), protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool SwitchRemoteObject::remoting__hasEvents() const
{
	return true;
}


void SwitchRemoteObject::event__stateChanged(const bool& data)
{
	stateChanged(this, data);
}


void SwitchRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


} // namespace Devices
} // namespace IoT

