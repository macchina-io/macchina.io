//
// SensorRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  SensorRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/SensorRemoteObject.h"
#include "IoT/Devices/SensorEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


SensorRemoteObject::SensorRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Sensor> pServiceObject):
	IoT::Devices::ISensor(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->valueChanged += Poco::delegate(this, &SensorRemoteObject::event__valueChanged);
	_pServiceObject->statusChanged += Poco::delegate(this, &SensorRemoteObject::event__statusChanged);
}


SensorRemoteObject::~SensorRemoteObject()
{
	try
	{
		_pServiceObject->valueChanged -= Poco::delegate(this, &SensorRemoteObject::event__valueChanged);
		_pServiceObject->statusChanged -= Poco::delegate(this, &SensorRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string SensorRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void SensorRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new SensorEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool SensorRemoteObject::remoting__hasEvents() const
{
	return true;
}


void SensorRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


void SensorRemoteObject::event__valueChanged(const double& data)
{
	valueChanged(this, data);
}


} // namespace Devices
} // namespace IoT

