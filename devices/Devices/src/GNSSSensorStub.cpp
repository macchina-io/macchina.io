//
// GNSSSensorStub.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  GNSSSensorStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/GNSSSensorStub.h"
#include "IoT/Devices/GNSSSensorEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


GNSSSensorStub::GNSSSensorStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::GNSSSensor> pServiceObject):
	IoT::Devices::GNSSSensorRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->positionLost += Poco::delegate(this, &GNSSSensorStub::event__positionLost);
	_pServiceObject->positionUpdate += Poco::delegate(this, &GNSSSensorStub::event__positionUpdate);
}


GNSSSensorStub::~GNSSSensorStub()
{
	try
	{
		_pServiceObject->positionLost -= Poco::delegate(this, &GNSSSensorStub::event__positionLost);
		_pServiceObject->positionUpdate -= Poco::delegate(this, &GNSSSensorStub::event__positionUpdate);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string GNSSSensorStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void GNSSSensorStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new GNSSSensorEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool GNSSSensorStub::remoting__hasEvents() const
{
	return true;
}


void GNSSSensorStub::event__positionLost()
{
	positionLost(this);
}


void GNSSSensorStub::event__positionUpdate(const IoT::Devices::PositionUpdate& data)
{
	positionUpdate(this, data);
}


} // namespace Devices
} // namespace IoT

