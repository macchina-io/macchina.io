//
// DateTime.cpp
//
// $Id$
//
// Library: OPC
// Package: OPC
// Module:  DateTime
//
// Copyright (c) 2010-2015, Günter Obiltschnig.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "IoT/OPC/DateTime.h"
#include "open62541.h"

using namespace Poco;


namespace IoT {
namespace OPC {


DateTime::DateTime(): _uaDT(UA_DateTime_now())
{
}


DateTime::DateTime(Poco::UInt64 ts): _uaDT(ts)
{
}


DateTime::DateTime(const std::string& str)
{
	*this = fromString(str);
}


DateTime::DateTime(const DateTime& dt): _uaDT(dt._uaDT)
{
}


DateTime::DateTime(const Poco::DateTime& dt, int ns):
	_uaDT((dt.utcTime() + (Timestamp::UtcTimeVal) round((double)ns/100.0)) -
	(12219292800LL - 11644473600LL) * UA_SEC_TO_DATETIME)
{
}


DateTime::DateTime(const Poco::LocalDateTime& ldt, int ns):
	_uaDT((ldt.utcTime() + (Timestamp::UtcTimeVal) round((double)ns/100.0)) -
	(12219292800LL - 11644473600LL) * UA_SEC_TO_DATETIME)
{
}


DateTime::~DateTime()
{
}


DateTime& DateTime::operator = (const DateTime& dt)
{
	if(&dt != this) _uaDT = dt._uaDT;
	return *this;
}


DateTime& DateTime::operator = (Poco::UInt64 ts)
{
	_uaDT = ts;
	return *this;
}


DateTime& DateTime::operator = (const Poco::DateTime& dt)
{
	_uaDT = dt.utcTime() * 10 + UA_DATETIME_UNIX_EPOCH;
	return *this;
}


DateTime& DateTime::operator = (const Poco::LocalDateTime& ldt)
{
	_uaDT = ldt.utcTime() * 10 + UA_DATETIME_UNIX_EPOCH;
	return *this;
}


DateTime& DateTime::operator = (const std::string& str)
{
	*this = fromString(str);
	return *this;
}


bool DateTime::operator == (const DateTime& other) const
{
	return _uaDT == other._uaDT;
}


bool DateTime::operator != (const DateTime& other) const
{
	return _uaDT != other._uaDT;
}


DateTime::operator Poco::DateTime () const
{
	UA_DateTimeStruct uaDTS = UA_DateTime_toStruct(_uaDT);
	Poco::DateTime dt(uaDTS.year, uaDTS.month, uaDTS.day,
		uaDTS.hour, uaDTS.min, uaDTS.sec, uaDTS.milliSec, uaDTS.microSec);
	return dt;
}


DateTime::operator Poco::LocalDateTime () const
{
	UA_DateTimeStruct uaDTS = UA_DateTime_toStruct(_uaDT);
	Poco::LocalDateTime ldt(uaDTS.year, uaDTS.month, uaDTS.day,
		uaDTS.hour, uaDTS.min, uaDTS.sec, uaDTS.milliSec, uaDTS.microSec);
	return ldt;
}


DateTime DateTime::fromString(const std::string& from)
{
	StringTokenizer st(from, "/ :.", StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);
	if(st.count() != 9)
	{
		throw Poco::InvalidArgumentException("Invalid DateTime format (expected MM/DD/YYYY HH24:MI:SS.mmm.uuu.nnn)");
	}

	Poco::DateTime dt(NumberParser::parse(st[2]),
					  NumberParser::parse(st[0]),
					  NumberParser::parse(st[1]),
					  NumberParser::parse(st[3]),
					  NumberParser::parse(st[4]),
					  NumberParser::parse(st[5]),
					  NumberParser::parse(st[6]),
					  NumberParser::parse(st[7]));

	return  DateTime(dt, NumberParser::parse(st[8]));
}


std::string DateTime::toString() const
{
	UA_DateTimeStruct uaDTS = UA_DateTime_toStruct(_uaDT);
	std::vector<char> str(32);
	printNumber(uaDTS.month, &str[0], 2);
	str[2] = '/';
	printNumber(uaDTS.day, &str[3], 2);
	str[5] = '/';
	printNumber(uaDTS.year, &str[6], 4);
	str[10] = ' ';
	printNumber(uaDTS.hour, &str[11], 2);
	str[13] = ':';
	printNumber(uaDTS.min, &str[14], 2);
	str[16] = ':';
	printNumber(uaDTS.sec, &str[17], 2);
	str[19] = '.';
	printNumber(uaDTS.milliSec, &str[20], 3);
	str[23] = '.';
	printNumber(uaDTS.microSec, &str[24], 3);
	str[27] = '.';
	printNumber(uaDTS.nanoSec, &str[28], 3);
	return std::string(&str[0]);
}


Int64 DateTime::now()
{
	return UA_DateTime_now();
}


void DateTime::printNumber(Poco::UInt16 n, char* pos, size_t digits)
{
	for(size_t i = digits; i > 0; --i)
	{
		pos[i-1] = ((n % 10) + '0');
		n = n / 10;
	}
}


} } // namespace IoT::OPC
