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
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
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
}


SwitchRemoteObject::~SwitchRemoteObject()
{
	try
	{
		_pServiceObject->stateChanged -= Poco::delegate(this, &SwitchRemoteObject::event__stateChanged);
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
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new SwitchEventDispatcher(this, protocol);
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


} // namespace Devices
} // namespace IoT

