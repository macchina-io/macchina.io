//
// DateTime.h
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  DateTime
//
// Definitions of the OPC standard types classes as specified in
// in OPC UA Part 3, 8. Standard Data Types.
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef IoT_OPC_DateTime_INCLUDED
#define IoT_OPC_DateTime_INCLUDED


#include "IoT/OPC/OPC.h"
#include "Poco/DateTime.h"
#include "Poco/LocalDateTime.h"
#include "Poco/Types.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Dynamic/VarHolder.h"
#include "open62541.h"
#include <vector>


namespace IoT {
namespace OPC {


class DateTime
	/// This Built-in DataType defines an instance in time.
{
public:
	DateTime();
		/// Creates the DateTime.

	DateTime(Poco::UInt64 ts);
		/// Creates the DateTime.

	DateTime(const DateTime& dt);
		/// Copy-constructs the DateTime.

	DateTime(const std::string& str);
		/// Constructs the DateTime from std::string.

	DateTime(const Poco::DateTime& dt, int ns = 0);
		/// Constructs the DateTime from Poco::DateTime.

	DateTime(const Poco::LocalDateTime& dt, int ns = 0);
		/// Constructs the DateTime from Poco::LocalDateTime.

	~DateTime();
		/// Destroys the DateTime.

	DateTime& operator = (const DateTime& dt);
		/// Assignment operator.

	DateTime& operator = (const std::string& str);
		/// Assignment operator.

	DateTime& operator = (Poco::UInt64 ts);
		/// Assignment operator.

	DateTime& operator = (const Poco::DateTime& dt);
		/// Assignment operator.

	DateTime& operator = (const Poco::LocalDateTime& ldt);
		/// Assignment operator.

	bool operator == (const DateTime& other) const;
		/// Equality operator.

	bool operator != (const DateTime& other) const;
		/// Inequality operator.

	operator Poco::DateTime () const;
		/// Cast operator.

	operator Poco::LocalDateTime () const;
		/// Cast operator.

	static DateTime fromString(const std::string& from);
		/// Creates and returns the DateTime from string.

	std::string toString() const;
		/// Returns the DateTime as string.

	static Poco::Int64 now();
		/// Returns current DateTime as timestamp.

	Poco::Int64 timestamp() const;
		/// Returns the timestamp (epoch 1/1/1601, 100 ns resolution).

	int year() const;
	int month() const;
	int day() const;
	int hour() const;
	int minute() const;
	int second() const;
	int millisecond() const;
	int microsecond() const;
	int nanosecond() const;


private:
	static void printNumber(Poco::UInt16 n, char* pos, size_t digits);
	UA_DateTimeStruct toStruct() const;

	UA_DateTime _uaDT;
};


//
// inlines
//

inline Poco::Int64 DateTime::timestamp() const
{
	return _uaDT;
}


inline int DateTime::year() const
{
	return toStruct().year;
}


inline int DateTime::month() const
{
	return toStruct().month;
}


inline int DateTime::day() const
{
	return toStruct().day;
}


inline int DateTime::hour() const
{
	return toStruct().hour;
}


inline int DateTime::minute() const
{
	return toStruct().min;
}


inline int DateTime::second() const
{
	return toStruct().sec;
}


inline int DateTime::millisecond() const
{
	return toStruct().milliSec;
}


inline int DateTime::microsecond() const
{
	return toStruct().microSec;
}


inline int DateTime::nanosecond() const
{
	return toStruct().nanoSec;
}


inline UA_DateTimeStruct DateTime::toStruct() const
{
	return UA_DateTime_toStruct(_uaDT);
}


} } // namespace IoT::OPC


namespace Poco {
namespace Dynamic {


template <>
class VarHolderImpl<IoT::OPC::DateTime>: public VarHolder
{
public:
	VarHolderImpl(const IoT::OPC::DateTime& val): _val(val)
	{
	}

	~VarHolderImpl()
	{
	}

	const std::type_info& type() const
	{
		return typeid(IoT::OPC::DateTime);
	}

	void convert(Int8& /*val*/) const
	{
		throw BadCastException();
	}

	void convert(Int16& /*val*/) const
	{
		throw BadCastException();
	}

	void convert(Int32& /*val*/) const
	{
		throw BadCastException();
	}

	void convert(Int64& val) const
	{
		val = _val.timestamp();
	}

	void convert(UInt64& val) const
	{
		val = _val.timestamp();
	}

	void convert(std::string& val) const
	{
		val = _val.toString();
	}

	void convert(IoT::OPC::DateTime& val) const
	{
		val = _val;
	}

	void convert(DateTime& dt) const
	{
		dt = _val;
	}

	void convert(LocalDateTime& ldt) const
	{
		ldt = _val;
	}

	void convert(Timestamp& ts) const
	{
		throw BadCastException(); // TODO
		//ts = _val.timestamp();
	}

	VarHolder* clone(Placeholder<VarHolder>* pVarHolder = 0) const
	{
		return cloneHolder(pVarHolder, _val);
	}

	const IoT::OPC::DateTime& value() const
	{
		return _val;
	}

	bool isArray() const
	{
		return false;
	}

	bool isStruct() const
	{
		return false;
	}

	bool isInteger() const
	{
		return false;
	}

	bool isSigned() const
	{
		return false;
	}

	bool isNumeric() const
	{
		return false;
	}

	bool isBoolean() const
	{
		return false;
	}

	bool isString() const
	{
		return false;
	}

private:
	VarHolderImpl();
	VarHolderImpl(const VarHolderImpl&);
	VarHolderImpl& operator = (const VarHolderImpl&);

	IoT::OPC::DateTime _val;
};


} } // namespace Poco::Dynamic


#endif // IoT_OPC_Node_INCLUDED
