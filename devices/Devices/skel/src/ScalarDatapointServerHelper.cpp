//
// ScalarDatapointServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  ScalarDatapointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/ScalarDatapointServerHelper.h"
#include "IoT/Devices/ScalarDatapointEventDispatcher.h"
#include "IoT/Devices/ScalarDatapointSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	Poco::SingletonHolder<ScalarDatapointServerHelper> shScalarDatapointServerHelper;
}


ScalarDatapointServerHelper::ScalarDatapointServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


ScalarDatapointServerHelper::~ScalarDatapointServerHelper()
{
}


void ScalarDatapointServerHelper::shutdown()
{
	ScalarDatapointServerHelper::instance().unregisterSkeleton();
	shScalarDatapointServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::ScalarDatapointRemoteObject> ScalarDatapointServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::ScalarDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new ScalarDatapointRemoteObject(oid, pServiceObject);
}


void ScalarDatapointServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<ScalarDatapointRemoteObject> pRemoteObject = pIdentifiable.cast<ScalarDatapointRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


ScalarDatapointServerHelper& ScalarDatapointServerHelper::instance()
{
	return *shScalarDatapointServerHelper.get();
}


std::string ScalarDatapointServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::ScalarDatapointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void ScalarDatapointServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.ScalarDatapoint", new ScalarDatapointSkeleton);
}


void ScalarDatapointServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void ScalarDatapointServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.ScalarDatapoint", true);
}


} // namespace Devices
} // namespace IoT

