//
// EnumDatapointRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  EnumDatapointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/EnumDatapointRemoteObject.h"
#include "IoT/Devices/EnumDatapointEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


EnumDatapointRemoteObject::EnumDatapointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::EnumDatapoint> pServiceObject):
	IoT::Devices::IEnumDatapoint(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->validated += Poco::delegate(this, &EnumDatapointRemoteObject::event__validated);
	_pServiceObject->valueChanged += Poco::delegate(this, &EnumDatapointRemoteObject::event__valueChanged);
	_pServiceObject->valueUpdated += Poco::delegate(this, &EnumDatapointRemoteObject::event__valueUpdated);
	_pServiceObject->invalidated += Poco::delegate(this, &EnumDatapointRemoteObject::event__invalidated);
	_pServiceObject->statusChanged += Poco::delegate(this, &EnumDatapointRemoteObject::event__statusChanged);
}


EnumDatapointRemoteObject::~EnumDatapointRemoteObject()
{
	try
	{
		_pServiceObject->validated -= Poco::delegate(this, &EnumDatapointRemoteObject::event__validated);
		_pServiceObject->valueChanged -= Poco::delegate(this, &EnumDatapointRemoteObject::event__valueChanged);
		_pServiceObject->valueUpdated -= Poco::delegate(this, &EnumDatapointRemoteObject::event__valueUpdated);
		_pServiceObject->invalidated -= Poco::delegate(this, &EnumDatapointRemoteObject::event__invalidated);
		_pServiceObject->statusChanged -= Poco::delegate(this, &EnumDatapointRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string EnumDatapointRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void EnumDatapointRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new EnumDatapointEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool EnumDatapointRemoteObject::remoting__hasEvents() const
{
	return true;
}


void EnumDatapointRemoteObject::event__invalidated()
{
	invalidated(this);
}


void EnumDatapointRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


void EnumDatapointRemoteObject::event__validated(const int& data)
{
	validated(this, data);
}


void EnumDatapointRemoteObject::event__valueChanged(const int& data)
{
	valueChanged(this, data);
}


void EnumDatapointRemoteObject::event__valueUpdated(const int& data)
{
	valueUpdated(this, data);
}


} // namespace Devices
} // namespace IoT

