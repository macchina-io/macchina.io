//
// EnumDatapointServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  EnumDatapointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/EnumDatapointServerHelper.h"
#include "IoT/Devices/EnumDatapointEventDispatcher.h"
#include "IoT/Devices/EnumDatapointSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	Poco::SingletonHolder<EnumDatapointServerHelper> shEnumDatapointServerHelper;
}


EnumDatapointServerHelper::EnumDatapointServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


EnumDatapointServerHelper::~EnumDatapointServerHelper()
{
}


void EnumDatapointServerHelper::shutdown()
{
	EnumDatapointServerHelper::instance().unregisterSkeleton();
	shEnumDatapointServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::EnumDatapointRemoteObject> EnumDatapointServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::EnumDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new EnumDatapointRemoteObject(oid, pServiceObject);
}


void EnumDatapointServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<EnumDatapointRemoteObject> pRemoteObject = pIdentifiable.cast<EnumDatapointRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


EnumDatapointServerHelper& EnumDatapointServerHelper::instance()
{
	return *shEnumDatapointServerHelper.get();
}


std::string EnumDatapointServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::EnumDatapointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void EnumDatapointServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.EnumDatapoint", new EnumDatapointSkeleton);
}


void EnumDatapointServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void EnumDatapointServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.EnumDatapoint", true);
}


} // namespace Devices
} // namespace IoT

