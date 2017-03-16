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
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
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
	/// disable asynchronous mode.
{
public:
	typedef Poco::AutoPtr<ModbusMasterRemoteObject> Ptr;

	ModbusMasterRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Modbus::ModbusMaster> pServiceObject);
		/// Creates a ModbusMasterRemoteObject.

	virtual ~ModbusMasterRemoteObject();
		/// Destroys the ModbusMasterRemoteObject.

	virtual void maskWriteRegister(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, Poco::UInt16 andMask, Poco::UInt16 orMask);
		/// Sends a Mask Write register request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector < bool > readCoils(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfCoils);
		/// Sends a Read Coils request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::vector < bool > readDiscreteInputs(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfInputs);
		/// Sends a Read Discrete Inputs request to the device and waits for the response.
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

	virtual std::vector < Poco::UInt16 > readWriteMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 writeStartingAddress, std::vector < Poco::UInt16 > writeValues, Poco::UInt16 readStartingAddress, Poco::UInt8 nOfReadRegisters);
		/// Sends a Read/Write Multiple registers request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void sendMaskWriteRegisterRequest(const IoT::Modbus::MaskWriteRegisterRequest& request);
		/// Sends a Mask Write Register request.
		///
		/// A response from the device will be reported via the
		/// maskWriteRegisterResponseReceived event.

	virtual void sendReadCoilsRequest(const IoT::Modbus::ReadCoilsRequest& request);
		/// Sends a Read Coils request.
		///
		/// A response from the device will be reported via the
		/// readCoilsResponseReceived event.

	virtual void sendReadDiscreteInputsRequest(const IoT::Modbus::ReadDiscreteInputsRequest& request);
		/// Sends a Read Discrete Inputs request.
		///
		/// A response from the device will be reported via the
		/// readDiscreteInputsResponseReceived event.

	virtual void sendReadExceptionStatusRequest(const IoT::Modbus::ReadExceptionStatusRequest& request);
		/// Sends a Read Exception Status request.
		///
		/// A response from the device will be reported via the
		/// readExceptionStatusResponseReceived event.

	virtual void sendReadFIFOQueueRequest(const IoT::Modbus::ReadFIFOQueueRequest& request);
		/// Sends a Read FIFO Queue request.
		///
		/// A response from the device will be reported via the
		/// readFIFOQueueResponseReceived event.

	virtual void sendReadHoldingRegistersRequest(const IoT::Modbus::ReadHoldingRegistersRequest& request);
		/// Sends a Read Holding Registers request.
		///
		/// A response from the device will be reported via the
		/// readHoldingRegistersResponseReceived event.

	virtual void sendReadInputRegistersRequest(const IoT::Modbus::ReadInputRegistersRequest& request);
		/// Sends a Read Input Registers request.
		///
		/// A response from the device will be reported via the
		/// readInputRegistersResponseReceived event.

	virtual void sendReadWriteMultipleRegistersRequest(const IoT::Modbus::ReadWriteMultipleRegistersRequest& request);
		/// Sends a Read Write Multiple Registers request.
		///
		/// A response from the device will be reported via the
		/// readWriteMultipleRegistersResponseReceived event.

	virtual void sendRequest(const IoT::Modbus::GenericMessage& message);
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

	virtual void sendWriteMultipleCoilsRequest(const IoT::Modbus::WriteMultipleCoilsRequest& request);
		/// Sends a Write Multiple Coils request.
		///
		/// A response from the device will be reported via the
		/// writeMultipleCoilsResponseReceived event.

	virtual void sendWriteMultipleRegistersRequest(const IoT::Modbus::WriteMultipleRegistersRequest& request);
		/// Sends a Write Multiple Registers request.
		///
		/// A response from the device will be reported via the
		/// writeMultipleRegistersResponseReceived event.

	virtual void sendWriteSingleCoilRequest(const IoT::Modbus::WriteSingleCoilRequest& request);
		/// Sends a Write Single Coil request.
		///
		/// A response from the device will be reported via the
		/// writeSingleCoilResponseReceived event.

	virtual void sendWriteSingleRegisterRequest(const IoT::Modbus::WriteSingleRegisterRequest& request);
		/// Sends a Write Single Register request.
		///
		/// A response from the device will be reported via the
		/// writeSingleRegisterResponseReceived event.

	virtual void writeMultipleCoils(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, std::vector < bool > values);
		/// Sends a Write Multiple Coils request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual void writeMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, std::vector < Poco::UInt16 > values);
		/// Sends a Write Multiple Registers request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual void writeSingleCoil(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, bool value);
		/// Sends a Write Single Coils request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

	virtual void writeSingleRegister(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, Poco::UInt16 value);
		/// Sends a Write Single Register request to the device and waits for the response.
		///
		/// Throws a Poco::TimeoutException if the device does not respond within the specified timeout.
		/// Throws a ModbusException if the device responds with an exception message.

