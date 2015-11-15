//
// ModbusException.h
//
// $Id$
//
// Library: IoT/Modbus
// Package: ModbusMaster
// Module:  ModbusException
//
// Definition of the ModbusException class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Modbus_ModbusException_INCLUDED
#define IoT_Modbus_ModbusException_INCLUDED


#include "IoT/Modbus/Modbus.h"
#include "Poco/Exception.h"


namespace IoT {
namespace Modbus {


class IoTModbus_API ModbusException: public Poco::IOException
	/// An exception class for Modbus exceptions.
{
public:
	ModbusException(Poco::UInt8 functionCode, Poco::UInt8 exceptionCode);
		/// Create ModbusException.

	ModbusException(const ModbusException& exc);
		/// Creates a new ModbusException from another one.

	~ModbusException() throw();
		/// Destroy the exception.

	ModbusException& operator = (const ModbusException& exc);
		/// Assignment operator.
		
	const char* name() const throw();
		/// Returns a static string describing the exception.

	const char* className() const throw();
		/// Returns the name of the exception class.

	Poco::Exception* clone() const;
		/// Creates an exact copy of the exception.
		
	void rethrow() const;
		/// (Re)Throws the exception.

	Poco::UInt8 functionCode() const;
		/// Returns the Modbus function code.

	Poco::UInt8 exceptionCode() const;
		/// Returns the Modbus exception code (same as code()).

	static std::string formatFunctionCode(Poco::UInt8 functionCode);
		/// Returns a string representation of the given function code.
		
	static std::string formatExceptionCode(Poco::UInt8 exceptionCode);
		/// Returns a string representation of the given exception code.
	
private:
	ModbusException();
	
	Poco::UInt8 _functionCode;
};


} } // namespace IoT::Modbus


#endif // IoT_Modbus_ModbusException_INCLUDED
