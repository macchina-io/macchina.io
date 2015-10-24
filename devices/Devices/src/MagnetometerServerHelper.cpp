//
// MagnetometerServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  MagnetometerServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/MagnetometerServerHelper.h"
#include "IoT/Devices/MagnetometerEventDispatcher.h"
#include "IoT/Devices/MagnetometerSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	static Poco::SingletonHolder<MagnetometerServerHelper> shMagnetometerServerHelper;
}


MagnetometerServerHelper::MagnetometerServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerSkeleton("Magnetometer", new MagnetometerSkeleton);
}


MagnetometerServerHelper::~MagnetometerServerHelper()
{
	try
	{
		_pORB->unregisterSkeleton("Magnetometer", true);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string MagnetometerServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::MagnetometerRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return MagnetometerServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


Poco::AutoPtr<IoT::Devices::MagnetometerRemoteObject> MagnetometerServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Magnetometer> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new MagnetometerRemoteObject(oid, pServiceObject);
}


void MagnetometerServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<MagnetometerRemoteObject> pRemoteObject = pIdentifiable.cast<MagnetometerRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


MagnetometerServerHelper& MagnetometerServerHelper::instance()
{
	return *shMagnetometerServerHelper.get();
}


std::string MagnetometerServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::MagnetometerRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void MagnetometerServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


} // namespace Devices
} // namespace IoT

