//
// TaggedBinarySerializer.h
//
// Library: JS/Bridge
// Package: Bridging
// Module:  TaggedBinarySerializer
//
// Definition of the TaggedBinarySerializer class.
//
// Copyright (c) 2013-2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_Bridge_TaggedBinarySerializer_INCLUDED
#define JS_Bridge_TaggedBinarySerializer_INCLUDED


#include "Poco/JS/Bridge/Bridge.h"
#include "Poco/RemotingNG/BinarySerializer.h"


namespace Poco {
namespace JS {
namespace Bridge {


class JSBridge_API TaggedBinarySerializer: public Poco::RemotingNG::Serializer
	/// An variation of the BinarySerializer that adds type tags and names to the stream.
{
public:
	enum TypeTag
	{
		TYPE_TAG_MESSAGE_BEGIN  = 0x10,
		TYPE_TAG_MESSAGE_END    = 0x18,
		TYPE_TAG_STRUCT_BEGIN   = 0x20,
		TYPE_TAG_STRUCT_END     = 0x28,
		TYPE_TAG_SEQUENCE_BEGIN = 0x21,
		TYPE_TAG_SEQUENCE_END   = 0x29,
		TYPE_TAG_NULLABLE_BEGIN = 0x22,
		TYPE_TAG_NULLABLE_END   = 0x2A,
		TYPE_TAG_OPTIONAL_BEGIN = 0x23,
		TYPE_TAG_OPTIONAL_END   = 0x2B,
		TYPE_TAG_INT8           = 0x30,
		TYPE_TAG_UINT8          = 0x31,
		TYPE_TAG_INT16          = 0x32,
		TYPE_TAG_UINT16         = 0x33,
		TYPE_TAG_INT32          = 0x34,
		TYPE_TAG_UINT32         = 0x35,
		TYPE_TAG_LONG           = 0x36,
		TYPE_TAG_ULONG          = 0x37,
		TYPE_TAG_INT64          = 0x38,
		TYPE_TAG_UINT64         = 0x39,
		TYPE_TAG_FLOAT          = 0x40,
		TYPE_TAG_DOUBLE         = 0x41,
		TYPE_TAG_BOOL           = 0x50,
		TYPE_TAG_CHAR           = 0x60,
		TYPE_TAG_STRING         = 0x70,
		TYPE_TAG_BUFFER         = 0x71
	};

	enum ContainerType
	{
		CONT_MESSAGE,
		CONT_STRUCT,
		CONT_SEQUENCE
	};

	TaggedBinarySerializer();
		/// Creates the TaggedBinarySerializer.

	~TaggedBinarySerializer();
		/// Destroys the TaggedBinarySerializer.

	// Poco::RemotingNG::Serializer
	void resetImpl();
	void setupImpl(std::ostream& ostr);
	void serializeMessageBegin(const std::string& name, Poco::RemotingNG::SerializerBase::MessageType type);
	void serializeMessageEnd(const std::string& name, Poco::RemotingNG::SerializerBase::MessageType type);
	void serializeFaultMessage(const std::string& name, Poco::Exception& exc);
	void serializeStructBegin(const std::string& name);
	void serializeStructEnd(const std::string& name);
	void serializeSequenceBegin(const std::string& name, Poco::UInt32 numElems);
	void serializeSequenceEnd(const std::string& name);
	void serializeNullableBegin(const std::string& name, bool isNull);
	void serializeNullableEnd(const std::string& name);
	void serializeOptionalBegin(const std::string& name, bool isSpecified);
	void serializeOptionalEnd(const std::string& name);
	void serialize(const std::string& name, Poco::Int8 val);
	void serialize(const std::string& name, Poco::UInt8 val);
	void serialize(const std::string& name, Poco::Int16 val);
	void serialize(const std::string& name, Poco::UInt16 val);
	void serialize(const std::string& name, Poco::Int32 val);
	void serialize(const std::string& name, Poco::UInt32 val);
	void serialize(const std::string& name, long val);
	void serialize(const std::string& name, unsigned long val);
#ifndef POCO_LONG_IS_64_BIT
	void serialize(const std::string& name, Poco::Int64 val);
	void serialize(const std::string& name, Poco::UInt64 val);
#endif
	void serialize(const std::string& name, float val);
	void serialize(const std::string& name, double val);
	void serialize(const std::string& name, bool val);
	void serialize(const std::string& name, char val);
	void serialize(const std::string& name, const std::string& val);
	void serialize(const std::string& name, const std::vector<char>& val);

protected:
	void serializeTypeTag(TypeTag tag);
		/// Serializes a TypeTag.

	void serializeName(const std::string& name);
		/// Serializes a name.

private:
	TaggedBinarySerializer(const TaggedBinarySerializer&);
	TaggedBinarySerializer& operator = (const TaggedBinarySerializer&);

private:
	Poco::RemotingNG::BinarySerializer _serializer;
	std::vector<ContainerType> _containerStack;
};


//
// inlines
//
inline void TaggedBinarySerializer::serializeTypeTag(TypeTag tag)
{
	_serializer.serializeToken(static_cast<Poco::UInt8>(tag));
}


inline void TaggedBinarySerializer::serializeName(const std::string& name)
{
	if (_containerStack.back() != CONT_SEQUENCE)
	{
		_serializer.serializeToken(name);
	}
}


} } } // namespace Poco::JS::Bridge


#endif // JS_Bridge_TaggedBinarySerializer_INCLUDED
