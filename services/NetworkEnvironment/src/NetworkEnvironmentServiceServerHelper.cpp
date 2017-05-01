//
// NetworkEnvironmentServiceServerHelper.cpp
//
// Library: IoT/NetworkEnvironment
// Package: Generated
// Module:  NetworkEnvironmentServiceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/NetworkEnvironment/NetworkEnvironmentServiceServerHelper.h"
#include "IoT/NetworkEnvironment/NetworkEnvironmentServiceEventDispatcher.h"
#include "IoT/NetworkEnvironment/NetworkEnvironmentServiceSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace NetworkEnvironment {


namespace
{
	static Poco::SingletonHolder<NetworkEnvironmentServiceServerHelper> shNetworkEnvironmentServiceServerHelper;
}


NetworkEnvironmentServiceServerHelper::NetworkEnvironmentServiceServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


NetworkEnvironmentServiceServerHelper::~NetworkEnvironmentServiceServerHelper()
{
}


void NetworkEnvironmentServiceServerHelper::shutdown()
{
	NetworkEnvironmentServiceServerHelper::instance().unregisterSkeleton();
	shNetworkEnvironmentServiceServerHelper.reset();
}


Poco::AutoPtr<IoT::NetworkEnvironment::NetworkEnvironmentServiceRemoteObject> NetworkEnvironmentServiceServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::NetworkEnvironment::NetworkEnvironmentService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new NetworkEnvironmentServiceStub(oid, pServiceObject);
}


void NetworkEnvironmentServiceServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<NetworkEnvironmentServiceRemoteObject> pRemoteObject = pIdentifiable.cast<NetworkEnvironmentServiceRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


NetworkEnvironmentServiceServerHelper& NetworkEnvironmentServiceServerHelper::instance()
{
	return *shNetworkEnvironmentServiceServerHelper.get();
}


std::string NetworkEnvironmentServiceServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::NetworkEnvironment::NetworkEnvironmentServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void NetworkEnvironmentServiceServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.NetworkEnvironment.NetworkEnvironmentService", new NetworkEnvironmentServiceSkeleton);
}


void NetworkEnvironmentServiceServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void NetworkEnvironmentServiceServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.NetworkEnvironment.NetworkEnvironmentService", true);
}


} // namespace NetworkEnvironment
} // namespace IoT

