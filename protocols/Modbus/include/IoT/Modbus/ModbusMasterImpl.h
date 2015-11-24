//
// ModbusMasterImpl.h
//
// $Id$
//
// Library: IoT/Modbus
// Package: ModbusMaster
// Module:  ModbusMasterImpl
//
// Definition of the ModbusMasterImpl class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Modbus_ModbusMasterImpl_INCLUDED
#define IoT_Modbus_ModbusMasterImpl_INCLUDED


#include "IoT/Modbus/ModbusMaster.h"
#include "IoT/Modbus/ModbusException.h"
#include "Poco/Runnable.h"
#include "Poco/Thread.h"


namespace IoT {
namespace Modbus {


template <class Port>
class IoTModbus_API ModbusMasterImpl: public ModbusMaster, public Poco::Runnable
	/// An implementation of the ModbusMaster interface for the Modbus RTU
	/// protocol over a serial line.
{
public:
	ModbusMasterImpl(Poco::SharedPtr<Port> pPort, Poco::Timespan timeout = Poco::Timespan(2, 0)):
		_pPort(pPort),
		_timeout(timeout)
	{
	}
		
	~ModbusMasterImpl()
	{
	}

	// ModbusMaster
	void sendRequest(const GenericMessage& message)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		_pPort->sendFrame(message);
	}
	
	void sendReadCoilsRequest(const ReadCoilsRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		_pPort->sendFrame(request);
	}

	void sendReadDiscreteInputsRequest(const ReadDiscreteInputsRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		_pPort->sendFrame(request);
	}

	void sendReadHoldingRegistersRequest(const ReadHoldingRegistersRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		_pPort->sendFrame(request);
	}

	void sendReadInputRegistersRequest(const ReadInputRegistersRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		_pPort->sendFrame(request);
	}

	void sendWriteSingleCoilRequest(const WriteSingleCoilRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		_pPort->sendFrame(request);
	}

	void sendWriteSingleRegisterRequest(const WriteSingleRegisterRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		_pPort->sendFrame(request);
	}

	void sendReadExceptionStatusRequest(const ReadExceptionStatusRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		_pPort->sendFrame(request);
	}

	void sendWriteMultipleCoilsRequest(const WriteMultipleCoilsRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		_pPort->sendFrame(request);
	}

	void sendWriteMultipleRegistersRequest(const WriteMultipleRegistersRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		_pPort->sendFrame(request);
	}

	void sendMaskWriteRegisterRequest(const MaskWriteRegisterRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		_pPort->sendFrame(request);
	}

	void sendReadWriteMultipleRegistersRequest(const ReadWriteMultipleRegistersRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		_pPort->sendFrame(request);
	}

	void sendReadFIFOQueueRequest(const ReadFIFOQueueRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		_pPort->sendFrame(request);
	}

	std::vector<bool> readCoils(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfCoils)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		ReadCoilsRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		request.startingAddress = startingAddress;
		request.nOfCoils = nOfCoils;
		_pPort->sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & 0x80) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->receiveFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & 0x7F) == request.functionCode)
			{
				ReadCoilsResponse response;
				_pPort->receiveFrame(response);
				return response.coilStatus;
			}
			else throw Poco::ProtocolException("incomplete or invalid frame received");
		}
		else throw Poco::TimeoutException();
	}

	std::vector<bool> readDiscreteInputs(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfInputs)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		ReadDiscreteInputsRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		request.startingAddress = startingAddress;
		request.nOfInputs = nOfInputs;
		_pPort->sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & 0x80) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->receiveFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & 0x7F) == request.functionCode)
			{
				ReadDiscreteInputsResponse response;
				_pPort->receiveFrame(response);
				return response.inputStatus;
			}
			else throw Poco::ProtocolException("incomplete or invalid frame received");
		}
		else throw Poco::TimeoutException();
	}

	std::vector<Poco::UInt16> readHoldingRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfRegisters)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		ReadHoldingRegistersRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		request.startingAddress = startingAddress;
		request.nOfRegisters = nOfRegisters;
		_pPort->sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & 0x80) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->receiveFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & 0x7F) == request.functionCode)
			{
				ReadHoldingRegistersResponse response;
				_pPort->receiveFrame(response);
				return response.registerValues;
			}
			else throw Poco::ProtocolException("incomplete or invalid frame received");
		}
		else throw Poco::TimeoutException();
	}

	std::vector<Poco::UInt16> readInputRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfRegisters)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		ReadInputRegistersRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		request.startingAddress = startingAddress;
		request.nOfRegisters = nOfRegisters;
		_pPort->sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & 0x80) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->receiveFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & 0x7F) == request.functionCode)
			{
				ReadInputRegistersResponse response;
				_pPort->receiveFrame(response);
				return response.registerValues;
			}
			else throw Poco::ProtocolException("incomplete or invalid frame received");
		}
		else throw Poco::TimeoutException();
	}

	void writeSingleCoil(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, bool value)
	{
		// TODO
	}

	void writeSingleRegister(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, Poco::UInt16 value)
	{
		// TODO
	}

	Poco::UInt8 readExceptionStatus(Poco::UInt8 slaveAddress)
	{
		// TODO
		return 0;
	}
	
protected:
	void enableEvents()
	{
		// TODO: start receiver thread
	}
	
	void disableEvents()
	{
		// TODO: stop receiver thread
	}
	
	// TODO: receiver thread for events
	
	// Runnable
	void run()
	{
	}
	
private:
	Poco::FastMutex _mutex;
	Poco::SharedPtr<Port> _pPort;
	Poco::Timespan _timeout;
};


} } // namespace IoT::Modbus


#endif // IoT_Modbus_ModbusMasterImpl_INCLUDED
