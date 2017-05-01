//
// MagnetometerStub.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  MagnetometerStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/MagnetometerStub.h"
#include "IoT/Devices/MagnetometerEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


MagnetometerStub::MagnetometerStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Magnetometer> pServiceObject):
	IoT::Devices::MagnetometerRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->fieldStrengthChanged += Poco::delegate(this, &MagnetometerStub::event__fieldStrengthChanged);
}


MagnetometerStub::~MagnetometerStub()
{
	try
	{
		_pServiceObject->fieldStrengthChanged -= Poco::delegate(this, &MagnetometerStub::event__fieldStrengthChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string MagnetometerStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void MagnetometerStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new MagnetometerEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool MagnetometerStub::remoting__hasEvents() const
{
	return true;
}


void MagnetometerStub::event__fieldStrengthChanged(const IoT::Devices::MagneticFieldStrength& data)
{
	fieldStrengthChanged(this, data);
}


} // namespace Devices
} // namespace IoT

