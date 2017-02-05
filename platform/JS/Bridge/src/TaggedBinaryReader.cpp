//
// TaggedBinaryReader.cpp
//
// $Id$
//
// Library: JSBridge
// Package: Bridge
// Module:  TaggedBinaryReader
//
// Copyright (c) 2013-2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Bridge/TaggedBinaryReader.h"
#include "Poco/JS/Bridge/TaggedBinarySerializer.h"
#include "Poco/RemotingNG/BinaryDeserializer.h"
#include "Poco/Exception.h"
#include <vector>


namespace Poco {
namespace JS {
namespace Bridge {


TaggedBinaryReader::TaggedBinaryReader(v8::Isolate* pIsolate):
	_serializer(pIsolate)
{
}

	
TaggedBinaryReader::~TaggedBinaryReader()
{
}

	
v8::Local<v8::Object> TaggedBinaryReader::read(std::istream& istream)
{
	Poco::RemotingNG::BinaryDeserializer deserializer;
	deserializer.setup(istream);

	std::vector<std::string> names;
	
	std::string messageName;
	Poco::RemotingNG::SerializerBase::MessageType messageType = deserializer.findMessage(messageName);
	deserializer.deserializeMessageBegin(messageName, messageType);
	_serializer.serializeMessageBegin(messageName, messageType);
	names.push_back(messageName);

	Poco::UInt8 tag;
	std::string name;
	std::string unused;
	deserializer.deserialize(unused, true, tag);
	while (tag != TaggedBinarySerializer::TYPE_TAG_MESSAGE_END)
	{
		switch (tag)
		{
		case TaggedBinarySerializer::TYPE_TAG_STRUCT_BEGIN:
			{
				deserializer.deserialize(unused, true, name);
				names.push_back(name);
				deserializer.deserializeStructBegin(name, true);
				_serializer.serializeStructBegin(name);
			}
			break;
		case TaggedBinarySerializer::TYPE_TAG_STRUCT_END:
			{
				deserializer.deserializeStructEnd(names.back());
				_serializer.serializeStructEnd(names.back());
				names.pop_back();
			}
			break;
		case TaggedBinarySerializer::TYPE_TAG_SEQUENCE_BEGIN:
			{
				deserializer.deserialize(unused, true, name);
				names.push_back(name);
				Poco::UInt32 lengthHint;
				deserializer.deserializeSequenceBegin(name, true, lengthHint);
				_serializer.serializeSequenceBegin(name, lengthHint);
			}
			break;
		case TaggedBinarySerializer::TYPE_TAG_SEQUENCE_END:
			{
				deserializer.deserializeSequenceEnd(names.back());
				_serializer.serializeSequenceEnd(names.back());
				names.pop_back();
			}
			break;
		case TaggedBinarySerializer::TYPE_TAG_NULLABLE_BEGIN:
			{
				deserializer.deserialize(unused, true, name);
				names.push_back(name);
				bool isNull;
				deserializer.deserializeNullableBegin(name, true, isNull);
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
				deserializer.deserialize(unused, true, name);
				names.push_back(name);
				bool isSpecified;
				deserializer.deserializeOptionalBegin(name, true, isSpecified);
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
			throw Poco::DataFormatException("Invalid type tag encountered during deserialization of", names.back());
		}
		deserializer.deserialize(name, true, tag);
	}
	_serializer.serializeMessageEnd(messageName, messageType);
	
	return _serializer.jsValue();
}


} } } // namespace Poco::JS::Bridge
