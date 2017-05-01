//
// SerialDeviceStub.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  SerialDeviceStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/SerialDeviceStub.h"
#include "IoT/Devices/SerialDeviceEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


SerialDeviceStub::SerialDeviceStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::SerialDevice> pServiceObject):
	IoT::Devices::SerialDeviceRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->lineReceived += Poco::delegate(this, &SerialDeviceStub::event__lineReceived);
}


SerialDeviceStub::~SerialDeviceStub()
{
	try
	{
		_pServiceObject->lineReceived -= Poco::delegate(this, &SerialDeviceStub::event__lineReceived);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string SerialDeviceStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void SerialDeviceStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new SerialDeviceEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool SerialDeviceStub::remoting__hasEvents() const
{
	return true;
}


void SerialDeviceStub::event__lineReceived(const std::string& data)
{
	lineReceived(this, data);
}


} // namespace Devices
} // namespace IoT

