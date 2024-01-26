//
// FlagsDatapointServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  FlagsDatapointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/FlagsDatapointServerHelper.h"
#include "IoT/Devices/FlagsDatapointEventDispatcher.h"
#include "IoT/Devices/FlagsDatapointSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	Poco::SingletonHolder<FlagsDatapointServerHelper> shFlagsDatapointServerHelper;
}


FlagsDatapointServerHelper::FlagsDatapointServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


FlagsDatapointServerHelper::~FlagsDatapointServerHelper()
{
}


void FlagsDatapointServerHelper::shutdown()
{
	FlagsDatapointServerHelper::instance().unregisterSkeleton();
	shFlagsDatapointServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::FlagsDatapointRemoteObject> FlagsDatapointServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::FlagsDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new FlagsDatapointRemoteObject(oid, pServiceObject);
}


void FlagsDatapointServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<FlagsDatapointRemoteObject> pRemoteObject = pIdentifiable.cast<FlagsDatapointRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


FlagsDatapointServerHelper& FlagsDatapointServerHelper::instance()
{
	return *shFlagsDatapointServerHelper.get();
}


std::string FlagsDatapointServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::FlagsDatapointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void FlagsDatapointServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.FlagsDatapoint", new FlagsDatapointSkeleton);
}


void FlagsDatapointServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void FlagsDatapointServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.FlagsDatapoint", true);
}


} // namespace Devices
} // namespace IoT

