//
// ModbusDeviceConnection.h
//
// Library: IoT/Modbus/Device
// Package: Device
// Module:  ModbusDeviceConnection
//
// Definition of the ModbusDeviceConnection class template.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Modbus_Device_ModbusDeviceConnection_INCLUDED
#define IoT_Modbus_Device_ModbusDeviceConnection_INCLUDED


#include "IoT/Modbus/Device/ModbusDevice.h"
#include "IoT/Modbus/Device/ModbusDeviceHandler.h"
#include "IoT/Modbus/ModbusException.h"
#include "Poco/Timestamp.h"
#include "Poco/Timespan.h"
#include "Poco/SharedPtr.h"
#include "Poco/Runnable.h"
#include "Poco/Logger.h"
#include <atomic>


namespace IoT {
namespace Modbus {
namespace Device {


template <class Request, class Response, class Port>
class MessageProcessor
{
public:
	typedef void (ModbusDeviceHandler::*HandlerFunc)(const Request& request, Response& response);

	static void processMessage(Port& port, ModbusDeviceHandler& deviceHandler, HandlerFunc handlerFunc)
	{
		Request request;
		port.decodeFrame(request);
		Response response;
		response.transactionID = request.transactionID;
		response.slaveOrUnitAddress = request.slaveOrUnitAddress;
		response.functionCode = request.functionCode;
		try
		{
			(deviceHandler.*handlerFunc)(request, response);
		}
		catch (ModbusException& exc)
		{
			ModbusExceptionMessage excResponse;
			excResponse.transactionID = request.transactionID;
			excResponse.slaveOrUnitAddress = request.slaveOrUnitAddress;
			excResponse.functionCode = request.functionCode | MODBUS_EXCEPTION_MASK;
			excResponse.exceptionCode = exc.exceptionCode();
			port.sendFrame(excResponse);
			return;
		}
		catch (std::exception& exc)
		{
			ModbusExceptionMessage excResponse;
			excResponse.transactionID = request.transactionID;
			excResponse.slaveOrUnitAddress = request.slaveOrUnitAddress;
			excResponse.functionCode = request.functionCode | MODBUS_EXCEPTION_MASK;
			excResponse.exceptionCode = MODBUS_EXC_SERVER_DEVICE_FAILURE;
			port.sendFrame(excResponse);
			throw;
		}
		port.sendFrame(response);
	}
};


template <class Port>
class ModbusDeviceConnection: public Poco::Runnable
	/// This is a basic implementation of a Modbus device server that
	/// reads incoming messages and dispatches them to a
	/// ModbusDeviceHandler instance, then sends back the response.
{
public:
	ModbusDeviceConnection(Poco::SharedPtr<Port> pPort, ModbusDeviceHandler& deviceHandler, Poco::UInt8 slaveOrUnitAddress = 0):
		/// Creates a ModbusDeviceConnection using the given ModbusDevice.
		_pPort(pPort),
		_deviceHandler(deviceHandler),
		_slaveOrUnitAddress(slaveOrUnitAddress),
		_logger(Poco::Logger::get("IoT.ModbusDeviceConnection"))
	{
	}

	virtual ~ModbusDeviceConnection()
	{
	}

	void stop()
	{
		_stopped = true;
	}

	// Runnable
	void run()
	{
		using namespace std::string_literals;
	
		Poco::Timestamp lastFrame;
		const Poco::Timespan pollTimeout(250*Poco::Timespan::MILLISECONDS);
		while (!stopped() && _pPort->isConnected())
		{
			if (_pPort->poll(pollTimeout))
			{
				try
				{
					lastFrame.update();
					processFrame();
				}
				catch (Poco::Exception& exc)
				{
					_logger.error("Error processing frame: %s"s, exc.displayText());
				}
				catch (std::exception& exc)
				{
					_logger.error("Error processing frame: %s"s, std::string(exc.what()));
				}	
			}
			else
			{
				Poco::Timespan idleTime(lastFrame.elapsed());
				if (!_deviceHandler.idle(idleTime)) 
				{
					_logger.notice("Disconnecting client %s due to inactivity."s, _pPort->address());
					break;
				}
			}
		}
		_logger.information("Modbus connection closed."s);
	}

protected:
	void processFrame()
	{
		using namespace std::string_literals;

		Poco::UInt8 fc = _pPort->receiveFrame();
		if (fc == 0) return;

		if (_slaveOrUnitAddress != 0 && _pPort->frameSlaveOrUnitAddress() != _slaveOrUnitAddress)
		{
			if (_logger.trace())
			{
				_logger.trace("Ignoring frame for other slave/unit address %02x."s, static_cast<unsigned>(_pPort->frameSlaveOrUnitAddress()));
			}
			return;
		}

		if (_logger.trace())
		{
			_logger.trace("Processing frame: %02x", static_cast<unsigned>(fc));
		}

		if ((fc & MODBUS_EXCEPTION_MASK) == MODBUS_EXCEPTION_MASK)
		{
			_logger.warning("Received and ignored message with exception bit set."s);
		}
		else switch (fc & MODBUS_FUNCTION_CODE_MASK)
		{
		case MODBUS_READ_COILS:
			MessageProcessor<ReadCoilsRequest, ReadCoilsResponse, Port>::processMessage(*_pPort, _deviceHandler, &ModbusDeviceHandler::readCoils);
			break;

		case MODBUS_READ_DISCRETE_INPUTS:
			MessageProcessor<ReadDiscreteInputsRequest, ReadDiscreteInputsResponse, Port>::processMessage(*_pPort, _deviceHandler, &ModbusDeviceHandler::readDiscreteInputs);
			break;

		case MODBUS_READ_HOLDING_REGISTERS:
			MessageProcessor<ReadHoldingRegistersRequest, ReadHoldingRegistersResponse, Port>::processMessage(*_pPort, _deviceHandler, &ModbusDeviceHandler::readHoldingRegisters);
			break;

		case MODBUS_READ_INPUT_REGISTERS:
			MessageProcessor<ReadInputRegistersRequest, ReadInputRegistersResponse, Port>::processMessage(*_pPort, _deviceHandler, &ModbusDeviceHandler::readInputRegisters);
			break;

		case MODBUS_WRITE_SINGLE_COIL:
			MessageProcessor<WriteSingleCoilRequest, WriteSingleCoilResponse, Port>::processMessage(*_pPort, _deviceHandler, &ModbusDeviceHandler::writeSingleCoil);
			break;

		case MODBUS_WRITE_SINGLE_REGISTER:
			MessageProcessor<WriteSingleRegisterRequest, WriteSingleRegisterResponse, Port>::processMessage(*_pPort, _deviceHandler, &ModbusDeviceHandler::writeSingleRegister);
			break;

		case MODBUS_READ_EXCEPTION_STATUS:
			MessageProcessor<ReadExceptionStatusRequest, ReadExceptionStatusResponse, Port>::processMessage(*_pPort, _deviceHandler, &ModbusDeviceHandler::readExceptionStatus);
			break;

		case MODBUS_WRITE_MULTIPLE_COILS:
			MessageProcessor<WriteMultipleCoilsRequest, WriteMultipleCoilsResponse, Port>::processMessage(*_pPort, _deviceHandler, &ModbusDeviceHandler::writeMultipleCoils);
			break;

		case MODBUS_WRITE_MULTIPLE_REGISTERS:
			MessageProcessor<WriteMultipleRegistersRequest, WriteMultipleRegistersResponse, Port>::processMessage(*_pPort, _deviceHandler, &ModbusDeviceHandler::writeMultipleRegisters);
			break;

		case MODBUS_MASK_WRITE_REGISTER:
			MessageProcessor<MaskWriteRegisterRequest, MaskWriteRegisterResponse, Port>::processMessage(*_pPort, _deviceHandler, &ModbusDeviceHandler::maskWriteRegister);
			break;

		case MODBUS_READ_WRITE_MULTIPLE_REGISTERS:
			MessageProcessor<ReadWriteMultipleRegistersRequest, ReadWriteMultipleRegistersResponse, Port>::processMessage(*_pPort, _deviceHandler, &ModbusDeviceHandler::readWriteMultipleRegisters);
			break;

		case MODBUS_READ_FIFO_QUEUE:
			MessageProcessor<ReadFIFOQueueRequest, ReadFIFOQueueResponse, Port>::processMessage(*_pPort, _deviceHandler, &ModbusDeviceHandler::readFIFOQueue);
			break;

		default:
			MessageProcessor<GenericMessage, GenericMessage, Port>::processMessage(*_pPort, _deviceHandler, &ModbusDeviceHandler::otherFunction);
			break;
		}
	}

	bool stopped() const
	{
		return _stopped;
	}

private:
	Poco::SharedPtr<Port> _pPort;
	ModbusDeviceHandler& _deviceHandler;
	Poco::UInt8 _slaveOrUnitAddress;
	std::atomic<bool> _stopped{false};
	Poco::Logger& _logger;

	ModbusDeviceConnection(const ModbusDeviceConnection&) = delete;
	ModbusDeviceConnection& operator = (const ModbusDeviceConnection&) = delete;
};


} } } // namespace IoT::Modbus::Device


#endif // IoT_Modbus_Device_ModbusDeviceConnection_INCLUDED
