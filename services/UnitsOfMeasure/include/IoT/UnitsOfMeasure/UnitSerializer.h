//
// UnitSerializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2018-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
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
		
		static const std::string REMOTING__NAMES[] = {"code"s,"icode"s,"name"s,"print"s,"property"s,"group"s,"dim"s,"metric"s,"unit"s,"iunit"s,"value"s,""s};
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[0], value.code, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[1], value.icode, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[2], value.name, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[3], value.print, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[4], value.property, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[5], value.group, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[6], value.dim, ser);
		TypeSerializer<bool>::serialize(REMOTING__NAMES[7], value.metric, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[8], value.unit, ser);
		TypeSerializer<std::string>::serialize(REMOTING__NAMES[9], value.iunit, ser);
		TypeSerializer<double>::serialize(REMOTING__NAMES[10], value.value, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_UnitsOfMeasure_Unit_INCLUDED

