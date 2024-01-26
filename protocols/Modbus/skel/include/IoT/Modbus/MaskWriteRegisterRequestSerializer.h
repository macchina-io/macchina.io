//
// MaskWriteRegisterRequestSerializer.h
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


#ifndef TypeSerializer_IoT_Modbus_MaskWriteRegisterRequest_INCLUDED
#define TypeSerializer_IoT_Modbus_MaskWriteRegisterRequest_INCLUDED


#include "IoT/Modbus/Types.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::Modbus::MaskWriteRegisterRequest>
{
public:
	static void serialize(const std::string& name, const IoT::Modbus::MaskWriteRegisterRequest& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::Modbus::MaskWriteRegisterRequest& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		// IoT::Modbus::ModbusMessage
		{
		static const std::string REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[] = {"functionCode"s,"slaveOrUnitAddress"s,"transactionID"s,""s};
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[0], value.functionCode, ser);
		TypeSerializer<Poco::UInt8 >::serialize(REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[1], value.slaveOrUnitAddress, ser);
		TypeSerializer<Poco::UInt16 >::serialize(REMOTING__NAMES__IOT__MODBUS__MODBUSMESSAGE[2], value.transactionID, ser);
		}
		
		static const std::string REMOTING__NAMES[] = {"andMask"s,"orMask"s,"referenceAddress"s,""s};
		TypeSerializer<Poco::UInt16 >::serialize(REMOTING__NAMES[0], value.andMask, ser);
		TypeSerializer<Poco::UInt16 >::serialize(REMOTING__NAMES[1], value.orMask, ser);
		TypeSerializer<Poco::UInt16 >::serialize(REMOTING__NAMES[2], value.referenceAddress, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_Modbus_MaskWriteRegisterRequest_INCLUDED

