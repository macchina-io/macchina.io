//
// StateRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  StateRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/StateRemoteObject.h"
#include "IoT/Devices/StateEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


StateRemoteObject::StateRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::State> pServiceObject):
	IoT::Devices::IState(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->stateChanged += Poco::delegate(this, &StateRemoteObject::event__stateChanged);
	_pServiceObject->statusChanged += Poco::delegate(this, &StateRemoteObject::event__statusChanged);
}


StateRemoteObject::~StateRemoteObject()
{
	try
	{
		_pServiceObject->stateChanged -= Poco::delegate(this, &StateRemoteObject::event__stateChanged);
		_pServiceObject->statusChanged -= Poco::delegate(this, &StateRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string StateRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void StateRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new StateEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool StateRemoteObject::remoting__hasEvents() const
{
	return true;
}


void StateRemoteObject::event__stateChanged(const Poco::UInt32& data)
{
	stateChanged(this, data);
}


void StateRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


} // namespace Devices
} // namespace IoT

