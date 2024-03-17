//
// ModbusMasterRemoteObject.h
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


#ifndef IoT_Modbus_ModbusMasterRemoteObject_INCLUDED
#define IoT_Modbus_ModbusMasterRemoteObject_INCLUDED


#include "IoT/Modbus/IModbusMaster.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Modbus {


class ModbusMasterRemoteObject: public IoT::Modbus::IModbusMaster, public Poco::RemotingNG::RemoteObject
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
	using Ptr = Poco::AutoPtr<ModbusMasterRemoteObject>;

	ModbusMasterRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Modbus::ModbusMaster> pServiceObject);
		/// Creates a ModbusMasterRemoteObject.

	virtual ~ModbusMasterRemoteObject();
		/// Destroys the ModbusMasterRemoteObject.

	virtual std::string address() const;
		/// Returns the Modbus master address as a string.

	virtual bool hasTransactionIDs() const;
		/// Returns true if the port supports transaction IDs,
		/// otherwise false. Currently, only Modbus/TCP supports
		/// transaction IDs.

	virtual void maskWriteRegister(Poco::UInt8 slaveAddress, Poco::UInt16 referenceAddress, Poco::UInt16 andMask, Poco::UInt16 orMask);
		/// Sends a Mask Write register request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::size_t maxSimultaneousTransactions() const;
		/// Returns the maximum allowed number of in-flight requests.

	virtual std::size_t pendingTransactions() const;
		/// Returns the current number of in-flight requests.

	virtual std::vector < bool > readCoils(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfCoils);
		/// Sends a Read Coils request to the device and waits for the response.
		///
		/// Note: due to the wire format of the Modbus protocol, the returned vector will always have
		/// a size that is a multiple of 8, and may thus contain up to 7 more values than specified in nOfCoils.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector < bool > readDiscreteInputs(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfInputs);
		/// Sends a Read Discrete Inputs request to the device and waits for the response.
		///
		/// Note: due to the wire format of the Modbus protocol, the returned vector will always have
		/// a size that is a multiple of 8, and may thus contain up to 7 more values than specified in nOfInputs.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual Poco::UInt8 readExceptionStatus(Poco::UInt8 slaveAddress);
		/// Sends a Read Exception Status request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector < Poco::UInt16 > readFIFOQueue(Poco::UInt8 slaveAddress, Poco::UInt16 fifoPointerAddress);
		/// Sends a Read FIFO Queue request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector < Poco::UInt16 > readHoldingRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfRegisters);
		/// Sends a Read Holding Registers request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector < Poco::UInt16 > readInputRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfRegisters);
		/// Sends a Read Input Registers request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector < Poco::UInt16 > readWriteMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 writeStartingAddress, const std::vector < Poco::UInt16 >& writeValues, Poco::UInt16 readStartingAddress, Poco::UInt8 nOfReadRegisters);
		/// Sends a Read/Write Multiple registers request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void reset();
		/// Resets the connection to the bus or device.

	virtual Poco::UInt16 sendMaskWriteRegisterRequest(const IoT::Modbus::MaskWriteRegisterRequest& request);
		/// Sends a Mask Write Register request.
		///
		/// A response from the device will be reported via the
		/// maskWriteRegisterResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendReadCoilsRequest(const IoT::Modbus::ReadCoilsRequest& request);
		/// Sends a Read Coils request.
		///
		/// A response from the device will be reported via the
		/// readCoilsResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendReadDiscreteInputsRequest(const IoT::Modbus::ReadDiscreteInputsRequest& request);
		/// Sends a Read Discrete Inputs request.
		///
		/// A response from the device will be reported via the
		/// readDiscreteInputsResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendReadExceptionStatusRequest(const IoT::Modbus::ReadExceptionStatusRequest& request);
		/// Sends a Read Exception Status request.
		///
		/// A response from the device will be reported via the
		/// readExceptionStatusResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendReadFIFOQueueRequest(const IoT::Modbus::ReadFIFOQueueRequest& request);
		/// Sends a Read FIFO Queue request.
		///
		/// A response from the device will be reported via the
		/// readFIFOQueueResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendReadHoldingRegistersRequest(const IoT::Modbus::ReadHoldingRegistersRequest& request);
		/// Sends a Read Holding Registers request.
		///
		/// A response from the device will be reported via the
		/// readHoldingRegistersResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendReadInputRegistersRequest(const IoT::Modbus::ReadInputRegistersRequest& request);
		/// Sends a Read Input Registers request.
		///
		/// A response from the device will be reported via the
		/// readInputRegistersResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendReadWriteMultipleRegistersRequest(const IoT::Modbus::ReadWriteMultipleRegistersRequest& request);
		/// Sends a Read Write Multiple Registers request.
		///
		/// A response from the device will be reported via the
		/// readWriteMultipleRegistersResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendRequest(const IoT::Modbus::GenericMessage& message);
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

	virtual Poco::UInt16 sendWriteMultipleCoilsRequest(const IoT::Modbus::WriteMultipleCoilsRequest& request);
		/// Sends a Write Multiple Coils request.
		///
		/// A response from the device will be reported via the
		/// writeMultipleCoilsResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendWriteMultipleRegistersRequest(const IoT::Modbus::WriteMultipleRegistersRequest& request);
		/// Sends a Write Multiple Registers request.
		///
		/// A response from the device will be reported via the
		/// writeMultipleRegistersResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendWriteSingleCoilRequest(const IoT::Modbus::WriteSingleCoilRequest& request);
		/// Sends a Write Single Coil request.
		///
		/// A response from the device will be reported via the
		/// writeSingleCoilResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual Poco::UInt16 sendWriteSingleRegisterRequest(const IoT::Modbus::WriteSingleRegisterRequest& request);
		/// Sends a Write Single Register request.
		///
		/// A response from the device will be reported via the
		/// writeSingleRegisterResponseReceived event.
		///
		/// Returns the transaction ID for the request.

	virtual void writeMultipleCoils(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, const std::vector < bool >& values);
		/// Sends a Write Multiple Coils request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual void writeMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, const std::vector < Poco::UInt16 >& values);
		/// Sends a Write Multiple Registers request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual void writeSingleCoil(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, bool value);
		/// Sends a Write Single Coils request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual void writeSingleRegister(Poco::UInt8 slaveAddress, Poco::UInt16 registerAddress, Poco::UInt16 value);
		/// Sends a Write Single Register request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

