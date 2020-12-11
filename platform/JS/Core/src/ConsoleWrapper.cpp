//
// ConsoleWrapper.cpp
//
// Library: JS/Core
// Package: Wrappers
// Module:  ConsoleWrapper
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/ConsoleWrapper.h"
#include "Poco/JS/Core/LoggerWrapper.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Logger.h"


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Core {


ConsoleWrapper::ConsoleWrapper()
{
}


ConsoleWrapper::~ConsoleWrapper()
{
}


v8::Handle<v8::ObjectTemplate> ConsoleWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::ObjectTemplate> loggerTemplate = v8::ObjectTemplate::New(pIsolate);
	loggerTemplate->SetInternalFieldCount(1);
	loggerTemplate->Set(toV8Internalized(pIsolate, "trace"s), v8::FunctionTemplate::New(pIsolate, trace));
	loggerTemplate->Set(toV8Internalized(pIsolate, "assert"s), v8::FunctionTemplate::New(pIsolate, xassert));
	loggerTemplate->Set(toV8Internalized(pIsolate, "log"s), v8::FunctionTemplate::New(pIsolate, log));
	loggerTemplate->Set(toV8Internalized(pIsolate, "debug"s), v8::FunctionTemplate::New(pIsolate, debug));
	loggerTemplate->Set(toV8Internalized(pIsolate, "info"s), v8::FunctionTemplate::New(pIsolate, info));
	loggerTemplate->Set(toV8Internalized(pIsolate, "warn"s), v8::FunctionTemplate::New(pIsolate, warn));
	loggerTemplate->Set(toV8Internalized(pIsolate, "error"s), v8::FunctionTemplate::New(pIsolate, error));
	loggerTemplate->Set(toV8Internalized(pIsolate, "dump"s), v8::FunctionTemplate::New(pIsolate, dump));
	return handleScope.Escape(loggerTemplate);
}


void ConsoleWrapper::trace(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	std::string text("Stack Trace:")	;
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::StackTrace> stackTrace = v8::StackTrace::CurrentStackTrace(pIsolate, 128, v8::StackTrace::kDetailed);
	for (int i = 0; i < stackTrace->GetFrameCount(); i++)
	{
		text.append("\n  Frame #");
		Poco::NumberFormatter::append(text, i);
		v8::Local<v8::StackFrame> frame = stackTrace->GetFrame(pIsolate, i);

		v8::Local<v8::String> function = frame->GetFunctionName();
		if (!function.IsEmpty())
		{
			std::string functionName(toString(pIsolate, frame->GetFunctionName()));
			if (!functionName.empty())
			{
				text.append(" ");
				text.append(functionName);
				text.append("()");
			}
		}
		text.append(" at ");
		v8::Local<v8::String> script = frame->GetScriptNameOrSourceURL();
		if (script.IsEmpty())
		{
			text.append("<unknown>");
		}
		else
		{
			text.append("\"");
			text.append(toString(pIsolate, script));
			text.append("\"");
		}
		if (frame->GetLineNumber() > 0)
		{
			text.append(", line ");
			Poco::NumberFormatter::append(text, frame->GetLineNumber());
		}
	}
	Poco::Logger* pLogger = Wrapper::unwrapNative<Poco::Logger>(args);
	pLogger->debug(text);
}


void ConsoleWrapper::xassert(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	if (!args[0]->BooleanValue(args.GetIsolate()))
	{
		LoggerWrapper::format(Poco::Message::PRIO_ERROR, args, 1, "Assertion failed: ");
		trace(args);
	}
}


void ConsoleWrapper::log(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	LoggerWrapper::format(Poco::Message::PRIO_INFORMATION, args);
}


void ConsoleWrapper::debug(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	LoggerWrapper::format(Poco::Message::PRIO_DEBUG, args);
}


void ConsoleWrapper::info(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	LoggerWrapper::format(Poco::Message::PRIO_INFORMATION, args);
}


void ConsoleWrapper::warn(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	LoggerWrapper::format(Poco::Message::PRIO_WARNING, args);
}


void ConsoleWrapper::error(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	LoggerWrapper::format(Poco::Message::PRIO_ERROR, args);
}


void ConsoleWrapper::dump(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	LoggerWrapper::dump(args);
}


} } } // namespace Poco::JS::Core
