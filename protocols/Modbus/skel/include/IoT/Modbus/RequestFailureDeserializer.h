//
// RequestFailureDeserializer.h
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


#ifndef TypeDeserializer_IoT_Modbus_RequestFailure_INCLUDED
#define TypeDeserializer_IoT_Modbus_RequestFailure_INCLUDED


#include "IoT/Modbus/Types.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::Modbus::RequestFailure>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::Modbus::RequestFailure& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::Modbus::RequestFailure& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"slaveOrUnitAddress"s,"functionCode"s,"transactionID"s,"reason"s,"message"s};
		bool ret = false;
		TypeDeserializer<Poco::UInt8>::deserialize(REMOTING__NAMES[0], true, deser, value.slaveOrUnitAddress);
		TypeDeserializer<Poco::UInt8>::deserialize(REMOTING__NAMES[1], true, deser, value.functionCode);
		TypeDeserializer<Poco::UInt16>::deserialize(REMOTING__NAMES[2], true, deser, value.transactionID);
		int genreason;
		ret = TypeDeserializer<int>::deserialize(REMOTING__NAMES[3], true, deser, genreason);
		if (ret) value.reason = static_cast<IoT::Modbus::RequestFailureReason>(genreason);
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES[4], true, deser, value.message);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_Modbus_RequestFailure_INCLUDED

