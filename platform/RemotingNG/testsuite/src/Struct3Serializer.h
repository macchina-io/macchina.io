//
// Struct3Serializer.h
//
// Package: Generated
// Module:  TypeSerializer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//


#ifndef TypeSerializer_Struct3_INCLUDED
#define TypeSerializer_Struct3_INCLUDED


#include "Poco/RemotingNG/TypeSerializer.h"
#include "Struct2Deserializer.h"
#include "Struct2Serializer.h"
#include "Tester.h"


namespace Poco {
namespace RemotingNG {


template <>
class TypeSerializer<Struct3>
{
public:
	static void serialize(const std::string& name, const Struct3& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMESPACE);
		static const std::string REMOTING__NAMESPACE("http://www.appinf.com/types");
		remoting__staticInitEnd(REMOTING__NAMESPACE);
		ser.registerNamespace(REMOTING__NAMESPACE);
		ser.serializeStructBegin(name);
		ser.pushProperty(SerializerBase::PROP_NAMESPACE, REMOTING__NAMESPACE);
		serializeImpl(value, ser);
		ser.popProperty(SerializerBase::PROP_NAMESPACE);
		ser.serializeStructEnd(name);
	}

	static void serializeImpl(const Struct3& value, Serializer& ser)
	{
		remoting__staticInitBegin(REMOTING__NAMES);
		static const std::string REMOTING__NAMES[] = {"aCharVector","aComplexVector","aList","aMultiSet","aNullable","aSet",""};
		remoting__staticInitEnd(REMOTING__NAMES);
		TypeSerializer<std::vector < char > >::serialize(REMOTING__NAMES[0], value.aCharVector, ser);
		TypeSerializer<std::vector < Struct2 > >::serialize(REMOTING__NAMES[1], value.aComplexVector, ser);
		TypeSerializer<std::list < Struct2 > >::serialize(REMOTING__NAMES[2], value.aList, ser);
		TypeSerializer<std::multiset < int > >::serialize(REMOTING__NAMES[3], value.aMultiSet, ser);
		TypeSerializer<Poco::Nullable < std::string > >::serialize(REMOTING__NAMES[4], value.aNullable, ser);
		TypeSerializer<std::set < int > >::serialize(REMOTING__NAMES[5], value.aSet, ser);
	}

};


} // namespace RemotingNG
} // namespace Poco


#endif // TypeSerializer_Struct3_INCLUDED

