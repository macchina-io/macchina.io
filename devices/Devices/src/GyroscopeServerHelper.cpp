//
// GyroscopeServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  GyroscopeServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/GyroscopeServerHelper.h"
#include "IoT/Devices/GyroscopeEventDispatcher.h"
#include "IoT/Devices/GyroscopeSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	static Poco::SingletonHolder<GyroscopeServerHelper> shGyroscopeServerHelper;
}


GyroscopeServerHelper::GyroscopeServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


GyroscopeServerHelper::~GyroscopeServerHelper()
{
}


void GyroscopeServerHelper::shutdown()
{
	GyroscopeServerHelper::instance().unregisterSkeleton();
	shGyroscopeServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::GyroscopeRemoteObject> GyroscopeServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Gyroscope> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new GyroscopeStub(oid, pServiceObject);
}


void GyroscopeServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<GyroscopeRemoteObject> pRemoteObject = pIdentifiable.cast<GyroscopeRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


GyroscopeServerHelper& GyroscopeServerHelper::instance()
{
	return *shGyroscopeServerHelper.get();
}


std::string GyroscopeServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::GyroscopeRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void GyroscopeServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.Gyroscope", new GyroscopeSkeleton);
}


void GyroscopeServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void GyroscopeServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.Gyroscope", true);
}


} // namespace Devices
} // namespace IoT

