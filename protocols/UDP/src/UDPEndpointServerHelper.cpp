//
// UDPEndpointServerHelper.cpp
//
// Library: IoT/UDP
// Package: Generated
// Module:  UDPEndpointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/UDP/UDPEndpointServerHelper.h"
#include "IoT/UDP/UDPEndpointEventDispatcher.h"
#include "IoT/UDP/UDPEndpointSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace UDP {


namespace
{
	Poco::SingletonHolder<UDPEndpointServerHelper> shUDPEndpointServerHelper;
}


UDPEndpointServerHelper::UDPEndpointServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


UDPEndpointServerHelper::~UDPEndpointServerHelper()
{
}


void UDPEndpointServerHelper::shutdown()
{
	UDPEndpointServerHelper::instance().unregisterSkeleton();
	shUDPEndpointServerHelper.reset();
}


Poco::AutoPtr<IoT::UDP::UDPEndpointRemoteObject> UDPEndpointServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::UDP::UDPEndpoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new UDPEndpointRemoteObject(oid, pServiceObject);
}


void UDPEndpointServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<UDPEndpointRemoteObject> pRemoteObject = pIdentifiable.cast<UDPEndpointRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


UDPEndpointServerHelper& UDPEndpointServerHelper::instance()
{
	return *shUDPEndpointServerHelper.get();
}


std::string UDPEndpointServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::UDP::UDPEndpointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void UDPEndpointServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.UDP.UDPEndpoint", new UDPEndpointSkeleton);
}


void UDPEndpointServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void UDPEndpointServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.UDP.UDPEndpoint", true);
}


} // namespace UDP
} // namespace IoT

