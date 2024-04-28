//
// GyroscopeRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  GyroscopeRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/GyroscopeRemoteObject.h"
#include "IoT/Devices/GyroscopeEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


GyroscopeRemoteObject::GyroscopeRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Gyroscope> pServiceObject):
	IoT::Devices::IGyroscope(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->rotationChanged += Poco::delegate(this, &GyroscopeRemoteObject::event__rotationChanged);
	_pServiceObject->statusChanged += Poco::delegate(this, &GyroscopeRemoteObject::event__statusChanged);
}


GyroscopeRemoteObject::~GyroscopeRemoteObject()
{
	try
	{
		_pServiceObject->rotationChanged -= Poco::delegate(this, &GyroscopeRemoteObject::event__rotationChanged);
		_pServiceObject->statusChanged -= Poco::delegate(this, &GyroscopeRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string GyroscopeRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void GyroscopeRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new GyroscopeEventDispatcher(this, remoting__objectId(), protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool GyroscopeRemoteObject::remoting__hasEvents() const
{
	return true;
}


void GyroscopeRemoteObject::event__rotationChanged(const IoT::Devices::Rotation& data)
{
	rotationChanged(this, data);
}


void GyroscopeRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


} // namespace Devices
} // namespace IoT