protected:
	void event__exceptionReceived(const IoT::Modbus::ModbusExceptionMessage& data);

	void event__maskWriteRegisterResponseReceived(IoT::Modbus::MaskWriteRegisterResponse& data);

	void event__readCoilsResponseReceived(IoT::Modbus::ReadCoilsResponse& data);

	void event__readDiscreteInputsResponseReceived(IoT::Modbus::ReadDiscreteInputsRequest& data);

	void event__readExceptionStatusResponseReceived(IoT::Modbus::ReadExceptionStatusResponse& data);

	void event__readFIFOQueueResponseReceived(IoT::Modbus::ReadFIFOQueueResponse& data);

	void event__readHoldingRegistersResponseReceived(IoT::Modbus::ReadHoldingRegistersResponse& data);

	void event__readInputRegistersResponseReceived(IoT::Modbus::ReadInputRegistersResponse& data);

	void event__readWriteMultipleRegistersResponseReceived(IoT::Modbus::ReadWriteMultipleRegistersResponse& data);

	void event__responseReceived(const IoT::Modbus::GenericMessage& data);

	void event__writeMultipleCoilsResponseReceived(IoT::Modbus::WriteMultipleCoilsResponse& data);

	void event__writeMultipleRegistersResponseReceived(IoT::Modbus::WriteMultipleRegistersResponse& data);

	void event__writeSingleCoilResponseReceived(IoT::Modbus::WriteSingleCoilResponse& data);

	void event__writeSingleRegisterResponseReceived(IoT::Modbus::WriteSingleRegisterResponse& data);

private:
	Poco::SharedPtr<IoT::Modbus::ModbusMaster> _pServiceObject;
};


inline void ModbusMasterRemoteObject::maskWriteRegister(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, Poco::UInt16 andMask, Poco::UInt16 orMask)
{
	_pServiceObject->maskWriteRegister(slaveAddress, outputAddress, andMask, orMask);
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


inline std::vector < Poco::UInt16 > ModbusMasterRemoteObject::readWriteMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 writeStartingAddress, std::vector < Poco::UInt16 > writeValues, Poco::UInt16 readStartingAddress, Poco::UInt8 nOfReadRegisters)
{
	return _pServiceObject->readWriteMultipleRegisters(slaveAddress, writeStartingAddress, writeValues, readStartingAddress, nOfReadRegisters);
}


inline const Poco::RemotingNG::Identifiable::TypeId& ModbusMasterRemoteObject::remoting__typeId() const
{
	return IModbusMaster::remoting__typeId();
}


inline void ModbusMasterRemoteObject::sendMaskWriteRegisterRequest(const IoT::Modbus::MaskWriteRegisterRequest& request)
{
	_pServiceObject->sendMaskWriteRegisterRequest(request);
}


inline void ModbusMasterRemoteObject::sendReadCoilsRequest(const IoT::Modbus::ReadCoilsRequest& request)
{
	_pServiceObject->sendReadCoilsRequest(request);
}


inline void ModbusMasterRemoteObject::sendReadDiscreteInputsRequest(const IoT::Modbus::ReadDiscreteInputsRequest& request)
{
	_pServiceObject->sendReadDiscreteInputsRequest(request);
}


inline void ModbusMasterRemoteObject::sendReadExceptionStatusRequest(const IoT::Modbus::ReadExceptionStatusRequest& request)
{
	_pServiceObject->sendReadExceptionStatusRequest(request);
}


inline void ModbusMasterRemoteObject::sendReadFIFOQueueRequest(const IoT::Modbus::ReadFIFOQueueRequest& request)
{
	_pServiceObject->sendReadFIFOQueueRequest(request);
}


inline void ModbusMasterRemoteObject::sendReadHoldingRegistersRequest(const IoT::Modbus::ReadHoldingRegistersRequest& request)
{
	_pServiceObject->sendReadHoldingRegistersRequest(request);
}


inline void ModbusMasterRemoteObject::sendReadInputRegistersRequest(const IoT::Modbus::ReadInputRegistersRequest& request)
{
	_pServiceObject->sendReadInputRegistersRequest(request);
}


inline void ModbusMasterRemoteObject::sendReadWriteMultipleRegistersRequest(const IoT::Modbus::ReadWriteMultipleRegistersRequest& request)
{
	_pServiceObject->sendReadWriteMultipleRegistersRequest(request);
}


inline void ModbusMasterRemoteObject::sendRequest(const IoT::Modbus::GenericMessage& message)
{
	_pServiceObject->sendRequest(message);
}


inline void ModbusMasterRemoteObject::sendWriteMultipleCoilsRequest(const IoT::Modbus::WriteMultipleCoilsRequest& request)
{
	_pServiceObject->sendWriteMultipleCoilsRequest(request);
}


inline void ModbusMasterRemoteObject::sendWriteMultipleRegistersRequest(const IoT::Modbus::WriteMultipleRegistersRequest& request)
{
	_pServiceObject->sendWriteMultipleRegistersRequest(request);
}


inline void ModbusMasterRemoteObject::sendWriteSingleCoilRequest(const IoT::Modbus::WriteSingleCoilRequest& request)
{
	_pServiceObject->sendWriteSingleCoilRequest(request);
}


inline void ModbusMasterRemoteObject::sendWriteSingleRegisterRequest(const IoT::Modbus::WriteSingleRegisterRequest& request)
{
	_pServiceObject->sendWriteSingleRegisterRequest(request);
}


inline void ModbusMasterRemoteObject::writeMultipleCoils(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, std::vector < bool > values)
{
	_pServiceObject->writeMultipleCoils(slaveAddress, outputAddress, values);
}


inline void ModbusMasterRemoteObject::writeMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, std::vector < Poco::UInt16 > values)
{
	_pServiceObject->writeMultipleRegisters(slaveAddress, outputAddress, values);
}


inline void ModbusMasterRemoteObject::writeSingleCoil(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, bool value)
{
	_pServiceObject->writeSingleCoil(slaveAddress, outputAddress, value);
}


inline void ModbusMasterRemoteObject::writeSingleRegister(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, Poco::UInt16 value)
{
	_pServiceObject->writeSingleRegister(slaveAddress, outputAddress, value);
}


} // namespace Modbus
} // namespace IoT


#endif // IoT_Modbus_ModbusMasterRemoteObject_INCLUDED

