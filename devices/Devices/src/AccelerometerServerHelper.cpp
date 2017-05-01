//
// AccelerometerServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  AccelerometerServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/AccelerometerServerHelper.h"
#include "IoT/Devices/AccelerometerEventDispatcher.h"
#include "IoT/Devices/AccelerometerSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	static Poco::SingletonHolder<AccelerometerServerHelper> shAccelerometerServerHelper;
}


AccelerometerServerHelper::AccelerometerServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


AccelerometerServerHelper::~AccelerometerServerHelper()
{
}


void AccelerometerServerHelper::shutdown()
{
	AccelerometerServerHelper::instance().unregisterSkeleton();
	shAccelerometerServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::AccelerometerRemoteObject> AccelerometerServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Accelerometer> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new AccelerometerStub(oid, pServiceObject);
}


void AccelerometerServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<AccelerometerRemoteObject> pRemoteObject = pIdentifiable.cast<AccelerometerRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


AccelerometerServerHelper& AccelerometerServerHelper::instance()
{
	return *shAccelerometerServerHelper.get();
}


std::string AccelerometerServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::AccelerometerRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void AccelerometerServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.Accelerometer", new AccelerometerSkeleton);
}


void AccelerometerServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void AccelerometerServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.Accelerometer", true);
}


} // namespace Devices
} // namespace IoT

