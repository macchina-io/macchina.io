//
// DeviceTreeServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  DeviceTreeServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/DeviceTreeServerHelper.h"
#include "IoT/Devices/DeviceTreeSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	Poco::SingletonHolder<DeviceTreeServerHelper> shDeviceTreeServerHelper;
}


DeviceTreeServerHelper::DeviceTreeServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


DeviceTreeServerHelper::~DeviceTreeServerHelper()
{
}


void DeviceTreeServerHelper::shutdown()
{
	DeviceTreeServerHelper::instance().unregisterSkeleton();
	shDeviceTreeServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::DeviceTreeRemoteObject> DeviceTreeServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::DeviceTree> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new DeviceTreeRemoteObject(oid, pServiceObject);
}


DeviceTreeServerHelper& DeviceTreeServerHelper::instance()
{
	return *shDeviceTreeServerHelper.get();
}


std::string DeviceTreeServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::DeviceTreeRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void DeviceTreeServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.DeviceTree", new DeviceTreeSkeleton);
}


void DeviceTreeServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void DeviceTreeServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.DeviceTree", true);
}


} // namespace Devices
} // namespace IoT

