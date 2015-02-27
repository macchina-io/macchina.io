//
// IMQTTClient.cpp
//
// Library: IoT/MQTT
// Package: Generated
// Module:  IMQTTClient
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/MQTT/IMQTTClient.h"


namespace IoT {
namespace MQTT {


IMQTTClient::IMQTTClient():
	Poco::OSP::Service(),
	connectionLost(),
	messageArrived(),
	messageDelivered()
{
}


IMQTTClient::~IMQTTClient()
{
}


bool IMQTTClient::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name();
}


const Poco::RemotingNG::Identifiable::TypeId& IMQTTClient::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("MQTTClient");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


const std::type_info& IMQTTClient::type() const
{
	return typeid(IMQTTClient);
}


} // namespace MQTT
} // namespace IoT

