//
// XBeeNodeStub.cpp
//
// Library: IoT/XBee
// Package: Generated
// Module:  XBeeNodeStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/XBee/XBeeNodeStub.h"
#include "IoT/XBee/XBeeNodeEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace XBee {


XBeeNodeStub::XBeeNodeStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::XBee::XBeeNode> pServiceObject):
	IoT::XBee::XBeeNodeRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->commandResponseReceived += Poco::delegate(this, &XBeeNodeStub::event__commandResponseReceived);
	_pServiceObject->explicitAddressingZigBeePacketReceived += Poco::delegate(this, &XBeeNodeStub::event__explicitAddressingZigBeePacketReceived);
	_pServiceObject->frameReceived += Poco::delegate(this, &XBeeNodeStub::event__frameReceived);
	_pServiceObject->ioDataReceived += Poco::delegate(this, &XBeeNodeStub::event__ioDataReceived);
	_pServiceObject->ioSampleReceived += Poco::delegate(this, &XBeeNodeStub::event__ioSampleReceived);
	_pServiceObject->modemStatusReceived += Poco::delegate(this, &XBeeNodeStub::event__modemStatusReceived);
	_pServiceObject->packetReceived += Poco::delegate(this, &XBeeNodeStub::event__packetReceived);
	_pServiceObject->remoteCommandResponseReceived += Poco::delegate(this, &XBeeNodeStub::event__remoteCommandResponseReceived);
	_pServiceObject->sensorReadReceived += Poco::delegate(this, &XBeeNodeStub::event__sensorReadReceived);
	_pServiceObject->transmitStatusReceived += Poco::delegate(this, &XBeeNodeStub::event__transmitStatusReceived);
	_pServiceObject->zigBeePacketReceived += Poco::delegate(this, &XBeeNodeStub::event__zigBeePacketReceived);
	_pServiceObject->zigBeeTransmitStatusReceived += Poco::delegate(this, &XBeeNodeStub::event__zigBeeTransmitStatusReceived);
}


XBeeNodeStub::~XBeeNodeStub()
{
	try
	{
		_pServiceObject->commandResponseReceived -= Poco::delegate(this, &XBeeNodeStub::event__commandResponseReceived);
		_pServiceObject->explicitAddressingZigBeePacketReceived -= Poco::delegate(this, &XBeeNodeStub::event__explicitAddressingZigBeePacketReceived);
		_pServiceObject->frameReceived -= Poco::delegate(this, &XBeeNodeStub::event__frameReceived);
		_pServiceObject->ioDataReceived -= Poco::delegate(this, &XBeeNodeStub::event__ioDataReceived);
		_pServiceObject->ioSampleReceived -= Poco::delegate(this, &XBeeNodeStub::event__ioSampleReceived);
		_pServiceObject->modemStatusReceived -= Poco::delegate(this, &XBeeNodeStub::event__modemStatusReceived);
		_pServiceObject->packetReceived -= Poco::delegate(this, &XBeeNodeStub::event__packetReceived);
		_pServiceObject->remoteCommandResponseReceived -= Poco::delegate(this, &XBeeNodeStub::event__remoteCommandResponseReceived);
		_pServiceObject->sensorReadReceived -= Poco::delegate(this, &XBeeNodeStub::event__sensorReadReceived);
		_pServiceObject->transmitStatusReceived -= Poco::delegate(this, &XBeeNodeStub::event__transmitStatusReceived);
		_pServiceObject->zigBeePacketReceived -= Poco::delegate(this, &XBeeNodeStub::event__zigBeePacketReceived);
		_pServiceObject->zigBeeTransmitStatusReceived -= Poco::delegate(this, &XBeeNodeStub::event__zigBeeTransmitStatusReceived);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string XBeeNodeStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void XBeeNodeStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new XBeeNodeEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool XBeeNodeStub::remoting__hasEvents() const
{
	return true;
}


void XBeeNodeStub::event__commandResponseReceived(const IoT::XBee::ATCommandResponse& data)
{
	commandResponseReceived(this, data);
}


void XBeeNodeStub::event__explicitAddressingZigBeePacketReceived(const IoT::XBee::ExplicitAddressingZigBeeReceivePacket& data)
{
	explicitAddressingZigBeePacketReceived(this, data);
}


void XBeeNodeStub::event__frameReceived(const IoT::XBee::APIFrame& data)
{
	frameReceived(this, data);
}


void XBeeNodeStub::event__ioDataReceived(const IoT::XBee::ReceivePacket& data)
{
	ioDataReceived(this, data);
}


void XBeeNodeStub::event__ioSampleReceived(const IoT::XBee::IOSample& data)
{
	ioSampleReceived(this, data);
}


void XBeeNodeStub::event__modemStatusReceived(const IoT::XBee::ModemStatus& data)
{
	modemStatusReceived(this, data);
}


void XBeeNodeStub::event__packetReceived(const IoT::XBee::ReceivePacket& data)
{
	packetReceived(this, data);
}


void XBeeNodeStub::event__remoteCommandResponseReceived(const IoT::XBee::RemoteATCommandResponse& data)
{
	remoteCommandResponseReceived(this, data);
}


void XBeeNodeStub::event__sensorReadReceived(const IoT::XBee::SensorRead& data)
{
	sensorReadReceived(this, data);
}


void XBeeNodeStub::event__transmitStatusReceived(const IoT::XBee::TransmitStatus& data)
{
	transmitStatusReceived(this, data);
}


void XBeeNodeStub::event__zigBeePacketReceived(const IoT::XBee::ZigBeeReceivePacket& data)
{
	zigBeePacketReceived(this, data);
}


void XBeeNodeStub::event__zigBeeTransmitStatusReceived(const IoT::XBee::ZigBeeTransmitStatus& data)
{
	zigBeeTransmitStatusReceived(this, data);
}


} // namespace XBee
} // namespace IoT

