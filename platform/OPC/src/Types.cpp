//
// Types.cpp
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  Server
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/OPC/Types.h"
#include "Poco/ByteOrder.h"
#include "Poco/Exception.h"
#include "open62541.h"


namespace Poco {
namespace OPC {


const UInt16 OPC_STANDARD_PORT = 4840;


//
// UAString
//

UAString::UAString(): _to()
{
}


UAString::UAString(const UAString& from): _to()
{
	allocate(from._to.data, from._to.length);
}


UAString::UAString(const std::string& from): _to()
{
	allocate(reinterpret_cast<const unsigned char*>(from.data()), from.size());
}


UAString::~UAString()
{
	UA_free(_to.data);
}


UAString& UAString::operator = (const std::string& from)
{
	release();
	allocate(reinterpret_cast<const unsigned char*>(from.data()), from.size());
	return *this;
}


UAString& UAString::operator = (const UAString& from)
{
	release();
	allocate(from._to.data, from._to.length);
	return *this;
}


UAString::operator const String&()
{
	return _to;
}


UAString::operator std::string()
{
	return std::string(reinterpret_cast<char*>(_to.data), _to.length);
}


void UAString::allocate(const unsigned char* data, std::size_t length)
{
	if((_to.length = length))
	{
		_to.data = (open62541::UA_Byte*) UA_malloc(_to.length);
		std::memcpy(_to.data, data, _to.length);
	}
}


void UAString::release()
{
	UA_free(_to.data);
	_to.data = 0;
	_to.length = 0;
}


//
// STDString
//

STDString::STDString(const String& from)
{
	assign(reinterpret_cast<char*>(from.data), from.length);
}


STDString::STDString(const STDString& from)
{
	assign(from._to.data(), from._to.size());
}


STDString::~STDString()
{
}


STDString& STDString::operator = (const STDString& from)
{
	if(&from != this)
	{
		assign(from._to.data(), from._to.size());
	}
	return *this;
}


STDString::operator const std::string&()
{
	return _to;
}


STDString::operator const String&()
{
	return _toUA;
}


void STDString::assign(const char* data, std::size_t length)
{
	if(length)
	{
		_to.assign(data, length);
		_toUA.data = (unsigned char*) _to.c_str();
		_toUA.length = _to.length();
	}
}


//
// NodeID
//

NodeID::NodeID(): _nodeId(open62541::UA_NODEID_NULL)
{
}


NodeID::NodeID(int nsIndex, UInt32 value)
{
	assignNumeric(nsIndex, value);
}


NodeID::NodeID(int nsIndex, const std::string& str)
{
	std::size_t length = str.size();
	const open62541::UA_Byte* data = length ?
			reinterpret_cast<const open62541::UA_Byte*>(str.data()) :
			reinterpret_cast<const open62541::UA_Byte*>(0);
	assignString(nsIndex, length, data, open62541::UA_NODEIDTYPE_STRING);
}


NodeID::NodeID(int nsIndex, const Poco::UUID& value)
{
	assignGuid(nsIndex, toUA(value));
}


NodeID::NodeID(int nsIndex, const ByteStringType& val)
{
	std::size_t length = val.size();
	const open62541::UA_Byte* data = length ? &val[0] : reinterpret_cast<const open62541::UA_Byte*>(0);
	assignString(nsIndex, length, data, open62541::UA_NODEIDTYPE_BYTESTRING);
}


NodeID::NodeID(const NodeID& other)
{
	assign(other);
}


NodeID::NodeID(const Type& other)
{
	UInt16 nsIndex = other.namespaceIndex;
	open62541::UA_NodeIdType idType = other.identifierType;
	switch(idType)
	{
	case open62541::UA_NODEIDTYPE_NUMERIC:
		assignNumeric(nsIndex, other.identifier.numeric);
		break;
	case open62541::UA_NODEIDTYPE_STRING:
	case open62541::UA_NODEIDTYPE_BYTESTRING:
	{
		std::size_t length = 0;
		const open62541::UA_Byte* data = 0;
		if(idType == open62541::UA_NODEIDTYPE_STRING)
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
	case open62541::UA_NODEIDTYPE_GUID:
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
	return open62541::UA_NodeId_equal(&_nodeId, &other._nodeId);
}


Boolean NodeID::operator != (const NodeID& other) const
{
	return !(*this == other);
}


Boolean NodeID::isNull() const
{
	return open62541::UA_NodeId_isNull(&_nodeId);
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
	open62541::UA_NodeIdType idType = other._nodeId.identifierType;
	switch(idType)
	{
	case open62541::UA_NODEIDTYPE_NUMERIC:
		assignNumeric(nsIndex, other._nodeId.identifier.numeric);
		break;
	case open62541::UA_NODEIDTYPE_STRING:
	case open62541::UA_NODEIDTYPE_BYTESTRING:
	{
		std::size_t length = other._buf.size();
		const open62541::UA_Byte* data = length ? &other._buf[0] : 0;
		assignString(nsIndex, length, data, idType);
		break;
	}
	case open62541::UA_NODEIDTYPE_GUID:
		assignGuid(nsIndex, other._nodeId.identifier.guid);
		break;
	}
}


void NodeID::assignNumeric(int nsIndex, UInt32 value)
{
	_nodeId.namespaceIndex = nsIndex;
	_nodeId.identifierType = open62541::UA_NODEIDTYPE_NUMERIC;
	_nodeId.identifier.numeric = value;
}


void NodeID::assignString(int nsIndex, std::size_t length, const open62541::UA_Byte* data, open62541::UA_NodeIdType type)
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
	if(type == open62541::UA_NODEIDTYPE_STRING)
	{
		_nodeId.identifier.string.length = length;
		_nodeId.identifier.string.data = length ? &_buf[0] : 0;
	}
	else if(type == open62541::UA_NODEIDTYPE_BYTESTRING)
	{
		_nodeId.identifier.byteString.length = length;
		_nodeId.identifier.byteString.data = length ? &_buf[0] : 0;
	}
	else
	{
		throw Poco::InvalidArgumentException("OPC::NodeID assignment: only string and byteString allowed.");
	}
}


void NodeID::assignGuid(int nsIndex, const open62541::UA_Guid& value)
{
	_nodeId.namespaceIndex = nsIndex;
	_nodeId.identifierType = open62541::UA_NODEIDTYPE_GUID;
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
		_nodeId.identifierType < open62541::UA_NODEIDTYPE_STRING;
}


bool NodeID::isString() const
{
	if(isNull()) return false;
	return _nodeId.identifierType == open62541::UA_NODEIDTYPE_STRING;
}


bool NodeID::isByteString() const
{
	if(isNull()) return false;
	return _nodeId.identifierType == open62541::UA_NODEIDTYPE_BYTESTRING;
}


bool NodeID::isGuid() const
{
	if(isNull()) return false;
	return _nodeId.identifierType == open62541::UA_NODEIDTYPE_GUID;
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


open62541::UA_Guid NodeID::toUA(const Poco::UUID& uuid)
{
	open62541::UA_Guid guid;
	char buffer[16];
	uuid.copyTo(buffer);
	open62541::UA_UInt32 ui32;
	open62541::UA_UInt16 ui16;
	std::memcpy(&ui32, &buffer[0], sizeof(open62541::UA_UInt32));
	guid.data1 = ByteOrder::fromNetwork(ui32);
	std::memcpy(&ui16, &buffer[4], sizeof(open62541::UA_UInt16));
	guid.data2 = ByteOrder::fromNetwork(ui16);
	std::memcpy(&ui16, &buffer[6], sizeof(open62541::UA_UInt16));
	guid.data3 = ByteOrder::fromNetwork(ui16);
	std::memcpy(guid.data4, &buffer[8], 8);
	return guid;
}


Poco::UUID NodeID::toPoco(const open62541::UA_Guid& guid)
{
	Poco::UUID uuid;
	char buffer[16];
	open62541::UA_UInt32 ui32 = ByteOrder::toNetwork(guid.data1);
	std::memcpy(&buffer[0], &ui32, sizeof(open62541::UA_UInt32));
	open62541::UA_UInt16 ui16 = ByteOrder::toNetwork(guid.data2);
	std::memcpy(&buffer[4], &ui16, sizeof(open62541::UA_UInt16));
	ui16 = ByteOrder::toNetwork(guid.data3);
	std::memcpy(&buffer[6], &ui16, sizeof(open62541::UA_UInt16));
	std::memcpy(&buffer[8], guid.data4, 8);
	uuid.copyFrom(buffer);
	return uuid;
}


//
// QualifiedName
//

const unsigned QualifiedName::OPC_MAX_QNAME_LENGTH = 512u;


QualifiedName::QualifiedName(Poco::UInt16 nsIndex, const std::string& name):
		_nsIndex(nsIndex),
		_name(name)
{
	if(_name.length() > OPC_MAX_QNAME_LENGTH)
	{
		throw RangeException("OPC qualified name too long (max allowed 512):" + _name);
	}
}


QualifiedName::~QualifiedName()
{
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


//
// LocalizedText
//

LocalizedText::LocalizedText(const std::string& text, const LocaleID& localeID):
	_text(open62541::UA_LOCALIZEDTEXT_ALLOC(text.c_str(), localeID.c_str()))
{
}


LocalizedText::LocalizedText(const LocalizedText& other): _text()
{
	copy(other);
}


void LocalizedText::cleanup()
{
	UA_free(_text.text.data);
	_text.text.data = 0;
	_text.text.length = 0;
	UA_free(_text.locale.data);
	_text.locale.data = 0;
	_text.locale.length = 0;
}


LocalizedText::~LocalizedText()
{
	cleanup();
}


LocalizedText& LocalizedText::operator = (const LocalizedText& other)
{
	if(&other != this)
	{
		cleanup();
		copy(other);
	}
	return *this;
}


LocalizedText::LocalizedText(const Type& other)
{
	copy(other);
}


LocalizedText& LocalizedText::operator = (const Type& other)
{
	cleanup();
	copy(other);
	return *this;
}


void LocalizedText::copy(const LocalizedText& other)
{
	_text.text.data = (open62541::UA_Byte*) UA_malloc(other._text.text.length);
	std::memcpy(_text.text.data, other._text.text.data, other._text.text.length);
	_text.text.length = other._text.text.length;
	_text.locale.data = (open62541::UA_Byte*) UA_malloc(other._text.locale.length);
	std::memcpy(_text.locale.data, other._text.locale.data, other._text.locale.length);
	_text.locale.length = other._text.locale.length;
}


void LocalizedText::copy(const Type& other)
{
	_text.text.data = (open62541::UA_Byte*) UA_malloc(other.text.length);
	std::memcpy(_text.text.data, other.text.data, other.text.length);
	_text.text.length = other.text.length;
	_text.locale.data = (open62541::UA_Byte*) UA_malloc(other.locale.length);
	std::memcpy(_text.locale.data, other.text.data, other.text.length);
	_text.locale.length = other.locale.length;
}


//
// EnumValueType
//

EnumValueType::EnumValueType(Int64 value,
	const LocalizedText& displayName,
	const LocalizedText& description):
		_value(value),
		_displayName(displayName),
		_description(description)
{
}


EnumValueType::~EnumValueType()
{
}


Int64 EnumValueType::getValue() const
{
	return _value;
}


const LocalizedText& EnumValueType::getDisplayName() const
{
	return _displayName;
}


const LocalizedText& EnumValueType::getDescription() const
{
	return _description;
}


//
// OptionSet
//

OptionSet::OptionSet(const ByteString& value, const ByteString& validBits):
		_value(value),
		_validBits(validBits)
{
}


OptionSet::~OptionSet()
{
}


const ByteString& OptionSet::getValue() const
{
	return _value;
}


const ByteString& OptionSet::getValidBits() const
{
	return _validBits;
}


//
// EnumField
//

EnumField::EnumField(const String& name): _name(name)
{
}


EnumField::~EnumField()
{
}


const String& EnumField::getName() const
{
	return _name;
}


//
// EnumDefinition
//


EnumDefinition::EnumDefinition(const EnumField::List& fields): _fields(fields)
{
}


EnumDefinition::~EnumDefinition()
{
}


const EnumField::List& EnumDefinition::getFields() const
{
	return _fields;
}


//
// Decimal
//


Decimal::Decimal(Int64 value, UInt64 scale): _value(value), _scale(scale)
{
	checkScale(_scale);
}


Decimal::~Decimal()
{
}


double Decimal::value() const
{
	return static_cast<double>(_value) / _scale;
}


Int64 Decimal::getValue() const
{
	return _value;
}


void Decimal::setValue(Int64 val)
{
	_value = val;
}


Int64 Decimal::getScale() const
{
	return _scale;
}


void Decimal::setScale(UInt64 scale)
{
	checkScale(scale);
	_scale = scale;
}


void Decimal::checkScale(UInt64 val) const
{
	if(!val || (val % 10))
	{
		throw Poco::InvalidArgumentException("OPC::Decimal: Invalid scale value.");
	}
}


//
// BaseNode
//
/*
BaseNode::BaseNode()
{
}


BaseNode::~BaseNode()
{
}
*/

} } // namespace Poco::OPC
