//
// ModbusDeviceHandler.h
//
// Library: IoT/Modbus/Device
// Package: Device
// Module:  ModbusDeviceHandler
//
// Definition of the ModbusDeviceHandler class.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Modbus_Device_ModbusDeviceHandler_INCLUDED
#define IoT_Modbus_Device_ModbusDeviceHandler_INCLUDED


#include "IoT/Modbus/Device/ModbusDevice.h"
#include "IoT/Modbus/Types.h"
#include "Poco/Timespan.h"


namespace IoT {
namespace Modbus {
namespace Device {


class IoTModbusDevice_API ModbusDeviceHandler
	/// This class defines the interface for Modbus devices.
	///
	/// The interface is used for both RTU and TCP connections.
	///
	/// For every defined function code there is a corresponding
	/// handler method. In case of an unknown function code,
	/// a generic otherFunction() method is provided.
	///
	/// The response object is pre-initialized with the correct
	/// function code, device address and transaction ID, so the
	/// handler method only needs to fill in the message-specific
	/// information.
	///
	/// A handler method can return an exception message by throwing
	/// a ModbusException with an appropriate function and exception code.
{
public:
	ModbusDeviceHandler();
		/// Creates a ModbusDeviceHandler.

	virtual ~ModbusDeviceHandler();
		/// Destroys the ModbusDeviceHandler.

	virtual void readCoils(const ReadCoilsRequest& request, ReadCoilsResponse& response) = 0;
		/// Handles a Read Coils request.
	
	virtual void readDiscreteInputs(const ReadDiscreteInputsRequest& request, ReadDiscreteInputsResponse& response) = 0;
		/// Handles a Read Discrete Inputs request.

	virtual void readHoldingRegisters(const ReadHoldingRegistersRequest& request, ReadHoldingRegistersResponse& response) = 0;
		/// Handles a Read Holding Registers request.
	
	virtual void readInputRegisters(const ReadInputRegistersRequest& request, ReadInputRegistersResponse& response) = 0;
		/// Handles a Read Input Registers request.

	virtual void writeSingleCoil(const WriteSingleCoilRequest& request, WriteSingleCoilResponse& response) = 0;
		/// Handles a Write Single Coil request.

	virtual void writeSingleRegister(const WriteSingleRegisterRequest& request, WriteSingleRegisterResponse& response) = 0;
		/// Handles a Write Single Register request.

	virtual void readExceptionStatus(const ReadExceptionStatusRequest& request, ReadExceptionStatusResponse& response) = 0;
		/// Handles a Read Exception Status request.

	virtual void writeMultipleCoils(const WriteMultipleCoilsRequest& request, WriteMultipleCoilsResponse& response) = 0;
		/// Handles a Write Multiple Coils request.

	virtual void writeMultipleRegisters(const WriteMultipleRegistersRequest& request, WriteMultipleRegistersResponse& response) = 0;
		/// Handles a Write Multiple Registers request.

	virtual void maskWriteRegister(const MaskWriteRegisterRequest& request, MaskWriteRegisterResponse& response) = 0;
		/// Handles a Mask Write Register request.

	virtual void readWriteMultipleRegisters(const ReadWriteMultipleRegistersRequest& request, ReadWriteMultipleRegistersResponse& response) = 0;
		/// Handles a Read Write Multiple Registers request.

	virtual void readFIFOQueue(const ReadFIFOQueueRequest& request, ReadFIFOQueueResponse& response) = 0;
		/// Handles a Read FIFO Queue request.

	virtual void otherFunction(const GenericMessage& request, GenericMessage& response) = 0;
		/// Handles any function code not covered by the other handler methods.

	virtual bool idle(Poco::Timespan idleTime) = 0;
		/// Called repeatedly when no other request is there to handle.
		///
		/// If the method returns false, the Modbus connection will be
		/// closed. 

private:
	ModbusDeviceHandler(const ModbusDeviceHandler&) = delete;
	ModbusDeviceHandler& operator = (const ModbusDeviceHandler&) = delete;
};


} } } // namespace IoT::Modbus::Device


#endif // IoT_Modbus_Device_ModbusDeviceHandler_INCLUDED
