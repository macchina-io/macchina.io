//
// CounterDatapointRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  CounterDatapointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/CounterDatapointRemoteObject.h"
#include "IoT/Devices/CounterDatapointEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


CounterDatapointRemoteObject::CounterDatapointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::CounterDatapoint> pServiceObject):
	IoT::Devices::ICounterDatapoint(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->validated += Poco::delegate(this, &CounterDatapointRemoteObject::event__validated);
	_pServiceObject->valueChanged += Poco::delegate(this, &CounterDatapointRemoteObject::event__valueChanged);
	_pServiceObject->invalidated += Poco::delegate(this, &CounterDatapointRemoteObject::event__invalidated);
	_pServiceObject->statusChanged += Poco::delegate(this, &CounterDatapointRemoteObject::event__statusChanged);
}


CounterDatapointRemoteObject::~CounterDatapointRemoteObject()
{
	try
	{
		_pServiceObject->validated -= Poco::delegate(this, &CounterDatapointRemoteObject::event__validated);
		_pServiceObject->valueChanged -= Poco::delegate(this, &CounterDatapointRemoteObject::event__valueChanged);
		_pServiceObject->invalidated -= Poco::delegate(this, &CounterDatapointRemoteObject::event__invalidated);
		_pServiceObject->statusChanged -= Poco::delegate(this, &CounterDatapointRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string CounterDatapointRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void CounterDatapointRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new CounterDatapointEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool CounterDatapointRemoteObject::remoting__hasEvents() const
{
	return true;
}


void CounterDatapointRemoteObject::event__invalidated()
{
	invalidated(this);
}


void CounterDatapointRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


void CounterDatapointRemoteObject::event__validated(const Poco::Int64& data)
{
	validated(this, data);
}


void CounterDatapointRemoteObject::event__valueChanged(const Poco::Int64& data)
{
	valueChanged(this, data);
}


} // namespace Devices
} // namespace IoT

