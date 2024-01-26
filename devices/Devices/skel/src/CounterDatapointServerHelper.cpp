//
// CounterDatapointServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  CounterDatapointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/CounterDatapointServerHelper.h"
#include "IoT/Devices/CounterDatapointEventDispatcher.h"
#include "IoT/Devices/CounterDatapointSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	Poco::SingletonHolder<CounterDatapointServerHelper> shCounterDatapointServerHelper;
}


CounterDatapointServerHelper::CounterDatapointServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


CounterDatapointServerHelper::~CounterDatapointServerHelper()
{
}


void CounterDatapointServerHelper::shutdown()
{
	CounterDatapointServerHelper::instance().unregisterSkeleton();
	shCounterDatapointServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::CounterDatapointRemoteObject> CounterDatapointServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::CounterDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new CounterDatapointRemoteObject(oid, pServiceObject);
}


void CounterDatapointServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<CounterDatapointRemoteObject> pRemoteObject = pIdentifiable.cast<CounterDatapointRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


CounterDatapointServerHelper& CounterDatapointServerHelper::instance()
{
	return *shCounterDatapointServerHelper.get();
}


std::string CounterDatapointServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::CounterDatapointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void CounterDatapointServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.CounterDatapoint", new CounterDatapointSkeleton);
}


void CounterDatapointServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void CounterDatapointServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.CounterDatapoint", true);
}


} // namespace Devices
} // namespace IoT

