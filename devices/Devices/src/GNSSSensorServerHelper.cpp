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
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
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
	_pORB->registerSkeleton("GNSSSensor", new GNSSSensorSkeleton);
}


GNSSSensorServerHelper::~GNSSSensorServerHelper()
{
	try
	{
		_pORB->unregisterSkeleton("GNSSSensor", true);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string GNSSSensorServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::GNSSSensorRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return GNSSSensorServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
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


void GNSSSensorServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


} // namespace Devices
} // namespace IoT

