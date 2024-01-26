//
// PeripheralServerHelper.cpp
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/BtLE/PeripheralServerHelper.h"
#include "IoT/BtLE/PeripheralEventDispatcher.h"
#include "IoT/BtLE/PeripheralSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace BtLE {


namespace
{
	Poco::SingletonHolder<PeripheralServerHelper> shPeripheralServerHelper;
}


PeripheralServerHelper::PeripheralServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


PeripheralServerHelper::~PeripheralServerHelper()
{
}


void PeripheralServerHelper::shutdown()
{
	PeripheralServerHelper::instance().unregisterSkeleton();
	shPeripheralServerHelper.reset();
}


Poco::AutoPtr<IoT::BtLE::PeripheralRemoteObject> PeripheralServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::BtLE::Peripheral> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new PeripheralRemoteObject(oid, pServiceObject);
}


void PeripheralServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<PeripheralRemoteObject> pRemoteObject = pIdentifiable.cast<PeripheralRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


PeripheralServerHelper& PeripheralServerHelper::instance()
{
	return *shPeripheralServerHelper.get();
}


std::string PeripheralServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::BtLE::PeripheralRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void PeripheralServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.BtLE.Peripheral", new PeripheralSkeleton);
}


void PeripheralServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void PeripheralServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.BtLE.Peripheral", true);
}


} // namespace BtLE
} // namespace IoT

