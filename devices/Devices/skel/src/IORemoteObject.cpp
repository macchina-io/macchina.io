//
// IORemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IORemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/IORemoteObject.h"
#include "IoT/Devices/IOEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


IORemoteObject::IORemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::IO> pServiceObject):
	IoT::Devices::IIO(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->stateChanged += Poco::delegate(this, &IORemoteObject::event__stateChanged);
	_pServiceObject->statusChanged += Poco::delegate(this, &IORemoteObject::event__statusChanged);
}


IORemoteObject::~IORemoteObject()
{
	try
	{
		_pServiceObject->stateChanged -= Poco::delegate(this, &IORemoteObject::event__stateChanged);
		_pServiceObject->statusChanged -= Poco::delegate(this, &IORemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string IORemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void IORemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new IOEventDispatcher(this, remoting__objectId(), protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool IORemoteObject::remoting__hasEvents() const
{
	return true;
}


void IORemoteObject::event__stateChanged(const bool& data)
{
	stateChanged(this, data);
}


void IORemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


} // namespace Devices
} // namespace IoT

