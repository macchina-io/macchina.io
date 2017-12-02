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
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/ConsoleWrapper.h"
#include "Poco/JS/Core/LoggerWrapper.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Logger.h"


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
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "trace"), v8::FunctionTemplate::New(pIsolate, trace));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "assert"), v8::FunctionTemplate::New(pIsolate, assert));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "log"), v8::FunctionTemplate::New(pIsolate, log));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "debug"), v8::FunctionTemplate::New(pIsolate, debug));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "info"), v8::FunctionTemplate::New(pIsolate, info));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "warn"), v8::FunctionTemplate::New(pIsolate, warn));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "error"), v8::FunctionTemplate::New(pIsolate, error));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "dump"), v8::FunctionTemplate::New(pIsolate, dump));
	return handleScope.Escape(loggerTemplate);
}


void ConsoleWrapper::trace(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	std::string text("Stack Trace:")	;
	v8::HandleScope scope(args.GetIsolate());
	v8::Local<v8::StackTrace> stackTrace = v8::StackTrace::CurrentStackTrace(args.GetIsolate(), 128, v8::StackTrace::kDetailed);
	for (int i = 0; i < stackTrace->GetFrameCount(); i++)
	{
		text.append("\n  Frame #");
		Poco::NumberFormatter::append(text, i);
		v8::Local<v8::StackFrame> frame = stackTrace->GetFrame(i);

		v8::Local<v8::String> function = frame->GetFunctionName();
		if (!function.IsEmpty())
		{
			std::string functionName(toString(frame->GetFunctionName()));
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
			text.append(toString(script));
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


void ConsoleWrapper::assert(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	if (!args[0]->BooleanValue())
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
