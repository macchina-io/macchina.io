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
#include "Poco/SharedPtr.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"
#include "Poco/Logger.h"
#include <map>


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
		_timeout(timeout),
		_stop(false),
		_nextTransactionID(0),
		_logger(Poco::Logger::get("IoT.ModbusMaster"))
	{
	}
		
	~ModbusMasterImpl()
	{
	}

	// ModbusMaster
	Poco::UInt16 sendRequest(const GenericMessage& message)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		return sendFrame(message);
	}
	
	Poco::UInt16 sendReadCoilsRequest(const ReadCoilsRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		return sendFrame(request);
	}

	Poco::UInt16 sendReadDiscreteInputsRequest(const ReadDiscreteInputsRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		return sendFrame(request);
	}

	Poco::UInt16 sendReadHoldingRegistersRequest(const ReadHoldingRegistersRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		return sendFrame(request);
	}

	Poco::UInt16 sendReadInputRegistersRequest(const ReadInputRegistersRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		return sendFrame(request);
	}

	Poco::UInt16 sendWriteSingleCoilRequest(const WriteSingleCoilRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		return sendFrame(request);
	}

	Poco::UInt16 sendWriteSingleRegisterRequest(const WriteSingleRegisterRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		return sendFrame(request);
	}

	Poco::UInt16 sendReadExceptionStatusRequest(const ReadExceptionStatusRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		return sendFrame(request);
	}

	Poco::UInt16 sendWriteMultipleCoilsRequest(const WriteMultipleCoilsRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		return sendFrame(request);
	}

	Poco::UInt16 sendWriteMultipleRegistersRequest(const WriteMultipleRegistersRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		return sendFrame(request);
	}

	Poco::UInt16 sendMaskWriteRegisterRequest(const MaskWriteRegisterRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		return sendFrame(request);
	}

	Poco::UInt16 sendReadWriteMultipleRegistersRequest(const ReadWriteMultipleRegistersRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		return sendFrame(request);
	}

	Poco::UInt16 sendReadFIFOQueueRequest(const ReadFIFOQueueRequest& request)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		enableEvents();
		return sendFrame(request);
	}

	std::vector<bool> readCoils(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, Poco::UInt16 nOfCoils)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		ReadCoilsRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		request.startingAddress = startingAddress;
		request.nOfCoils = nOfCoils;
		
		Poco::UInt16 transactionID = sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & MODBUS_EXCEPTION_MASK) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->decodeFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & MODBUS_FUNCTION_CODE_MASK) == request.functionCode)
			{
				ReadCoilsResponse response;
				decodeFrame(response, transactionID);
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
		
		Poco::UInt16 transactionID = sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & MODBUS_EXCEPTION_MASK) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->decodeFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & MODBUS_FUNCTION_CODE_MASK) == request.functionCode)
			{
				ReadDiscreteInputsResponse response;
				decodeFrame(response, transactionID);
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
		
		Poco::UInt16 transactionID = sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & MODBUS_EXCEPTION_MASK) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->decodeFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & MODBUS_FUNCTION_CODE_MASK) == request.functionCode)
			{
				ReadHoldingRegistersResponse response;
				decodeFrame(response, transactionID);
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
		
		Poco::UInt16 transactionID = sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & MODBUS_EXCEPTION_MASK) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->decodeFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & MODBUS_FUNCTION_CODE_MASK) == request.functionCode)
			{
				ReadInputRegistersResponse response;
				decodeFrame(response, transactionID);
				return response.registerValues;
			}
			else throw Poco::ProtocolException("incomplete or invalid frame received");
		}
		else throw Poco::TimeoutException();
	}

	void writeSingleCoil(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, bool value)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		WriteSingleCoilRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		request.outputAddress = outputAddress;
		request.value = value;
		
		Poco::UInt16 transactionID = sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & MODBUS_EXCEPTION_MASK) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->decodeFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & MODBUS_FUNCTION_CODE_MASK) == request.functionCode)
			{
				WriteSingleCoilResponse response;
				decodeFrame(response, transactionID);
			}
			else throw Poco::ProtocolException("incomplete or invalid frame received");
		}
		else throw Poco::TimeoutException();
	}

	void writeSingleRegister(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, Poco::UInt16 value)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		WriteSingleRegisterRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		request.outputAddress = outputAddress;
		request.value = value;
		
		Poco::UInt16 transactionID = sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & MODBUS_EXCEPTION_MASK) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->decodeFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & MODBUS_FUNCTION_CODE_MASK) == request.functionCode)
			{
				WriteSingleRegisterResponse response;
				decodeFrame(response, transactionID);
			}
			else throw Poco::ProtocolException("incomplete or invalid frame received");
		}
		else throw Poco::TimeoutException();
	}

	Poco::UInt8 readExceptionStatus(Poco::UInt8 slaveAddress)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		ReadExceptionStatusRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		
		Poco::UInt16 transactionID = sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & MODBUS_EXCEPTION_MASK) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->decodeFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & MODBUS_FUNCTION_CODE_MASK) == request.functionCode)
			{
				ReadExceptionStatusResponse response;
				decodeFrame(response, transactionID);
				return response.data;
			}
			else throw Poco::ProtocolException("incomplete or invalid frame received");
		}
		else throw Poco::TimeoutException();

		return 0;
	}

	void writeMultipleCoils(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, std::vector<bool> values)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		WriteMultipleCoilsRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		request.startingAddress = outputAddress;
		request.values = values;
		
		Poco::UInt16 transactionID = sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & MODBUS_EXCEPTION_MASK) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->decodeFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & MODBUS_FUNCTION_CODE_MASK) == request.functionCode)
			{
				WriteMultipleCoilsResponse response;
				decodeFrame(response, transactionID);
			}
			else throw Poco::ProtocolException("incomplete or invalid frame received");
		}
		else throw Poco::TimeoutException();
	}

	void writeMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, std::vector<Poco::UInt16> values)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		WriteMultipleRegistersRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		request.startingAddress = outputAddress;
		request.values = values;
		
		Poco::UInt16 transactionID = sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & MODBUS_EXCEPTION_MASK) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->decodeFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & MODBUS_FUNCTION_CODE_MASK) == request.functionCode)
			{
				WriteMultipleRegistersResponse response;
				decodeFrame(response, transactionID);
			}
			else throw Poco::ProtocolException("incomplete or invalid frame received");
		}
		else throw Poco::TimeoutException();
	}

	void maskWriteRegister(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, Poco::UInt16 andMask, Poco::UInt16 orMask)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		MaskWriteRegisterRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		request.referenceAddress = outputAddress;
		request.andMask = andMask;
		request.orMask = orMask;
		
		Poco::UInt16 transactionID = sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & MODBUS_EXCEPTION_MASK) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->decodeFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & MODBUS_FUNCTION_CODE_MASK) == request.functionCode)
			{
				MaskWriteRegisterResponse response;
				decodeFrame(response, transactionID);
			}
			else throw Poco::ProtocolException("incomplete or invalid frame received");
		}
		else throw Poco::TimeoutException();
	}

	std::vector<Poco::UInt16> readWriteMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 writeStartingAddress, std::vector<Poco::UInt16> writeValues, Poco::UInt16 readStartingAddress, Poco::UInt8 nOfReadRegisters)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		ReadWriteMultipleRegistersRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		request.readStartingAddress = readStartingAddress;
		request.readCount = nOfReadRegisters;
		request.writeStartingAddress = writeStartingAddress;
		request.values = writeValues;
		
		Poco::UInt16 transactionID = sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & MODBUS_EXCEPTION_MASK) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->decodeFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & MODBUS_FUNCTION_CODE_MASK) == request.functionCode)
			{
				ReadWriteMultipleRegistersResponse response;
				decodeFrame(response, transactionID);
				return response.values;
			}
			else throw Poco::ProtocolException("incomplete or invalid frame received");
		}
		else throw Poco::TimeoutException();
	}

	std::vector<Poco::UInt16> readFIFOQueue(Poco::UInt8 slaveAddress, Poco::UInt16 fifoPointerAddress)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		ReadFIFOQueueRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		request.fifoAddress = fifoPointerAddress;

		Poco::UInt16 transactionID = sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
			if ((fc & MODBUS_EXCEPTION_MASK) == MODBUS_EXCEPTION_MASK)
			{
				ModbusExceptionMessage message;
				_pPort->decodeFrame(message);
				throw ModbusException(message.functionCode, message.exceptionCode);
			}
			else if ((fc & MODBUS_FUNCTION_CODE_MASK) == request.functionCode)
			{
				ReadFIFOQueueResponse response;
				decodeFrame(response, transactionID);
				return response.values;
			}
			else throw Poco::ProtocolException("incomplete or invalid frame received");
		}
		else throw Poco::TimeoutException();
	}

