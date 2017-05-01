//
// DeviceStatusServiceStub.cpp
//
// Library: IoT/DeviceStatus
// Package: Generated
// Module:  DeviceStatusServiceStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/DeviceStatus/DeviceStatusServiceStub.h"
#include "IoT/DeviceStatus/DeviceStatusServiceEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace DeviceStatus {


DeviceStatusServiceStub::DeviceStatusServiceStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::DeviceStatus::DeviceStatusService> pServiceObject):
	IoT::DeviceStatus::DeviceStatusServiceRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->statusChanged += Poco::delegate(this, &DeviceStatusServiceStub::event__statusChanged);
	_pServiceObject->statusUpdated += Poco::delegate(this, &DeviceStatusServiceStub::event__statusUpdated);
}


DeviceStatusServiceStub::~DeviceStatusServiceStub()
{
	try
	{
		_pServiceObject->statusChanged -= Poco::delegate(this, &DeviceStatusServiceStub::event__statusChanged);
		_pServiceObject->statusUpdated -= Poco::delegate(this, &DeviceStatusServiceStub::event__statusUpdated);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string DeviceStatusServiceStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void DeviceStatusServiceStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new DeviceStatusServiceEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool DeviceStatusServiceStub::remoting__hasEvents() const
{
	return true;
}


void DeviceStatusServiceStub::event__statusChanged(const IoT::DeviceStatus::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


void DeviceStatusServiceStub::event__statusUpdated(const IoT::DeviceStatus::DeviceStatusChange& data)
{
	statusUpdated(this, data);
}


} // namespace DeviceStatus
} // namespace IoT

