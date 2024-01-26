//
// DatapointRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  DatapointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/DatapointRemoteObject.h"
#include "IoT/Devices/DatapointEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


DatapointRemoteObject::DatapointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Datapoint> pServiceObject):
	IoT::Devices::IDatapoint(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->invalidated += Poco::delegate(this, &DatapointRemoteObject::event__invalidated);
	_pServiceObject->statusChanged += Poco::delegate(this, &DatapointRemoteObject::event__statusChanged);
}


DatapointRemoteObject::~DatapointRemoteObject()
{
	try
	{
		_pServiceObject->invalidated -= Poco::delegate(this, &DatapointRemoteObject::event__invalidated);
		_pServiceObject->statusChanged -= Poco::delegate(this, &DatapointRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string DatapointRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void DatapointRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new DatapointEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool DatapointRemoteObject::remoting__hasEvents() const
{
	return true;
}


void DatapointRemoteObject::event__invalidated()
{
	invalidated(this);
}


void DatapointRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


} // namespace Devices
} // namespace IoT

