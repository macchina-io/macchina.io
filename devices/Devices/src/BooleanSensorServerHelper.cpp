//
// BooleanSensorServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  BooleanSensorServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/BooleanSensorServerHelper.h"
#include "IoT/Devices/BooleanSensorEventDispatcher.h"
#include "IoT/Devices/BooleanSensorSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	Poco::SingletonHolder<BooleanSensorServerHelper> shBooleanSensorServerHelper;
}


BooleanSensorServerHelper::BooleanSensorServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


BooleanSensorServerHelper::~BooleanSensorServerHelper()
{
}


void BooleanSensorServerHelper::shutdown()
{
	BooleanSensorServerHelper::instance().unregisterSkeleton();
	shBooleanSensorServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::BooleanSensorRemoteObject> BooleanSensorServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::BooleanSensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new BooleanSensorRemoteObject(oid, pServiceObject);
}


void BooleanSensorServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<BooleanSensorRemoteObject> pRemoteObject = pIdentifiable.cast<BooleanSensorRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


BooleanSensorServerHelper& BooleanSensorServerHelper::instance()
{
	return *shBooleanSensorServerHelper.get();
}


std::string BooleanSensorServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::BooleanSensorRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void BooleanSensorServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.BooleanSensor", new BooleanSensorSkeleton);
}


void BooleanSensorServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void BooleanSensorServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.BooleanSensor", true);
}


} // namespace Devices
} // namespace IoT

