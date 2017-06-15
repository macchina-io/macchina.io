//
// String.cpp
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  String
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "IoT/OPC/String.h"
#include "Poco/ByteOrder.h"
//#include "Poco/Exception.h"
#include "open62541.h"

using namespace Poco;


namespace IoT {
namespace OPC {


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
		_to.data = (UA_Byte*) UA_malloc(_to.length);
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
	if(data && length) _to.assign(data, length);
	else _to.clear();
	_toUA.data = (unsigned char*) _to.c_str();
	_toUA.length = _to.length();
}


} } // namespace IoT::OPC
