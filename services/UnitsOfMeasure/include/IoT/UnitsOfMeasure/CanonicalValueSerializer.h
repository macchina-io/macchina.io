//
// CanonicalValueSerializer.h
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


#ifndef TypeSerializer_IoT_UnitsOfMeasure_CanonicalValue_INCLUDED
#define TypeSerializer_IoT_UnitsOfMeasure_CanonicalValue_INCLUDED


#include "IoT/UnitsOfMeasure/UnitsOfMeasureService.h"
#include "Poco/RemotingNG/TypeSerializer.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<IoT::UnitsOfMeasure::CanonicalValue>
{
public:
	static void serialize(const std::string& name, const IoT::UnitsOfMeasure::CanonicalValue& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const IoT::UnitsOfMeasure::CanonicalValue& value, Serializer& ser)
	{
		static const std::string REMOTING__NAMES[] = {"code","value",""};
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.code, ser);
		TypeSerializer<double >::serialize(REMOTING__NAMES[1], value.value, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_IoT_UnitsOfMeasure_CanonicalValue_INCLUDED

