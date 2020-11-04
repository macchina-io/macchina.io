//
// PrefixUnitDeserializer.h
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
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef TypeDeserializer_IoT_UnitsOfMeasure_PrefixUnit_INCLUDED
#define TypeDeserializer_IoT_UnitsOfMeasure_PrefixUnit_INCLUDED


#include "IoT/UnitsOfMeasure/PrefixDeserializer.h"
#include "IoT/UnitsOfMeasure/PrefixSerializer.h"
#include "IoT/UnitsOfMeasure/UnitDeserializer.h"
#include "IoT/UnitsOfMeasure/UnitSerializer.h"
#include "IoT/UnitsOfMeasure/UnitsOfMeasureService.h"
#include "Poco/RemotingNG/TypeDeserializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeDeserializer<IoT::UnitsOfMeasure::PrefixUnit>
{
public:
	static bool deserialize(const std::string& name, bool isMandatory, Deserializer& deser, IoT::UnitsOfMeasure::PrefixUnit& value)
	{
		bool ret = deser.deserializeStructBegin(name, isMandatory);
		if (ret)
		{
			deserializeImpl(deser, value);
			deser.deserializeStructEnd(name);
		}
		return ret;
	}

	static void deserializeImpl(Deserializer& deser, IoT::UnitsOfMeasure::PrefixUnit& value)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"prefix","unit"};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeDeserializer<Poco::Optional < IoT::UnitsOfMeasure::Prefix > >::deserialize(REMOTING__NAMES[0], true, deser, value.prefix);
		TypeDeserializer<IoT::UnitsOfMeasure::Unit >::deserialize(REMOTING__NAMES[1], true, deser, value.unit);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeDeserializer_IoT_UnitsOfMeasure_PrefixUnit_INCLUDED

