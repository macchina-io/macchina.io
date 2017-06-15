//
// String.h
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  String
//
// Definitions of the OPC String types wrappers..
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef IoT_OPC_String_INCLUDED
#define IoT_OPC_String_INCLUDED


#include "IoT/OPC/OPC.h"
#include "IoT/OPC/Types.h"/*
#include "Poco/UUID.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Dynamic/VarHolder.h"
#include "open62541.h"
#include <vector>
#include <cstring>
#include <chrono>
*/

namespace IoT {
namespace OPC {


class OPC_API UAString
	/// A string conversion utility class with value semantics.
	/// It can be constructed from std::string and provides
	/// implicit conversion to/from UA_String.
{
public:
	UAString();
		/// Creates the UAString.

	UAString(const UAString& from);
		/// Copy-constructs the UAString.

	UAString(const std::string& from);
		/// Creates the UAString from std::string.

	~UAString();
		/// Destroys the UAString.

	UAString& operator = (const std::string& from);
		/// Asignment operator.

	UAString& operator = (const UAString& from);
		/// Asignment operator.

	operator const String&();
		/// Cast operator.

	operator std::string();
		/// Cast operator.

	std::size_t length() const
	{
		return _to.length;
	}

	const unsigned char* data() const
	{
		return _to.data;
	}

private:
	void allocate(const unsigned char* data, std::size_t length);
	void release();

	String _to;
};


class OPC_API STDString
	/// A string conversion utility class with value semantics.
	/// It can be constructed from UA_String and provides
	/// implicit conversion to/from std::string.
{
public:
	STDString(const String& from);
		/// Creates the STDString.

	STDString(const STDString& from);
		/// Copy-constructs the STDString.

	~STDString();
		/// Destroys the STDString.

	STDString& operator = (const STDString& from);
		/// Asignment operator.

	operator const std::string&();
		/// Cast operator.

	operator const String&();
		/// Cast operator.

	std::size_t length() const;
		/// Returns length of the string.

	const unsigned char* data() const;
		/// returns pointer to string data.

private:
	void assign(const char* data, std::size_t length);

	std::string _to;
	String      _toUA;
};


inline std::size_t STDString::length() const
{
	return _toUA.length;
}


inline const unsigned char* STDString::data() const
{
	return _toUA.data;
}


} } // namespace IoT::OPC


#endif // IoT_OPC_String_INCLUDED
