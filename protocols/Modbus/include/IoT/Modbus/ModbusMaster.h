//
// ModbusMaster.h
//
// $Id$
//
// Library: IoT/Modbus
// Package: ModbusMaster
// Module:  ModbusMaster
//
// Definition of the ModbusMaster class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Modbus_ModbusMaster_INCLUDED
#define IoT_Modbus_ModbusMaster_INCLUDED


#include "IoT/Modbus/Modbus.h"
#include "Poco/BasicEvent.h"
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
	Poco::UInt8 exceptionCode;
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
	
	Poco::UInt16 startingAddress;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 nOfCoils;
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
	
	Poco::UInt16 startingAddress;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 nOfInputs;
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
	
	Poco::UInt16 startingAddress;
		/// 0x0000 to 0xFFFF
		
	Poco::UInt16 nOfRegisters;
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
	
	Poco::UInt16 startingAddress;
		/// 0x0000 to 0xFFFF
	
	Poco::UInt16 nOfRegisters;
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
	
	Poco::UInt16 outputAddress;
		/// 0x0000 to 0xFFFF

	bool value;
};


//@ serialize
struct WriteSingleCoilResponse: public ModbusMessage
	/// Modbus Write Single Coil Response
	///
	/// Function Code: 0x05
{
	Poco::UInt16 outputAddress;
		/// 0x0000 to 0xFFFF

	bool value;
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

	Poco::UInt16 outputAddress;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 value;
		/// 0x0000 to 0xFFFF
};


//@ serialize
struct WriteSingleRegisterResponse: public ModbusMessage
	/// Modbus Write Single Register Response
	///
	/// Function Code: 0x06
{
	Poco::UInt16 outputAddress;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 value;
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
	Poco::UInt8 data;
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

	Poco::UInt16 startingAddress;
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
	Poco::UInt16 startingAddress;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 nOfCoils;
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

	Poco::UInt16 startingAddress;
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
	Poco::UInt16 startingAddress;
		/// 0x0000 to 0xFFFF

	Poco::UInt16 nOfRegisters;
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

	Poco::UInt16 referenceAddress;
		/// 0x0000 to 0xFFFF
		
	Poco::UInt16 andMask;
	Poco::UInt16 orMask;
};


