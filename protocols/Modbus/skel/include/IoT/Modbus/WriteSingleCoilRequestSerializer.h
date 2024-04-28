//
// WriteSingleCoilRequestSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_Modbus_WriteSingleCoilRequest_INCLUDED
#define TypeSerializer_IoT_Modbus_WriteSingleCoilRequest_INCLUDED


#include "IoT/Modbus/Types.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::Modbus::WriteSingleCoilRequest>
{
public:
	static void serialize(const std::string& name, const IoT::Modbus::WriteSingleCoilRequest& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::Modbus::WriteSingleCoilRequest& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		// IoT::Modbus::ModbusMessage
		{
		static const std::string REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[] = {"transactionID"s,"slaveOrUnitAddress"s,"functionCode"s,""s};
		TypeSerializer<Poco::UInt16>::serialize(REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[0], value.transactionID, ser);
		TypeSerializer<Poco::UInt8>::serialize(REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[1], value.slaveOrUnitAddress, ser);
		TypeSerializer<Poco::UInt8>::serialize(REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[2], value.functionCode, ser);
		}
		
		static const std::string REMOTING__NAMES[] = {"outputAddress"s,"value"s,""s};
		TypeSerializer<Poco::UInt16>::serialize(REMOTING__NAMES[0], value.outputAddress, ser);
		TypeSerializer<bool>::serialize(REMOTING__NAMES[1], value.value, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_Modbus_WriteSingleCoilRequest_INCLUDED

