//
// TaggedBinarySerializer.cpp
//
// $Id$
//
// Library: JS/Bridge
// Package: Bridging
// Module:  TaggedBinarySerializer
//
// Copyright (c) 2013-2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Bridge/TaggedBinarySerializer.h"


namespace Poco {
namespace JS {
namespace Bridge {


using Poco::RemotingNG::BinarySerializer;


const std::string TaggedBinarySerializer::EMPTY;


TaggedBinarySerializer::TaggedBinarySerializer()
{
}


TaggedBinarySerializer::~TaggedBinarySerializer()
{
}


void TaggedBinarySerializer::serializeMessageBegin(const std::string& name, Poco::RemotingNG::SerializerBase::MessageType type)
{
	BinarySerializer::serializeMessageBegin(name, type);
}


void TaggedBinarySerializer::serializeMessageEnd(const std::string& name, Poco::RemotingNG::SerializerBase::MessageType type)
{
	serializeTypeTag(TYPE_TAG_MESSAGE_END);
	BinarySerializer::serializeMessageEnd(name, type);
}


void TaggedBinarySerializer::serializeFaultMessage(const std::string& methodName, Poco::Exception& e)
{
	BinarySerializer::serializeFaultMessage(methodName, e);
}


void TaggedBinarySerializer::serializeStructBegin(const std::string& name)
{
	serializeTypeTag(TYPE_TAG_STRUCT_BEGIN);
	serializeName(name);
	BinarySerializer::serializeStructBegin(name);
}


void TaggedBinarySerializer::serializeStructEnd(const std::string& name)
{
	serializeTypeTag(TYPE_TAG_STRUCT_END);
	BinarySerializer::serializeStructEnd(name);
}


void TaggedBinarySerializer::serializeSequenceBegin(const std::string& name, Poco::UInt32 numElems)
{
	serializeTypeTag(TYPE_TAG_SEQUENCE_BEGIN);
	serializeName(name);
	BinarySerializer::serializeSequenceBegin(name, numElems);
}


void TaggedBinarySerializer::serializeSequenceEnd(const std::string& name)
{
	serializeTypeTag(TYPE_TAG_SEQUENCE_END);
	BinarySerializer::serializeSequenceEnd(name);
}


void TaggedBinarySerializer::serializeNullableBegin(const std::string& name, bool isNull)
{
	serializeTypeTag(TYPE_TAG_NULLABLE_BEGIN);
	serializeName(name);
	BinarySerializer::serializeNullableBegin(name, isNull);
}


void TaggedBinarySerializer::serializeNullableEnd(const std::string& name)
{
	serializeTypeTag(TYPE_TAG_NULLABLE_END);
	BinarySerializer::serializeNullableEnd(name);
}


void TaggedBinarySerializer::serializeOptionalBegin(const std::string& name, bool isSpecified)
{
	serializeTypeTag(TYPE_TAG_OPTIONAL_BEGIN);
	serializeName(name);
	BinarySerializer::serializeOptionalBegin(name, isSpecified);
}


void TaggedBinarySerializer::serializeOptionalEnd(const std::string& name)
{
	serializeTypeTag(TYPE_TAG_OPTIONAL_END);
	BinarySerializer::serializeOptionalEnd(name);
}


void TaggedBinarySerializer::serialize(const std::string& name, Poco::Int8 val)
{
	serializeTypeTag(TYPE_TAG_INT8);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}


void TaggedBinarySerializer::serialize(const std::string& name, Poco::UInt8 val)
{
	serializeTypeTag(TYPE_TAG_UINT8);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}


void TaggedBinarySerializer::serialize(const std::string& name, Poco::Int16 val)
{
	serializeTypeTag(TYPE_TAG_INT16);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}


void TaggedBinarySerializer::serialize(const std::string& name, Poco::UInt16 val)
{
	serializeTypeTag(TYPE_TAG_UINT16);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}


void TaggedBinarySerializer::serialize(const std::string& name, Poco::Int32 val)
{
	serializeTypeTag(TYPE_TAG_INT32);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}


void TaggedBinarySerializer::serialize(const std::string& name, Poco::UInt32 val)
{
	serializeTypeTag(TYPE_TAG_UINT32);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}


void TaggedBinarySerializer::serialize(const std::string& name, long val)
{
	serializeTypeTag(TYPE_TAG_LONG);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}


void TaggedBinarySerializer::serialize(const std::string& name, unsigned long val)
{
	serializeTypeTag(TYPE_TAG_ULONG);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}


#ifndef POCO_LONG_IS_64_BIT
void TaggedBinarySerializer::serialize(const std::string& name, Poco::Int64 val)
{
	serializeTypeTag(TYPE_TAG_INT64);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}


void TaggedBinarySerializer::serialize(const std::string& name, Poco::UInt64 val)
{
	serializeTypeTag(TYPE_TAG_UINT64);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}
#endif


void TaggedBinarySerializer::serialize(const std::string& name, float val)
{
	serializeTypeTag(TYPE_TAG_FLOAT);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}


void TaggedBinarySerializer::serialize(const std::string& name, double val)
{
	serializeTypeTag(TYPE_TAG_DOUBLE);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}


void TaggedBinarySerializer::serialize(const std::string& name, bool val)
{
	serializeTypeTag(TYPE_TAG_BOOL);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}


void TaggedBinarySerializer::serialize(const std::string& name, char val)
{
	serializeTypeTag(TYPE_TAG_CHAR);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}


void TaggedBinarySerializer::serialize(const std::string& name, const std::string& val)
{
	serializeTypeTag(TYPE_TAG_STRING);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}


void TaggedBinarySerializer::serialize(const std::string& name, const std::vector<char>& val)
{
	serializeTypeTag(TYPE_TAG_BUFFER);
	serializeName(name);
	BinarySerializer::serialize(name, val);
}


} } } // namespace Poco::JS::Bridge
