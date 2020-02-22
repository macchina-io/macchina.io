//
// PeripheralBrowserServerHelper.cpp
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralBrowserServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/BtLE/PeripheralBrowserServerHelper.h"
#include "IoT/BtLE/PeripheralBrowserEventDispatcher.h"
#include "IoT/BtLE/PeripheralBrowserSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace BtLE {


namespace
{
	static Poco::SingletonHolder<PeripheralBrowserServerHelper> shPeripheralBrowserServerHelper;
}


PeripheralBrowserServerHelper::PeripheralBrowserServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


PeripheralBrowserServerHelper::~PeripheralBrowserServerHelper()
{
}


void PeripheralBrowserServerHelper::shutdown()
{
	PeripheralBrowserServerHelper::instance().unregisterSkeleton();
	shPeripheralBrowserServerHelper.reset();
}


Poco::AutoPtr<IoT::BtLE::PeripheralBrowserRemoteObject> PeripheralBrowserServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::BtLE::PeripheralBrowser> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new PeripheralBrowserRemoteObject(oid, pServiceObject);
}


void PeripheralBrowserServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<PeripheralBrowserRemoteObject> pRemoteObject = pIdentifiable.cast<PeripheralBrowserRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


PeripheralBrowserServerHelper& PeripheralBrowserServerHelper::instance()
{
	return *shPeripheralBrowserServerHelper.get();
}


std::string PeripheralBrowserServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::BtLE::PeripheralBrowserRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void PeripheralBrowserServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.BtLE.PeripheralBrowser", new PeripheralBrowserSkeleton);
}


void PeripheralBrowserServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void PeripheralBrowserServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.BtLE.PeripheralBrowser", true);
}


} // namespace BtLE
} // namespace IoT

