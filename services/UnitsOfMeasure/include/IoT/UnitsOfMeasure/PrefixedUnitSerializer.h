//
// PrefixedUnitSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2018-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeSerializer_IoT_UnitsOfMeasure_PrefixedUnit_INCLUDED
#define TypeSerializer_IoT_UnitsOfMeasure_PrefixedUnit_INCLUDED


#include "IoT/UnitsOfMeasure/PrefixDeserializer.h"
#include "IoT/UnitsOfMeasure/PrefixSerializer.h"
#include "IoT/UnitsOfMeasure/UnitDeserializer.h"
#include "IoT/UnitsOfMeasure/UnitSerializer.h"
#include "IoT/UnitsOfMeasure/UnitsOfMeasureService.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::UnitsOfMeasure::PrefixedUnit>
{
public:
	static void serialize(const std::string& name, const IoT::UnitsOfMeasure::PrefixedUnit& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::UnitsOfMeasure::PrefixedUnit& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"prefix"s,"unit"s,""s};
		TypeSerializer<Poco::SharedPtr < IoT::UnitsOfMeasure::Prefix > >::serialize(REMOTING__NAMES[0], value.prefix, ser);
		TypeSerializer<Poco::SharedPtr < IoT::UnitsOfMeasure::Unit > >::serialize(REMOTING__NAMES[1], value.unit, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_UnitsOfMeasure_PrefixedUnit_INCLUDED

