//
// ReadWriteMultipleRegistersRequestDeserializer.h
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


#ifndef TypeDeserializer_IoT_Modbus_ReadWriteMultipleRegistersRequest_INCLUDED
#define TypeDeserializer_IoT_Modbus_ReadWriteMultipleRegistersRequest_INCLUDED


#include "IoT/Modbus/ModbusMaster.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::Modbus::ReadWriteMultipleRegistersRequest>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::Modbus::ReadWriteMultipleRegistersRequest& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::Modbus::ReadWriteMultipleRegistersRequest& value)
	{
		using namespace std::string_literals;
		
		// IoT::Modbus::ModbusMessage
		{
		static const std::string REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[] = {"functionCode"s,"slaveOrUnitAddress"s,"transactionID"s};
		TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[0], true, deser, value.functionCode);
		TypeDeserializer<Poco::UInt8 >::deserialize(REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[1], true, deser, value.slaveOrUnitAddress);
		TypeDeserializer<Poco::UInt16 >::deserialize(REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[2], true, deser, value.transactionID);
		}
		
		static const std::string REMOTING__NAMES[] = {"readCount"s,"readStartingAddress"s,"values"s,"writeStartingAddress"s};
		TypeDeserializer<Poco::UInt16 >::deserialize(REMOTING__NAMES[0], true, deser, value.readCount);
		TypeDeserializer<Poco::UInt16 >::deserialize(REMOTING__NAMES[1], true, deser, value.readStartingAddress);
		TypeDeserializer<std::vector < Poco::UInt16 > >::deserialize(REMOTING__NAMES[2], true, deser, value.values);
		TypeDeserializer<Poco::UInt16 >::deserialize(REMOTING__NAMES[3], true, deser, value.writeStartingAddress);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_Modbus_ReadWriteMultipleRegistersRequest_INCLUDED

