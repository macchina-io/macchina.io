//
// AccelerometerRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  AccelerometerRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/AccelerometerRemoteObject.h"
#include "IoT/Devices/AccelerometerEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


AccelerometerRemoteObject::AccelerometerRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Accelerometer> pServiceObject):
	IoT::Devices::IAccelerometer(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->accelerationChanged += Poco::delegate(this, &AccelerometerRemoteObject::event__accelerationChanged);
	_pServiceObject->statusChanged += Poco::delegate(this, &AccelerometerRemoteObject::event__statusChanged);
}


AccelerometerRemoteObject::~AccelerometerRemoteObject()
{
	try
	{
		_pServiceObject->accelerationChanged -= Poco::delegate(this, &AccelerometerRemoteObject::event__accelerationChanged);
		_pServiceObject->statusChanged -= Poco::delegate(this, &AccelerometerRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string AccelerometerRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void AccelerometerRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new AccelerometerEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool AccelerometerRemoteObject::remoting__hasEvents() const
{
	return true;
}


void AccelerometerRemoteObject::event__accelerationChanged(const IoT::Devices::Acceleration& data)
{
	accelerationChanged(this, data);
}


void AccelerometerRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


} // namespace Devices
} // namespace IoT

