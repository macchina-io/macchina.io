//
// DateTimeWrapper.cpp
//
// Library: JS/Core
// Package: Wrappers
// Module:  DateTimeWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/DateTimeWrapper.h"
#include "Poco/JS/Core/LocalDateTimeWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Timespan.h"
#include "Poco/Exception.h"
#include "Poco/String.h"
#include <cmath>


namespace Poco {
namespace JS {
namespace Core {


DateTimeWrapper::DateTimeWrapper()
{
}


DateTimeWrapper::~DateTimeWrapper()
{
}


v8::Handle<v8::FunctionTemplate> DateTimeWrapper::constructor(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::FunctionTemplate> funcTemplate = v8::FunctionTemplate::New(pIsolate, construct);
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "isDateTime"), v8::FunctionTemplate::New(pIsolate, isDateTime));
	return handleScope.Escape(funcTemplate);
}


v8::Handle<v8::ObjectTemplate> DateTimeWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	PooledIsolate* pPooledIso = PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Core.DateTime"));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "year"), year);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "month"), month);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "day"), day);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "hour"), hour);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "hour12"), hourAMPM);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "am"), isAM);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "pm"), isPM);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "minute"), minute);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "second"), second);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "dayOfWeek"), dayOfWeek);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "dayOfYear"), dayOfYear);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "julian"), julian);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "timestamp"), timestamp);
		objectTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "epoch"), epoch);

		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "daysOfMonth"), v8::FunctionTemplate::New(pIsolate, daysOfMonth));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "isLeapYear"), v8::FunctionTemplate::New(pIsolate, isLeapYear));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "addSeconds"), v8::FunctionTemplate::New(pIsolate, addSeconds));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "addHours"), v8::FunctionTemplate::New(pIsolate, addHours));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "addDays"), v8::FunctionTemplate::New(pIsolate, addDays));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "local"), v8::FunctionTemplate::New(pIsolate, local));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "format"), v8::FunctionTemplate::New(pIsolate, format));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "toString"), v8::FunctionTemplate::New(pIsolate, format));
		objectTemplate->Set(v8::String::NewFromUtf8(pIsolate, "toDate"), v8::FunctionTemplate::New(pIsolate, toDate));
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> dateTimeTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(dateTimeTemplate);
}


void DateTimeWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	Poco::DateTime* pDateTime = 0;
	try
	{
		if (args.Length() == 0)
		{
			pDateTime = new Poco::DateTime;
		}
		else
		{
			if (args[0]->IsString())
			{
				if (args.Length() > 1 && args[1]->IsString())
				{
					std::string dateTimeString = toString(args[0]);
					std::string formatString   = mapFormat(toString(args[1]));
					Poco::DateTime dt;
					int tzd;
					Poco::DateTimeParser::parse(formatString, dateTimeString, dt, tzd);
					dt.makeUTC(tzd);
					pDateTime = new Poco::DateTime(dt);
				}
				else
				{
					std::string dateTimeString = toString(args[0]);
					Poco::DateTime dt;
					int tzd;
					Poco::DateTimeParser::parse(dateTimeString, dt, tzd);
					dt.makeUTC(tzd);
					pDateTime = new Poco::DateTime(dt);
				}
			}
			else if (args[0]->IsDate())
			{
				v8::Local<v8::Date> jsDate = v8::Local<v8::Date>::Cast(args[0]);
				double millis = jsDate->ValueOf();
				Poco::Timestamp ts(static_cast<Poco::Timestamp::TimeVal>(millis*1000));
				pDateTime = new Poco::DateTime(ts);
			}
			else if (args.Length() >= 3 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber())
			{
				int year   = args[0]->Int32Value();
				int month  = args[1]->Int32Value();
				int day    = args[2]->Int32Value();
				int hour   = 0;
				int minute = 0;
				double second = 0;
				if (args.Length() >= 4 && args[3]->IsNumber()) hour = args[3]->Int32Value();
				if (args.Length() >= 5 && args[4]->IsNumber()) minute = args[4]->Int32Value();
				if (args.Length() >= 6 && args[5]->IsNumber()) second = args[5]->NumberValue();
				double fracSecond = second - std::floor(second);
				pDateTime = new Poco::DateTime(year, month, day, hour, minute, static_cast<int>(second), static_cast<int>(1000*fracSecond));
			}
			else if (args.Length() >= 1 && args[0]->IsNumber())
			{
				pDateTime = new Poco::DateTime(args[0]->NumberValue()); // Julian
			}
			else throw Poco::InvalidArgumentException("Invalid arguments to construct DateTime");
		}
		DateTimeWrapper wrapper;
		v8::Persistent<v8::Object>& dateTimeObject(wrapper.wrapNativePersistent(args.GetIsolate(), pDateTime));
		args.GetReturnValue().Set(dateTimeObject);
	}
	catch (Poco::Exception& exc)
	{
		delete pDateTime;
		returnException(args, exc);
	}
}


