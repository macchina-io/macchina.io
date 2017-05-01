//
// GyroscopeStub.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  GyroscopeStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/GyroscopeStub.h"
#include "IoT/Devices/GyroscopeEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


GyroscopeStub::GyroscopeStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Gyroscope> pServiceObject):
	IoT::Devices::GyroscopeRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->rotationChanged += Poco::delegate(this, &GyroscopeStub::event__rotationChanged);
}


GyroscopeStub::~GyroscopeStub()
{
	try
	{
		_pServiceObject->rotationChanged -= Poco::delegate(this, &GyroscopeStub::event__rotationChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string GyroscopeStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void GyroscopeStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new GyroscopeEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool GyroscopeStub::remoting__hasEvents() const
{
	return true;
}


void GyroscopeStub::event__rotationChanged(const IoT::Devices::Rotation& data)
{
	rotationChanged(this, data);
}


} // namespace Devices
} // namespace IoT

