//
// VectorDatapointRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  VectorDatapointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/VectorDatapointRemoteObject.h"
#include "IoT/Devices/VectorDatapointEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


VectorDatapointRemoteObject::VectorDatapointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::VectorDatapoint> pServiceObject):
	IoT::Devices::IVectorDatapoint(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->validated += Poco::delegate(this, &VectorDatapointRemoteObject::event__validated);
	_pServiceObject->valueChanged += Poco::delegate(this, &VectorDatapointRemoteObject::event__valueChanged);
	_pServiceObject->valueUpdated += Poco::delegate(this, &VectorDatapointRemoteObject::event__valueUpdated);
	_pServiceObject->invalidated += Poco::delegate(this, &VectorDatapointRemoteObject::event__invalidated);
	_pServiceObject->statusChanged += Poco::delegate(this, &VectorDatapointRemoteObject::event__statusChanged);
}


VectorDatapointRemoteObject::~VectorDatapointRemoteObject()
{
	try
	{
		_pServiceObject->validated -= Poco::delegate(this, &VectorDatapointRemoteObject::event__validated);
		_pServiceObject->valueChanged -= Poco::delegate(this, &VectorDatapointRemoteObject::event__valueChanged);
		_pServiceObject->valueUpdated -= Poco::delegate(this, &VectorDatapointRemoteObject::event__valueUpdated);
		_pServiceObject->invalidated -= Poco::delegate(this, &VectorDatapointRemoteObject::event__invalidated);
		_pServiceObject->statusChanged -= Poco::delegate(this, &VectorDatapointRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string VectorDatapointRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void VectorDatapointRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new VectorDatapointEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool VectorDatapointRemoteObject::remoting__hasEvents() const
{
	return true;
}


void VectorDatapointRemoteObject::event__invalidated()
{
	invalidated(this);
}


void VectorDatapointRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


void VectorDatapointRemoteObject::event__validated(const std::vector < double >& data)
{
	validated(this, data);
}


void VectorDatapointRemoteObject::event__valueChanged(const std::vector < double >& data)
{
	valueChanged(this, data);
}


void VectorDatapointRemoteObject::event__valueUpdated(const std::vector < double >& data)
{
	valueUpdated(this, data);
}


} // namespace Devices
} // namespace IoT

