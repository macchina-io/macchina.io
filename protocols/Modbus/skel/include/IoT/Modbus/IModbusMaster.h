//
// IModbusMaster.h
//
// Library: IoT/Modbus
// Package: Generated
// Module:  IModbusMaster
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Modbus_IModbusMaster_INCLUDED
#define IoT_Modbus_IModbusMaster_INCLUDED


#include "IoT/Modbus/ModbusMaster.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Modbus {


class IModbusMaster: public Poco::OSP::Service
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
	using Ptr = Poco::AutoPtr<IModbusMaster>;

	IModbusMaster();
		/// Creates a IModbusMaster.

	virtual ~IModbusMaster();
		/// Destroys the IModbusMaster.

	virtual std::string address() const = 0;
		/// Returns the Modbus master address as a string.

	virtual bool hasTransactionIDs() const = 0;
		/// Returns true if the port supports transaction IDs,
		/// otherwise false. Currently, only Modbus/TCP supports
		/// transaction IDs.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual void maskWriteRegister(Poco::UInt8 slaveAddress, Poco::UInt16 referenceAddress, Poco::UInt16 andMask, Poco::UInt16 orMask) = 0;
		/// Sends a Mask Write register request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::size_t maxSimultaneousTransactions() const = 0;
		/// Returns the maximum allowed number of in-flight requests.

	virtual std::size_t pendingTransactions() const = 0;
		/// Returns the current number of in-flight requests.

	virtual std::vector < bool > readCoils(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfCoils) = 0;
		/// Sends a Read Coils request to the device and waits for the response.
		///
		/// Note: due to the wire format of the Modbus protocol, the returned vector will always have
		/// a size that is a multiple of 8, and may thus contain up to 7 more values than specified in nOfCoils.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector < bool > readDiscreteInputs(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfInputs) = 0;
		/// Sends a Read Discrete Inputs request to the device and waits for the response.
		///
		/// Note: due to the wire format of the Modbus protocol, the returned vector will always have
		/// a size that is a multiple of 8, and may thus contain up to 7 more values than specified in nOfInputs.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual Poco::UInt8 readExceptionStatus(Poco::UInt8 slaveAddress) = 0;
		/// Sends a Read Exception Status request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector < Poco::UInt16 > readFIFOQueue(Poco::UInt8 slaveAddress, Poco::UInt16 fifoPointerAddress) = 0;
		/// Sends a Read FIFO Queue request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector < Poco::UInt16 > readHoldingRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfRegisters) = 0;
		/// Sends a Read Holding Registers request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector < Poco::UInt16 > readInputRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfRegisters) = 0;
		/// Sends a Read Input Registers request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector < Poco::UInt16 > readWriteMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 writeStartingAddress, const std::vector < Poco::UInt16 >& writeValues, Poco::UInt16 readStartingAddress, Poco::UInt8 nOfReadRegisters) = 0;
		/// Sends a Read/Write Multiple registers request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void reset() = 0;
		/// Resets the connection to the bus or device.

	virtual Poco::UInt16 sendMaskWriteRegisterRequest(const IoT::Modbus::MaskWriteRegisterRequest& request) = 0;
		/// Sends a Mask Write Register request.
		///
		/// A response from the device will be reported via the
		/// maskWriteRegisterResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendReadCoilsRequest(const IoT::Modbus::ReadCoilsRequest& request) = 0;
		/// Sends a Read Coils request.
		///
		/// A response from the device will be reported via the
		/// readCoilsResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendReadDiscreteInputsRequest(const IoT::Modbus::ReadDiscreteInputsRequest& request) = 0;
		/// Sends a Read Discrete Inputs request.
		///
		/// A response from the device will be reported via the
		/// readDiscreteInputsResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendReadExceptionStatusRequest(const IoT::Modbus::ReadExceptionStatusRequest& request) = 0;
		/// Sends a Read Exception Status request.
		///
		/// A response from the device will be reported via the
		/// readExceptionStatusResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendReadFIFOQueueRequest(const IoT::Modbus::ReadFIFOQueueRequest& request) = 0;
		/// Sends a Read FIFO Queue request.
		///
		/// A response from the device will be reported via the
		/// readFIFOQueueResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendReadHoldingRegistersRequest(const IoT::Modbus::ReadHoldingRegistersRequest& request) = 0;
		/// Sends a Read Holding Registers request.
		///
		/// A response from the device will be reported via the
		/// readHoldingRegistersResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendReadInputRegistersRequest(const IoT::Modbus::ReadInputRegistersRequest& request) = 0;
		/// Sends a Read Input Registers request.
		///
		/// A response from the device will be reported via the
		/// readInputRegistersResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendReadWriteMultipleRegistersRequest(const IoT::Modbus::ReadWriteMultipleRegistersRequest& request) = 0;
		/// Sends a Read Write Multiple Registers request.
		///
		/// A response from the device will be reported via the
		/// readWriteMultipleRegistersResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendRequest(const IoT::Modbus::GenericMessage& message) = 0;
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

	virtual Poco::UInt16 sendWriteMultipleCoilsRequest(const IoT::Modbus::WriteMultipleCoilsRequest& request) = 0;
		/// Sends a Write Multiple Coils request.
		///
		/// A response from the device will be reported via the
		/// writeMultipleCoilsResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendWriteMultipleRegistersRequest(const IoT::Modbus::WriteMultipleRegistersRequest& request) = 0;
		/// Sends a Write Multiple Registers request.
		///
		/// A response from the device will be reported via the
		/// writeMultipleRegistersResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendWriteSingleCoilRequest(const IoT::Modbus::WriteSingleCoilRequest& request) = 0;
		/// Sends a Write Single Coil request.
		///
		/// A response from the device will be reported via the
		/// writeSingleCoilResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendWriteSingleRegisterRequest(const IoT::Modbus::WriteSingleRegisterRequest& request) = 0;
		/// Sends a Write Single Register request.
		///
		/// A response from the device will be reported via the
		/// writeSingleRegisterResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	virtual void writeMultipleCoils(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, const std::vector < bool >& values) = 0;
		/// Sends a Write Multiple Coils request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual void writeMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, const std::vector < Poco::UInt16 >& values) = 0;
		/// Sends a Write Multiple Registers request to the device and waits for the response.
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

	Poco::BasicEvent < void > badFrameReceived;
	Poco::BasicEvent < const IoT::Modbus::ConnectionState > connectionStateChanged;
	Poco::BasicEvent < const std::string > error;
	Poco::BasicEvent < const IoT::Modbus::ModbusExceptionMessage > exceptionReceived;
	Poco::BasicEvent < const IoT::Modbus::MaskWriteRegisterResponse > maskWriteRegisterResponseReceived;
	Poco::BasicEvent < const IoT::Modbus::ReadCoilsResponse > readCoilsResponseReceived;
	Poco::BasicEvent < const IoT::Modbus::ReadDiscreteInputsResponse > readDiscreteInputsResponseReceived;
	Poco::BasicEvent < const IoT::Modbus::ReadExceptionStatusResponse > readExceptionStatusResponseReceived;
	Poco::BasicEvent < const IoT::Modbus::ReadFIFOQueueResponse > readFIFOQueueResponseReceived;
	Poco::BasicEvent < const IoT::Modbus::ReadHoldingRegistersResponse > readHoldingRegistersResponseReceived;
	Poco::BasicEvent < const IoT::Modbus::ReadInputRegistersResponse > readInputRegistersResponseReceived;
	Poco::BasicEvent < const IoT::Modbus::ReadWriteMultipleRegistersResponse > readWriteMultipleRegistersResponseReceived;
	Poco::BasicEvent < const IoT::Modbus::RequestFailure > requestFailed;
	Poco::BasicEvent < const IoT::Modbus::GenericMessage > responseReceived;
	Poco::BasicEvent < const Poco::UInt16 > timeout;
	Poco::BasicEvent < const IoT::Modbus::WriteMultipleCoilsResponse > writeMultipleCoilsResponseReceived;
	Poco::BasicEvent < const IoT::Modbus::WriteMultipleRegistersResponse > writeMultipleRegistersResponseReceived;
	Poco::BasicEvent < const IoT::Modbus::WriteSingleCoilResponse > writeSingleCoilResponseReceived;
	Poco::BasicEvent < const IoT::Modbus::WriteSingleRegisterResponse > writeSingleRegisterResponseReceived;
};


} // namespace Modbus
} // namespace IoT


#endif // IoT_Modbus_IModbusMaster_INCLUDED

