//
// VectorDatapointServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  VectorDatapointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/VectorDatapointServerHelper.h"
#include "IoT/Devices/VectorDatapointEventDispatcher.h"
#include "IoT/Devices/VectorDatapointSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	Poco::SingletonHolder<VectorDatapointServerHelper> shVectorDatapointServerHelper;
}


VectorDatapointServerHelper::VectorDatapointServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


VectorDatapointServerHelper::~VectorDatapointServerHelper()
{
}


void VectorDatapointServerHelper::shutdown()
{
	VectorDatapointServerHelper::instance().unregisterSkeleton();
	shVectorDatapointServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::VectorDatapointRemoteObject> VectorDatapointServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::VectorDatapoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new VectorDatapointRemoteObject(oid, pServiceObject);
}


void VectorDatapointServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<VectorDatapointRemoteObject> pRemoteObject = pIdentifiable.cast<VectorDatapointRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


VectorDatapointServerHelper& VectorDatapointServerHelper::instance()
{
	return *shVectorDatapointServerHelper.get();
}


std::string VectorDatapointServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::VectorDatapointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void VectorDatapointServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.VectorDatapoint", new VectorDatapointSkeleton);
}


void VectorDatapointServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void VectorDatapointServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.VectorDatapoint", true);
}


} // namespace Devices
} // namespace IoT

