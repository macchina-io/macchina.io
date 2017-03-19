//
// ModbusMasterEventDispatcher.h
//
// Library: IoT/Modbus
// Package: Generated
// Module:  ModbusMasterEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Modbus_ModbusMasterEventDispatcher_INCLUDED
#define IoT_Modbus_ModbusMasterEventDispatcher_INCLUDED


#include "IoT/Modbus/ModbusMasterRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace Modbus {


class ModbusMasterEventDispatcher: public Poco::RemotingNG::EventDispatcher
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
	ModbusMasterEventDispatcher(ModbusMasterRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a ModbusMasterEventDispatcher.

	virtual ~ModbusMasterEventDispatcher();
		/// Destroys the ModbusMasterEventDispatcher.

	void event__badFrameReceived(const void* pSender);

	void event__exceptionReceived(const void* pSender, const IoT::Modbus::ModbusExceptionMessage& data);

	void event__maskWriteRegisterResponseReceived(const void* pSender, const IoT::Modbus::MaskWriteRegisterResponse& data);

	void event__readCoilsResponseReceived(const void* pSender, const IoT::Modbus::ReadCoilsResponse& data);

	void event__readDiscreteInputsResponseReceived(const void* pSender, const IoT::Modbus::ReadDiscreteInputsResponse& data);

	void event__readExceptionStatusResponseReceived(const void* pSender, const IoT::Modbus::ReadExceptionStatusResponse& data);

	void event__readFIFOQueueResponseReceived(const void* pSender, const IoT::Modbus::ReadFIFOQueueResponse& data);

	void event__readHoldingRegistersResponseReceived(const void* pSender, const IoT::Modbus::ReadHoldingRegistersResponse& data);

	void event__readInputRegistersResponseReceived(const void* pSender, const IoT::Modbus::ReadInputRegistersResponse& data);

	void event__readWriteMultipleRegistersResponseReceived(const void* pSender, const IoT::Modbus::ReadWriteMultipleRegistersResponse& data);

	void event__responseReceived(const void* pSender, const IoT::Modbus::GenericMessage& data);

	void event__timeout(const void* pSender, const Poco::UInt16& data);

	void event__writeMultipleCoilsResponseReceived(const void* pSender, const IoT::Modbus::WriteMultipleCoilsResponse& data);

	void event__writeMultipleRegistersResponseReceived(const void* pSender, const IoT::Modbus::WriteMultipleRegistersResponse& data);

	void event__writeSingleCoilResponseReceived(const void* pSender, const IoT::Modbus::WriteSingleCoilResponse& data);

	void event__writeSingleRegisterResponseReceived(const void* pSender, const IoT::Modbus::WriteSingleRegisterResponse& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__badFrameReceivedImpl(const std::string& subscriberURI);

	void event__exceptionReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ModbusExceptionMessage& data);

	void event__maskWriteRegisterResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::MaskWriteRegisterResponse& data);

	void event__readCoilsResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ReadCoilsResponse& data);

	void event__readDiscreteInputsResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ReadDiscreteInputsResponse& data);

	void event__readExceptionStatusResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ReadExceptionStatusResponse& data);

	void event__readFIFOQueueResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ReadFIFOQueueResponse& data);

	void event__readHoldingRegistersResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ReadHoldingRegistersResponse& data);

	void event__readInputRegistersResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ReadInputRegistersResponse& data);

	void event__readWriteMultipleRegistersResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::ReadWriteMultipleRegistersResponse& data);

	void event__responseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::GenericMessage& data);

	void event__timeoutImpl(const std::string& subscriberURI, const Poco::UInt16& data);

	void event__writeMultipleCoilsResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::WriteMultipleCoilsResponse& data);

	void event__writeMultipleRegistersResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::WriteMultipleRegistersResponse& data);

	void event__writeSingleCoilResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::WriteSingleCoilResponse& data);

	void event__writeSingleRegisterResponseReceivedImpl(const std::string& subscriberURI, const IoT::Modbus::WriteSingleRegisterResponse& data);

	static const std::string DEFAULT_NS;
	ModbusMasterRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& ModbusMasterEventDispatcher::remoting__typeId() const
{
	return IModbusMaster::remoting__typeId();
}


} // namespace Modbus
} // namespace IoT


#endif // IoT_Modbus_ModbusMasterEventDispatcher_INCLUDED

