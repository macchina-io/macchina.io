//
// Class1Serializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#ifndef TypeSerializer_Class1_INCLUDED
#define TypeSerializer_Class1_INCLUDED


#include "Poco/RemotingNG/TypeSerializer.h"
#include "Tester.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<Class1>
{
public:
	static void serialize(const std::string& name, const Class1& value, Serializer& ser)
	{
		ser.serializeStructBegin(name);
		serializeImpl(value, ser);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const Class1& value, Serializer& ser)
	{
		static const std::string REMOTING__NAMES[] = {"aString","anEnum","anInt",""};
		TypeSerializer<std::string >::serialize(REMOTING__NAMES[0], value.getAString(), ser);
		TypeSerializer<int >::serialize(REMOTING__NAMES[1], value.getAnEnum(), ser);
		TypeSerializer<int >::serialize(REMOTING__NAMES[2], value.getAnInt(), ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_Class1_INCLUDED

