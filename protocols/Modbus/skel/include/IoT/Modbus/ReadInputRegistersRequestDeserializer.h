//
// ReadInputRegistersRequestDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeDeserializer_IoT_Modbus_ReadInputRegistersRequest_INCLUDED
#define TypeDeserializer_IoT_Modbus_ReadInputRegistersRequest_INCLUDED


#include "IoT/Modbus/Types.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::Modbus::ReadInputRegistersRequest>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::Modbus::ReadInputRegistersRequest& value)
	{
		using namespace std::string_literals;
		
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::Modbus::ReadInputRegistersRequest& value)
	{
		using namespace std::string_literals;
		
		// IoT::Modbus::ModbusMessage
		{
		static const std::string REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[] = {"transactionID"s,"slaveOrUnitAddress"s,"functionCode"s};
		TypeDeserializer<Poco::UInt16>::deserialize(REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[0], true, deser, value.transactionID);
		TypeDeserializer<Poco::UInt8>::deserialize(REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[1], true, deser, value.slaveOrUnitAddress);
		TypeDeserializer<Poco::UInt8>::deserialize(REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[2], true, deser, value.functionCode);
		}
		
		static const std::string REMOTING__NAMES[] = {"startingAddress"s,"nOfRegisters"s};
		TypeDeserializer<Poco::UInt16>::deserialize(REMOTING__NAMES[0], true, deser, value.startingAddress);
		TypeDeserializer<Poco::UInt16>::deserialize(REMOTING__NAMES[1], true, deser, value.nOfRegisters);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_Modbus_ReadInputRegistersRequest_INCLUDED

