//
// AbstractModbusDeviceHandler.cpp
//
// Library: IoT/Modbus/Device
// Package: Device
// Module:  AbstractModbusDeviceHandler
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Modbus/Device/AbstractModbusDeviceHandler.h"
#include "IoT/Modbus/ModbusException.h"


namespace IoT {
namespace Modbus {
namespace Device {


void AbstractModbusDeviceHandler::readCoils(const ReadCoilsRequest& request, ReadCoilsResponse& /*response*/)
{
	throw ModbusException(request.functionCode, MODBUS_EXC_ILLEGAL_FUNCTION);
}


void AbstractModbusDeviceHandler::readDiscreteInputs(const ReadDiscreteInputsRequest& request, ReadDiscreteInputsResponse& /*response*/)
{
	throw ModbusException(request.functionCode, MODBUS_EXC_ILLEGAL_FUNCTION);
}


void AbstractModbusDeviceHandler::readHoldingRegisters(const ReadHoldingRegistersRequest& request, ReadHoldingRegistersResponse& /*response*/)
{
	throw ModbusException(request.functionCode, MODBUS_EXC_ILLEGAL_FUNCTION);
}


void AbstractModbusDeviceHandler::readInputRegisters(const ReadInputRegistersRequest& request, ReadInputRegistersResponse& /*response*/)
{
	throw ModbusException(request.functionCode, MODBUS_EXC_ILLEGAL_FUNCTION);
}


void AbstractModbusDeviceHandler::writeSingleCoil(const WriteSingleCoilRequest& request, WriteSingleCoilResponse& /*response*/)
{
	throw ModbusException(request.functionCode, MODBUS_EXC_ILLEGAL_FUNCTION);
}


void AbstractModbusDeviceHandler::writeSingleRegister(const WriteSingleRegisterRequest& request, WriteSingleRegisterResponse& /*response*/)
{
	throw ModbusException(request.functionCode, MODBUS_EXC_ILLEGAL_FUNCTION);
}


void AbstractModbusDeviceHandler::readExceptionStatus(const ReadExceptionStatusRequest& request, ReadExceptionStatusResponse& /*response*/)
{
	throw ModbusException(request.functionCode, MODBUS_EXC_ILLEGAL_FUNCTION);
}


void AbstractModbusDeviceHandler::writeMultipleCoils(const WriteMultipleCoilsRequest& request, WriteMultipleCoilsResponse& /*response*/)
{
	throw ModbusException(request.functionCode, MODBUS_EXC_ILLEGAL_FUNCTION);
}


void AbstractModbusDeviceHandler::writeMultipleRegisters(const WriteMultipleRegistersRequest& request, WriteMultipleRegistersResponse& /*response*/)
{
	throw ModbusException(request.functionCode, MODBUS_EXC_ILLEGAL_FUNCTION);
}


void AbstractModbusDeviceHandler::maskWriteRegister(const MaskWriteRegisterRequest& request, MaskWriteRegisterResponse& /*response*/)
{
	throw ModbusException(request.functionCode, MODBUS_EXC_ILLEGAL_FUNCTION);
}


void AbstractModbusDeviceHandler::readWriteMultipleRegisters(const ReadWriteMultipleRegistersRequest& request, ReadWriteMultipleRegistersResponse& /*response*/)
{
	throw ModbusException(request.functionCode, MODBUS_EXC_ILLEGAL_FUNCTION);
}


void AbstractModbusDeviceHandler::readFIFOQueue(const ReadFIFOQueueRequest& request, ReadFIFOQueueResponse& /*response*/)
{
	throw ModbusException(request.functionCode, MODBUS_EXC_ILLEGAL_FUNCTION);
}


void AbstractModbusDeviceHandler::otherFunction(const GenericMessage& request, GenericMessage& /*response*/)
{
	throw ModbusException(request.functionCode, MODBUS_EXC_ILLEGAL_FUNCTION);
}


bool AbstractModbusDeviceHandler::idle(Poco::Timespan /*idleTime*/)
{
	return true;
}


} } } // namespace IoT::Modbus::Device
