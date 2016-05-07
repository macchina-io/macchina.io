//
// DeviceStatusServiceServerHelper.cpp
//
// Library: IoT/DeviceStatus
// Package: Generated
// Module:  DeviceStatusServiceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/DeviceStatus/DeviceStatusServiceServerHelper.h"
#include "IoT/DeviceStatus/DeviceStatusServiceEventDispatcher.h"
#include "IoT/DeviceStatus/DeviceStatusServiceSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace DeviceStatus {


namespace
{
	static Poco::SingletonHolder<DeviceStatusServiceServerHelper> shDeviceStatusServiceServerHelper;
}


DeviceStatusServiceServerHelper::DeviceStatusServiceServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerSkeleton("IoT.DeviceStatus.DeviceStatusService", new DeviceStatusServiceSkeleton);
}


DeviceStatusServiceServerHelper::~DeviceStatusServiceServerHelper()
{
	try
	{
		_pORB->unregisterSkeleton("IoT.DeviceStatus.DeviceStatusService", true);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string DeviceStatusServiceServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::DeviceStatus::DeviceStatusServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return DeviceStatusServiceServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


Poco::AutoPtr<IoT::DeviceStatus::DeviceStatusServiceRemoteObject> DeviceStatusServiceServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::DeviceStatus::DeviceStatusService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new DeviceStatusServiceRemoteObject(oid, pServiceObject);
}


void DeviceStatusServiceServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<DeviceStatusServiceRemoteObject> pRemoteObject = pIdentifiable.cast<DeviceStatusServiceRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


DeviceStatusServiceServerHelper& DeviceStatusServiceServerHelper::instance()
{
	return *shDeviceStatusServiceServerHelper.get();
}


std::string DeviceStatusServiceServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::DeviceStatus::DeviceStatusServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void DeviceStatusServiceServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


} // namespace DeviceStatus
} // namespace IoT

