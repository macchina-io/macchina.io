//
// Struct2Serializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#ifndef TypeSerializer_Struct2_INCLUDED
#define TypeSerializer_Struct2_INCLUDED


#include "Poco/RemotingNG/TypeSerializer.h"
#include "Struct1Deserializer.h"
#include "Struct1Serializer.h"
#include "Tester.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<Struct2>
{
public:
	static void serialize(const std::string& name, const Struct2& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const Struct2& value, Serializer& ser)
	{
		using namespace std::string_literals;
		
		static const std::string REMOTING__NAMES[] = {"aDateTime"s,"aLocalDateTime"s,"aTimestamp"s,"aVector"s,"anURI"s,"anUUID"s,"anotherVector"s,""s};
		TypeSerializer<Poco::DateTime >::serialize(REMOTING__NAMES[0], value.aDateTime, ser);
		TypeSerializer<Poco::LocalDateTime >::serialize(REMOTING__NAMES[1], value.aLocalDateTime, ser);
		TypeSerializer<Poco::Timestamp >::serialize(REMOTING__NAMES[2], value.aTimestamp, ser);
		TypeSerializer<std::vector < Struct1 > >::serialize(REMOTING__NAMES[3], value.aVector, ser);
		TypeSerializer<Poco::URI >::serialize(REMOTING__NAMES[4], value.anURI, ser);
		TypeSerializer<Poco::UUID >::serialize(REMOTING__NAMES[5], value.anUUID, ser);
		TypeSerializer<std::vector < Poco::SharedPtr < Struct1 > > >::serialize(REMOTING__NAMES[6], value.anotherVector, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_Struct2_INCLUDED

