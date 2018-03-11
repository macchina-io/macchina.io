//
// CANEndpointServerHelper.cpp
//
// Library: IoT/CAN
// Package: Generated
// Module:  CANEndpointServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/CAN/CANEndpointServerHelper.h"
#include "IoT/CAN/CANEndpointEventDispatcher.h"
#include "IoT/CAN/CANEndpointSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace CAN {


namespace
{
	static Poco::SingletonHolder<CANEndpointServerHelper> shCANEndpointServerHelper;
}


CANEndpointServerHelper::CANEndpointServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


CANEndpointServerHelper::~CANEndpointServerHelper()
{
}


void CANEndpointServerHelper::shutdown()
{
	CANEndpointServerHelper::instance().unregisterSkeleton();
	shCANEndpointServerHelper.reset();
}


Poco::AutoPtr<IoT::CAN::CANEndpointRemoteObject> CANEndpointServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::CAN::CANEndpoint> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new CANEndpointRemoteObject(oid, pServiceObject);
}


void CANEndpointServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<CANEndpointRemoteObject> pRemoteObject = pIdentifiable.cast<CANEndpointRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


CANEndpointServerHelper& CANEndpointServerHelper::instance()
{
	return *shCANEndpointServerHelper.get();
}


std::string CANEndpointServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::CAN::CANEndpointRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void CANEndpointServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.CAN.CANEndpoint", new CANEndpointSkeleton);
}


void CANEndpointServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void CANEndpointServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.CAN.CANEndpoint", true);
}


} // namespace CAN
} // namespace IoT

