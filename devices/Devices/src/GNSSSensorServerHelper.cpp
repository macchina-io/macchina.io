//
// GNSSSensorServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  GNSSSensorServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/GNSSSensorServerHelper.h"
#include "IoT/Devices/GNSSSensorEventDispatcher.h"
#include "IoT/Devices/GNSSSensorSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	static Poco::SingletonHolder<GNSSSensorServerHelper> shGNSSSensorServerHelper;
}


GNSSSensorServerHelper::GNSSSensorServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


GNSSSensorServerHelper::~GNSSSensorServerHelper()
{
}


void GNSSSensorServerHelper::shutdown()
{
	GNSSSensorServerHelper::instance().unregisterSkeleton();
	shGNSSSensorServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::GNSSSensorRemoteObject> GNSSSensorServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::GNSSSensor> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new GNSSSensorRemoteObject(oid, pServiceObject);
}


void GNSSSensorServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<GNSSSensorRemoteObject> pRemoteObject = pIdentifiable.cast<GNSSSensorRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


GNSSSensorServerHelper& GNSSSensorServerHelper::instance()
{
	return *shGNSSSensorServerHelper.get();
}


std::string GNSSSensorServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::GNSSSensorRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void GNSSSensorServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.GNSSSensor", new GNSSSensorSkeleton);
}


void GNSSSensorServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void GNSSSensorServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.GNSSSensor", true);
}


} // namespace Devices
} // namespace IoT

