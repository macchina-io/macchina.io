//
// BooleanDatapointServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  BooleanDatapointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/BooleanDatapointServerHelper.h"
#include "IoT/Devices/BooleanDatapointEventDispatcher.h"
#include "IoT/Devices/BooleanDatapointSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	Poco::SingletonHolder<BooleanDatapointServerHelper> shBooleanDatapointServerHelper;
}


BooleanDatapointServerHelper::BooleanDatapointServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


BooleanDatapointServerHelper::~BooleanDatapointServerHelper()
{
}


void BooleanDatapointServerHelper::shutdown()
{
	BooleanDatapointServerHelper::instance().unregisterSkeleton();
	shBooleanDatapointServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::BooleanDatapointRemoteObject> BooleanDatapointServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::BooleanDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new BooleanDatapointRemoteObject(oid, pServiceObject);
}


void BooleanDatapointServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<BooleanDatapointRemoteObject> pRemoteObject = pIdentifiable.cast<BooleanDatapointRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


BooleanDatapointServerHelper& BooleanDatapointServerHelper::instance()
{
	return *shBooleanDatapointServerHelper.get();
}


std::string BooleanDatapointServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::BooleanDatapointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void BooleanDatapointServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.BooleanDatapoint", new BooleanDatapointSkeleton);
}


void BooleanDatapointServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void BooleanDatapointServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.BooleanDatapoint", true);
}


} // namespace Devices
} // namespace IoT