protected:
	void event__badFrameReceived();

	void event__connectionStateChanged(const IoT::Modbus::ConnectionState& data);

	void event__error(const std::string& data);

	void event__exceptionReceived(const IoT::Modbus::ModbusExceptionMessage& data);

	void event__maskWriteRegisterResponseReceived(const IoT::Modbus::MaskWriteRegisterResponse& data);

	void event__readCoilsResponseReceived(const IoT::Modbus::ReadCoilsResponse& data);

	void event__readDiscreteInputsResponseReceived(const IoT::Modbus::ReadDiscreteInputsResponse& data);

	void event__readExceptionStatusResponseReceived(const IoT::Modbus::ReadExceptionStatusResponse& data);

	void event__readFIFOQueueResponseReceived(const IoT::Modbus::ReadFIFOQueueResponse& data);

	void event__readHoldingRegistersResponseReceived(const IoT::Modbus::ReadHoldingRegistersResponse& data);

	void event__readInputRegistersResponseReceived(const IoT::Modbus::ReadInputRegistersResponse& data);

	void event__readWriteMultipleRegistersResponseReceived(const IoT::Modbus::ReadWriteMultipleRegistersResponse& data);

	void event__requestFailed(const IoT::Modbus::RequestFailure& data);

	void event__responseReceived(const IoT::Modbus::GenericMessage& data);

	void event__timeout(const Poco::UInt16& data);

	void event__writeMultipleCoilsResponseReceived(const IoT::Modbus::WriteMultipleCoilsResponse& data);

	void event__writeMultipleRegistersResponseReceived(const IoT::Modbus::WriteMultipleRegistersResponse& data);

	void event__writeSingleCoilResponseReceived(const IoT::Modbus::WriteSingleCoilResponse& data);

	void event__writeSingleRegisterResponseReceived(const IoT::Modbus::WriteSingleRegisterResponse& data);

