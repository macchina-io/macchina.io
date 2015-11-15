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
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
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
	_pServiceObject->exceptionReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__exceptionReceived);
	_pServiceObject->maskWriteRegisterResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__maskWriteRegisterResponseReceived);
	_pServiceObject->readCoilsResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__readCoilsResponseReceived);
	_pServiceObject->readDiscreteInputsResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__readDiscreteInputsResponseReceived);
	_pServiceObject->readExceptionStatusResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__readExceptionStatusResponseReceived);
	_pServiceObject->readFIFOQueueResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__readFIFOQueueResponseReceived);
	_pServiceObject->readHoldingRegistersResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__readHoldingRegistersResponseReceived);
	_pServiceObject->readInputRegistersResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__readInputRegistersResponseReceived);
	_pServiceObject->readWriteMultipleRegistersResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__readWriteMultipleRegistersResponseReceived);
	_pServiceObject->responseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__responseReceived);
	_pServiceObject->writeMultipleCoilsResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__writeMultipleCoilsResponseReceived);
	_pServiceObject->writeMultipleRegistersResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__writeMultipleRegistersResponseReceived);
	_pServiceObject->writeSingleCoilResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__writeSingleCoilResponseReceived);
	_pServiceObject->writeSingleRegisterResponseReceived += Poco::delegate(this, &ModbusMasterRemoteObject::event__writeSingleRegisterResponseReceived);
}


ModbusMasterRemoteObject::~ModbusMasterRemoteObject()
{
	try
	{
		_pServiceObject->exceptionReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__exceptionReceived);
		_pServiceObject->maskWriteRegisterResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__maskWriteRegisterResponseReceived);
		_pServiceObject->readCoilsResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__readCoilsResponseReceived);
		_pServiceObject->readDiscreteInputsResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__readDiscreteInputsResponseReceived);
		_pServiceObject->readExceptionStatusResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__readExceptionStatusResponseReceived);
		_pServiceObject->readFIFOQueueResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__readFIFOQueueResponseReceived);
		_pServiceObject->readHoldingRegistersResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__readHoldingRegistersResponseReceived);
		_pServiceObject->readInputRegistersResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__readInputRegistersResponseReceived);
		_pServiceObject->readWriteMultipleRegistersResponseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__readWriteMultipleRegistersResponseReceived);
		_pServiceObject->responseReceived -= Poco::delegate(this, &ModbusMasterRemoteObject::event__responseReceived);
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


void ModbusMasterRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
}


void ModbusMasterRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new ModbusMasterEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool ModbusMasterRemoteObject::remoting__hasEvents() const
{
	return true;
}


void ModbusMasterRemoteObject::event__exceptionReceived(const IoT::Modbus::ModbusExceptionMessage& data)
{
	exceptionReceived(this, data);
}


void ModbusMasterRemoteObject::event__maskWriteRegisterResponseReceived(IoT::Modbus::MaskWriteRegisterResponse& data)
{
	maskWriteRegisterResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__readCoilsResponseReceived(IoT::Modbus::ReadCoilsResponse& data)
{
	readCoilsResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__readDiscreteInputsResponseReceived(IoT::Modbus::ReadDiscreteInputsRequest& data)
{
	readDiscreteInputsResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__readExceptionStatusResponseReceived(IoT::Modbus::ReadExceptionStatusResponse& data)
{
	readExceptionStatusResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__readFIFOQueueResponseReceived(IoT::Modbus::ReadFIFOQueueResponse& data)
{
	readFIFOQueueResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__readHoldingRegistersResponseReceived(IoT::Modbus::ReadHoldingRegistersResponse& data)
{
	readHoldingRegistersResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__readInputRegistersResponseReceived(IoT::Modbus::ReadInputRegistersResponse& data)
{
	readInputRegistersResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__readWriteMultipleRegistersResponseReceived(IoT::Modbus::ReadWriteMultipleRegistersResponse& data)
{
	readWriteMultipleRegistersResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__responseReceived(const IoT::Modbus::GenericMessage& data)
{
	responseReceived(this, data);
}


void ModbusMasterRemoteObject::event__writeMultipleCoilsResponseReceived(IoT::Modbus::WriteMultipleCoilsResponse& data)
{
	writeMultipleCoilsResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__writeMultipleRegistersResponseReceived(IoT::Modbus::WriteMultipleRegistersResponse& data)
{
	writeMultipleRegistersResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__writeSingleCoilResponseReceived(IoT::Modbus::WriteSingleCoilResponse& data)
{
	writeSingleCoilResponseReceived(this, data);
}


void ModbusMasterRemoteObject::event__writeSingleRegisterResponseReceived(IoT::Modbus::WriteSingleRegisterResponse& data)
{
	writeSingleRegisterResponseReceived(this, data);
}


} // namespace Modbus
} // namespace IoT

