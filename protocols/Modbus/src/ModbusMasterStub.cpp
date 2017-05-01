//
// ModbusMasterStub.cpp
//
// Library: IoT/Modbus
// Package: Generated
// Module:  ModbusMasterStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Modbus/ModbusMasterStub.h"
#include "IoT/Modbus/ModbusMasterEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Modbus {


ModbusMasterStub::ModbusMasterStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Modbus::ModbusMaster> pServiceObject):
	IoT::Modbus::ModbusMasterRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->badFrameReceived += Poco::delegate(this, &ModbusMasterStub::event__badFrameReceived);
	_pServiceObject->exceptionReceived += Poco::delegate(this, &ModbusMasterStub::event__exceptionReceived);
	_pServiceObject->maskWriteRegisterResponseReceived += Poco::delegate(this, &ModbusMasterStub::event__maskWriteRegisterResponseReceived);
	_pServiceObject->readCoilsResponseReceived += Poco::delegate(this, &ModbusMasterStub::event__readCoilsResponseReceived);
	_pServiceObject->readDiscreteInputsResponseReceived += Poco::delegate(this, &ModbusMasterStub::event__readDiscreteInputsResponseReceived);
	_pServiceObject->readExceptionStatusResponseReceived += Poco::delegate(this, &ModbusMasterStub::event__readExceptionStatusResponseReceived);
	_pServiceObject->readFIFOQueueResponseReceived += Poco::delegate(this, &ModbusMasterStub::event__readFIFOQueueResponseReceived);
	_pServiceObject->readHoldingRegistersResponseReceived += Poco::delegate(this, &ModbusMasterStub::event__readHoldingRegistersResponseReceived);
	_pServiceObject->readInputRegistersResponseReceived += Poco::delegate(this, &ModbusMasterStub::event__readInputRegistersResponseReceived);
	_pServiceObject->readWriteMultipleRegistersResponseReceived += Poco::delegate(this, &ModbusMasterStub::event__readWriteMultipleRegistersResponseReceived);
	_pServiceObject->responseReceived += Poco::delegate(this, &ModbusMasterStub::event__responseReceived);
	_pServiceObject->timeout += Poco::delegate(this, &ModbusMasterStub::event__timeout);
	_pServiceObject->writeMultipleCoilsResponseReceived += Poco::delegate(this, &ModbusMasterStub::event__writeMultipleCoilsResponseReceived);
	_pServiceObject->writeMultipleRegistersResponseReceived += Poco::delegate(this, &ModbusMasterStub::event__writeMultipleRegistersResponseReceived);
	_pServiceObject->writeSingleCoilResponseReceived += Poco::delegate(this, &ModbusMasterStub::event__writeSingleCoilResponseReceived);
	_pServiceObject->writeSingleRegisterResponseReceived += Poco::delegate(this, &ModbusMasterStub::event__writeSingleRegisterResponseReceived);
}