private:
	Poco::SharedPtr<IoT::Modbus::ModbusMaster> _pServiceObject;
};


inline std::string ModbusMasterRemoteObject::address() const
{
	return _pServiceObject->address();
}


inline bool ModbusMasterRemoteObject::hasTransactionIDs() const
{
	return _pServiceObject->hasTransactionIDs();
}


inline void ModbusMasterRemoteObject::maskWriteRegister(Poco::UInt8 slaveAddress, Poco::UInt16 referenceAddress, Poco::UInt16 andMask, Poco::UInt16 orMask)
{
	_pServiceObject->maskWriteRegister(slaveAddress, referenceAddress, andMask, orMask);
}


inline std::size_t ModbusMasterRemoteObject::maxSimultaneousTransactions() const
{
	return _pServiceObject->maxSimultaneousTransactions();
}


inline std::size_t ModbusMasterRemoteObject::pendingTransactions() const
{
	return _pServiceObject->pendingTransactions();
}


inline std::vector < bool > ModbusMasterRemoteObject::readCoils(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfCoils)
{
	return _pServiceObject->readCoils(slaveAddress, startingAddress, nOfCoils);
}


inline std::vector < bool > ModbusMasterRemoteObject::readDiscreteInputs(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfInputs)
{
	return _pServiceObject->readDiscreteInputs(slaveAddress, startingAddress, nOfInputs);
}


inline Poco::UInt8 ModbusMasterRemoteObject::readExceptionStatus(Poco::UInt8 slaveAddress)
{
	return _pServiceObject->readExceptionStatus(slaveAddress);
}


inline std::vector < Poco::UInt16 > ModbusMasterRemoteObject::readFIFOQueue(Poco::UInt8 slaveAddress, Poco::UInt16 fifoPointerAddress)
{
	return _pServiceObject->readFIFOQueue(slaveAddress, fifoPointerAddress);
}


inline std::vector < Poco::UInt16 > ModbusMasterRemoteObject::readHoldingRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfRegisters)
{
	return _pServiceObject->readHoldingRegisters(slaveAddress, startingAddress, nOfRegisters);
}


inline std::vector < Poco::UInt16 > ModbusMasterRemoteObject::readInputRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfRegisters)
{
	return _pServiceObject->readInputRegisters(slaveAddress, startingAddress, nOfRegisters);
}


inline std::vector < Poco::UInt16 > ModbusMasterRemoteObject::readWriteMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 writeStartingAddress, const std::vector < Poco::UInt16 >& writeValues, Poco::UInt16 readStartingAddress, Poco::UInt8 nOfReadRegisters)
{
	return _pServiceObject->readWriteMultipleRegisters(slaveAddress, writeStartingAddress, writeValues, readStartingAddress, nOfReadRegisters);
}


inline const Poco::RemotingNG::Identifiable::TypeId& ModbusMasterRemoteObject::remoting__typeId() const
{
	return IModbusMaster::remoting__typeId();
}


inline void ModbusMasterRemoteObject::reset()
{
	_pServiceObject->reset();
}


inline Poco::UInt16 ModbusMasterRemoteObject::sendMaskWriteRegisterRequest(const IoT::Modbus::MaskWriteRegisterRequest& request)
{
	return _pServiceObject->sendMaskWriteRegisterRequest(request);
}


