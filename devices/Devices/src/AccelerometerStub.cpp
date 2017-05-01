//
// AccelerometerStub.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  AccelerometerStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/AccelerometerStub.h"
#include "IoT/Devices/AccelerometerEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


AccelerometerStub::AccelerometerStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Accelerometer> pServiceObject):
	IoT::Devices::AccelerometerRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->accelerationChanged += Poco::delegate(this, &AccelerometerStub::event__accelerationChanged);
}


AccelerometerStub::~AccelerometerStub()
{
	try
	{
		_pServiceObject->accelerationChanged -= Poco::delegate(this, &AccelerometerStub::event__accelerationChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string AccelerometerStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void AccelerometerStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new AccelerometerEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool AccelerometerStub::remoting__hasEvents() const
{
	return true;
}


void AccelerometerStub::event__accelerationChanged(const IoT::Devices::Acceleration& data)
{
	accelerationChanged(this, data);
}


} // namespace Devices
} // namespace IoT

