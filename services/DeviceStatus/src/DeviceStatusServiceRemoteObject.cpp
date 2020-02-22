//
// DeviceStatusServiceRemoteObject.cpp
//
// Library: IoT/DeviceStatus
// Package: Generated
// Module:  DeviceStatusServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/DeviceStatus/DeviceStatusServiceRemoteObject.h"
#include "IoT/DeviceStatus/DeviceStatusServiceEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace DeviceStatus {


DeviceStatusServiceRemoteObject::DeviceStatusServiceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::DeviceStatus::DeviceStatusService> pServiceObject):
	IoT::DeviceStatus::IDeviceStatusService(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->statusChanged += Poco::delegate(this, &DeviceStatusServiceRemoteObject::event__statusChanged);
	_pServiceObject->statusUpdated += Poco::delegate(this, &DeviceStatusServiceRemoteObject::event__statusUpdated);
}


DeviceStatusServiceRemoteObject::~DeviceStatusServiceRemoteObject()
{
	try
	{
		_pServiceObject->statusChanged -= Poco::delegate(this, &DeviceStatusServiceRemoteObject::event__statusChanged);
		_pServiceObject->statusUpdated -= Poco::delegate(this, &DeviceStatusServiceRemoteObject::event__statusUpdated);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string DeviceStatusServiceRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void DeviceStatusServiceRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new DeviceStatusServiceEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool DeviceStatusServiceRemoteObject::remoting__hasEvents() const
{
	return true;
}


void DeviceStatusServiceRemoteObject::event__statusChanged(const IoT::DeviceStatus::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


void DeviceStatusServiceRemoteObject::event__statusUpdated(const IoT::DeviceStatus::DeviceStatusChange& data)
{
	statusUpdated(this, data);
}


} // namespace DeviceStatus
} // namespace IoT