void DateTimeWrapper::isDateTime(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() > 0)
	{
		args.GetReturnValue().Set(Wrapper::isWrapper<Poco::DateTime>(args.GetIsolate(), args[0]));
	}
	else
	{
		args.GetReturnValue().Set(false);
	}
}


void DateTimeWrapper::year(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(info);
	info.GetReturnValue().Set(pDateTime->year());
}


void DateTimeWrapper::month(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(info);
	info.GetReturnValue().Set(pDateTime->month());
}


void DateTimeWrapper::day(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(info);
	info.GetReturnValue().Set(pDateTime->day());
}


void DateTimeWrapper::hour(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(info);
	info.GetReturnValue().Set(pDateTime->hour());
}


void DateTimeWrapper::hourAMPM(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(info);
	info.GetReturnValue().Set(pDateTime->hourAMPM());
}


void DateTimeWrapper::isAM(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(info);
	info.GetReturnValue().Set(pDateTime->isAM());
}


void DateTimeWrapper::isPM(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(info);
	info.GetReturnValue().Set(pDateTime->isPM());
}


void DateTimeWrapper::minute(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(info);
	info.GetReturnValue().Set(pDateTime->minute());
}


void DateTimeWrapper::second(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(info);
	info.GetReturnValue().Set(double(pDateTime->second()) + pDateTime->millisecond()/1000.0);
}


void DateTimeWrapper::dayOfWeek(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(info);
	info.GetReturnValue().Set(pDateTime->dayOfWeek());
}


void DateTimeWrapper::dayOfYear(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(info);
	info.GetReturnValue().Set(pDateTime->dayOfYear());
}


void DateTimeWrapper::julian(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(info);
	info.GetReturnValue().Set(pDateTime->julianDay());
}


void DateTimeWrapper::timestamp(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(info);
	info.GetReturnValue().Set(static_cast<double>(pDateTime->timestamp().epochMicroseconds()));
}


void DateTimeWrapper::epoch(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(info);
	info.GetReturnValue().Set(static_cast<Poco::UInt32>(pDateTime->timestamp().epochTime()));
}


void DateTimeWrapper::daysOfMonth(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(args);
	int year = pDateTime->year();
	int month = pDateTime->month();
	if (args.Length() > 1 && args[0]->IsNumber() && args[1]->IsNumber())
	{
		year  = args[0]->Int32Value();
		month = args[1]->Int32Value();
	}
	else if (args.Length() > 0 && args[0]->IsNumber())
	{
		month = args[0]->Int32Value();
	}
	int dom = 0;
	if (month >= 1 && month <= 12) dom = Poco::DateTime::daysOfMonth(year, month);
	args.GetReturnValue().Set(dom);
}


void DateTimeWrapper::isLeapYear(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(args);
	int year = pDateTime->year();
	if (args.Length() > 0 && args[0]->IsNumber())
	{
		year = args[0]->Int32Value();
	}
	args.GetReturnValue().Set(Poco::DateTime::isLeapYear(year));
}


