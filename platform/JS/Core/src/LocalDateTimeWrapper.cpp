//
// LocalDateTimeWrapper.cpp
//
// Library: JS/Core
// Package: Wrappers
// Module:  LocalDateTimeWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/LocalDateTimeWrapper.h"
#include "Poco/JS/Core/DateTimeWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/Timespan.h"
#include "Poco/Exception.h"
#include "Poco/String.h"
#include <cmath>


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Core {


LocalDateTimeWrapper::LocalDateTimeWrapper()
{
}


LocalDateTimeWrapper::~LocalDateTimeWrapper()
{
}


v8::Handle<v8::FunctionTemplate> LocalDateTimeWrapper::constructor(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::FunctionTemplate> funcTemplate = v8::FunctionTemplate::New(pIsolate, construct);
	funcTemplate->Set(toV8String(pIsolate, "isLocalDateTime"s), v8::FunctionTemplate::New(pIsolate, isLocalDateTime));
	return handleScope.Escape(funcTemplate);
}


v8::Handle<v8::ObjectTemplate> LocalDateTimeWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	PooledIsolate* pPooledIso = PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledObjectTemplate(pPooledIso->objectTemplate("Core.LocalDateTime"s));
	if (pooledObjectTemplate.IsEmpty())
	{
		v8::Handle<v8::ObjectTemplate> objectTemplate = v8::ObjectTemplate::New(pIsolate);
		objectTemplate->SetInternalFieldCount(1);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "year"s), year);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "month"s), month);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "day"s), day);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "hour"s), hour);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "hour12"s), hourAMPM);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "am"s), isAM);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "pm"s), isPM);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "minute"s), minute);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "second"s), second);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "dayOfWeek"s), dayOfWeek);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "dayOfYear"s), dayOfYear);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "julian"s), julian);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "timestamp"s), timestamp);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "epoch"s), epoch);
		objectTemplate->SetAccessor(toV8Internalized(pIsolate, "tzd"s), tzd);

		objectTemplate->Set(toV8Internalized(pIsolate, "daysOfMonth"s), v8::FunctionTemplate::New(pIsolate, daysOfMonth));
		objectTemplate->Set(toV8Internalized(pIsolate, "isLeapYear"s), v8::FunctionTemplate::New(pIsolate, isLeapYear));
		objectTemplate->Set(toV8Internalized(pIsolate, "addSeconds"s), v8::FunctionTemplate::New(pIsolate, addSeconds));
		objectTemplate->Set(toV8Internalized(pIsolate, "addHours"s), v8::FunctionTemplate::New(pIsolate, addHours));
		objectTemplate->Set(toV8Internalized(pIsolate, "addDays"s), v8::FunctionTemplate::New(pIsolate, addDays));
		objectTemplate->Set(toV8Internalized(pIsolate, "utc"s), v8::FunctionTemplate::New(pIsolate, utc));
		objectTemplate->Set(toV8Internalized(pIsolate, "format"s), v8::FunctionTemplate::New(pIsolate, format));
		objectTemplate->Set(toV8Internalized(pIsolate, "toString"s), v8::FunctionTemplate::New(pIsolate, format));
		objectTemplate->Set(toV8Internalized(pIsolate, "toDate"s), v8::FunctionTemplate::New(pIsolate, toDate));
		objectTemplate->Set(toV8Internalized(pIsolate, "toJSON"s), v8::FunctionTemplate::New(pIsolate, toJSON));
		pooledObjectTemplate.Reset(pIsolate, objectTemplate);
	}
	v8::Local<v8::ObjectTemplate> localDateTimeTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledObjectTemplate);
	return handleScope.Escape(localDateTimeTemplate);
}


void LocalDateTimeWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Poco::LocalDateTime* pLocalDateTime = 0;
	try
	{
		if (args.Length() == 0)
		{
			pLocalDateTime = new Poco::LocalDateTime;
		}
		else
		{
			if (args[0]->IsString())
			{
				if (args.Length() > 1 && args[1]->IsString())
				{
					std::string dateTimeString = toString(pIsolate, args[0]);
					std::string formatString   = DateTimeWrapper::mapFormat(toString(pIsolate, args[1]));
					Poco::DateTime dt;
					int tzd;
					Poco::DateTimeParser::parse(formatString, dateTimeString, dt, tzd);
					dt.makeUTC(tzd);
					pLocalDateTime = new Poco::LocalDateTime(dt);
				}
				else
				{
					std::string dateTimeString = toString(pIsolate, args[0]);
					Poco::DateTime dt;
					int tzd;
					Poco::DateTimeParser::parse(dateTimeString, dt, tzd);
					dt.makeUTC(tzd);
					pLocalDateTime = new Poco::LocalDateTime(dt);
				}
			}
			else if (args[0]->IsDate())
			{
				v8::Local<v8::Date> jsDate = v8::Local<v8::Date>::Cast(args[0]);
				double millis = jsDate->ValueOf();
				Poco::Timestamp ts(static_cast<Poco::Timestamp::TimeVal>(millis*1000));
				Poco::DateTime dateTime(ts);
				pLocalDateTime = new Poco::LocalDateTime(dateTime);
			}
			else if (args.Length() >= 3 && args[0]->IsNumber() && args[1]->IsNumber() && args[2]->IsNumber())
			{
				int year   = args[0]->Int32Value(context).FromMaybe(0);
				int month  = args[1]->Int32Value(context).FromMaybe(0);
				int day    = args[2]->Int32Value(context).FromMaybe(0);
				int hour   = 0;
				int minute = 0;
				double second = 0;
				if (args.Length() >= 4 && args[3]->IsNumber()) hour = args[3]->Int32Value(context).FromMaybe(0);
				if (args.Length() >= 5 && args[4]->IsNumber()) minute = args[4]->Int32Value(context).FromMaybe(0);
				if (args.Length() >= 6 && args[5]->IsNumber()) second = args[5]->NumberValue(context).FromMaybe(0);
				double fracSecond = second - std::floor(second);
				pLocalDateTime = new Poco::LocalDateTime(year, month, day, hour, minute, static_cast<long>(second), static_cast<int>(1000*fracSecond));
			}
			else if (args.Length() >= 1 && args[0]->IsNumber())
			{
				pLocalDateTime = new Poco::LocalDateTime(args[0]->NumberValue(context).FromMaybe(0.0)); // Julian
			}
			else throw Poco::InvalidArgumentException("Invalid arguments to construct LocalDateTime");
		}
		LocalDateTimeWrapper wrapper;
		v8::Persistent<v8::Object>& dateTimeObject(wrapper.wrapNativePersistent(args.GetIsolate(), pLocalDateTime));
		args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, dateTimeObject));
	}
	catch (Poco::Exception& exc)
	{
		delete pLocalDateTime;
		returnException(args, exc);
	}
}


void LocalDateTimeWrapper::isLocalDateTime(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() > 0)
	{
		args.GetReturnValue().Set(Wrapper::isWrapper<Poco::LocalDateTime>(args.GetIsolate(), args[0]));
	}
	else
	{
		args.GetReturnValue().Set(false);
	}
}


void LocalDateTimeWrapper::year(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(info);
	info.GetReturnValue().Set(pLocalDateTime->year());
}


void LocalDateTimeWrapper::month(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(info);
	info.GetReturnValue().Set(pLocalDateTime->month());
}


void LocalDateTimeWrapper::day(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(info);
	info.GetReturnValue().Set(pLocalDateTime->day());
}


void LocalDateTimeWrapper::hour(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(info);
	info.GetReturnValue().Set(pLocalDateTime->hour());
}


void LocalDateTimeWrapper::hourAMPM(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(info);
	info.GetReturnValue().Set(pLocalDateTime->hourAMPM());
}


void LocalDateTimeWrapper::isAM(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(info);
	info.GetReturnValue().Set(pLocalDateTime->isAM());
}


void LocalDateTimeWrapper::isPM(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(info);
	info.GetReturnValue().Set(pLocalDateTime->isPM());
}


void LocalDateTimeWrapper::minute(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(info);
	info.GetReturnValue().Set(pLocalDateTime->minute());
}


void LocalDateTimeWrapper::second(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(info);
	info.GetReturnValue().Set(double(pLocalDateTime->second()) + pLocalDateTime->millisecond()/1000.0);
}


void LocalDateTimeWrapper::dayOfWeek(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(info);
	info.GetReturnValue().Set(pLocalDateTime->dayOfWeek());
}


void LocalDateTimeWrapper::dayOfYear(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(info);
	info.GetReturnValue().Set(pLocalDateTime->dayOfYear());
}


void LocalDateTimeWrapper::julian(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(info);
	info.GetReturnValue().Set(pLocalDateTime->julianDay());
}


