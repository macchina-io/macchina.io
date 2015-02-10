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
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
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
	_pServiceObject->accelerationUpdate += Poco::delegate(this, &AccelerometerRemoteObject::event__accelerationUpdate);
}


AccelerometerRemoteObject::~AccelerometerRemoteObject()
{
	try
	{
		_pServiceObject->accelerationUpdate -= Poco::delegate(this, &AccelerometerRemoteObject::event__accelerationUpdate);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void AccelerometerRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
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


void AccelerometerRemoteObject::event__accelerationUpdate(const IoT::Devices::Acceleration& data)
{
	accelerationUpdate(this, data);
}


} // namespace Devices
} // namespace IoT

