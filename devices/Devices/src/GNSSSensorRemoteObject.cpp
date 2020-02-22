//
// GNSSSensorRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  GNSSSensorRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/GNSSSensorRemoteObject.h"
#include "IoT/Devices/GNSSSensorEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


GNSSSensorRemoteObject::GNSSSensorRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::GNSSSensor> pServiceObject):
	IoT::Devices::IGNSSSensor(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->positionLost += Poco::delegate(this, &GNSSSensorRemoteObject::event__positionLost);
	_pServiceObject->positionUpdate += Poco::delegate(this, &GNSSSensorRemoteObject::event__positionUpdate);
	_pServiceObject->statusChanged += Poco::delegate(this, &GNSSSensorRemoteObject::event__statusChanged);
}


GNSSSensorRemoteObject::~GNSSSensorRemoteObject()
{
	try
	{
		_pServiceObject->positionLost -= Poco::delegate(this, &GNSSSensorRemoteObject::event__positionLost);
		_pServiceObject->positionUpdate -= Poco::delegate(this, &GNSSSensorRemoteObject::event__positionUpdate);
		_pServiceObject->statusChanged -= Poco::delegate(this, &GNSSSensorRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string GNSSSensorRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void GNSSSensorRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new GNSSSensorEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool GNSSSensorRemoteObject::remoting__hasEvents() const
{
	return true;
}


void GNSSSensorRemoteObject::event__positionLost()
{
	positionLost(this);
}


void GNSSSensorRemoteObject::event__positionUpdate(const IoT::Devices::PositionUpdate& data)
{
	positionUpdate(this, data);
}


void GNSSSensorRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


} // namespace Devices
} // namespace IoT

