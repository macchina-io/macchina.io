//
// DatapointServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  DatapointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/DatapointServerHelper.h"
#include "IoT/Devices/DatapointEventDispatcher.h"
#include "IoT/Devices/DatapointSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	Poco::SingletonHolder<DatapointServerHelper> shDatapointServerHelper;
}


DatapointServerHelper::DatapointServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


DatapointServerHelper::~DatapointServerHelper()
{
}


void DatapointServerHelper::shutdown()
{
	DatapointServerHelper::instance().unregisterSkeleton();
	shDatapointServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::DatapointRemoteObject> DatapointServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Datapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new DatapointRemoteObject(oid, pServiceObject);
}


void DatapointServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<DatapointRemoteObject> pRemoteObject = pIdentifiable.cast<DatapointRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


DatapointServerHelper& DatapointServerHelper::instance()
{
	return *shDatapointServerHelper.get();
}


std::string DatapointServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::DatapointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void DatapointServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.Datapoint", new DatapointSkeleton);
}


void DatapointServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void DatapointServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.Datapoint", true);
}


} // namespace Devices
} // namespace IoT

