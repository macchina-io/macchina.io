//
// JSONEventSerializer.h
//
// $Id: //poco/1.4/JS/Bridge/src/JSONEventSerializer.cpp#3 $
//
// Library: JSBridge
// Package: Bridge
// Module:  JSONEventSerializer
//
// Definition of the JSONEventSerializser class.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Bridge/JSONEventSerializer.h"
#include "Poco/Base64Encoder.h"
#include "Poco/NumberFormatter.h"
#include <sstream>


namespace Poco {
namespace JS {
namespace Bridge {


const std::string JSONEventSerializer::JSON_TRUE("true");
const std::string JSONEventSerializer::JSON_FALSE("false");
const std::string JSONEventSerializer::JSON_NULL("null");


JSONEventSerializer::JSONEventSerializer():
	_pStream(0),
	_indent(0)
{
}


JSONEventSerializer::~JSONEventSerializer()
{
}


void JSONEventSerializer::setupImpl(std::ostream& out)
{
	resetImpl();
	_pStream = &out;
}


void JSONEventSerializer::serializeMessageBegin(const std::string& name, Poco::RemotingNG::SerializerBase::MessageType type)
{
	poco_assert_dbg(_pStream);
	poco_assert_dbg(type == Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);

	*_pStream << "{\n";
	_indent = 1;
	_state.push_back(ST_OBJECT_FIRST);
}


void JSONEventSerializer::serializeMessageEnd(const std::string& name, Poco::RemotingNG::SerializerBase::MessageType type)
{
	poco_assert_dbg(_pStream);
	poco_assert_dbg(type == Poco::RemotingNG::SerializerBase::MESSAGE_EVENT);

	_state.pop_back();
	_indent = 0;
	*_pStream << 
		"\n" <<
		"}\n";
	_pStream->flush();
	_pStream = 0;
}


void JSONEventSerializer::serializeFaultMessage(const std::string& methodName, Poco::Exception& e)
{
}


void JSONEventSerializer::serializeStructBegin(const std::string& name)
{
	writeSeparator();
	if (_state.back() != ST_ARRAY)
	{
		*_pStream << std::string(_indent, '\t') << "\"" << name << "\":\n";
	}
	*_pStream << std::string(_indent, '\t') << "{";
	++_indent;
	_state.push_back(ST_OBJECT_FIRST);
}


void JSONEventSerializer::serializeStructEnd(const std::string& name)
{
	_state.pop_back();
	--_indent;
	*_pStream <<
		"\n" <<
		std::string(_indent, '\t') << "}";
}


void JSONEventSerializer::serializeSequenceBegin(const std::string& name, Poco::UInt32 numElems)
{
	writeSeparator();
	if (_state.back() != ST_ARRAY)
	{
		*_pStream << std::string(_indent, '\t') << "\"" << name << "\":\n";
	}
	*_pStream << std::string(_indent, '\t') << "[";
	++_indent;
	_state.push_back(ST_ARRAY_FIRST);
}


void JSONEventSerializer::serializeSequenceEnd(const std::string& name)
{
	_state.pop_back();
	--_indent;
	*_pStream <<
		"\n" <<
		std::string(_indent, '\t') << "]";
}


void JSONEventSerializer::serializeNullableBegin(const std::string& name, bool isNull)
{
	if (isNull)
	{
		serializeData(name, JSON_NULL);
	}
}


void JSONEventSerializer::serializeNullableEnd(const std::string&)
{
}


void JSONEventSerializer::serializeOptionalBegin(const std::string& name, bool isSpecified)
{
}


void JSONEventSerializer::serializeOptionalEnd(const std::string& name)
{
}


void JSONEventSerializer::serialize(const std::string& name, char val)
{
	std::string tmp("\"");
	tmp += val;
	tmp += '\"';
	serializeData(name, tmp);
}


void JSONEventSerializer::serialize(const std::string& name, const std::vector<char>& val)
{
	std::stringstream base64;
	base64 << '\"';
	Poco::Base64Encoder encoder(base64);
	encoder.write(&val[0], static_cast<std::streamsize>(val.size()));
	encoder.close();
	base64 << '\"';
	serializeData(name, base64.str());
}


void JSONEventSerializer::serialize(const std::string& name, const std::string& val)
{
	std::string str("\"");
	for (std::string::const_iterator it = val.begin(); it != val.end(); ++it)
	{
		switch (*it)
		{
		case '\f':
			str += "\\f";
			break;
		case '\t':
			str += "\\t";
			break;
		case '\r':
			str += "\\r";
			break;
		case '\n':
			str += "\\n";
			break;
		case '\b':
			str += "\\b";
			break;
		case '"':
			str += "\\\"";
			break;
		case '\\':
			str += "\\\\";
			break;
		default:
			if (*it >= 0 && *it < ' ')
			{
				str += "\\u";
				Poco::NumberFormatter::appendHex(str, *it, 4);
			}
			else str += *it;
		}
	}
	str.append("\"");
	serializeData(name, str);
}


void JSONEventSerializer::serializeData(const std::string& name, const std::string& val)
{
	writeSeparator();
	*_pStream << std::string(_indent, '\t');
	if (_state.back() != ST_ARRAY)
	{
		*_pStream << "\"" << name << "\": ";
	}
	*_pStream << val;
}


void JSONEventSerializer::writeSeparator()
{
	switch (_state.back())
	{
	case ST_OBJECT_FIRST:
		*_pStream << "\n";
		_state.back() = ST_OBJECT;
		break;
	case ST_ARRAY_FIRST:
		*_pStream << "\n";
		_state.back() = ST_ARRAY;
		break;
	default:
		*_pStream << ",\n";
		break;
	}
}


void JSONEventSerializer::resetImpl()
{
	_indent = 0;
	_state.clear();
}


} } } // namespace Poco::JS::Bridge
