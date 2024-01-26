//
// StringDatapointRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  StringDatapointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/StringDatapointRemoteObject.h"
#include "IoT/Devices/StringDatapointEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


StringDatapointRemoteObject::StringDatapointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::StringDatapoint> pServiceObject):
	IoT::Devices::IStringDatapoint(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->validated += Poco::delegate(this, &StringDatapointRemoteObject::event__validated);
	_pServiceObject->valueChanged += Poco::delegate(this, &StringDatapointRemoteObject::event__valueChanged);
	_pServiceObject->valueUpdated += Poco::delegate(this, &StringDatapointRemoteObject::event__valueUpdated);
	_pServiceObject->invalidated += Poco::delegate(this, &StringDatapointRemoteObject::event__invalidated);
	_pServiceObject->statusChanged += Poco::delegate(this, &StringDatapointRemoteObject::event__statusChanged);
}


StringDatapointRemoteObject::~StringDatapointRemoteObject()
{
	try
	{
		_pServiceObject->validated -= Poco::delegate(this, &StringDatapointRemoteObject::event__validated);
		_pServiceObject->valueChanged -= Poco::delegate(this, &StringDatapointRemoteObject::event__valueChanged);
		_pServiceObject->valueUpdated -= Poco::delegate(this, &StringDatapointRemoteObject::event__valueUpdated);
		_pServiceObject->invalidated -= Poco::delegate(this, &StringDatapointRemoteObject::event__invalidated);
		_pServiceObject->statusChanged -= Poco::delegate(this, &StringDatapointRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string StringDatapointRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void StringDatapointRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new StringDatapointEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool StringDatapointRemoteObject::remoting__hasEvents() const
{
	return true;
}


void StringDatapointRemoteObject::event__invalidated()
{
	invalidated(this);
}


void StringDatapointRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


void StringDatapointRemoteObject::event__validated(const std::string& data)
{
	validated(this, data);
}


void StringDatapointRemoteObject::event__valueChanged(const std::string& data)
{
	valueChanged(this, data);
}


void StringDatapointRemoteObject::event__valueUpdated(const std::string& data)
{
	valueUpdated(this, data);
}


} // namespace Devices
} // namespace IoT

