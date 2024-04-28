//
// ModbusMasterRemoteObject.cpp
//
// Library: IoT/Modbus
// Package: Generated
// Module:  ModbusMasterRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Modbus/ModbusMasterRemoteObject.h"
#include "IoT/Modbus/ModbusMasterEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Modbus {


ModbusMasterRemoteObject::ModbusMasterRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Modbus::ModbusMaster> pServiceObject):
	IoT::Modbus::IModbusMaster(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->badFrameReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__badFrameReceived);
	_pServiceObject->connectionStateChanged += Poco::delegate(this, &ModbusMasterRemoteObject::event__connectionStateChanged);
	_pServiceObject->error += Poco::delegate(this, &ModbusMasterRemoteObject::event__error);
	_pServiceObject->exceptionReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__exceptionReceived);
	_pServiceObject->maskWriteRegisterResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__maskWriteRegisterResponseReceived);
	_pServiceObject->readCoilsResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__readCoilsResponseReceived);
	_pServiceObject->readDiscreteInputsResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__readDiscreteInputsResponseReceived);
	_pServiceObject->readExceptionStatusResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__readExceptionStatusResponseReceived);
	_pServiceObject->readFIFOQueueResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__readFIFOQueueResponseReceived);
	_pServiceObject->readHoldingRegistersResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__readHoldingRegistersResponseReceived);
	_pServiceObject->readInputRegistersResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__readInputRegistersResponseReceived);
	_pServiceObject->readWriteMultipleRegistersResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__readWriteMultipleRegistersResponseReceived);
	_pServiceObject->requestFailed += Poco::delegate(this, &ModbusMasterRemoteObject::event__requestFailed);
	_pServiceObject->responseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__responseReceived);
	_pServiceObject->timeout += Poco::delegate(this, &ModbusMasterRemoteObject::event__timeout);
	_pServiceObject->writeMultipleCoilsResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__writeMultipleCoilsResponseReceived);
	_pServiceObject->writeMultipleRegistersResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__writeMultipleRegistersResponseReceived);
	_pServiceObject->writeSingleCoilResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__writeSingleCoilResponseReceived);
	_pServiceObject->writeSingleRegisterResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__writeSingleRegisterResponseReceived);
}


ModbusMasterRemoteObject::~ModbusMasterRemoteObject()
{
	try
	{
		_pServiceObject->badFrameReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__badFrameReceived);
		_pServiceObject->connectionStateChanged -= Poco::delegate(this, &ModbusMasterRemoteObject::event__connectionStateChanged);
		_pServiceObject->error -= Poco::delegate(this, &ModbusMasterRemoteObject::event__error);
		_pServiceObject->exceptionReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__exceptionReceived);
		_pServiceObject->maskWriteRegisterResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__maskWriteRegisterResponseReceived);
		_pServiceObject->readCoilsResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__readCoilsResponseReceived);
		_pServiceObject->readDiscreteInputsResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__readDiscreteInputsResponseReceived);
		_pServiceObject->readExceptionStatusResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__readExceptionStatusResponseReceived);
		_pServiceObject->readFIFOQueueResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__readFIFOQueueResponseReceived);
		_pServiceObject->readHoldingRegistersResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__readHoldingRegistersResponseReceived);
		_pServiceObject->readInputRegistersResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__readInputRegistersResponseReceived);
		_pServiceObject->readWriteMultipleRegistersResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__readWriteMultipleRegistersResponseReceived);
		_pServiceObject->requestFailed -= Poco::delegate(this, &ModbusMasterRemoteObject::event__requestFailed);
		_pServiceObject->responseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__responseReceived);
		_pServiceObject->timeout -= Poco::delegate(this, &ModbusMasterRemoteObject::event__timeout);
		_pServiceObject->writeMultipleCoilsResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__writeMultipleCoilsResponseReceived);
		_pServiceObject->writeMultipleRegistersResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__writeMultipleRegistersResponseReceived);
		_pServiceObject->writeSingleCoilResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__writeSingleCoilResponseReceived);
		_pServiceObject->writeSingleRegisterResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__writeSingleRegisterResponseReceived);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string ModbusMasterRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void ModbusMasterRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new ModbusMasterEventDispatcher(this, remoting__objectId(), protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool ModbusMasterRemoteObject::remoting__hasEvents() const
{
	return true;
}


void ModbusMasterRemoteObject::event__badFrameReceived()
{
	badFrameReceived(this);
}


void ModbusMasterRemoteObject::event__connectionStateChanged(const IoT::Modbus::ConnectionState& data)
{
	connectionStateChanged(this, data);
}


void ModbusMasterRemoteObject::event__error(const std::string& data)
{
	error(this, data);
}


void ModbusMasterRemoteObject::event__exceptionReceived(const IoT::Modbus::ModbusExceptionMessage& data)
{
	exceptionReceived(this, data);
}


void ModbusMasterRemoteObject::event__maskWriteRegisterResponseReceived(const IoT::Modbus::MaskWriteRegisterResponse& data)
{
	maskWriteRegisterResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__readCoilsResponseReceived(const IoT::Modbus::ReadCoilsResponse& data)
{
	readCoilsResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__readDiscreteInputsResponseReceived(const IoT::Modbus::ReadDiscreteInputsResponse& data)
{
	readDiscreteInputsResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__readExceptionStatusResponseReceived(const IoT::Modbus::ReadExceptionStatusResponse& data)
{
	readExceptionStatusResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__readFIFOQueueResponseReceived(const IoT::Modbus::ReadFIFOQueueResponse& data)
{
	readFIFOQueueResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__readHoldingRegistersResponseReceived(const IoT::Modbus::ReadHoldingRegistersResponse& data)
{
	readHoldingRegistersResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__readInputRegistersResponseReceived(const IoT::Modbus::ReadInputRegistersResponse& data)
{
	readInputRegistersResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__readWriteMultipleRegistersResponseReceived(const IoT::Modbus::ReadWriteMultipleRegistersResponse& data)
{
	readWriteMultipleRegistersResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__requestFailed(const IoT::Modbus::RequestFailure& data)
{
	requestFailed(this, data);
}


void ModbusMasterRemoteObject::event__responseReceived(const IoT::Modbus::GenericMessage& data)
{
	responseReceived(this, data);
}


void ModbusMasterRemoteObject::event__timeout(const Poco::UInt16& data)
{
	timeout(this, data);
}


void ModbusMasterRemoteObject::event__writeMultipleCoilsResponseReceived(const IoT::Modbus::WriteMultipleCoilsResponse& data)
{
	writeMultipleCoilsResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__writeMultipleRegistersResponseReceived(const IoT::Modbus::WriteMultipleRegistersResponse& data)
{
	writeMultipleRegistersResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__writeSingleCoilResponseReceived(const IoT::Modbus::WriteSingleCoilResponse& data)
{
	writeSingleCoilResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__writeSingleRegisterResponseReceived(const IoT::Modbus::WriteSingleRegisterResponse& data)
{
	writeSingleRegisterResponseReceived(this, data);
}


} // namespace Modbus
} // namespace IoT

