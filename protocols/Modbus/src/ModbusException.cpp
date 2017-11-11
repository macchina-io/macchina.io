//
// ModbusException.cpp
//
// Library: IoT/Modbus
// Package: ModbusMaster
// Module:  ModbusException
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Modbus/ModbusException.h"
#include "IoT/Modbus/ModbusMaster.h"
#include "Poco/Format.h"
#include <typeinfo>


namespace IoT {
namespace Modbus {


ModbusException::ModbusException(Poco::UInt8 functionCode, Poco::UInt8 exceptionCode):
	Poco::IOException(formatFunctionCode(functionCode), formatExceptionCode(exceptionCode), exceptionCode),
	_functionCode(functionCode)
{
}


ModbusException::ModbusException(const ModbusException& exc):
	Poco::IOException(exc),
	_functionCode(exc._functionCode)
{
}


ModbusException::~ModbusException() throw()
{
}


ModbusException& ModbusException::operator = (const ModbusException& exc)
{
	if (&exc != this)
	{
		Poco::IOException::operator = (exc);
		_functionCode = exc._functionCode;
	}
	return *this;
}

	
const char* ModbusException::name() const throw()
{
	return "ModbusException";
}


const char* ModbusException::className() const throw()
{
	return typeid(*this).name();
}


Poco::Exception* ModbusException::clone() const
{
	return new ModbusException(*this);
}

	
void ModbusException::rethrow() const
{
	throw *this;
}


Poco::UInt8 ModbusException::functionCode() const
{
	return _functionCode;
}


Poco::UInt8 ModbusException::exceptionCode() const
{
	return static_cast<Poco::UInt8>(code());
}


std::string ModbusException::formatFunctionCode(Poco::UInt8 functionCode)
{
	switch (functionCode)
	{
	case MODBUS_READ_COILS:
		return "Read Coils";
	case MODBUS_READ_DISCRETE_INPUTS:
		return "Read Discrete Inputs";
	case MODBUS_READ_HOLDING_REGISTERS:
		return "Read Holding Registers";
	case MODBUS_READ_INPUT_REGISTERS:
		return "Read Input Registers";
	case MODBUS_WRITE_SINGLE_COIL:
		return "Write Single Coil";
	case MODBUS_WRITE_SINGLE_REGISTER:
		return "Write Single Register";
	case MODBUS_READ_EXCEPTION_STATUS:
		return "Read Exception Status";
	case MODBUS_DIAGNOSTICS:
		return "Diagnostics";
	case MODBUS_GET_COMM_EVENT_COUNTER:
		return "Get Comm Event Counter";
	case MODBUS_GET_COMM_EVENT_LOG:
		return "Get Comm Event Log";
	case MODBUS_WRITE_MULTIPLE_COILS:
		return "Write Multiple Coils";
	case MODBUS_WRITE_MULTIPLE_REGISTERS:
		return "Write Multiple Registers";
	case MODBUS_REPORT_SERVER_ID:
		return "Report Server ID";
	case MODBUS_READ_FILE_RECORD:
		return "Read File Record";
	case MODBUS_WRITE_FILE_RECORD:
		return "Write File Record";
	case MODBUS_MASK_WRITE_REGISTER:
		return "Mask Write Register";
	case MODBUS_READ_WRITE_MULTIPLE_REGISTERS:
		return "Read Write Multiple Registers";
	case MODBUS_READ_FIFO_QUEUE:
		return "Read FIFO Queue";
	case MODBUS_ENCAPSULATED_INTERFACE_TRANSPORT:
		return "Encapsulated Interface Transport";
	default:
		return Poco::format("Function Code %02X", static_cast<unsigned>(functionCode));
	}
}

	
std::string ModbusException::formatExceptionCode(Poco::UInt8 exceptionCode)
{
	switch (exceptionCode)
	{
	case MODBUS_EXC_ILLEGAL_FUNCTION:
		return "illegal function";
	case MODBUS_EXC_ILLEGAL_DATA_ADDRESS:
		return "illegal data address";
	case MODBUS_EXC_ILLEGAL_DATA_VALUE:
		return "illegal data value";
	case MODBUS_EXC_SERVER_DEVICE_FAILURE:
		return "server device failure";
	case MODBUS_EXC_ACKNOWLEDGE:
		return "acknowledge";
	case MODBUS_EXC_SERVER_DEVICE_BUSY:
		return "server device busy";
	case MODBUS_EXC_MEMORY_PARITY_ERROR:
		return "memory parity error";
	case MODBUS_EXC_GATEWAY_PATH_UNAVAILABLE:
		return "gateway path unavailable";
	case MODBUS_EXC_GATEWAY_TARGET_DEVICE_FAILED_TO_RESPOND:
		return "gateway target device failed to response";
	default:
		return Poco::format("Exception Code %02X", static_cast<unsigned>(exceptionCode));
	}
}


} } // namespace IoT::Modbus
