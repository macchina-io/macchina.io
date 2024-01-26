//
// Types.h
//
// Library: IoT/Modbus
// Package: ModbusCore
// Module:  Types
//
// Definition of Modbus Types.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Modbus_Types_INCLUDED
#define IoT_Modbus_Types_INCLUDED


#include "IoT/Modbus/Modbus.h"
#include "Poco/Types.h"
#include <vector>


namespace IoT {
namespace Modbus {


enum FunctionCodes
	/// See the MODBUS Application Protocol Specification V1.1b3
	/// for a detailed description of these function codes.
{
	MODBUS_READ_COILS                       = 0x01,
	MODBUS_READ_DISCRETE_INPUTS             = 0x02,
	MODBUS_READ_HOLDING_REGISTERS           = 0x03,
	MODBUS_READ_INPUT_REGISTERS             = 0x04,
	MODBUS_WRITE_SINGLE_COIL                = 0x05,
	MODBUS_WRITE_SINGLE_REGISTER            = 0x06,
	MODBUS_READ_EXCEPTION_STATUS            = 0x07,
	MODBUS_DIAGNOSTICS                      = 0x08,
	MODBUS_GET_COMM_EVENT_COUNTER           = 0x0B,
	MODBUS_GET_COMM_EVENT_LOG               = 0x0C,
	MODBUS_WRITE_MULTIPLE_COILS             = 0x0F,
	MODBUS_WRITE_MULTIPLE_REGISTERS         = 0x10,
	MODBUS_REPORT_SERVER_ID                 = 0x11,
	MODBUS_READ_FILE_RECORD                 = 0x14,
	MODBUS_WRITE_FILE_RECORD                = 0x15,
	MODBUS_MASK_WRITE_REGISTER              = 0x16,
	MODBUS_READ_WRITE_MULTIPLE_REGISTERS    = 0x17,
	MODBUS_READ_FIFO_QUEUE                  = 0x18,
	MODBUS_ENCAPSULATED_INTERFACE_TRANSPORT = 0x2B,
	MODBUS_EXCEPTION_MASK                   = 0x80,
	MODBUS_FUNCTION_CODE_MASK               = 0x7F
};


enum ExceptionCodes
	/// See the MODBUS Application Protocol Specification V1.1b3
	/// for a detailed description of these exception codes.
{
	MODBUS_EXC_ILLEGAL_FUNCTION                        = 0x01,
	MODBUS_EXC_ILLEGAL_DATA_ADDRESS                    = 0x02,
	MODBUS_EXC_ILLEGAL_DATA_VALUE                      = 0x03,
	MODBUS_EXC_SERVER_DEVICE_FAILURE                   = 0x04,
	MODBUS_EXC_ACKNOWLEDGE                             = 0x05,
	MODBUS_EXC_SERVER_DEVICE_BUSY                      = 0x06,
	MODBUS_EXC_MEMORY_PARITY_ERROR                     = 0x08,
	MODBUS_EXC_GATEWAY_PATH_UNAVAILABLE                = 0x0A,
	MODBUS_EXC_GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND = 0x0B
};


//@ serialize
struct ModbusMessage
{
	ModbusMessage():
		transactionID(0),
		slaveOrUnitAddress(0),
		functionCode(0)
	{
	}

	ModbusMessage(Poco::UInt8 fc):
		transactionID(0),
		slaveOrUnitAddress(0),
		functionCode(fc)
	{
	}

	ModbusMessage(Poco::UInt16 xid, Poco::UInt8 fc):
		transactionID(xid),
		slaveOrUnitAddress(0),
		functionCode(fc)
	{
	}

	mutable Poco::UInt16 transactionID;
		/// Transaction identifier for Modbus TCP.

	Poco::UInt8 slaveOrUnitAddress;
		/// Slave or unit address/ID.

