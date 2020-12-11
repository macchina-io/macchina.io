//
// ApplicationWrapper.cpp
//
// Library: JS/Core
// Package: Wrappers
// Module:  ApplicationWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/ApplicationWrapper.h"
#include "Poco/JS/Core/DateTimeWrapper.h"
#include "Poco/JS/Core/LoggerWrapper.h"
#include "Poco/JS/Core/ConfigurationWrapper.h"
#include "Poco/Util/Application.h"


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Core {


ApplicationWrapper::ApplicationWrapper()
{
}


ApplicationWrapper::~ApplicationWrapper()
{
}


v8::Handle<v8::ObjectTemplate> ApplicationWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::ObjectTemplate> applicationTemplate = v8::ObjectTemplate::New(pIsolate);
	applicationTemplate->SetInternalFieldCount(1);
	applicationTemplate->SetAccessor(toV8Internalized(pIsolate, "name"s), name);
	applicationTemplate->SetAccessor(toV8Internalized(pIsolate, "startTime"s), startTime);
	applicationTemplate->SetAccessor(toV8Internalized(pIsolate, "uptime"s), uptime);
	applicationTemplate->SetAccessor(toV8Internalized(pIsolate, "config"s), config);
	applicationTemplate->SetAccessor(toV8Internalized(pIsolate, "logger"s), logger);
	return handleScope.Escape(applicationTemplate);
}


void ApplicationWrapper::name(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);
	try
	{
		Poco::Util::Application& app = Poco::Util::Application::instance();
		returnString(info, app.commandName());
	}
	catch (...)
	{
		info.GetReturnValue().Set(v8::Null(pIsolate));
	}
}


void ApplicationWrapper::startTime(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);
	try
	{
		Poco::Util::Application& app = Poco::Util::Application::instance();
		Poco::DateTime* pDateTime = new Poco::DateTime(app.startTime());
		DateTimeWrapper wrapper;
		v8::Persistent<v8::Object>& dateTimeObject(wrapper.wrapNativePersistent(pIsolate, pDateTime));
		info.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, dateTimeObject));
	}
	catch (...)
	{
		info.GetReturnValue().Set(v8::Null(pIsolate));
	}
}


void ApplicationWrapper::uptime(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);
	try
	{
		Poco::Util::Application& app = Poco::Util::Application::instance();
		double uptime = app.uptime().totalMilliseconds()/1000.0;
		info.GetReturnValue().Set(uptime);
	}
	catch (...)
	{
		info.GetReturnValue().Set(v8::Null(pIsolate));
	}
}


void ApplicationWrapper::config(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);
	try
	{
		Poco::Util::Application& app = Poco::Util::Application::instance();
		ConfigurationWrapper wrapper;
		v8::MaybeLocal<v8::Object> maybeConfigurationObject = wrapper.wrapNative(pIsolate, const_cast<Poco::Util::LayeredConfiguration*>(&app.config()));
		v8::Local<v8::Object> configurationObject;
		if (maybeConfigurationObject.ToLocal(&configurationObject))
		{
			info.GetReturnValue().Set(configurationObject);
		}
	}
	catch (...)
	{
		info.GetReturnValue().Set(v8::Null(pIsolate));
	}
}


void ApplicationWrapper::logger(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);
	try
	{
		Poco::Util::Application& app = Poco::Util::Application::instance();
		Poco::JS::Core::LoggerWrapper wrapper;
		v8::MaybeLocal<v8::Object> maybeLoggerObject = wrapper.wrapNative(pIsolate, &app.logger());
		v8::Local<v8::Object> loggerObject;
		if (maybeLoggerObject.ToLocal(&loggerObject))
		{
			info.GetReturnValue().Set(loggerObject);
		}
	}
	catch (...)
	{
		info.GetReturnValue().Set(v8::Null(pIsolate));
	}
}


} } } // namespace Poco::JS::Core
