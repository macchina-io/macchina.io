//
// LoggerWrapper.cpp
//
// $Id: //poco/1.4/JS/Core/src/LoggerWrapper.cpp#5 $
//
// Library: JSCore
// Package: JSCore
// Module:  LoggerWrapper
//
// Copyright (c) 2013-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/LoggerWrapper.h"
#include "Poco/Logger.h"
#include "Poco/NumberParser.h"
#include "Poco/NumberFormatter.h"


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

	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "TRACE"), v8::Integer::New(pIsolate, 8));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "DEBUG"), v8::Integer::New(pIsolate, 7));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "INFORMATION"), v8::Integer::New(pIsolate, 6));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "NOTICE"), v8::Integer::New(pIsolate, 5));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "WARNING"), v8::Integer::New(pIsolate, 4));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "ERROR"), v8::Integer::New(pIsolate, 3));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "CRITICAL"), v8::Integer::New(pIsolate, 2));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "FATAL"), v8::Integer::New(pIsolate, 1));

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
		format(prio, args, 1);
	}
	catch (...)
	{
	}
}


void LoggerWrapper::format(int prio, const v8::FunctionCallbackInfo<v8::Value>& args, int firstArgIndex, const std::string& prefix)
{
	if (args.Length() <= firstArgIndex) return;
	v8::HandleScope scope(args.GetIsolate());
	Poco::Logger* pLogger = Wrapper::unwrapNative<Poco::Logger>(args);
	try
	{
		if (pLogger->is(prio))
		{
			std::string text(prefix);
			int nextArgIndex = firstArgIndex;
			if (args[nextArgIndex]->IsString())
			{
				std::string fmt(toString(args[nextArgIndex]));
				nextArgIndex++;
				std::string::const_iterator it = fmt.begin(); 
				while (it != fmt.end())
				{
					if (*it == '%')
					{
						++it;
						if (it != fmt.end())
						{
							switch (*it)
							{
							case 'd':
							case 'i':
								if (nextArgIndex < args.Length())
								{
									if (args[nextArgIndex]->IsNumber())
									{
										Poco::Int64 intValue = args[nextArgIndex]->IntegerValue();
										Poco::NumberFormatter::append(text, intValue);
									}
									else
									{
										text.append(toString(args[nextArgIndex]));
									}
								}
								nextArgIndex++;
								break;
							case 'f':
								if (nextArgIndex < args.Length())
								{
									if (args[nextArgIndex]->IsNumber())
									{
										double doubleValue = args[nextArgIndex]->NumberValue();
										Poco::NumberFormatter::append(text, doubleValue);
									}
									else
									{
										text.append(toString(args[nextArgIndex]));
									}
								}
								nextArgIndex++;
								break;
							case 's':
								if (nextArgIndex < args.Length())
								{
									text.append(toString(args[nextArgIndex]));
								}
								nextArgIndex++;
								break;
							case 'o':
								if (nextArgIndex < args.Length())
								{
									// use built-in JSON.stringify() 
									v8::Local<v8::Context> context = args.GetIsolate()->GetCurrentContext();
									v8::Local<v8::Object> global = context->Global();
									v8::Local<v8::Object> json = global->Get(v8::String::NewFromUtf8(args.GetIsolate(), "JSON"))->ToObject();
									v8::Local<v8::Function> stringify = v8::Handle<v8::Function>::Cast(json->Get(v8::String::NewFromUtf8(args.GetIsolate(), "stringify")));
									v8::Local<v8::Value> argv[1] = {args[nextArgIndex]};
									text.append(toString(stringify->Call(json, 1, argv)));
								}
								nextArgIndex++;
								break;
							case '%':
								text += '%';
								break;
							default:
								text += '%';
								text += *it;
								break;
							}
							it++;
						}
					}
					else text += *it++;
				}
			}
			for (int i = nextArgIndex; i < args.Length(); i++)
			{
				text.append(toString(args[i]));
			}
			Poco::Message msg(pLogger->name(), text, static_cast<Poco::Message::Priority>(prio));
			pLogger->log(msg);
		}
	}
	catch (...)
	{
	}
}


void LoggerWrapper::trace(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	format(Poco::Message::PRIO_TRACE, args);
}


void LoggerWrapper::debug(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	format(Poco::Message::PRIO_DEBUG, args);
}


void LoggerWrapper::information(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	format(Poco::Message::PRIO_INFORMATION, args);
}


void LoggerWrapper::notice(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	format(Poco::Message::PRIO_NOTICE, args);
}


void LoggerWrapper::warning(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	format(Poco::Message::PRIO_WARNING, args);
}


void LoggerWrapper::error(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	format(Poco::Message::PRIO_ERROR, args);
}


void LoggerWrapper::critical(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	format(Poco::Message::PRIO_CRITICAL, args);
}


void LoggerWrapper::fatal(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	format(Poco::Message::PRIO_FATAL, args);
}


} } } // namespace Poco::JS::Core
