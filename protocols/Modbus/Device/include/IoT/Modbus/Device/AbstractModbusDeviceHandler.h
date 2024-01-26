//
// AbstractModbusDeviceHandler.h
//
// Library: IoT/Modbus/Device
// Package: Device
// Module:  AbstractModbusDeviceHandler
//
// Definition of the AbstractModbusDeviceHandler class.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Modbus_Device_AbstractModbusDeviceHandler_INCLUDED
#define IoT_Modbus_Device_AbstractModbusDeviceHandler_INCLUDED


#include "IoT/Modbus/Device/ModbusDevice.h"
#include "IoT/Modbus/Device/ModbusDeviceHandler.h"


namespace IoT {
namespace Modbus {
namespace Device {


class IoTModbusDevice_API AbstractModbusDeviceHandler: public ModbusDeviceHandler
	/// This is an implementation of the ModbusDeviceHandler interface, which
	/// provides a trivial implementation of every method that simply
	/// throws a ModbusException with a MODBUS_EXC_ILLEGAL_FUNCTION 
	/// exception code.
	///
	/// This class can be used as base class for custom implementations
	/// that only implement a limited set of function codes.
{
public:
	// ModbusDeviceHandler
	void readCoils(const ReadCoilsRequest& request, ReadCoilsResponse& response);
	void readDiscreteInputs(const ReadDiscreteInputsRequest& request, ReadDiscreteInputsResponse& response);
	void readHoldingRegisters(const ReadHoldingRegistersRequest& request, ReadHoldingRegistersResponse& response);
	void readInputRegisters(const ReadInputRegistersRequest& request, ReadInputRegistersResponse& response);
	void writeSingleCoil(const WriteSingleCoilRequest& request, WriteSingleCoilResponse& response);
	void writeSingleRegister(const WriteSingleRegisterRequest& request, WriteSingleRegisterResponse& response);
	void readExceptionStatus(const ReadExceptionStatusRequest& request, ReadExceptionStatusResponse& response);
	void writeMultipleCoils(const WriteMultipleCoilsRequest& request, WriteMultipleCoilsResponse& response);
	void writeMultipleRegisters(const WriteMultipleRegistersRequest& request, WriteMultipleRegistersResponse& response);
	void maskWriteRegister(const MaskWriteRegisterRequest& request, MaskWriteRegisterResponse& response);
	void readWriteMultipleRegisters(const ReadWriteMultipleRegistersRequest& request, ReadWriteMultipleRegistersResponse& response);
	void readFIFOQueue(const ReadFIFOQueueRequest& request, ReadFIFOQueueResponse& response);
	void otherFunction(const GenericMessage& request, GenericMessage& response);
	bool idle(Poco::Timespan idleTime);
};


} } } // namespace IoT::Modbus::Device


#endif // IoT_Modbus_Device_AbstractModbusDeviceHandler_INCLUDED
