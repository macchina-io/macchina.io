//
// DateTimeWrapper.h
//
// Library: JS/Core
// Package: Wrappers
// Module:  DateTimeWrapper
//
// Definition of the DateTimeWrapper interface.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef JS_Core_DateTimeWrapper_INCLUDED
#define JS_Core_DateTimeWrapper_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Wrapper.h"
#include "Poco/DateTime.h"


namespace Poco {
namespace JS {
namespace Core {


class JSCore_API DateTimeWrapper: public Wrapper
	/// JavaScript wrapper for Poco::DateTime.
{
public:
	DateTimeWrapper();
		/// Creates the DateTimeWrapper.

	~DateTimeWrapper();
		/// Destroys the DateTimeWrapper.

	v8::Handle<v8::FunctionTemplate> constructor(v8::Isolate* pIsolate);
		/// Creates and returns a V8 FunctionTemplate for the constructor function.

	// Wrapper
	v8::Handle<v8::ObjectTemplate> objectTemplate(v8::Isolate* pIsolate);

protected:
	static void construct(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void isDateTime(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void year(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void month(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void day(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void hour(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void hourAMPM(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void isAM(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void isPM(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void minute(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void second(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void dayOfWeek(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void dayOfYear(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void julian(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void timestamp(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void epoch(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info);
	static void daysOfMonth(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void isLeapYear(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void addSeconds(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void addHours(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void addDays(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void local(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void format(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void toDate(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void toJSON(const v8::FunctionCallbackInfo<v8::Value>& args);
	static std::string mapFormat(const std::string& formatString);

	friend class LocalDateTimeWrapper;
};


} } } // namespace Poco::JS::Core


#endif // JS_Core_DateTimeWrapper_INCLUDED