inline Poco::UInt16 ModbusMasterRemoteObject::sendReadCoilsRequest(const IoT::Modbus::ReadCoilsRequest& request)
{
	return _pServiceObject->sendReadCoilsRequest(request);
}


inline Poco::UInt16 ModbusMasterRemoteObject::sendReadDiscreteInputsRequest(const IoT::Modbus::ReadDiscreteInputsRequest& request)
{
	return _pServiceObject->sendReadDiscreteInputsRequest(request);
}


inline Poco::UInt16 ModbusMasterRemoteObject::sendReadExceptionStatusRequest(const IoT::Modbus::ReadExceptionStatusRequest& request)
{
	return _pServiceObject->sendReadExceptionStatusRequest(request);
}


inline Poco::UInt16 ModbusMasterRemoteObject::sendReadFIFOQueueRequest(const IoT::Modbus::ReadFIFOQueueRequest& request)
{
	return _pServiceObject->sendReadFIFOQueueRequest(request);
}


inline Poco::UInt16 ModbusMasterRemoteObject::sendReadHoldingRegistersRequest(const IoT::Modbus::ReadHoldingRegistersRequest& request)
{
	return _pServiceObject->sendReadHoldingRegistersRequest(request);
}


inline Poco::UInt16 ModbusMasterRemoteObject::sendReadInputRegistersRequest(const IoT::Modbus::ReadInputRegistersRequest& request)
{
	return _pServiceObject->sendReadInputRegistersRequest(request);
}


inline Poco::UInt16 ModbusMasterRemoteObject::sendReadWriteMultipleRegistersRequest(const IoT::Modbus::ReadWriteMultipleRegistersRequest& request)
{
	return _pServiceObject->sendReadWriteMultipleRegistersRequest(request);
}


inline Poco::UInt16 ModbusMasterRemoteObject::sendRequest(const IoT::Modbus::GenericMessage& message)
{
	return _pServiceObject->sendRequest(message);
}


inline Poco::UInt16 ModbusMasterRemoteObject::sendWriteMultipleCoilsRequest(const IoT::Modbus::WriteMultipleCoilsRequest& request)
{
	return _pServiceObject->sendWriteMultipleCoilsRequest(request);
}


inline Poco::UInt16 ModbusMasterRemoteObject::sendWriteMultipleRegistersRequest(const IoT::Modbus::WriteMultipleRegistersRequest& request)
{
	return _pServiceObject->sendWriteMultipleRegistersRequest(request);
}


inline Poco::UInt16 ModbusMasterRemoteObject::sendWriteSingleCoilRequest(const IoT::Modbus::WriteSingleCoilRequest& request)
{
	return _pServiceObject->sendWriteSingleCoilRequest(request);
}


inline Poco::UInt16 ModbusMasterRemoteObject::sendWriteSingleRegisterRequest(const IoT::Modbus::WriteSingleRegisterRequest& request)
{
	return _pServiceObject->sendWriteSingleRegisterRequest(request);
}


inline void ModbusMasterRemoteObject::writeMultipleCoils(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, const std::vector < bool >& values)
{
	_pServiceObject->writeMultipleCoils(slaveAddress, startingAddress, values);
}


inline void ModbusMasterRemoteObject::writeMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, const std::vector < Poco::UInt16 >& values)
{
	_pServiceObject->writeMultipleRegisters(slaveAddress, startingAddress, values);
}


inline void ModbusMasterRemoteObject::writeSingleCoil(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, bool value)
{
	_pServiceObject->writeSingleCoil(slaveAddress, outputAddress, value);
}


inline void ModbusMasterRemoteObject::writeSingleRegister(Poco::UInt8 slaveAddress, Poco::UInt16 registerAddress, Poco::UInt16 value)
{
	_pServiceObject->writeSingleRegister(slaveAddress, registerAddress, value);
}


} // namespace Modbus
} // namespace IoT


#endif // IoT_Modbus_ModbusMasterRemoteObject_INCLUDED

