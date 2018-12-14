//
// StateServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  StateServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/StateServerHelper.h"
#include "IoT/Devices/StateEventDispatcher.h"
#include "IoT/Devices/StateSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	static Poco::SingletonHolder<StateServerHelper> shStateServerHelper;
}


StateServerHelper::StateServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


StateServerHelper::~StateServerHelper()
{
}


void StateServerHelper::shutdown()
{
	StateServerHelper::instance().unregisterSkeleton();
	shStateServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::StateRemoteObject> StateServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::State> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new StateRemoteObject(oid, pServiceObject);
}


void StateServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<StateRemoteObject> pRemoteObject = pIdentifiable.cast<StateRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


StateServerHelper& StateServerHelper::instance()
{
	return *shStateServerHelper.get();
}


std::string StateServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::StateRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void StateServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.State", new StateSkeleton);
}


void StateServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void StateServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.State", true);
}


} // namespace Devices
} // namespace IoT

