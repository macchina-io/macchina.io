//
// TaggedBinaryReader.cpp
//
// Library: JS/Bridge
// Package: Bridging
// Module:  TaggedBinaryReader
//
// Copyright (c) 2013-2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Bridge/TaggedBinaryReader.h"


namespace Poco {
namespace JS {
namespace Bridge {


TaggedBinaryReader::TaggedBinaryReader(v8::Isolate* pIsolate):
	_serializer(pIsolate)
{
	_containerStack.reserve(32);
}


TaggedBinaryReader::~TaggedBinaryReader()
{
}


const v8::Global<v8::Object>& TaggedBinaryReader::read(std::istream& istream)
{
	Poco::RemotingNG::BinaryDeserializer deserializer;
	deserializer.setup(istream);

	std::vector<std::string> names;

	std::string messageName;
	Poco::RemotingNG::SerializerBase::MessageType messageType = deserializer.findMessage(messageName);
	deserializer.deserializeMessageBegin(messageName, messageType);
	_serializer.serializeMessageBegin(messageName, messageType);
	names.push_back(messageName);
	_containerStack.push_back(TaggedBinarySerializer::CONT_MESSAGE);

	std::string name;
	std::string unused;
	Poco::UInt8 tag = deserializeTypeTag(deserializer);
	while (istream.good() && tag != TaggedBinarySerializer::TYPE_TAG_MESSAGE_END)
	{
		switch (tag)
		{
		case TaggedBinarySerializer::TYPE_TAG_STRUCT_BEGIN:
			{
				name = deserializeName(deserializer);
				names.push_back(name);
				check(deserializer.deserializeStructBegin(name, true));
				_serializer.serializeStructBegin(name);
				_containerStack.push_back(TaggedBinarySerializer::CONT_STRUCT);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_STRUCT_END:
			{
				_containerStack.pop_back();
				deserializer.deserializeStructEnd(names.back());
				_serializer.serializeStructEnd(names.back());
				names.pop_back();
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_SEQUENCE_BEGIN:
			{
				name = deserializeName(deserializer);
				names.push_back(name);
				Poco::UInt32 lengthHint;
				check(deserializer.deserializeSequenceBegin(name, true, lengthHint));
				_serializer.serializeSequenceBegin(name, lengthHint);
				_containerStack.push_back(TaggedBinarySerializer::CONT_SEQUENCE);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_SEQUENCE_END:
			{
				_containerStack.pop_back();
				deserializer.deserializeSequenceEnd(names.back());
				_serializer.serializeSequenceEnd(names.back());
				names.pop_back();
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_NULLABLE_BEGIN:
			{
				name = deserializeName(deserializer);
				names.push_back(name);
				bool isNull;
				check(deserializer.deserializeNullableBegin(name, true, isNull));
				_serializer.serializeNullableBegin(name, isNull);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_NULLABLE_END:
			{
				deserializer.deserializeNullableEnd(names.back());
				_serializer.serializeNullableEnd(names.back());
				names.pop_back();
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_OPTIONAL_BEGIN:
			{
				name = deserializeName(deserializer);
				names.push_back(name);
				bool isSpecified;
				check(deserializer.deserializeOptionalBegin(name, true, isSpecified));
				_serializer.serializeOptionalBegin(name, isSpecified);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_OPTIONAL_END:
			{
				deserializer.deserializeOptionalEnd(names.back());
				_serializer.serializeOptionalEnd(names.back());
				names.pop_back();
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_INT8:
			{
				read<Poco::Int8>(deserializer);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_UINT8:
			{
				read<Poco::UInt8>(deserializer);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_INT16:
			{
				read<Poco::Int16>(deserializer);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_UINT16:
			{
				read<Poco::UInt16>(deserializer);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_INT32:
			{
				read<Poco::Int32>(deserializer);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_UINT32:
			{
				read<Poco::UInt32>(deserializer);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_LONG:
			{
				read<long>(deserializer);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_ULONG:
			{
				read<unsigned long>(deserializer);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_INT64:
			{
				read<Poco::Int64>(deserializer);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_UINT64:
			{
				read<Poco::UInt64>(deserializer);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_FLOAT:
			{
				read<float>(deserializer);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_DOUBLE:
			{
				read<double>(deserializer);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_BOOL:
			{
				read<bool>(deserializer);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_CHAR:
			{
				read<char>(deserializer);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_STRING:
			{
				read<std::string>(deserializer);
			}
			break;

		case TaggedBinarySerializer::TYPE_TAG_BUFFER:
			{
				read<std::vector<char> >(deserializer);
			}
			break;

		default:
			throw Poco::RemotingNG::DeserializerException("Invalid type tag encountered during deserialization of", names.back());
		}
		tag = deserializeTypeTag(deserializer);
	}
	if (istream.good())
	{
		_serializer.serializeMessageEnd(messageName, messageType);
		_containerStack.pop_back();
		poco_assert (_containerStack.empty());
		return _serializer.jsValue();
	}
	else throw Poco::RemotingNG::DeserializerException("Unexpected end of stream");
}


} } } // namespace Poco::JS::Bridge
