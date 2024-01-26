//
// ModbusMaster.h
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
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Modbus_ModbusMaster_INCLUDED
#define IoT_Modbus_ModbusMaster_INCLUDED


#include "IoT/Modbus/Modbus.h"
#include "IoT/Modbus/Types.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Modbus {


//@ remote
class IoTModbus_API ModbusMaster
	/// This class defines the interface for Modbus clients.
	///
	/// The interface supports two basic modes of operation:
	///    - Asynchronous requests: One of the sendXXXRequest() methods is used
	///      to send a request to the device. The method returns as soon as the
	///      request has been queued to be sent over the wire (actual sending is
	///      done in a separate thread). The device's response, is
	///      reported asynchronously via an appropriate XXXResponseReceived event.
	///      Errors encountered during sending are reported via requestFailed.
	///      Modbus exception responses are reported via exceptionReceived.
	///      A timeout waiting for the response is reported via the timeout event.
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
	Poco::BasicEvent<const ConnectionState> connectionStateChanged;
		/// Fired when the state of the connection changes.
		/// Currently only fired for Modbus TCP connections.

	Poco::BasicEvent<void> badFrameReceived;
		/// Fired when an empty or incomplete frame has been received.

	Poco::BasicEvent<const Poco::UInt16> timeout;
		/// Fired when no response has been received within the
		/// specified timeout for the transaction with the given
		/// transaction ID.

	Poco::BasicEvent<const std::string> error;
		/// Fired when an exception has been thrown while reading a message.

	Poco::BasicEvent<const RequestFailure> requestFailed;
		/// Fired when an asynchronous request message could not be sent.

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

	virtual std::string address() const = 0;
		/// Returns the Modbus master address as a string.

	virtual std::size_t maxSimultaneousTransactions() const = 0;
		/// Returns the maximum allowed number of in-flight requests.

	virtual std::size_t pendingTransactions() const = 0;
		/// Returns the current number of in-flight requests.

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
		/// Note: due to the wire format of the Modbus protocol, the returned vector will always have
		/// a size that is a multiple of 8, and may thus contain up to 7 more values than specified in nOfCoils.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector<bool> readDiscreteInputs(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfInputs) = 0;
		/// Sends a Read Discrete Inputs request to the device and waits for the response.
		///
		/// Note: due to the wire format of the Modbus protocol, the returned vector will always have
		/// a size that is a multiple of 8, and may thus contain up to 7 more values than specified in nOfInputs.
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

	virtual void writeSingleRegister(Poco::UInt8 slaveAddress, Poco::UInt16 registerAddress, Poco::UInt16 value) = 0;
		/// Sends a Write Single Register request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual Poco::UInt8 readExceptionStatus(Poco::UInt8 slaveAddress) = 0;
		/// Sends a Read Exception Status request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual void writeMultipleCoils(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, const std::vector<bool>& values) = 0;
		/// Sends a Write Multiple Coils request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual void writeMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, const std::vector<Poco::UInt16>& values) = 0;
		/// Sends a Write Multiple Registers request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual void maskWriteRegister(Poco::UInt8 slaveAddress, Poco::UInt16 referenceAddress, Poco::UInt16 andMask, Poco::UInt16 orMask) = 0;
		/// Sends a Mask Write register request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector<Poco::UInt16> readWriteMultipleRegisters(
			Poco::UInt8 slaveAddress, 
			Poco::UInt16 writeStartingAddress,
			const std::vector<Poco::UInt16>& writeValues, 
			Poco::UInt16 readStartingAddress, 
			Poco::UInt8 nOfReadRegisters) = 0;
		/// Sends a Read/Write Multiple registers request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector<Poco::UInt16> readFIFOQueue(Poco::UInt8 slaveAddress, Poco::UInt16 fifoPointerAddress) = 0;
		/// Sends a Read FIFO Queue request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual void reset() = 0;
		/// Resets the connection to the bus or device.

private:
	ModbusMaster(const ModbusMaster&);
	ModbusMaster& operator = (const ModbusMaster&);
};


} } // namespace IoT::Modbus


#endif // IoT_Modbus_ModbusMaster_INCLUDED