protected:
	typedef std::map<Poco::UInt16, Poco::Timestamp> PendingMap;

	template <typename M>
	Poco::UInt16 sendFrame(const M& message)
	{
		if (_logger.debug())
		{
			_logger.debug("Sending frame: functionCode=%02x, slaveOrUnit=%02x", static_cast<unsigned>(message.functionCode), static_cast<unsigned>(message.slaveOrUnitAddress));
		}
		
		int maxTrans = _pPort->maxSimultaneousTransactions();
		if (_pThread && _pendingMap.size() >= maxTrans)
		{
			throw Poco::ProtocolException("Maximum number of pending requests exceeded");
		}

		message.transactionID = _nextTransactionID;
		if (maxTrans > 1)
		{
			++_nextTransactionID;
		}

		_pPort->sendFrame(message);

		if (_pThread)
		{
			_pendingMap[message.transactionID] = Poco::Timestamp();
		}
		
		return message.transactionID;
	}
	
	template <typename M>
	void decodeFrame(M& message, Poco::UInt16 transactionID)
	{
		_pPort->decodeFrame(message);
		if (message.transactionID != transactionID) throw Poco::ProtocolException("transaction ID mismatch");
	}
	
	void enableEvents()
	{
		if (!_pThread)
		{
			_logger.debug("Enabling events");
			_stop = false;
			_pendingMap.clear();
			_pThread = new Poco::Thread;
			_pThread->start(*this);
		}
	}
	
	void disableEvents()
	{
		if (_pThread)
		{
			_logger.debug("Disabling events");
			_stop = true;
			_pThread->join();
			_pThread = 0;
		}
	}
	
	// Runnable
	void run()
	{
		while (!stopped())
		{
			Poco::Timespan timeout(0, 250);
			if (_pPort->poll(timeout))
			{
				processFrame();
			}
			else
			{
				processPendingTimeouts();
			}
		}
	}
	
	void processFrame()
	{
		Poco::UInt8 fc = _pPort->receiveFrame(_timeout);
		if (fc == 0)
		{
			_logger.notice("Invalid or imcomplete frame received.");
			this->badFrameReceived(this);
			return;
		}
		
		if (_logger.debug())
		{
			_logger.debug("Processing frame: %02x", static_cast<unsigned>(fc));
		}
		
		if ((fc & MODBUS_EXCEPTION_MASK) == MODBUS_EXCEPTION_MASK)
		{
			ModbusExceptionMessage message;
			_pPort->decodeFrame(message);
			this->exceptionReceived(this, message);
		}
		else switch (fc & MODBUS_FUNCTION_CODE_MASK)
		{
		case MODBUS_READ_COILS:
			{
				ReadCoilsResponse response;
				_pPort->decodeFrame(response);  
				removePending(response.transactionID);
				this->readCoilsResponseReceived(this, response);
			}
			break;
			
		case MODBUS_READ_DISCRETE_INPUTS:
			{
				ReadDiscreteInputsResponse response;
				_pPort->decodeFrame(response);  
				removePending(response.transactionID);
				this->readDiscreteInputsResponseReceived(this, response);
			}
			break;
			
		case MODBUS_READ_HOLDING_REGISTERS:
			{
				ReadHoldingRegistersResponse response;
				_pPort->decodeFrame(response);  
				removePending(response.transactionID);
				_logger.debug("Firing readHoldingRegistersResponseReceived event...");
				this->readHoldingRegistersResponseReceived(this, response); 
			}
			break;
			
		case MODBUS_READ_INPUT_REGISTERS:
			{
				ReadInputRegistersResponse response;
				_pPort->decodeFrame(response);  
				removePending(response.transactionID);
				this->readInputRegistersResponseReceived(this, response);
			}
			break;
			
		case MODBUS_WRITE_SINGLE_COIL:
			{
				WriteSingleCoilResponse	response;
				_pPort->decodeFrame(response);  
				removePending(response.transactionID);
				this->writeSingleCoilResponseReceived(this, response);
			}
			break;
			
		case MODBUS_WRITE_SINGLE_REGISTER:           
			{
				WriteSingleRegisterResponse	response;
				_pPort->decodeFrame(response);  
				removePending(response.transactionID);
				this->writeSingleRegisterResponseReceived(this, response);
			}
			break;
			
		case MODBUS_READ_EXCEPTION_STATUS:
			{
				ReadExceptionStatusResponse	response;
				_pPort->decodeFrame(response);  
				removePending(response.transactionID);
				this->readExceptionStatusResponseReceived(this, response);        
			}
			break;
			
		case MODBUS_WRITE_MULTIPLE_COILS:
			{
				WriteMultipleCoilsResponse response;
				_pPort->decodeFrame(response);  
				removePending(response.transactionID);
				this->writeMultipleCoilsResponseReceived(this, response);
			}
			break;
			
		case MODBUS_WRITE_MULTIPLE_REGISTERS:        
			{
				WriteMultipleRegistersResponse response;
				_pPort->decodeFrame(response);  
				removePending(response.transactionID);
				this->writeMultipleRegistersResponseReceived(this, response);
			}
			break;
			
		case MODBUS_MASK_WRITE_REGISTER:    
			{
				MaskWriteRegisterResponse response;
				_pPort->decodeFrame(response);  
				removePending(response.transactionID);
				this->maskWriteRegisterResponseReceived(this, response);
			}
			break;
			
		case MODBUS_READ_WRITE_MULTIPLE_REGISTERS:   
			{
				ReadWriteMultipleRegistersResponse response;
				_pPort->decodeFrame(response);  
				removePending(response.transactionID);
				this->readWriteMultipleRegistersResponseReceived(this, response);   
			}
			break;
			
		case MODBUS_READ_FIFO_QUEUE:  
		    {
				ReadFIFOQueueResponse response;
				_pPort->decodeFrame(response);  
				removePending(response.transactionID);
				this->readFIFOQueueResponseReceived(this, response);   
			}
			break; 
			              
		default:
			{
				GenericMessage response;
				_pPort->decodeFrame(response);  
				removePending(response.transactionID);
				this->responseReceived(this, response);
			}
			break;
		}
	}
	
	void removePending(Poco::UInt16 transactionID)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		_pendingMap.erase(transactionID);
	}
	
	void processPendingTimeouts()
	{
		std::vector<Poco::UInt16> timeoutIDs;
		{
			Poco::FastMutex::ScopedLock lock(_mutex);
			for (PendingMap::iterator it = _pendingMap.begin(); it != _pendingMap.end();)
			{
				if (it->second.isElapsed(_timeout.totalMicroseconds()))
				{
					timeoutIDs.push_back(it->first);
					PendingMap::iterator itDel = it;
					++it;
					_pendingMap.erase(itDel);	
				}
				else
				{
					++it;
				}
			}
		}
		
		for (std::vector<Poco::UInt16>::const_iterator it = timeoutIDs.begin(); it != timeoutIDs.end(); ++it)
		{
			this->timeout(this, *it);
		}
	}
	
	bool stopped()
	{
		Poco::FastMutex::ScopedLock lock(_mutex);
		return _stop;
	}
	
private:
	Poco::FastMutex _mutex;
	Poco::SharedPtr<Port> _pPort;
	Poco::Timespan _timeout;
	Poco::SharedPtr<Poco::Thread> _pThread;
	bool _stop;
	Poco::UInt16 _nextTransactionID;
	PendingMap _pendingMap;
	Poco::Logger& _logger;
};


} } // namespace IoT::Modbus


#endif // IoT_Modbus_ModbusMasterImpl_INCLUDED
