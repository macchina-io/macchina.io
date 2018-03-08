//
// TaggedBinaryReader.h
//
// Library: JS/Bridge
// Package: Bridging
// Module:  TaggedBinaryReader
//
// Definition of the TaggedBinaryReader class.
//
// Copyright (c) 2013-2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_Bridge_TaggedBinaryReader_INCLUDED
#define JS_Bridge_TaggedBinaryReader_INCLUDED


#include "Poco/JS/Bridge/Bridge.h"
#include "Poco/JS/Bridge/Serializer.h"
#include "Poco/JS/Bridge/TaggedBinarySerializer.h"
#include "Poco/RemotingNG/BinaryDeserializer.h"
#include "Poco/RemotingNG/RemotingException.h"
#include <vector>


namespace Poco {
namespace JS {
namespace Bridge {


class JSBridge_API TaggedBinaryReader
	/// This class creates a JavaScript object from a tagged binary stream produced
	/// by TaggedBinarySerializer.
{
public:
	TaggedBinaryReader(v8::Isolate* pIsolate);
		/// Creates the TaggedBinaryReader.
		
	~TaggedBinaryReader();
		/// Destroys the TaggedBinaryReader.
		
	const v8::Global<v8::Object>& read(std::istream& istream);
		/// Reads a JavaScript object from the given stream.

protected:
	template <typename T>
	void read(Poco::RemotingNG::BinaryDeserializer& deserializer)
	{
		std::string name = deserializeName(deserializer);

		T value;
		check(deserializer.deserialize(name, true, value));
		_serializer.serialize(name, value); 
	}
	
	std::string deserializeName(Poco::RemotingNG::BinaryDeserializer& deserializer);
	Poco::UInt8 deserializeTypeTag(Poco::RemotingNG::BinaryDeserializer& deserializer);
	void check(bool result);
	
private:
	Serializer _serializer;
	std::vector<TaggedBinarySerializer::ContainerType> _containerStack;
};


//
// inlines
//


inline std::string TaggedBinaryReader::deserializeName(Poco::RemotingNG::BinaryDeserializer& deserializer)
{
	std::string name;
	if (_containerStack.back() != TaggedBinarySerializer::CONT_SEQUENCE)
	{
		name = deserializer.deserializeToken<std::string>();
	}
	return name;
}


inline Poco::UInt8 TaggedBinaryReader::deserializeTypeTag(Poco::RemotingNG::BinaryDeserializer& deserializer)
{
	return deserializer.deserializeToken<Poco::UInt8>();
}


inline void TaggedBinaryReader::check(bool result)
{
	if (!result) throw Poco::RemotingNG::DeserializerException("Expected item not found");
}


} } } // namespace Poco::JS::Bridge


#endif // JS_Bridge_TaggedBinaryReader_INCLUDED
