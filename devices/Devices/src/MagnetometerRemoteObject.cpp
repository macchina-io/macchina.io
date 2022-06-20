//
// MagnetometerRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  MagnetometerRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/MagnetometerRemoteObject.h"
#include "IoT/Devices/MagnetometerEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


MagnetometerRemoteObject::MagnetometerRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Magnetometer> pServiceObject):
	IoT::Devices::IMagnetometer(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->fieldStrengthChanged += Poco::delegate(this, &MagnetometerRemoteObject::event__fieldStrengthChanged);
	_pServiceObject->statusChanged += Poco::delegate(this, &MagnetometerRemoteObject::event__statusChanged);
}


MagnetometerRemoteObject::~MagnetometerRemoteObject()
{
	try
	{
		_pServiceObject->fieldStrengthChanged -= Poco::delegate(this, &MagnetometerRemoteObject::event__fieldStrengthChanged);
		_pServiceObject->statusChanged -= Poco::delegate(this, &MagnetometerRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string MagnetometerRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void MagnetometerRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new MagnetometerEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool MagnetometerRemoteObject::remoting__hasEvents() const
{
	return true;
}


void MagnetometerRemoteObject::event__fieldStrengthChanged(const IoT::Devices::MagneticFieldStrength& data)
{
	fieldStrengthChanged(this, data);
}


void MagnetometerRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


} // namespace Devices
} // namespace IoT

