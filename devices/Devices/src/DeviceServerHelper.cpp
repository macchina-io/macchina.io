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
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/DeviceServerHelper.h"
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
	_pORB->registerSkeleton("Device", new DeviceSkeleton);
}


DeviceServerHelper::~DeviceServerHelper()
{
	try
	{
		_pORB->unregisterSkeleton("Device", true);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string DeviceServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::DeviceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return DeviceServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


Poco::AutoPtr<IoT::Devices::DeviceRemoteObject> DeviceServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Device> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new DeviceRemoteObject(oid, pServiceObject);
}


DeviceServerHelper& DeviceServerHelper::instance()
{
	return *shDeviceServerHelper.get();
}


std::string DeviceServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::DeviceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void DeviceServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


} // namespace Devices
} // namespace IoT

