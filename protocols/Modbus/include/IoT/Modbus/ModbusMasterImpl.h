//
// ModbusMasterImpl.h
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
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Modbus_ModbusMasterImpl_INCLUDED
#define IoT_Modbus_ModbusMasterImpl_INCLUDED


#include "IoT/Modbus/ModbusMaster.h"
#include "IoT/Modbus/ModbusException.h"
#include "Poco/Thread.h"
#include "Poco/NotificationQueue.h"
#include "Poco/SharedPtr.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"
#include "Poco/Delegate.h"
#include "Poco/Logger.h"
#include <atomic>
#include <memory>
#include <map>


namespace IoT {
namespace Modbus {


template <class Port>
class IoTModbus_API ModbusMasterImpl: public ModbusMaster, public Poco::Runnable
	/// An implementation of the ModbusMaster interface for the Modbus RTU
	/// protocol over a serial line.
{
public:
	ModbusMasterImpl(Poco::SharedPtr<Port> pPort, Poco::Timespan responseTimeout = Poco::Timespan(2, 0)):
		_pPort(pPort),
		_timeout(responseTimeout),
		_nextTransactionID(0),
		_logger(Poco::Logger::get("IoT.ModbusMaster"))
	{
		_pPort->connectionStateChanged += Poco::delegate(this, &ModbusMasterImpl::onConnectionStateChanged);
	}

	~ModbusMasterImpl()
	{
		_pPort->connectionStateChanged -= Poco::delegate(this, &ModbusMasterImpl::onConnectionStateChanged);
	}

	// ModbusMaster
	std::string address() const
	{
		return _pPort->address();
	}

	std::size_t maxSimultaneousTransactions() const
	{
		return _pPort->maxSimultaneousTransactions();
	}

	std::size_t pendingTransactions() const
	{
		return countPending();
	}

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
			Poco::UInt8 fc = _pPort->receiveFrame();
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
			Poco::UInt8 fc = _pPort->receiveFrame();
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
			Poco::UInt8 fc = _pPort->receiveFrame();
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
			Poco::UInt8 fc = _pPort->receiveFrame();
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
			Poco::UInt8 fc = _pPort->receiveFrame();
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

	void writeSingleRegister(Poco::UInt8 slaveAddress, Poco::UInt16 registerAddress, Poco::UInt16 value)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		WriteSingleRegisterRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		request.registerAddress = registerAddress;
		request.value = value;

		Poco::UInt16 transactionID = sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame();
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
			Poco::UInt8 fc = _pPort->receiveFrame();
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

	void writeMultipleCoils(Poco::UInt8 slaveAddress, Poco::UInt16 outputAddress, const std::vector<bool>& values)
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
			Poco::UInt8 fc = _pPort->receiveFrame();
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

	void writeMultipleRegisters(Poco::UInt8 slaveAddress, Poco::UInt16 startingAddress, const std::vector<Poco::UInt16>& values)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		WriteMultipleRegistersRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		request.startingAddress = startingAddress;
		request.values = values;

		Poco::UInt16 transactionID = sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame();
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

	void maskWriteRegister(Poco::UInt8 slaveAddress, Poco::UInt16 referenceAddress, Poco::UInt16 andMask, Poco::UInt16 orMask)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		disableEvents();
		MaskWriteRegisterRequest request;
		request.slaveOrUnitAddress = slaveAddress;
		request.referenceAddress = referenceAddress;
		request.andMask = andMask;
		request.orMask = orMask;

		Poco::UInt16 transactionID = sendFrame(request);
		if (_pPort->poll(_timeout))
		{
			Poco::UInt8 fc = _pPort->receiveFrame();
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

	std::vector<Poco::UInt16> readWriteMultipleRegisters(
			Poco::UInt8 slaveAddress, 
			Poco::UInt16 writeStartingAddress,
			const std::vector<Poco::UInt16>& writeValues, 
			Poco::UInt16 readStartingAddress, 
			Poco::UInt8 nOfReadRegisters)
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
			Poco::UInt8 fc = _pPort->receiveFrame();
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
			Poco::UInt8 fc = _pPort->receiveFrame();
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

	void reset()
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		abortPending(FAILURE_RESET);
		disableEvents();
		_pPort->reset();
	}

protected:
	struct PendingInfo
	{
		Poco::UInt8 functionCode = 0;
		Poco::UInt8 slaveOrUnitAddress = 0;
		Poco::Timestamp timeSent;
	};
	using PendingMap = std::map<Poco::UInt16, PendingInfo>;

	class SendNotification: public Poco::Notification
	{
	public:
		virtual void run() = 0;
		virtual const ModbusMessage& message() const = 0;
	};

	template <typename M, typename P>
	class SendNotificationImpl: public SendNotification
	{
	public:
		SendNotificationImpl(const M& message, Poco::SharedPtr<P> pPort):
			_message(message),
			_pPort(pPort)
		{
		}

		void run()
		{
			_pPort->sendFrame(_message);
		}

		const ModbusMessage& message() const 
		{
			return _message;
		}

	private:
		const M _message;
		Poco::SharedPtr<P> _pPort;
	};

	class StopNotification: public Poco::Notification
	{
	};

	template <typename M>
	Poco::UInt16 sendFrame(const M& message)
	{
		// NOTE: Mutex must be locked by caller
	
		using namespace std::string_literals;

		if (_logger.trace())
		{
			_logger.trace("Sending frame: functionCode=%02x, slaveOrUnit=%02x"s, static_cast<unsigned>(message.functionCode), static_cast<unsigned>(message.slaveOrUnitAddress));
		}

		int maxTrans = _pPort->maxSimultaneousTransactions();
		if (_pAsyncThread && countPending() >= maxTrans)
		{
			throw Poco::ProtocolException("Maximum number of pending requests exceeded");
		}

		message.transactionID = _nextTransactionID;
		if (maxTrans > 1)
		{
			++_nextTransactionID;
		}

		if (_pAsyncThread)
		{
			addPending(message);
			_asyncQueue.enqueueNotification(new SendNotificationImpl<M, Port>(message, _pPort));
		}
		else
		{
			_pPort->sendFrame(message);
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
		using namespace std::string_literals;

		if (!_pAsyncThread)
		{
			_logger.debug("Enabling events"s);
			clearPending();
			_pAsyncThread.reset(new Poco::Thread);
			_pAsyncThread->start(*this);
		}
	}

	void disableEvents()
	{
		using namespace std::string_literals;

		if (_pAsyncThread)
		{
			_logger.debug("Disabling events"s);
			_asyncQueue.enqueueNotification(new StopNotification);
			_pAsyncThread->join();
			_pAsyncThread.reset();
			clearPending();
		}
	}

	void run()
	{
		bool stopped = false;
		while (!stopped)
		{
			long dequeueTimeout = countPending() == 0 ? 100 : 0;
			Poco::Notification::Ptr pNf = _asyncQueue.waitDequeueNotification(dequeueTimeout);
			if (pNf)
			{
				if (pNf.cast<StopNotification>())
				{
					stopped = true;
				}
				else
				{
					Poco::AutoPtr<SendNotification> pSendNf = pNf.cast<SendNotification>();
					if (pSendNf)
					{
						try
						{
							pSendNf->run();
						}
						catch (Poco::Exception& exc)
						{
							removePending(pSendNf->message().transactionID);
							RequestFailure requestFailure;
							requestFailure.slaveOrUnitAddress = pSendNf->message().slaveOrUnitAddress;
							requestFailure.functionCode = pSendNf->message().functionCode;
							requestFailure.transactionID = pSendNf->message().transactionID;
							requestFailure.reason = FAILURE_ERROR;
							requestFailure.message = exc.displayText();
							this->requestFailed(this, requestFailure);
						}
					}
				}
			}
			
			if (!stopped && countPending() > 0)
			{
				try
				{
					Poco::Timespan timeout(0, _asyncQueue.empty() ? 250 : 0);
					if (_pPort->poll(timeout))
					{
						try
						{
							processFrame();
						}
						catch (Poco::Exception& exc)
						{
							this->error(this, exc.displayText());
						}
					}
				}
				catch (Poco::Exception& exc)
				{
					// Note: this can only happen if poll() fails for some reason.
					this->error(this, exc.displayText());
				}
				processPendingTimeouts();
			}
		}
	}

	void processFrame()
	{
		using namespace std::string_literals;

		Poco::UInt8 fc = _pPort->receiveFrame();
		if (fc == 0)
		{
			_logger.notice("Invalid or incomplete frame received."s);
			this->badFrameReceived(this);
			return;
		}

		if (_logger.trace())
		{
			_logger.trace("Processing frame: %02x"s, static_cast<unsigned>(fc));
		}

		if ((fc & MODBUS_EXCEPTION_MASK) == MODBUS_EXCEPTION_MASK)
		{
			ModbusExceptionMessage message;
			_pPort->decodeFrame(message);
			if (removePending(message.transactionID))
			{
				this->exceptionReceived(this, message);
			}
		}
		else switch (fc & MODBUS_FUNCTION_CODE_MASK)
		{
		case MODBUS_READ_COILS:
			{
				ReadCoilsResponse response;
				_pPort->decodeFrame(response);
				if (removePending(response.transactionID))
				{
					this->readCoilsResponseReceived(this, response);
				}
			}
			break;

		case MODBUS_READ_DISCRETE_INPUTS:
			{
				ReadDiscreteInputsResponse response;
				_pPort->decodeFrame(response);
				if (removePending(response.transactionID))
				{
					this->readDiscreteInputsResponseReceived(this, response);
				}
			}
			break;

		case MODBUS_READ_HOLDING_REGISTERS:
			{
				ReadHoldingRegistersResponse response;
				_pPort->decodeFrame(response);
				if (removePending(response.transactionID))
				{
					this->readHoldingRegistersResponseReceived(this, response);
				}
			}
			break;

		case MODBUS_READ_INPUT_REGISTERS:
			{
				ReadInputRegistersResponse response;
				_pPort->decodeFrame(response);
				if (removePending(response.transactionID))
				{
					this->readInputRegistersResponseReceived(this, response);
				}
			}
			break;

		case MODBUS_WRITE_SINGLE_COIL:
			{
				WriteSingleCoilResponse	response;
				_pPort->decodeFrame(response);
				if (removePending(response.transactionID))
				{
					this->writeSingleCoilResponseReceived(this, response);
				}
			}
			break;

		case MODBUS_WRITE_SINGLE_REGISTER:
			{
				WriteSingleRegisterResponse	response;
				_pPort->decodeFrame(response);
				if (removePending(response.transactionID))
				{
					this->writeSingleRegisterResponseReceived(this, response);
				}
			}
			break;

		case MODBUS_READ_EXCEPTION_STATUS:
			{
				ReadExceptionStatusResponse	response;
				_pPort->decodeFrame(response);
				if (removePending(response.transactionID))
				{
					this->readExceptionStatusResponseReceived(this, response);
				}
			}
			break;

		case MODBUS_WRITE_MULTIPLE_COILS:
			{
				WriteMultipleCoilsResponse response;
				_pPort->decodeFrame(response);
				if (removePending(response.transactionID))
				{
					this->writeMultipleCoilsResponseReceived(this, response);
				}
			}
			break;

		case MODBUS_WRITE_MULTIPLE_REGISTERS:
			{
				WriteMultipleRegistersResponse response;
				_pPort->decodeFrame(response);
				if (removePending(response.transactionID))
				{
					this->writeMultipleRegistersResponseReceived(this, response);
				}
			}
			break;

		case MODBUS_MASK_WRITE_REGISTER:
			{
				MaskWriteRegisterResponse response;
				_pPort->decodeFrame(response);
				if (removePending(response.transactionID))
				{
					this->maskWriteRegisterResponseReceived(this, response);
				}
			}
			break;

		case MODBUS_READ_WRITE_MULTIPLE_REGISTERS:
			{
				ReadWriteMultipleRegistersResponse response;
				_pPort->decodeFrame(response);
				if (removePending(response.transactionID))
				{
					this->readWriteMultipleRegistersResponseReceived(this, response);
				}
			}
			break;

		case MODBUS_READ_FIFO_QUEUE:
		    {
				ReadFIFOQueueResponse response;
				_pPort->decodeFrame(response);
				if (removePending(response.transactionID))
				{
					this->readFIFOQueueResponseReceived(this, response);
				}
			}
			break;

		default:
			{
				GenericMessage response;
				_pPort->decodeFrame(response);
				if (removePending(response.transactionID))
				{
					this->responseReceived(this, response);
				}
			}
			break;
		}
	}

	void processPendingTimeouts()
	{
		PendingMap timeouts;
		{
			Poco::FastMutex::ScopedLock lock(_pendingMutex);
			for (typename PendingMap::iterator it = _pendingMap.begin(); it != _pendingMap.end();)
			{
				if (it->second.timeSent.isElapsed(_timeout.totalMicroseconds()))
				{
					timeouts[it->first] = it->second;
					typename PendingMap::iterator itDel = it;
					++it;
					_pendingMap.erase(itDel);
				}
				else
				{
					++it;
				}
			}
		}

		for (const auto& p: timeouts)
		{
			this->timeout(this, p.first);

			RequestFailure failure;
			failure.transactionID = p.first;
			failure.functionCode = p.second.functionCode;
			failure.slaveOrUnitAddress = p.second.slaveOrUnitAddress;
			failure.reason = FAILURE_TIMEOUT;
			this->requestFailed(this, failure);
		}
	}

	void abortPending(RequestFailureReason reason, const std::string& message = std::string())
	{
		PendingMap pendingMap;
		{
			Poco::FastMutex::ScopedLock lock(_pendingMutex);
			std::swap(pendingMap, _pendingMap);
		}
		for (const auto& p: pendingMap)
		{
			RequestFailure failure;
			failure.transactionID = p.first;
			failure.functionCode = p.second.functionCode;
			failure.slaveOrUnitAddress = p.second.slaveOrUnitAddress;
			failure.reason = reason;
			failure.message = message;
			this->requestFailed(this, failure);
		}
	}

	void addPending(const ModbusMessage& message)
	{
		Poco::FastMutex::ScopedLock lock(_pendingMutex);
		auto& info = _pendingMap[message.transactionID];
		info.functionCode = message.functionCode;
		info.slaveOrUnitAddress = message.slaveOrUnitAddress;
	}

	bool removePending(Poco::UInt16 transactionID)
	{
		Poco::FastMutex::ScopedLock lock(_pendingMutex);
		return _pendingMap.erase(transactionID) != 0;
	}

	std::size_t countPending() const
	{
		Poco::FastMutex::ScopedLock lock(_pendingMutex);
		return _pendingMap.size();
	}

	void clearPending()
	{
		Poco::FastMutex::ScopedLock lock(_pendingMutex);
		_pendingMap.clear();
	}

	void onConnectionStateChanged(const ConnectionState& state)
	{
		using namespace std::string_literals;

		if (state == CONNECTION_CLOSING || state == CONNECTION_CLOSED)
		{
			abortPending(FAILURE_CLOSED);
		}
		this->connectionStateChanged(this, state);
	}

private:
	mutable Poco::FastMutex _mutex;
	mutable Poco::FastMutex _pendingMutex;
	Poco::SharedPtr<Port> _pPort;
	Poco::Timespan _timeout;
	std::unique_ptr<Poco::Thread> _pAsyncThread;
	Poco::NotificationQueue _asyncQueue;
	Poco::UInt16 _nextTransactionID;
	PendingMap _pendingMap;
	Poco::Logger& _logger;
};


} } // namespace IoT::Modbus


#endif // IoT_Modbus_ModbusMasterImpl_INCLUDED
