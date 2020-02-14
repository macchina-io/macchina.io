//
// PrefixedUnitDeserializer.h
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


#ifndef TypeDeserializer_IoT_UnitsOfMeasure_PrefixedUnit_INCLUDED
#define TypeDeserializer_IoT_UnitsOfMeasure_PrefixedUnit_INCLUDED


#include "IoT/UnitsOfMeasure/PrefixDeserializer.h"
#include "IoT/UnitsOfMeasure/PrefixSerializer.h"
#include "IoT/UnitsOfMeasure/UnitDeserializer.h"
#include "IoT/UnitsOfMeasure/UnitSerializer.h"
#include "IoT/UnitsOfMeasure/UnitsOfMeasureService.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::UnitsOfMeasure::PrefixedUnit>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::UnitsOfMeasure::PrefixedUnit& value)
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

	static void deserializeImpl(Deserializer& deser, IoT::UnitsOfMeasure::PrefixedUnit& value)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"prefix"s,"unit"s};
		TypeDeserializer<Poco::SharedPtr < IoT::UnitsOfMeasure::Prefix > >::deserialize(REMOTING__NAMES[0], true, deser, value.prefix);
		TypeDeserializer<Poco::SharedPtr < IoT::UnitsOfMeasure::Unit > >::deserialize(REMOTING__NAMES[1], true, deser, value.unit);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_UnitsOfMeasure_PrefixedUnit_INCLUDED

