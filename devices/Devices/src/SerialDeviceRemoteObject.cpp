//
// SerialDeviceRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  SerialDeviceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/SerialDeviceRemoteObject.h"
#include "IoT/Devices/SerialDeviceEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


SerialDeviceRemoteObject::SerialDeviceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::SerialDevice> pServiceObject):
	IoT::Devices::ISerialDevice(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->lineReceived += Poco::delegate(this, &SerialDeviceRemoteObject::event__lineReceived);
}


SerialDeviceRemoteObject::~SerialDeviceRemoteObject()
{
	try
	{
		_pServiceObject->lineReceived -= Poco::delegate(this, &SerialDeviceRemoteObject::event__lineReceived);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void SerialDeviceRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
}


void SerialDeviceRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new SerialDeviceEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool SerialDeviceRemoteObject::remoting__hasEvents() const
{
	return true;
}


void SerialDeviceRemoteObject::event__lineReceived(const std::string& data)
{
	lineReceived(this, data);
}


} // namespace Devices
} // namespace IoT

