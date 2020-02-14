//
// UnitSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef TypeSerializer_IoT_UnitsOfMeasure_Unit_INCLUDED
#define TypeSerializer_IoT_UnitsOfMeasure_Unit_INCLUDED


#include "IoT/UnitsOfMeasure/UnitsOfMeasureService.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::UnitsOfMeasure::Unit>
{
public:
	static void serialize(const std::string& name, const IoT::UnitsOfMeasure::Unit& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::UnitsOfMeasure::Unit& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"code"s,"dim"s,"group"s,"icode"s,"iunit"s,"metric"s,"name"s,"print"s,"property"s,"unit"s,"value"s,""s};
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.code, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[1], value.dim, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[2], value.group, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[3], value.icode, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[4], value.iunit, ser);
		TypeSerializer<bool >::serialize(REMOTING__NAMES[5], value.metric, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[6], value.name, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[7], value.print, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[8], value.property, ser);
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[9], value.unit, ser);
		TypeSerializer<double >::serialize(REMOTING__NAMES[10], value.value, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_UnitsOfMeasure_Unit_INCLUDED