	Poco::UInt8 functionCode;
		/// Modbus Function Code: 0x00 to 0x7F (see FunctionCodes).
};


//@ serialize
struct GenericMessage: public ModbusMessage
	/// A generic Modbus frame.
{
	GenericMessage()
	{
	}

	GenericMessage(Poco::UInt8 fc):
		ModbusMessage(fc)
	{
	}

	std::vector<Poco::UInt8> data;
		/// Function-specific data.
};


//@ serialize
struct ModbusExceptionMessage: public ModbusMessage
	/// Modbus Exception Message
{
	Poco::UInt8 exceptionCode = 0;
		/// Modbus exception code (see ExceptionCodes).
};


//@ serialize
struct ReadCoilsRequest: public ModbusMessage
	/// Modbus Read Coils Request
	///
	/// Function Code: 0x01
{
	ReadCoilsRequest():
		ModbusMessage(MODBUS_READ_COILS)
	{
	}

	Poco::UInt16 startingAddress = 0;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 nOfCoils = 0;
		/// 1 to 2000 (0x7D0)
};


//@ serialize
struct ReadCoilsResponse: public ModbusMessage
	/// Modbus Read Coils Response
	///
	/// Function Code: 0x01
{
	std::vector<bool> coilStatus;
		/// Status of coils.
};


//@ serialize
struct ReadDiscreteInputsRequest: public ModbusMessage
	/// Modbus Read Inputs Request
	///
	/// Function Code: 0x02
{
	ReadDiscreteInputsRequest():
		ModbusMessage(MODBUS_READ_DISCRETE_INPUTS)
	{
	}

	Poco::UInt16 startingAddress = 0;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 nOfInputs = 0;
		/// 1 to 2000 (0x7D0)
};


//@ serialize
struct ReadDiscreteInputsResponse: public ModbusMessage
	/// Modbus Read Inputs Response
	///
	/// Function Code: 0x02
{
	std::vector<bool> inputStatus;
		/// Status of inputs.
};


//@ serialize
struct ReadHoldingRegistersRequest: public ModbusMessage
	/// Modbus Read Holding Registers Request
	///
	/// Function Code: 0x03
{
	ReadHoldingRegistersRequest():
		ModbusMessage(MODBUS_READ_HOLDING_REGISTERS)
	{
	}

	Poco::UInt16 startingAddress = 0;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 nOfRegisters = 0;
		/// 1 to 125 (0x7D)
};


//@ serialize
struct ReadHoldingRegistersResponse: public ModbusMessage
	/// Modbus Read Holding Registers Response
	///
	/// Function Code: 0x03
{
	std::vector<Poco::UInt16> registerValues;
};


//@ serialize
struct ReadInputRegistersRequest: public ModbusMessage
	/// Modbus Read Input Registers Request
	///
	/// Function Code: 0x04
{
	ReadInputRegistersRequest():
		ModbusMessage(MODBUS_READ_INPUT_REGISTERS)
	{
	}

	Poco::UInt16 startingAddress = 0;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 nOfRegisters = 0;
		/// 1 to 125 (0x7D)
};


//@ serialize
struct ReadInputRegistersResponse: public ModbusMessage
	/// Modbus Read Input Registers Response
	///
	/// Function Code: 0x04
{
	std::vector<Poco::UInt16> registerValues;
};


//@ serialize
struct WriteSingleCoilRequest: public ModbusMessage
	/// Modbus Write Single Coil Request
	///
	/// Function Code: 0x05
{
	WriteSingleCoilRequest():
		ModbusMessage(MODBUS_WRITE_SINGLE_COIL)
	{
	}

	Poco::UInt16 outputAddress = 0;
		/// 0x0000 to 0xFFFF

	bool value = false;
};


//@ serialize
struct WriteSingleCoilResponse: public ModbusMessage
	/// Modbus Write Single Coil Response
	///
	/// Function Code: 0x05
{
	Poco::UInt16 outputAddress = 0;
		/// 0x0000 to 0xFFFF

	bool value = false;
};


//@ serialize
struct WriteSingleRegisterRequest: public ModbusMessage
	/// Modbus Write Single Register Request
	///
	/// Function Code: 0x06
{
	WriteSingleRegisterRequest():
		ModbusMessage(MODBUS_WRITE_SINGLE_REGISTER)
	{
	}

	Poco::UInt16 registerAddress = 0;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 value = 0;
		/// 0x0000 to 0xFFFF
};


//@ serialize
struct WriteSingleRegisterResponse: public ModbusMessage
	/// Modbus Write Single Register Response
	///
	/// Function Code: 0x06
{
	Poco::UInt16 registerAddress = 0;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 value = 0;
		/// 0x0000 to 0xFFFF
};


//@ serialize
struct ReadExceptionStatusRequest: public ModbusMessage
	/// Modbus Read Exception Status Request
	///
	/// Function Code: 0x07
{
	ReadExceptionStatusRequest():
		ModbusMessage(MODBUS_READ_EXCEPTION_STATUS)
	{
	}
};


//@ serialize
struct ReadExceptionStatusResponse: public ModbusMessage
	/// Modbus Read Exception Status Response
	///
	/// Function Code: 0x07
{
	Poco::UInt8 data = 0;
};


//@ serialize
struct WriteMultipleCoilsRequest: public ModbusMessage
	/// Modbus Write Multiple Coils Request
	///
	/// Function Code: 0x0F
{
	WriteMultipleCoilsRequest():
		ModbusMessage(MODBUS_WRITE_MULTIPLE_COILS)
	{
	}

	Poco::UInt16 startingAddress = 0;
		/// 0x0000 to 0xFFFF

	std::vector<bool> values;
		/// 0x0001 to 0x07B0 values
};


//@ serialize
struct WriteMultipleCoilsResponse: public ModbusMessage
	/// Modbus Write Multiple Coils Response
	///
	/// Function Code: 0x0F
{
	Poco::UInt16 startingAddress = 0;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 nOfCoils = 0;
		/// 0x0001 to 0x07B0
};


//@ serialize
struct WriteMultipleRegistersRequest: public ModbusMessage
	/// Modbus Write Multiple Registers Request
	///
	/// Function Code: 0x10
{
	WriteMultipleRegistersRequest():
		ModbusMessage(MODBUS_WRITE_MULTIPLE_REGISTERS)
	{
	}

	Poco::UInt16 startingAddress = 0;
		/// 0x0000 to 0xFFFF

	std::vector<Poco::UInt16> values;
		/// 0x0001 to 0x07B0 values
};


//@ serialize
struct WriteMultipleRegistersResponse: public ModbusMessage
	/// Modbus Read Multiple Registers Response
	///
	/// Function Code: 0x10
{
	Poco::UInt16 startingAddress = 0;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 nOfRegisters = 0;
		/// 0x0001 to 0x07B0
};


//@ serialize
struct MaskWriteRegisterRequest: public ModbusMessage
	/// Modbus Mask Write Register Request
	///
	/// Function Code: 0x16
{
	MaskWriteRegisterRequest():
		ModbusMessage(MODBUS_MASK_WRITE_REGISTER)
	{
	}

	Poco::UInt16 referenceAddress = 0;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 andMask = 0;
	Poco::UInt16 orMask = 0;
};


//@ serialize
struct MaskWriteRegisterResponse: public ModbusMessage
	/// Modbus Mask Write Register Response
	///
	/// Function Code: 0x16
{
	Poco::UInt16 referenceAddress = 0;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 andMask = 0;
	Poco::UInt16 orMask = 0;
};


//@ serialize
struct ReadWriteMultipleRegistersRequest: public ModbusMessage
	/// Modbus Read/Write Multiple Registers Request
	///
	/// Function Code: 0x17
{
	ReadWriteMultipleRegistersRequest():
		ModbusMessage(MODBUS_READ_WRITE_MULTIPLE_REGISTERS)
	{
	}

	Poco::UInt16 readStartingAddress = 0;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 readCount = 0;
		/// 0x0001 to 0x007D

	Poco::UInt16 writeStartingAddress = 0;
		/// 0x0000 to 0xFFFF

	std::vector<Poco::UInt16> values;
		/// Up to 191 (0x79) values to be written to registers.
};


//@ serialize
struct ReadWriteMultipleRegistersResponse: public ModbusMessage
	/// Modbus Read/Write Multiple Registers Response
	///
	/// Function Code: 0x17
{
	std::vector<Poco::UInt16> values;
		/// Values read from registers.
};


//@ serialize
struct ReadFIFOQueueRequest: public ModbusMessage
	/// Modbus Read FIFO Queue Request
	///
	/// Function Code: 0x18
{
	ReadFIFOQueueRequest():
		ModbusMessage(MODBUS_READ_FIFO_QUEUE)
	{
	}

	Poco::UInt16 fifoAddress = 0;
		/// 0x0000 to 0xFFFF
};


//@ serialize
struct ReadFIFOQueueResponse: public ModbusMessage
	/// Modbus Read FIFO Queue Response
	///
	/// Function Code: 0x18
{
	std::vector<Poco::UInt16> values;
		/// Values read from FIFO registers.
};


enum RequestFailureReason
{
	FAILURE_TIMEOUT = 0,
		/// Request timed out.

	FAILURE_RESET = 1,
		/// Request aborted due to reset.

	FAILURE_CLOSED = 2,
		/// Request aborted due to connection being closed.

	FAILURE_ERROR = 3,
		/// Request aborted due to exception or network error.
};


//@ serialize
struct RequestFailure
{
	Poco::UInt8 slaveOrUnitAddress;
		/// Slave or unit address/ID.

	Poco::UInt8 functionCode;
		/// Function code specified in failed request.

	Poco::UInt16 transactionID;
		/// Transaction ID of failed request.

	RequestFailureReason reason;
		/// Failure reason.

	std::string message;
		/// Error message;
};


enum ConnectionState
{
	CONNECTION_CLOSED   = 0,
	CONNECTION_OPENING  = 1,
	CONNECTION_OPEN     = 2,
	CONNECTION_CLOSING  = 3,
	CONNECTION_TIMEOUT  = 4,
	CONNECTION_ERROR    = 5
};


} } // namespace IoT::Modbus


#endif // IoT_Modbus_Types_INCLUDED
