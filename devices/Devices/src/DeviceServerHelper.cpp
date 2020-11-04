//
// DeviceServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  DeviceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/DeviceServerHelper.h"
#include "IoT/Devices/DeviceEventDispatcher.h"
#include "IoT/Devices/DeviceSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	static Poco::SingletonHolder<DeviceServerHelper> shDeviceServerHelper;
}


DeviceServerHelper::DeviceServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


DeviceServerHelper::~DeviceServerHelper()
{
}


void DeviceServerHelper::shutdown()
{
	DeviceServerHelper::instance().unregisterSkeleton();
	shDeviceServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::DeviceRemoteObject> DeviceServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Device> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new DeviceRemoteObject(oid, pServiceObject);
}


void DeviceServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<DeviceRemoteObject> pRemoteObject = pIdentifiable.cast<DeviceRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


DeviceServerHelper& DeviceServerHelper::instance()
{
	return *shDeviceServerHelper.get();
}


std::string DeviceServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::DeviceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void DeviceServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.Device", new DeviceSkeleton);
}


void DeviceServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void DeviceServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.Device", true);
}


} // namespace Devices
} // namespace IoT

