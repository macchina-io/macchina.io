//
// IOServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IOServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/IOServerHelper.h"
#include "IoT/Devices/IOEventDispatcher.h"
#include "IoT/Devices/IOSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	static Poco::SingletonHolder<IOServerHelper> shIOServerHelper;
}


IOServerHelper::IOServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


IOServerHelper::~IOServerHelper()
{
}


void IOServerHelper::shutdown()
{
	IOServerHelper::instance().unregisterSkeleton();
	shIOServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::IORemoteObject> IOServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::IO> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new IOStub(oid, pServiceObject);
}


void IOServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<IORemoteObject> pRemoteObject = pIdentifiable.cast<IORemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


IOServerHelper& IOServerHelper::instance()
{
	return *shIOServerHelper.get();
}


std::string IOServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::IORemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void IOServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.IO", new IOSkeleton);
}


void IOServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void IOServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.IO", true);
}


} // namespace Devices
} // namespace IoT

