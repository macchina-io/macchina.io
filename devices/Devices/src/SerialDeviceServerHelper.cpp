//
// SerialDeviceServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  SerialDeviceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/SerialDeviceServerHelper.h"
#include "IoT/Devices/SerialDeviceEventDispatcher.h"
#include "IoT/Devices/SerialDeviceSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	static Poco::SingletonHolder<SerialDeviceServerHelper> shSerialDeviceServerHelper;
}


SerialDeviceServerHelper::SerialDeviceServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerSkeleton("SerialDevice", new SerialDeviceSkeleton);
}


SerialDeviceServerHelper::~SerialDeviceServerHelper()
{
	try
	{
		_pORB->unregisterSkeleton("SerialDevice", true);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string SerialDeviceServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::SerialDeviceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return SerialDeviceServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


Poco::AutoPtr<IoT::Devices::SerialDeviceRemoteObject> SerialDeviceServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::SerialDevice> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new SerialDeviceRemoteObject(oid, pServiceObject);
}


void SerialDeviceServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<SerialDeviceRemoteObject> pRemoteObject = pIdentifiable.cast<SerialDeviceRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


SerialDeviceServerHelper& SerialDeviceServerHelper::instance()
{
	return *shSerialDeviceServerHelper.get();
}


std::string SerialDeviceServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::SerialDeviceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void SerialDeviceServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


} // namespace Devices
} // namespace IoT

