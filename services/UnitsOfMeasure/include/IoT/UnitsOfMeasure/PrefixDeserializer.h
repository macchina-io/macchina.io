//
// PrefixDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2018-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeDeserializer_IoT_UnitsOfMeasure_Prefix_INCLUDED
#define TypeDeserializer_IoT_UnitsOfMeasure_Prefix_INCLUDED


#include "IoT/UnitsOfMeasure/UnitsOfMeasureService.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::UnitsOfMeasure::Prefix>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::UnitsOfMeasure::Prefix& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::UnitsOfMeasure::Prefix& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"code"s,"icode"s,"name"s,"print"s,"value"s};
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES[0], true, deser, value.code);
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES[1], true, deser, value.icode);
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES[2], true, deser, value.name);
		TypeDeserializer<std::string>::deserialize(REMOTING__NAMES[3], true, deser, value.print);
		TypeDeserializer<double>::deserialize(REMOTING__NAMES[4], true, deser, value.value);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_UnitsOfMeasure_Prefix_INCLUDED

