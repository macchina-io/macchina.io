//
// ScalarDatapointRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  ScalarDatapointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/ScalarDatapointRemoteObject.h"
#include "IoT/Devices/ScalarDatapointEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


ScalarDatapointRemoteObject::ScalarDatapointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::ScalarDatapoint> pServiceObject):
	IoT::Devices::IScalarDatapoint(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->validated += Poco::delegate(this, &ScalarDatapointRemoteObject::event__validated);
	_pServiceObject->valueChanged += Poco::delegate(this, &ScalarDatapointRemoteObject::event__valueChanged);
	_pServiceObject->valueUpdated += Poco::delegate(this, &ScalarDatapointRemoteObject::event__valueUpdated);
	_pServiceObject->invalidated += Poco::delegate(this, &ScalarDatapointRemoteObject::event__invalidated);
	_pServiceObject->statusChanged += Poco::delegate(this, &ScalarDatapointRemoteObject::event__statusChanged);
}


ScalarDatapointRemoteObject::~ScalarDatapointRemoteObject()
{
	try
	{
		_pServiceObject->validated -= Poco::delegate(this, &ScalarDatapointRemoteObject::event__validated);
		_pServiceObject->valueChanged -= Poco::delegate(this, &ScalarDatapointRemoteObject::event__valueChanged);
		_pServiceObject->valueUpdated -= Poco::delegate(this, &ScalarDatapointRemoteObject::event__valueUpdated);
		_pServiceObject->invalidated -= Poco::delegate(this, &ScalarDatapointRemoteObject::event__invalidated);
		_pServiceObject->statusChanged -= Poco::delegate(this, &ScalarDatapointRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string ScalarDatapointRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void ScalarDatapointRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new ScalarDatapointEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool ScalarDatapointRemoteObject::remoting__hasEvents() const
{
	return true;
}


void ScalarDatapointRemoteObject::event__invalidated()
{
	invalidated(this);
}


void ScalarDatapointRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


void ScalarDatapointRemoteObject::event__validated(const double& data)
{
	validated(this, data);
}


void ScalarDatapointRemoteObject::event__valueChanged(const double& data)
{
	valueChanged(this, data);
}


void ScalarDatapointRemoteObject::event__valueUpdated(const double& data)
{
	valueUpdated(this, data);
}


} // namespace Devices
} // namespace IoT