//@ serialize
struct MaskWriteRegisterResponse: public ModbusMessage
	/// Modbus Mask Write Register Response
	///
	/// Function Code: 0x16
{
	Poco::UInt16 referenceAddress;
		/// 0x0000 to 0xFFFF
		
	Poco::UInt16 andMask;
	Poco::UInt16 orMask;
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

	Poco::UInt16 readStartingAddress;
		/// 0x0000 to 0xFFFF
		
	Poco::UInt16 readCount;
		/// 0x0001 to 0x007D
		
	Poco::UInt16 writeStartingAddress;
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

	Poco::UInt16 fifoAddress;
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


//@ remote
class IoTModbus_API ModbusMaster
	/// This class defines the interface for Modbus clients.
	///
	/// The interface supports two basic modes of operation:
	///    - Asynchronous requests: One of the sendXXXRequest() methods is used
	///      to send a request to the device. The method returns as soon as the
	///      request has been sent over the wire. The device's response is
	///      reported asynchronously via an appropriate XXXResponseReceived event.
	///    - Synchronous requests: After sending the request, the method waits
	///      for the response from the device and directly returns it to the caller.
	///      In case no response is received within the specified timeout, a
	///      Poco::TimeoutException is thrown. If an exception message is received
	///      from the device, a ModbusException is thrown. If an incomplete or invalid
	///      message is received, a Poco::ProtocolException is thrown.
	///
	/// Note that asynchronous and synchronous (blocking) mode cannot be used
	/// simultaneously. Calling one of the asynchronous request methods will enable
	/// asynchronous mode. Calling one of the synchronous request methods will
	/// disable asynchronous mode. Switching to synchronous mode while a response
	/// to an asynchronous request is pending will lead to undefined results,
	/// including possible mismatch of requests and responses.
	///
	/// In asynchronous operation, requests are associated with a transaction ID,
	/// to tell apart multiple concurrent transactions. Transaction IDs are not guaranteed
	/// to be unique for subsequent requests. In fact, for Modbus RTU, which does not
	/// allow multiple simultaneous requests, the transaction ID will always be zero.
{
public:
	Poco::BasicEvent<void> badFrameReceived;
		/// Fired when an empty or incomplete frame has been received.

	Poco::BasicEvent<const Poco::UInt16> timeout;
		/// Fired when no response has been received within the 
		/// specified timeout for the transaction with the given
		/// transaction ID.

	Poco::BasicEvent<const GenericMessage> responseReceived;
		/// Fired when a valid, but unsupported Modbus response message has been received.
		///
		/// Whenever a valid Modbus message (response) is received, the message will
		/// be decoded and the corresponding event will be fired. For valid messages
		/// that don't have a corresponding event, this event will be fired.
		///
		/// Together with sendRequest(), this event can be used to handle Modbus messages 
		/// not directly supported by the ModbusMaster interface.
	
	Poco::BasicEvent<const ModbusExceptionMessage> exceptionReceived;
		/// Fired when a Modbus exception message has been received.
	
	Poco::BasicEvent<const ReadCoilsResponse> readCoilsResponseReceived;
		/// Fired when a response to a Read Coils request
		/// (function code 0x01) has been received.
		
	Poco::BasicEvent<const ReadDiscreteInputsResponse> readDiscreteInputsResponseReceived;
		/// Fired when a response to a Read Discrete Inputs request 
		/// (function code 0x02) has been received.
		
	Poco::BasicEvent<const ReadHoldingRegistersResponse> readHoldingRegistersResponseReceived;
		/// Fired when a response to a Read Holding Registers request
		/// (function code 0x03) has been received.
		
	Poco::BasicEvent<const ReadInputRegistersResponse> readInputRegistersResponseReceived;
		/// Fired when a response to a Read Input Registers request 
		/// (function code 0x04) has been received.
		
	Poco::BasicEvent<const WriteSingleCoilResponse> writeSingleCoilResponseReceived;
		/// Fired when a response to a Write Single Coil request
		/// (function code 0x05) has been received.
		
	Poco::BasicEvent<const WriteSingleRegisterResponse> writeSingleRegisterResponseReceived;
		/// Fired when a response to a Write Single Register request
		/// (function code 0x06) has been received.
		
	Poco::BasicEvent<const ReadExceptionStatusResponse> readExceptionStatusResponseReceived;
		/// Fired when a response to a Read Exception Status request
		/// (function code 0x07) has been received.
	
	Poco::BasicEvent<const WriteMultipleCoilsResponse> writeMultipleCoilsResponseReceived;
		/// Fired when a response to a Write Multiple Coils request
		/// (function code 0x0F) has been received.
		
	Poco::BasicEvent<const WriteMultipleRegistersResponse> writeMultipleRegistersResponseReceived;
		/// Fired when a response to a Write Multiple Registers request
		/// (function code 0x10) has been received.
		
	Poco::BasicEvent<const MaskWriteRegisterResponse> maskWriteRegisterResponseReceived;
		/// Fired when a response to a Mask Write Register request
		/// (function code 0x16) has been received.
		
	Poco::BasicEvent<const ReadWriteMultipleRegistersResponse> readWriteMultipleRegistersResponseReceived;
		/// Fired when a response to a Read/Write Multiple Registers Response request
		/// (function code 0x17) has been received.
		
	Poco::BasicEvent<const ReadFIFOQueueResponse> readFIFOQueueResponseReceived;
		/// Fired when a response to a Read FIFO Queue Response request
		/// (function code 0x18) has been received.
	
	ModbusMaster();
		/// Creates a ModbusMaster.
		
	virtual ~ModbusMaster();
		/// Destroys the ModbusMaster.

	virtual Poco::UInt16 sendRequest(const GenericMessage& message) = 0;
		/// Sends a generic Modbus message.
		///
		/// The caller is responsible for correct formatting of the
		/// messages's data field. 
		///
		/// This can be used to send Modbus requests not directly supported
		/// by the ModbusMaster interface.
		///
		/// A response from the device will be reported via the responseReceived event 
		/// or a more specific event if the response message type is supported.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendReadCoilsRequest(const ReadCoilsRequest& request) = 0;
		/// Sends a Read Coils request.
		///
		/// A response from the device will be reported via the
		/// readCoilsResponseReceived event.
		///
		/// Returns the transaction ID for the request.
		
	virtual Poco::UInt16 sendReadDiscreteInputsRequest(const ReadDiscreteInputsRequest& request) = 0;
		/// Sends a Read Discrete Inputs request.
		///
		/// A response from the device will be reported via the
		/// readDiscreteInputsResponseReceived event.
		///
		/// Returns the transaction ID for the request.
		
	virtual Poco::UInt16 sendReadHoldingRegistersRequest(const ReadHoldingRegistersRequest& request) = 0;
		/// Sends a Read Holding Registers request.
		///
		/// A response from the device will be reported via the
		/// readHoldingRegistersResponseReceived event.
		///
		/// Returns the transaction ID for the request.
		
	virtual Poco::UInt16 sendReadInputRegistersRequest(const ReadInputRegistersRequest& request) = 0;
		/// Sends a Read Input Registers request.
		///
		/// A response from the device will be reported via the
		/// readInputRegistersResponseReceived event.
		///
		/// Returns the transaction ID for the request.
		
	virtual Poco::UInt16 sendWriteSingleCoilRequest(const WriteSingleCoilRequest& request) = 0;
		/// Sends a Write Single Coil request.
		///
		/// A response from the device will be reported via the
		/// writeSingleCoilResponseReceived event.
		///
		/// Returns the transaction ID for the request.
		
	virtual Poco::UInt16 sendWriteSingleRegisterRequest(const WriteSingleRegisterRequest& request) = 0;
		/// Sends a Write Single Register request.
		///
		/// A response from the device will be reported via the
		/// writeSingleRegisterResponseReceived event.
		///
		/// Returns the transaction ID for the request.
		
	virtual Poco::UInt16 sendReadExceptionStatusRequest(const ReadExceptionStatusRequest& request) = 0;
		/// Sends a Read Exception Status request.
		///
		/// A response from the device will be reported via the
		/// readExceptionStatusResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendWriteMultipleCoilsRequest(const WriteMultipleCoilsRequest& request) = 0;
		/// Sends a Write Multiple Coils request.
		///
		/// A response from the device will be reported via the
		/// writeMultipleCoilsResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendWriteMultipleRegistersRequest(const WriteMultipleRegistersRequest& request) = 0;
		/// Sends a Write Multiple Registers request.
		///
		/// A response from the device will be reported via the
		/// writeMultipleRegistersResponseReceived event.
		///
		/// Returns the transaction ID for the request.
	
	virtual Poco::UInt16 sendMaskWriteRegisterRequest(const MaskWriteRegisterRequest& request) = 0;
		/// Sends a Mask Write Register request.
		///
		/// A response from the device will be reported via the
		/// maskWriteRegisterResponseReceived event.
		///
		/// Returns the transaction ID for the request.
		
	virtual Poco::UInt16 sendReadWriteMultipleRegistersRequest(const ReadWriteMultipleRegistersRequest& request) = 0;
		/// Sends a Read Write Multiple Registers request.
		///
		/// A response from the device will be reported via the
		/// readWriteMultipleRegistersResponseReceived event.
		///
		/// Returns the transaction ID for the request.
		
	virtual Poco::UInt16 sendReadFIFOQueueRequest(const ReadFIFOQueueRequest& request) = 0;
		/// Sends a Read FIFO Queue request.
		///
		/// A response from the device will be reported via the
		/// readFIFOQueueResponseReceived event.
		///
		/// Returns the transaction ID for the request.
	
	virtual std::vector<bool> readCoils(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfCoils) = 0; 
		/// Sends a Read Coils request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector<bool> readDiscreteInputs(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfInputs) = 0; 
		/// Sends a Read Discrete Inputs request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector<Poco::UInt16> readHoldingRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfRegisters) = 0;
		/// Sends a Read Holding Registers request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector<Poco::UInt16> readInputRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfRegisters) = 0;
		/// Sends a Read Input Registers request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual void writeSingleCoil(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, bool value) = 0;
		/// Sends a Write Single Coils request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual void writeSingleRegister(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, Poco::UInt16 value) = 0;
		/// Sends a Write Single Register request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual Poco::UInt8 readExceptionStatus(Poco::UInt8 slaveAddress) = 0;
		/// Sends a Read Exception Status request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.
		
	virtual void writeMultipleCoils(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, std::vector<bool> values) = 0;
		/// Sends a Write Multiple Coils request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual void writeMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, std::vector<Poco::UInt16> values) = 0;
		/// Sends a Write Multiple Registers request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual void maskWriteRegister(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, Poco::UInt16 andMask, Poco::UInt16 orMask) = 0;
		/// Sends a Mask Write register request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector<Poco::UInt16> readWriteMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 writeStartingAddress, std::vector<Poco::UInt16> writeValues, Poco::UInt16 readStartingAddress, Poco::UInt8 nOfReadRegisters) = 0;
		/// Sends a Read/Write Multiple registers request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector<Poco::UInt16> readFIFOQueue(Poco::UInt8 slaveAddress, Poco::UInt16 fifoPointerAddress) = 0;
		/// Sends a Read FIFO Queue request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

private:
	ModbusMaster(const ModbusMaster&);
	ModbusMaster& operator = (const ModbusMaster&);
};


} } // namespace IoT::Modbus


#endif // IoT_Modbus_ModbusMaster_INCLUDED
