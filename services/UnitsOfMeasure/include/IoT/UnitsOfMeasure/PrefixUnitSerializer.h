//
// PrefixUnitSerializer.h
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
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeSerializer_IoT_UnitsOfMeasure_PrefixUnit_INCLUDED
#define TypeSerializer_IoT_UnitsOfMeasure_PrefixUnit_INCLUDED


#include "IoT/UnitsOfMeasure/PrefixDeserializer.h"
#include "IoT/UnitsOfMeasure/PrefixSerializer.h"
#include "IoT/UnitsOfMeasure/UnitDeserializer.h"
#include "IoT/UnitsOfMeasure/UnitSerializer.h"
#include "IoT/UnitsOfMeasure/UnitsOfMeasureService.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::UnitsOfMeasure::PrefixUnit>
{
public:
	static void serialize(const std::string& name, const IoT::UnitsOfMeasure::PrefixUnit& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::UnitsOfMeasure::PrefixUnit& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"prefix","unit",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<Poco::Optional < IoT::UnitsOfMeasure::Prefix > >::serialize(REMOTING__NAMES[0], value.prefix, ser);
		TypeSerializer<IoT::UnitsOfMeasure::Unit >::serialize(REMOTING__NAMES[1], value.unit, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_UnitsOfMeasure_PrefixUnit_INCLUDED