void LocalDateTimeWrapper::timestamp(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(info);
	info.GetReturnValue().Set(static_cast<double>(pLocalDateTime->timestamp().epochMicroseconds()));
}


void LocalDateTimeWrapper::epoch(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(info);
	info.GetReturnValue().Set(static_cast<Poco::UInt32>(pLocalDateTime->timestamp().epochTime()));
}


void LocalDateTimeWrapper::tzd(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(info);
	info.GetReturnValue().Set(static_cast<Poco::Int32>(pLocalDateTime->tzd()));
}


void LocalDateTimeWrapper::daysOfMonth(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(args);
	int year = pLocalDateTime->year();
	int month = pLocalDateTime->month();
	if (args.Length() > 1 && args[0]->IsNumber() && args[1]->IsNumber())
	{
		year  = args[0]->Int32Value(context).FromMaybe(0);
		month = args[1]->Int32Value(context).FromMaybe(0);
	}
	else if (args.Length() > 0 && args[0]->IsNumber())
	{
		month = args[0]->Int32Value(context).FromMaybe(0);
	}
	int dom = 0;
	if (month >= 1 && month <= 12) dom = Poco::DateTime::daysOfMonth(year, month);
	args.GetReturnValue().Set(dom);
}


void LocalDateTimeWrapper::isLeapYear(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(args);
	int year = pLocalDateTime->year();
	if (args.Length() > 0 && args[0]->IsNumber())
	{
		year = args[0]->Int32Value(context).FromMaybe(0);
	}
	args.GetReturnValue().Set(Poco::DateTime::isLeapYear(year));
}


void LocalDateTimeWrapper::addSeconds(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0 && args[0]->IsNumber())
	{
		Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(args);
		double second = args[0]->NumberValue(context).FromMaybe(0.0);
		double fracSecond = second - std::floor(second);
		Poco::Timespan ts(static_cast<long>(second), static_cast<long>(1000000*fracSecond));
		*pLocalDateTime += ts;
	}
	args.GetReturnValue().Set(args.Holder());
}


void LocalDateTimeWrapper::addHours(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0 && args[0]->IsNumber())
	{
		Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(args);
		Poco::Timespan ts(0, args[0]->Int32Value(context).FromMaybe(0), 0, 0, 0);
		*pLocalDateTime += ts;
	}
	args.GetReturnValue().Set(args.Holder());
}


void LocalDateTimeWrapper::addDays(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	if (args.Length() > 0 && args[0]->IsNumber())
	{
		Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(args);
		Poco::Timespan ts(args[0]->Int32Value(context).FromMaybe(0), 0, 0, 0, 0);
		*pLocalDateTime += ts;
	}
	args.GetReturnValue().Set(args.Holder());
}


void LocalDateTimeWrapper::format(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(args);
	std::string format;
	if (args.Length() > 0)
		format = DateTimeWrapper::mapFormat(toString(pIsolate, args[0]));
	else
		format = Poco::DateTimeFormat::ISO8601_FORMAT;
	try
	{
		returnString(args, Poco::DateTimeFormatter::format(*pLocalDateTime, format));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void LocalDateTimeWrapper::toDate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(args);
	try
	{
		double millis = pLocalDateTime->utc().timestamp().epochMicroseconds()/1000.0;
		v8::MaybeLocal<v8::Value> maybeJSDate(v8::Date::New(pIsolate->GetCurrentContext(), millis));
		v8::Local<v8::Value> jsDate;
		if (maybeJSDate.ToLocal(&jsDate))
		{
			args.GetReturnValue().Set(jsDate);
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void LocalDateTimeWrapper::toJSON(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope scope(args.GetIsolate());
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(args);
	try
	{
		returnString(args, Poco::DateTimeFormatter::format(*pLocalDateTime, Poco::DateTimeFormat::ISO8601_FRAC_FORMAT));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void LocalDateTimeWrapper::utc(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Poco::LocalDateTime* pLocalDateTime = Wrapper::unwrapNative<Poco::LocalDateTime>(args);
	Poco::DateTime* pDateTime = 0;
	try
	{
		pDateTime = new Poco::DateTime(pLocalDateTime->utc());
		DateTimeWrapper wrapper;
		v8::Persistent<v8::Object>& dateTimeObject(wrapper.wrapNativePersistent(pIsolate, pDateTime));
		args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, dateTimeObject));
	}
	catch (Poco::Exception& exc)
	{
		delete pDateTime;
		returnException(args, exc);
	}
}


} } } // namespace Poco::JS::Core
