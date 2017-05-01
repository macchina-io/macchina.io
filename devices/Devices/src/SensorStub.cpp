//
// SensorStub.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  SensorStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/SensorStub.h"
#include "IoT/Devices/SensorEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


SensorStub::SensorStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Sensor> pServiceObject):
	IoT::Devices::SensorRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->valueChanged += Poco::delegate(this, &SensorStub::event__valueChanged);
}


SensorStub::~SensorStub()
{
	try
	{
		_pServiceObject->valueChanged -= Poco::delegate(this, &SensorStub::event__valueChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string SensorStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void SensorStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new SensorEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool SensorStub::remoting__hasEvents() const
{
	return true;
}


void SensorStub::event__valueChanged(const double& data)
{
	valueChanged(this, data);
}


} // namespace Devices
} // namespace IoT

