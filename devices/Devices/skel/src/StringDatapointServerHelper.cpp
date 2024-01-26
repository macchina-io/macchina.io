//
// StringDatapointServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  StringDatapointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/StringDatapointServerHelper.h"
#include "IoT/Devices/StringDatapointEventDispatcher.h"
#include "IoT/Devices/StringDatapointSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	Poco::SingletonHolder<StringDatapointServerHelper> shStringDatapointServerHelper;
}


StringDatapointServerHelper::StringDatapointServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


StringDatapointServerHelper::~StringDatapointServerHelper()
{
}


void StringDatapointServerHelper::shutdown()
{
	StringDatapointServerHelper::instance().unregisterSkeleton();
	shStringDatapointServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::StringDatapointRemoteObject> StringDatapointServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::StringDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new StringDatapointRemoteObject(oid, pServiceObject);
}


void StringDatapointServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<StringDatapointRemoteObject> pRemoteObject = pIdentifiable.cast<StringDatapointRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


StringDatapointServerHelper& StringDatapointServerHelper::instance()
{
	return *shStringDatapointServerHelper.get();
}


std::string StringDatapointServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::StringDatapointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void StringDatapointServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.StringDatapoint", new StringDatapointSkeleton);
}


void StringDatapointServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void StringDatapointServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.StringDatapoint", true);
}


} // namespace Devices
} // namespace IoT

