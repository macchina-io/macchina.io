//
// BooleanSensorRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  BooleanSensorRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/BooleanSensorRemoteObject.h"
#include "IoT/Devices/BooleanSensorEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


BooleanSensorRemoteObject::BooleanSensorRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::BooleanSensor> pServiceObject):
	IoT::Devices::IBooleanSensor(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->stateChanged += Poco::delegate(this, &BooleanSensorRemoteObject::event__stateChanged);
	_pServiceObject->statusChanged += Poco::delegate(this, &BooleanSensorRemoteObject::event__statusChanged);
}


BooleanSensorRemoteObject::~BooleanSensorRemoteObject()
{
	try
	{
		_pServiceObject->stateChanged -= Poco::delegate(this, &BooleanSensorRemoteObject::event__stateChanged);
		_pServiceObject->statusChanged -= Poco::delegate(this, &BooleanSensorRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string BooleanSensorRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void BooleanSensorRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new BooleanSensorEventDispatcher(this, remoting__objectId(), protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool BooleanSensorRemoteObject::remoting__hasEvents() const
{
	return true;
}


void BooleanSensorRemoteObject::event__stateChanged(const bool& data)
{
	stateChanged(this, data);
}


void BooleanSensorRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


} // namespace Devices
} // namespace IoT

