//
// FlagsDatapointRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  FlagsDatapointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/FlagsDatapointRemoteObject.h"
#include "IoT/Devices/FlagsDatapointEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


FlagsDatapointRemoteObject::FlagsDatapointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::FlagsDatapoint> pServiceObject):
	IoT::Devices::IFlagsDatapoint(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->validated += Poco::delegate(this, &FlagsDatapointRemoteObject::event__validated);
	_pServiceObject->valueChanged += Poco::delegate(this, &FlagsDatapointRemoteObject::event__valueChanged);
	_pServiceObject->valueUpdated += Poco::delegate(this, &FlagsDatapointRemoteObject::event__valueUpdated);
	_pServiceObject->invalidated += Poco::delegate(this, &FlagsDatapointRemoteObject::event__invalidated);
	_pServiceObject->statusChanged += Poco::delegate(this, &FlagsDatapointRemoteObject::event__statusChanged);
}


FlagsDatapointRemoteObject::~FlagsDatapointRemoteObject()
{
	try
	{
		_pServiceObject->validated -= Poco::delegate(this, &FlagsDatapointRemoteObject::event__validated);
		_pServiceObject->valueChanged -= Poco::delegate(this, &FlagsDatapointRemoteObject::event__valueChanged);
		_pServiceObject->valueUpdated -= Poco::delegate(this, &FlagsDatapointRemoteObject::event__valueUpdated);
		_pServiceObject->invalidated -= Poco::delegate(this, &FlagsDatapointRemoteObject::event__invalidated);
		_pServiceObject->statusChanged -= Poco::delegate(this, &FlagsDatapointRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string FlagsDatapointRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void FlagsDatapointRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new FlagsDatapointEventDispatcher(this, remoting__objectId(), protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool FlagsDatapointRemoteObject::remoting__hasEvents() const
{
	return true;
}


void FlagsDatapointRemoteObject::event__invalidated()
{
	invalidated(this);
}


void FlagsDatapointRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


void FlagsDatapointRemoteObject::event__validated(const std::vector<bool>& data)
{
	validated(this, data);
}


void FlagsDatapointRemoteObject::event__valueChanged(const std::vector<bool>& data)
{
	valueChanged(this, data);
}


void FlagsDatapointRemoteObject::event__valueUpdated(const std::vector<bool>& data)
{
	valueUpdated(this, data);
}


} // namespace Devices
} // namespace IoT

