//
// XBeeNodeRemoteObject.cpp
//
// Library: IoT/XBee
// Package: Generated
// Module:  XBeeNodeRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/XBee/XBeeNodeRemoteObject.h"
#include "IoT/XBee/XBeeNodeEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace XBee {


XBeeNodeRemoteObject::XBeeNodeRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::XBee::XBeeNode> pServiceObject):
	IoT::XBee::IXBeeNode(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->commandResponseReceived += Poco::delegate(this, &XBeeNodeRemoteObject::event__commandResponseReceived);
	_pServiceObject->explicitAddressingZigBeePacketReceived += Poco::delegate(this, &XBeeNodeRemoteObject::event__explicitAddressingZigBeePacketReceived);
	_pServiceObject->frameReceived += Poco::delegate(this, &XBeeNodeRemoteObject::event__frameReceived);
	_pServiceObject->ioDataReceived += Poco::delegate(this, &XBeeNodeRemoteObject::event__ioDataReceived);
	_pServiceObject->ioSampleReceived += Poco::delegate(this, &XBeeNodeRemoteObject::event__ioSampleReceived);
	_pServiceObject->modemStatusReceived += Poco::delegate(this, &XBeeNodeRemoteObject::event__modemStatusReceived);
	_pServiceObject->packetReceived += Poco::delegate(this, &XBeeNodeRemoteObject::event__packetReceived);
	_pServiceObject->remoteCommandResponseReceived += Poco::delegate(this, &XBeeNodeRemoteObject::event__remoteCommandResponseReceived);
	_pServiceObject->sensorReadReceived += Poco::delegate(this, &XBeeNodeRemoteObject::event__sensorReadReceived);
	_pServiceObject->transmitStatusReceived += Poco::delegate(this, &XBeeNodeRemoteObject::event__transmitStatusReceived);
	_pServiceObject->zigBeePacketReceived += Poco::delegate(this, &XBeeNodeRemoteObject::event__zigBeePacketReceived);
	_pServiceObject->zigBeeTransmitStatusReceived += Poco::delegate(this, &XBeeNodeRemoteObject::event__zigBeeTransmitStatusReceived);
}


XBeeNodeRemoteObject::~XBeeNodeRemoteObject()
{
	try
	{
		_pServiceObject->commandResponseReceived -= Poco::delegate(this, &XBeeNodeRemoteObject::event__commandResponseReceived);
		_pServiceObject->explicitAddressingZigBeePacketReceived -= Poco::delegate(this, &XBeeNodeRemoteObject::event__explicitAddressingZigBeePacketReceived);
		_pServiceObject->frameReceived -= Poco::delegate(this, &XBeeNodeRemoteObject::event__frameReceived);
		_pServiceObject->ioDataReceived -= Poco::delegate(this, &XBeeNodeRemoteObject::event__ioDataReceived);
		_pServiceObject->ioSampleReceived -= Poco::delegate(this, &XBeeNodeRemoteObject::event__ioSampleReceived);
		_pServiceObject->modemStatusReceived -= Poco::delegate(this, &XBeeNodeRemoteObject::event__modemStatusReceived);
		_pServiceObject->packetReceived -= Poco::delegate(this, &XBeeNodeRemoteObject::event__packetReceived);
		_pServiceObject->remoteCommandResponseReceived -= Poco::delegate(this, &XBeeNodeRemoteObject::event__remoteCommandResponseReceived);
		_pServiceObject->sensorReadReceived -= Poco::delegate(this, &XBeeNodeRemoteObject::event__sensorReadReceived);
		_pServiceObject->transmitStatusReceived -= Poco::delegate(this, &XBeeNodeRemoteObject::event__transmitStatusReceived);
		_pServiceObject->zigBeePacketReceived -= Poco::delegate(this, &XBeeNodeRemoteObject::event__zigBeePacketReceived);
		_pServiceObject->zigBeeTransmitStatusReceived -= Poco::delegate(this, &XBeeNodeRemoteObject::event__zigBeeTransmitStatusReceived);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string XBeeNodeRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void XBeeNodeRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new XBeeNodeEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool XBeeNodeRemoteObject::remoting__hasEvents() const
{
	return true;
}


void XBeeNodeRemoteObject::event__commandResponseReceived(const IoT::XBee::ATCommandResponse& data)
{
	commandResponseReceived(this, data);
}


void XBeeNodeRemoteObject::event__explicitAddressingZigBeePacketReceived(const IoT::XBee::ExplicitAddressingZigBeeReceivePacket& data)
{
	explicitAddressingZigBeePacketReceived(this, data);
}


void XBeeNodeRemoteObject::event__frameReceived(const IoT::XBee::APIFrame& data)
{
	frameReceived(this, data);
}


void XBeeNodeRemoteObject::event__ioDataReceived(const IoT::XBee::ReceivePacket& data)
{
	ioDataReceived(this, data);
}


void XBeeNodeRemoteObject::event__ioSampleReceived(const IoT::XBee::IOSample& data)
{
	ioSampleReceived(this, data);
}


void XBeeNodeRemoteObject::event__modemStatusReceived(const IoT::XBee::ModemStatus& data)
{
	modemStatusReceived(this, data);
}


void XBeeNodeRemoteObject::event__packetReceived(const IoT::XBee::ReceivePacket& data)
{
	packetReceived(this, data);
}


void XBeeNodeRemoteObject::event__remoteCommandResponseReceived(const IoT::XBee::RemoteATCommandResponse& data)
{
	remoteCommandResponseReceived(this, data);
}


void XBeeNodeRemoteObject::event__sensorReadReceived(const IoT::XBee::SensorRead& data)
{
	sensorReadReceived(this, data);
}


void XBeeNodeRemoteObject::event__transmitStatusReceived(const IoT::XBee::TransmitStatus& data)
{
	transmitStatusReceived(this, data);
}


void XBeeNodeRemoteObject::event__zigBeePacketReceived(const IoT::XBee::ZigBeeReceivePacket& data)
{
	zigBeePacketReceived(this, data);
}


void XBeeNodeRemoteObject::event__zigBeeTransmitStatusReceived(const IoT::XBee::ZigBeeTransmitStatus& data)
{
	zigBeeTransmitStatusReceived(this, data);
}


} // namespace XBee
} // namespace IoT

