//
// CounterServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  CounterServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/CounterServerHelper.h"
#include "IoT/Devices/CounterEventDispatcher.h"
#include "IoT/Devices/CounterSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	static Poco::SingletonHolder<CounterServerHelper> shCounterServerHelper;
}


CounterServerHelper::CounterServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


CounterServerHelper::~CounterServerHelper()
{
}


void CounterServerHelper::shutdown()
{
	CounterServerHelper::instance().unregisterSkeleton();
	shCounterServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::CounterRemoteObject> CounterServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Counter> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new CounterRemoteObject(oid, pServiceObject);
}


void CounterServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<CounterRemoteObject> pRemoteObject = pIdentifiable.cast<CounterRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


CounterServerHelper& CounterServerHelper::instance()
{
	return *shCounterServerHelper.get();
}


std::string CounterServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::CounterRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void CounterServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.Counter", new CounterSkeleton);
}


void CounterServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void CounterServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.Counter", true);
}


} // namespace Devices
} // namespace IoT

