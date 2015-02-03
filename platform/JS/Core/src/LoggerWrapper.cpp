//
// LoggerWrapper.cpp
//
// $Id: //poco/1.4/JS/Core/src/LoggerWrapper.cpp#5 $
//
// Library: JSCore
// Package: JSCore
// Module:  LoggerWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/LoggerWrapper.h"
#include "Poco/Logger.h"
#include "Poco/NumberParser.h"


namespace Poco {
namespace JS {
namespace Core {


LoggerWrapper::LoggerWrapper()
{
}


LoggerWrapper::~LoggerWrapper()
{
}


v8::Handle<v8::ObjectTemplate> LoggerWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::ObjectTemplate> loggerTemplate = v8::ObjectTemplate::New();
	loggerTemplate->SetInternalFieldCount(1);
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "trace"), v8::FunctionTemplate::New(pIsolate, trace));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "debug"), v8::FunctionTemplate::New(pIsolate, debug));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "information"), v8::FunctionTemplate::New(pIsolate, information));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "notice"), v8::FunctionTemplate::New(pIsolate, notice));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "warning"), v8::FunctionTemplate::New(pIsolate, warning));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "error"), v8::FunctionTemplate::New(pIsolate, error));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "critical"), v8::FunctionTemplate::New(pIsolate, critical));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "fatal"), v8::FunctionTemplate::New(pIsolate, fatal));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "log"), v8::FunctionTemplate::New(pIsolate, log));
	return handleScope.Escape(loggerTemplate);
}
	

void LoggerWrapper::log(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	v8::HandleScope scope(args.GetIsolate());
	std::string prioStr = toString(args[0]);
	int prio = 0;
	try
	{
		if (!Poco::NumberParser::tryParse(prioStr, prio))
		{
			prio = Poco::Logger::parseLevel(prioStr);
		}
		Poco::Logger* pLogger = Wrapper::unwrapNative<Poco::Logger>(args);
		if (pLogger->is(prio))
		{
			for (int i = 1; i < args.Length(); i++)
			{
				v8::String::Utf8Value value(args[i]);
				Poco::Message msg(pLogger->name(), std::string(*value), static_cast<Poco::Message::Priority>(prio));
				pLogger->log(msg);
			}
		}
	}
	catch (...)
	{
	}
}


void LoggerWrapper::log2(Poco::Message::Priority prio, const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::HandleScope scope(args.GetIsolate());
	Poco::Logger* pLogger = Wrapper::unwrapNative<Poco::Logger>(args);
	try
	{
		if (pLogger->is(prio))
		{
			for (int i = 0; i < args.Length(); i++)
			{
				Poco::Message msg(pLogger->name(), toString(args[i]), static_cast<Poco::Message::Priority>(prio));
				pLogger->log(msg);
			}
		}
	}
	catch (...)
	{
	}
}


void LoggerWrapper::trace(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	log2(Poco::Message::PRIO_TRACE, args);
}


void LoggerWrapper::debug(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	log2(Poco::Message::PRIO_DEBUG, args);
}


void LoggerWrapper::information(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	log2(Poco::Message::PRIO_INFORMATION, args);
}


void LoggerWrapper::notice(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	log2(Poco::Message::PRIO_NOTICE, args);
}


void LoggerWrapper::warning(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	log2(Poco::Message::PRIO_WARNING, args);
}


void LoggerWrapper::error(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	log2(Poco::Message::PRIO_ERROR, args);
}


void LoggerWrapper::critical(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	log2(Poco::Message::PRIO_CRITICAL, args);
}


void LoggerWrapper::fatal(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	log2(Poco::Message::PRIO_FATAL, args);
}


} } } // namespace Poco::JS::Core
