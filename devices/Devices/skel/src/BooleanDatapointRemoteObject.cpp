//
// BooleanDatapointRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  BooleanDatapointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/BooleanDatapointRemoteObject.h"
#include "IoT/Devices/BooleanDatapointEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


BooleanDatapointRemoteObject::BooleanDatapointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::BooleanDatapoint> pServiceObject):
	IoT::Devices::IBooleanDatapoint(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->validated += Poco::delegate(this, &BooleanDatapointRemoteObject::event__validated);
	_pServiceObject->valueChanged += Poco::delegate(this, &BooleanDatapointRemoteObject::event__valueChanged);
	_pServiceObject->valueUpdated += Poco::delegate(this, &BooleanDatapointRemoteObject::event__valueUpdated);
	_pServiceObject->invalidated += Poco::delegate(this, &BooleanDatapointRemoteObject::event__invalidated);
	_pServiceObject->statusChanged += Poco::delegate(this, &BooleanDatapointRemoteObject::event__statusChanged);
}


BooleanDatapointRemoteObject::~BooleanDatapointRemoteObject()
{
	try
	{
		_pServiceObject->validated -= Poco::delegate(this, &BooleanDatapointRemoteObject::event__validated);
		_pServiceObject->valueChanged -= Poco::delegate(this, &BooleanDatapointRemoteObject::event__valueChanged);
		_pServiceObject->valueUpdated -= Poco::delegate(this, &BooleanDatapointRemoteObject::event__valueUpdated);
		_pServiceObject->invalidated -= Poco::delegate(this, &BooleanDatapointRemoteObject::event__invalidated);
		_pServiceObject->statusChanged -= Poco::delegate(this, &BooleanDatapointRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string BooleanDatapointRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void BooleanDatapointRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new BooleanDatapointEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool BooleanDatapointRemoteObject::remoting__hasEvents() const
{
	return true;
}


void BooleanDatapointRemoteObject::event__invalidated()
{
	invalidated(this);
}


void BooleanDatapointRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


void BooleanDatapointRemoteObject::event__validated(const bool& data)
{
	validated(this, data);
}


void BooleanDatapointRemoteObject::event__valueChanged(const bool& data)
{
	valueChanged(this, data);
}


void BooleanDatapointRemoteObject::event__valueUpdated(const bool& data)
{
	valueUpdated(this, data);
}


} // namespace Devices
} // namespace IoT

