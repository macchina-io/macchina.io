//
// MQTTClientServerHelper.cpp
//
// Library: IoT/MQTT
// Package: Generated
// Module:  MQTTClientServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/MQTT/MQTTClientServerHelper.h"
#include "IoT/MQTT/MQTTClientEventDispatcher.h"
#include "IoT/MQTT/MQTTClientSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace MQTT {


namespace
{
	Poco::SingletonHolder<MQTTClientServerHelper> shMQTTClientServerHelper;
}


MQTTClientServerHelper::MQTTClientServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


MQTTClientServerHelper::~MQTTClientServerHelper()
{
}


void MQTTClientServerHelper::shutdown()
{
	MQTTClientServerHelper::instance().unregisterSkeleton();
	shMQTTClientServerHelper.reset();
}


Poco::AutoPtr<IoT::MQTT::MQTTClientRemoteObject> MQTTClientServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::MQTT::MQTTClient> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new MQTTClientRemoteObject(oid, pServiceObject);
}


void MQTTClientServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<MQTTClientRemoteObject> pRemoteObject = pIdentifiable.cast<MQTTClientRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


MQTTClientServerHelper& MQTTClientServerHelper::instance()
{
	return *shMQTTClientServerHelper.get();
}


std::string MQTTClientServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::MQTT::MQTTClientRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void MQTTClientServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.MQTT.MQTTClient", new MQTTClientSkeleton);
}


void MQTTClientServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void MQTTClientServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.MQTT.MQTTClient", true);
}


} // namespace MQTT
} // namespace IoT