ModbusMasterStub::~ModbusMasterStub()
{
	try
	{
		_pServiceObject->badFrameReceived -= Poco::delegate(this, &ModbusMasterStub::event__badFrameReceived);
		_pServiceObject->exceptionReceived -= Poco::delegate(this, &ModbusMasterStub::event__exceptionReceived);
		_pServiceObject->maskWriteRegisterResponseReceived -= Poco::delegate(this, &ModbusMasterStub::event__maskWriteRegisterResponseReceived);
		_pServiceObject->readCoilsResponseReceived -= Poco::delegate(this, &ModbusMasterStub::event__readCoilsResponseReceived);
		_pServiceObject->readDiscreteInputsResponseReceived -= Poco::delegate(this, &ModbusMasterStub::event__readDiscreteInputsResponseReceived);
		_pServiceObject->readExceptionStatusResponseReceived -= Poco::delegate(this, &ModbusMasterStub::event__readExceptionStatusResponseReceived);
		_pServiceObject->readFIFOQueueResponseReceived -= Poco::delegate(this, &ModbusMasterStub::event__readFIFOQueueResponseReceived);
		_pServiceObject->readHoldingRegistersResponseReceived -= Poco::delegate(this, &ModbusMasterStub::event__readHoldingRegistersResponseReceived);
		_pServiceObject->readInputRegistersResponseReceived -= Poco::delegate(this, &ModbusMasterStub::event__readInputRegistersResponseReceived);
		_pServiceObject->readWriteMultipleRegistersResponseReceived -= Poco::delegate(this, &ModbusMasterStub::event__readWriteMultipleRegistersResponseReceived);
		_pServiceObject->responseReceived -= Poco::delegate(this, &ModbusMasterStub::event__responseReceived);
		_pServiceObject->timeout -= Poco::delegate(this, &ModbusMasterStub::event__timeout);
		_pServiceObject->writeMultipleCoilsResponseReceived -= Poco::delegate(this, &ModbusMasterStub::event__writeMultipleCoilsResponseReceived);
		_pServiceObject->writeMultipleRegistersResponseReceived -= Poco::delegate(this, &ModbusMasterStub::event__writeMultipleRegistersResponseReceived);
		_pServiceObject->writeSingleCoilResponseReceived -= Poco::delegate(this, &ModbusMasterStub::event__writeSingleCoilResponseReceived);
		_pServiceObject->writeSingleRegisterResponseReceived -= Poco::delegate(this, &ModbusMasterStub::event__writeSingleRegisterResponseReceived);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string ModbusMasterStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void ModbusMasterStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new ModbusMasterEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool ModbusMasterStub::remoting__hasEvents() const
{
	return true;
}


void ModbusMasterStub::event__badFrameReceived()
{
	badFrameReceived(this);
}


void ModbusMasterStub::event__exceptionReceived(const IoT::Modbus::ModbusExceptionMessage& data)
{
	exceptionReceived(this, data);
}


void ModbusMasterStub::event__maskWriteRegisterResponseReceived(const IoT::Modbus::MaskWriteRegisterResponse& data)
{
	maskWriteRegisterResponseReceived(this, data);
}


void ModbusMasterStub::event__readCoilsResponseReceived(const IoT::Modbus::ReadCoilsResponse& data)
{
	readCoilsResponseReceived(this, data);
}


void ModbusMasterStub::event__readDiscreteInputsResponseReceived(const IoT::Modbus::ReadDiscreteInputsResponse& data)
{
	readDiscreteInputsResponseReceived(this, data);
}


void ModbusMasterStub::event__readExceptionStatusResponseReceived(const IoT::Modbus::ReadExceptionStatusResponse& data)
{
	readExceptionStatusResponseReceived(this, data);
}


void ModbusMasterStub::event__readFIFOQueueResponseReceived(const IoT::Modbus::ReadFIFOQueueResponse& data)
{
	readFIFOQueueResponseReceived(this, data);
}


void ModbusMasterStub::event__readHoldingRegistersResponseReceived(const IoT::Modbus::ReadHoldingRegistersResponse& data)
{
	readHoldingRegistersResponseReceived(this, data);
}


void ModbusMasterStub::event__readInputRegistersResponseReceived(const IoT::Modbus::ReadInputRegistersResponse& data)
{
	readInputRegistersResponseReceived(this, data);
}


void ModbusMasterStub::event__readWriteMultipleRegistersResponseReceived(const IoT::Modbus::ReadWriteMultipleRegistersResponse& data)
{
	readWriteMultipleRegistersResponseReceived(this, data);
}


void ModbusMasterStub::event__responseReceived(const IoT::Modbus::GenericMessage& data)
{
	responseReceived(this, data);
}


void ModbusMasterStub::event__timeout(const Poco::UInt16& data)
{
	timeout(this, data);
}


void ModbusMasterStub::event__writeMultipleCoilsResponseReceived(const IoT::Modbus::WriteMultipleCoilsResponse& data)
{
	writeMultipleCoilsResponseReceived(this, data);
}


void ModbusMasterStub::event__writeMultipleRegistersResponseReceived(const IoT::Modbus::WriteMultipleRegistersResponse& data)
{
	writeMultipleRegistersResponseReceived(this, data);
}


void ModbusMasterStub::event__writeSingleCoilResponseReceived(const IoT::Modbus::WriteSingleCoilResponse& data)
{
	writeSingleCoilResponseReceived(this, data);
}


void ModbusMasterStub::event__writeSingleRegisterResponseReceived(const IoT::Modbus::WriteSingleRegisterResponse& data)
{
	writeSingleRegisterResponseReceived(this, data);
}


} // namespace Modbus
} // namespace IoT

