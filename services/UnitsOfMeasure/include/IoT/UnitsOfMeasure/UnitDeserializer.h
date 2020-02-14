//
// UnitDeserializer.h
//
// Package: Generated
// Module:  TypeDeserializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeDeserializer_IoT_UnitsOfMeasure_Unit_INCLUDED
#define TypeDeserializer_IoT_UnitsOfMeasure_Unit_INCLUDED


#include "IoT/UnitsOfMeasure/UnitsOfMeasureService.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::UnitsOfMeasure::Unit>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::UnitsOfMeasure::Unit& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::UnitsOfMeasure::Unit& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"code"s,"dim"s,"group"s,"icode"s,"iunit"s,"metric"s,"name"s,"print"s,"property"s,"unit"s,"value"s};
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[0], true, deser, value.code);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[1], true, deser, value.dim);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[2], true, deser, value.group);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[3], true, deser, value.icode);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[4], true, deser, value.iunit);
		TypeDeserializer<bool >::deserialize(REMOTING__NAMES[5], true, deser, value.metric);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[6], true, deser, value.name);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[7], true, deser, value.print);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[8], true, deser, value.property);
		TypeDeserializer<std::string >::deserialize(REMOTING__NAMES[9], true, deser, value.unit);
		TypeDeserializer<double >::deserialize(REMOTING__NAMES[10], true, deser, value.value);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_UnitsOfMeasure_Unit_INCLUDED

