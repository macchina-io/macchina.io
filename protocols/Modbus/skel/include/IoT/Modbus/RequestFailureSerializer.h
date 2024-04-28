//
// RequestFailureSerializer.h
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


#ifndef TypeSerializer_IoT_Modbus_RequestFailure_INCLUDED
#define TypeSerializer_IoT_Modbus_RequestFailure_INCLUDED


#include "IoT/Modbus/Types.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::Modbus::RequestFailure>
{
public:
	static void serialize(const std::string& name, const IoT::Modbus::RequestFailure& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::Modbus::RequestFailure& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"slaveOrUnitAddress"s,"functionCode"s,"transactionID"s,"reason"s,"message"s,""s};
		TypeSerializer<Poco::UInt8>::serialize(REMOTING__NAMES[0], value.slaveOrUnitAddress, ser);
		TypeSerializer<Poco::UInt8>::serialize(REMOTING__NAMES[1], value.functionCode, ser);
		TypeSerializer<Poco::UInt16>::serialize(REMOTING__NAMES[2], value.transactionID, ser);
		TypeSerializer<int>::serialize(REMOTING__NAMES[3], static_cast<int>(value.reason), ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[4], value.message, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_Modbus_RequestFailure_INCLUDED

