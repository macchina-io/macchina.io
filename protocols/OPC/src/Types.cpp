//
// Types.cpp
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  Types
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "IoT/OPC/Types.h"
#include "Poco/ByteOrder.h"
#include "Poco/Exception.h"
#include "open62541.h"
#include <iostream>

using namespace Poco;


namespace IoT {
namespace OPC {


const UInt16 OPC_STANDARD_PORT = 4840;


//
// NodeID
//

NodeID::NodeID(): _nodeId(UA_NODEID_NULL)
{
}


NodeID::NodeID(int nsIndex, UInt32 value)
{
	assignNumeric(nsIndex, value);
}


NodeID::NodeID(int nsIndex, const std::string& str)
{
	std::size_t length = str.size();
	const UA_Byte* data = length ?
			reinterpret_cast<const UA_Byte*>(str.data()) :
			reinterpret_cast<const UA_Byte*>(0);
	assignString(nsIndex, length, data, UA_NODEIDTYPE_STRING);
}


NodeID::NodeID(int nsIndex, const Poco::UUID& value)
{
	assignGuid(nsIndex, toUA(value));
}


NodeID::NodeID(int nsIndex, const ByteStringType& val)
{
	std::size_t length = val.size();
	const UA_Byte* data = length ? &val[0] : reinterpret_cast<const UA_Byte*>(0);
	assignString(nsIndex, length, data, UA_NODEIDTYPE_BYTESTRING);
}


NodeID::NodeID(const NodeID& other)
{
	assign(other);
}


NodeID::NodeID(const Type& other)
{
	UInt16 nsIndex = other.namespaceIndex;
	UA_NodeIdType idType = other.identifierType;
	switch(idType)
	{
	case UA_NODEIDTYPE_NUMERIC:
		assignNumeric(nsIndex, other.identifier.numeric);
		break;
	case UA_NODEIDTYPE_STRING:
	case UA_NODEIDTYPE_BYTESTRING:
	{
		std::size_t length = 0;
		const UA_Byte* data = 0;
		if(idType == UA_NODEIDTYPE_STRING)
		{
			length = other.identifier.string.length;
			if(length) data = other.identifier.string.data;
		}
		else
		{
			length = other.identifier.byteString.length;
			if(length) data = other.identifier.byteString.data;
		}
		assignString(nsIndex, length, data, idType);
		break;
	}
	case UA_NODEIDTYPE_GUID:
		assignGuid(nsIndex, other.identifier.guid);
		break;
	}
}


NodeID::~NodeID()
{
}


NodeID& NodeID::operator = (const NodeID& other)
{
	if(&other != this) assign(other);
	return *this;
}


Boolean NodeID::operator == (const NodeID& other) const
{
	return UA_NodeId_equal(&_nodeId, &other._nodeId);
}


Boolean NodeID::operator != (const NodeID& other) const
{
	return !(*this == other);
}


Boolean NodeID::isNull() const
{
	return UA_NodeId_isNull(&_nodeId);
}


void NodeID::throwIfNull() const
{
	if(isNull())
		throw Poco::NullPointerException("NodeId is null.");
}


void NodeID::throwIf(bool cond) const
{
	if(cond)
		throw Poco::InvalidAccessException("Invalid Node ID type access.");
}


void NodeID::assign(const NodeID& other)
{
	UInt16 nsIndex = other._nodeId.namespaceIndex;
	UA_NodeIdType idType = other._nodeId.identifierType;
	switch(idType)
	{
	case UA_NODEIDTYPE_NUMERIC:
		assignNumeric(nsIndex, other._nodeId.identifier.numeric);
		break;
	case UA_NODEIDTYPE_STRING:
	case UA_NODEIDTYPE_BYTESTRING:
	{
		std::size_t length = other._buf.size();
		const UA_Byte* data = length ? &other._buf[0] : 0;
		assignString(nsIndex, length, data, idType);
		break;
	}
	case UA_NODEIDTYPE_GUID:
		assignGuid(nsIndex, other._nodeId.identifier.guid);
		break;
	}
}


void NodeID::assignNumeric(int nsIndex, UInt32 value)
{
	_nodeId.namespaceIndex = nsIndex;
	_nodeId.identifierType = UA_NODEIDTYPE_NUMERIC;
	_nodeId.identifier.numeric = value;
}


void NodeID::assignString(int nsIndex, std::size_t length, const UA_Byte* data, UA_NodeIdType type)
{
	_nodeId.namespaceIndex = nsIndex;
	_nodeId.identifierType = type;
	if (length)
	{
		_buf.resize(length);
		if(data)
		{
			std::memcpy(&_buf[0], data, length);
		}
		else
		{
			throw Poco::NullPointerException("OPC::NodeID assignment: length > 0, data == null.");
		}
	}
	if(type == UA_NODEIDTYPE_STRING)
	{
		_nodeId.identifier.string.length = length;
		_nodeId.identifier.string.data = length ? &_buf[0] : 0;
	}
	else if(type == UA_NODEIDTYPE_BYTESTRING)
	{
		_nodeId.identifier.byteString.length = length;
		_nodeId.identifier.byteString.data = length ? &_buf[0] : 0;
	}
	else
	{
		throw Poco::InvalidArgumentException("OPC::NodeID assignment: only string and byteString allowed.");
	}
}


void NodeID::assignGuid(int nsIndex, const UA_Guid& value)
{
	_nodeId.namespaceIndex = nsIndex;
	_nodeId.identifierType = UA_NODEIDTYPE_GUID;
	_nodeId.identifier.guid = value;
}


Poco::UInt16 NodeID::getNSIndex() const
{
	throwIfNull();
	return _nodeId.namespaceIndex;
}


NodeID::IDType NodeID::getIDType() const
{
	throwIfNull();
	return _nodeId.identifierType;
}


NodeID::Type NodeID::getType() const
{
	throwIfNull();
	return _nodeId;
}


bool NodeID::isNumeric() const
{
	if(isNull()) return false;
	return _nodeId.identifierType >= 0 &&
		_nodeId.identifierType < UA_NODEIDTYPE_STRING;
}


bool NodeID::isString() const
{
	if(isNull()) return false;
	return _nodeId.identifierType == UA_NODEIDTYPE_STRING;
}


bool NodeID::isByteString() const
{
	if(isNull()) return false;
	return _nodeId.identifierType == UA_NODEIDTYPE_BYTESTRING;
}


bool NodeID::isGuid() const
{
	if(isNull()) return false;
	return _nodeId.identifierType == UA_NODEIDTYPE_GUID;
}


UInt32 NodeID::getNumeric() const
{
	throwIfNull();
	throwIf(!isNumeric());
	return _nodeId.identifier.numeric;
}


std::string NodeID::getString() const
{
	throwIfNull();
	throwIf(!isString());
	return std::string(const_cast<char*>(reinterpret_cast<const char*>(&_buf[0])), _buf.size());
}


const NodeID::ByteStringType& NodeID::getByteString() const
{
	throwIfNull();
	throwIf(!isByteString());
	return _buf;
}


UUID NodeID::getGuid() const
{
	throwIfNull();
	throwIf(!isGuid());
	return toPoco(_nodeId.identifier.guid);
}


UA_Guid NodeID::toUA(const Poco::UUID& uuid)
{
	UA_Guid guid;
	char buffer[16];
	uuid.copyTo(buffer);
	UA_UInt32 ui32;
	UA_UInt16 ui16;
	std::memcpy(&ui32, &buffer[0], sizeof(UA_UInt32));
	guid.data1 = ByteOrder::fromNetwork(ui32);
	std::memcpy(&ui16, &buffer[4], sizeof(UA_UInt16));
	guid.data2 = ByteOrder::fromNetwork(ui16);
	std::memcpy(&ui16, &buffer[6], sizeof(UA_UInt16));
	guid.data3 = ByteOrder::fromNetwork(ui16);
	std::memcpy(guid.data4, &buffer[8], 8);
	return guid;
}


Poco::UUID NodeID::toPoco(const UA_Guid& guid)
{
	Poco::UUID uuid;
	char buffer[16];
	UA_UInt32 ui32 = ByteOrder::toNetwork(guid.data1);
	std::memcpy(&buffer[0], &ui32, sizeof(UA_UInt32));
	UA_UInt16 ui16 = ByteOrder::toNetwork(guid.data2);
	std::memcpy(&buffer[4], &ui16, sizeof(UA_UInt16));
	ui16 = ByteOrder::toNetwork(guid.data3);
	std::memcpy(&buffer[6], &ui16, sizeof(UA_UInt16));
	std::memcpy(&buffer[8], guid.data4, 8);
	uuid.copyFrom(buffer);
	return uuid;
}


//
// DataTypeMember
//

DataTypeMember::DataTypeMember(UInt16 index,
	const std::string& name,
	Byte padding,
	Boolean nsZero,
	Boolean isArray): _name(name)
{
	_type.memberTypeIndex = index;
	_type.memberName = _name.c_str();
	_type.padding = padding;
	_type.namespaceZero = nsZero;
	_type.isArray = isArray;
}

DataTypeMember::~DataTypeMember()
{
}

UInt16 DataTypeMember::getIndex() const
{
	return _type.memberTypeIndex;
}

void DataTypeMember::setIndex(UInt16 idx)
{
_type.memberTypeIndex = idx;
}

const std::string& DataTypeMember::getName() const
{
	return _name;
}

void DataTypeMember::setName(const std::string& name)
{
	_name = name;
}

Byte DataTypeMember::getPadding() const
{
	return _type.padding;
}

void DataTypeMember::setPadding(Byte padding)
{
	_type.padding = padding;
}

Boolean DataTypeMember::getNSZero() const
{
	return _type.namespaceZero;
}

void DataTypeMember::setNSZero(Boolean nsZero)
{
	_type.namespaceZero = nsZero;
}

Boolean DataTypeMember::getIsArray() const
{
	return _type.isArray;
}

void DataTypeMember::setIsArray(Boolean isArray)
{
	_type.isArray = isArray;
}

const DataTypeMember::Type& DataTypeMember::get() const
{
	return _type;
}

void DataTypeMember::set(const Type& type)
{
	if(type.memberName && strlen(type.memberName))
	{
		_name.assign(type.memberName, strlen(type.memberName));
	}
	else
	{
		_name.clear();
	}
	_type = type;
	_type.memberName = _name.c_str();
}


} } // namespace IoT::OPC
