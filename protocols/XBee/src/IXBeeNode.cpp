//
// IXBeeNode.cpp
//
// Library: IoT/XBee
// Package: Generated
// Module:  IXBeeNode
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/XBee/IXBeeNode.h"


namespace IoT {
namespace XBee {


IXBeeNode::IXBeeNode():
	Poco::OSP::Service(),
	commandResponseReceived(),
	explicitAddressingZigBeePacketReceived(),
	frameReceived(),
	ioDataReceived(),
	ioSampleReceived(),
	modemStatusReceived(),
	packetReceived(),
	remoteCommandResponseReceived(),
	sensorReadReceived(),
	transmitStatusReceived(),
	zigBeePacketReceived(),
	zigBeeTransmitStatusReceived()
{
}


IXBeeNode::~IXBeeNode()
{
}


bool IXBeeNode::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name();
}


const Poco::RemotingNG::Identifiable::TypeId& IXBeeNode::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("XBeeNode");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


const std::type_info& IXBeeNode::type() const
{
	return typeid(IXBeeNode);
}


} // namespace XBee
} // namespace IoT