void DateTimeWrapper::addSeconds(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());
	if (args.Length() > 0 && args[0]->IsNumber())
	{
		Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(args);
		double second = args[0]->NumberValue();
		double fracSecond = second - std::floor(second);
		Poco::Timespan ts(static_cast<long>(second), static_cast<long>(1000000*fracSecond));
		*pDateTime += ts;
	}
	args.GetReturnValue().Set(args.Holder());
}


void DateTimeWrapper::addHours(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());
	if (args.Length() > 0 && args[0]->IsNumber())
	{
		Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(args);
		Poco::Timespan ts(0, args[0]->Int32Value(), 0, 0, 0);
		*pDateTime += ts;
	}
	args.GetReturnValue().Set(args.Holder());
}


void DateTimeWrapper::addDays(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());
	if (args.Length() > 0 && args[0]->IsNumber())
	{
		Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(args);
		Poco::Timespan ts(args[0]->Int32Value(), 0, 0, 0, 0);
		*pDateTime += ts;
	}
	args.GetReturnValue().Set(args.Holder());
}


void DateTimeWrapper::format(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(args);
	std::string format;
	if (args.Length() > 0)
		format = mapFormat(toString(args[0]));
	else
		format = Poco::DateTimeFormat::ISO8601_FORMAT;
	try
	{
		returnString(args, Poco::DateTimeFormatter::format(*pDateTime, format));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void DateTimeWrapper::local(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(args);
	Poco::LocalDateTime* pLocalDateTime = 0;
	try
	{
		pLocalDateTime = new Poco::LocalDateTime(*pDateTime);
		LocalDateTimeWrapper wrapper;
		v8::Persistent<v8::Object>& localDateTimeObject(wrapper.wrapNativePersistent(args.GetIsolate(), pLocalDateTime));
		args.GetReturnValue().Set(localDateTimeObject);
	}
	catch (Poco::Exception& exc)
	{
		delete pLocalDateTime;
		returnException(args, exc);
	}
}


void DateTimeWrapper::toDate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());
	Poco::DateTime* pDateTime = Wrapper::unwrapNative<Poco::DateTime>(args);
	try
	{
		double millis = pDateTime->timestamp().epochMicroseconds()/1000.0;
		v8::Local<v8::Value> jsDate(v8::Date::New(args.GetIsolate(), millis));
		args.GetReturnValue().Set(jsDate);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


std::string DateTimeWrapper::mapFormat(const std::string& formatString)
{
	if (Poco::icompare(formatString, "sortable") == 0)
		return Poco::DateTimeFormat::SORTABLE_FORMAT;
	else if (Poco::icompare(formatString, "iso8601frac") == 0)
		return Poco::DateTimeFormat::ISO8601_FRAC_FORMAT;
	if (Poco::icompare(formatString, "asctime") == 0)
		return Poco::DateTimeFormat::ASCTIME_FORMAT;
	else if (Poco::icompare(formatString, "http") == 0)
		return Poco::DateTimeFormat::HTTP_FORMAT;
	else if (Poco::icompare(formatString, "iso8601") == 0)
		return Poco::DateTimeFormat::ISO8601_FORMAT;
	else if (Poco::icompare(formatString, "rfc1036") == 0)
		return Poco::DateTimeFormat::RFC1036_FORMAT;
	else if (Poco::icompare(formatString, "rfc1123") == 0)
		return Poco::DateTimeFormat::RFC1123_FORMAT;
	else if (Poco::icompare(formatString, "rfc850") == 0)
		return Poco::DateTimeFormat::RFC850_FORMAT;
	else if (Poco::icompare(formatString, "rfc822") == 0)
		return Poco::DateTimeFormat::RFC822_FORMAT;
	else
		return formatString;
}


} } } // namespace Poco::JS::Core
