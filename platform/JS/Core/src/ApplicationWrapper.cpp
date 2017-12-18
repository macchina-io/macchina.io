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
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/ApplicationWrapper.h"
#include "Poco/JS/Core/DateTimeWrapper.h"
#include "Poco/JS/Core/LoggerWrapper.h"
#include "Poco/JS/Core/ConfigurationWrapper.h"
#include "Poco/Util/Application.h"


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
	applicationTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "name"), name);
	applicationTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "startTime"), startTime);
	applicationTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "uptime"), uptime);
	applicationTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "config"), config);
	applicationTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "logger"), logger);
	return handleScope.Escape(applicationTemplate);
}


void ApplicationWrapper::name(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::HandleScope scope(info.GetIsolate());
	try
	{
		Poco::Util::Application& app = Poco::Util::Application::instance();
		returnString(info, app.commandName());
	}
	catch (...)
	{
		info.GetReturnValue().Set(v8::Null(info.GetIsolate()));
	}
}


void ApplicationWrapper::startTime(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::HandleScope scope(info.GetIsolate());
	try
	{
		Poco::Util::Application& app = Poco::Util::Application::instance();
		Poco::DateTime* pDateTime = new Poco::DateTime(app.startTime());
		DateTimeWrapper wrapper;
		v8::Persistent<v8::Object>& dateTimeObject(wrapper.wrapNativePersistent(info.GetIsolate(), pDateTime));
		info.GetReturnValue().Set(dateTimeObject);
	}
	catch (...)
	{
		info.GetReturnValue().Set(v8::Null(info.GetIsolate()));
	}
}


void ApplicationWrapper::uptime(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::HandleScope scope(info.GetIsolate());
	try
	{
		Poco::Util::Application& app = Poco::Util::Application::instance();
		double uptime = app.uptime().totalMilliseconds()/1000.0;
		info.GetReturnValue().Set(uptime);
	}
	catch (...)
	{
		info.GetReturnValue().Set(v8::Null(info.GetIsolate()));
	}
}


void ApplicationWrapper::config(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::HandleScope scope(info.GetIsolate());
	try
	{
		Poco::Util::Application& app = Poco::Util::Application::instance();
		ConfigurationWrapper wrapper;
		v8::Local<v8::Object> configurationObject = wrapper.wrapNative(info.GetIsolate(), const_cast<Poco::Util::LayeredConfiguration*>(&app.config()));
		info.GetReturnValue().Set(configurationObject);
	}
	catch (...)
	{
		info.GetReturnValue().Set(v8::Null(info.GetIsolate()));
	}
}


void ApplicationWrapper::logger(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::HandleScope scope(info.GetIsolate());
	try
	{
		Poco::Util::Application& app = Poco::Util::Application::instance();
		Poco::JS::Core::LoggerWrapper wrapper;
		v8::Local<v8::Object> loggerObject = wrapper.wrapNative(info.GetIsolate(), &app.logger());
		info.GetReturnValue().Set(loggerObject);
	}
	catch (...)
	{
		info.GetReturnValue().Set(v8::Null(info.GetIsolate()));
	}
}


} } } // namespace Poco::JS::Core
