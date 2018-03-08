//
// LoggerWrapper.cpp
//
// Library: JS/Core
// Package: Wrappers
// Module:  LoggerWrapper
//
// Copyright (c) 2013-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/LoggerWrapper.h"
#include "Poco/JS/Core/BufferWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/Logger.h"
#include "Poco/LoggingFactory.h"
#include "Poco/LoggingRegistry.h"
#include "Poco/FormattingChannel.h"
#include "Poco/PatternFormatter.h"
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


v8::Handle<v8::FunctionTemplate> LoggerWrapper::constructor(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::FunctionTemplate> funcTemplate = v8::FunctionTemplate::New(pIsolate, construct);
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "TRACE"), v8::Integer::New(pIsolate, 8));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "DEBUG"), v8::Integer::New(pIsolate, 7));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "INFORMATION"), v8::Integer::New(pIsolate, 6));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "NOTICE"), v8::Integer::New(pIsolate, 5));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "WARNING"), v8::Integer::New(pIsolate, 4));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "ERROR"), v8::Integer::New(pIsolate, 3));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "CRITICAL"), v8::Integer::New(pIsolate, 2));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "FATAL"), v8::Integer::New(pIsolate, 1));
	funcTemplate->Set(v8::String::NewFromUtf8(pIsolate, "isLogger"), v8::FunctionTemplate::New(pIsolate, isLogger));

	return handleScope.Escape(funcTemplate);
}


v8::Handle<v8::ObjectTemplate> LoggerWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	PooledIsolate* pPooledIso = PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledLoggerTemplate(pPooledIso->objectTemplate("Core.Logger"));
	if (pooledLoggerTemplate.IsEmpty())
	{
		v8::Local<v8::ObjectTemplate> loggerTemplate = v8::ObjectTemplate::New(pIsolate);
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
		loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "dump"), v8::FunctionTemplate::New(pIsolate, dump));
		pooledLoggerTemplate.Reset(pIsolate, loggerTemplate);
	}
	v8::Local<v8::ObjectTemplate> localLoggerTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledLoggerTemplate);
	return handleScope.Escape(localLoggerTemplate);
}


void LoggerWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::HandleScope handleScope(args.GetIsolate());

	Poco::Logger* pLogger = 0;
	try
	{
		if (args.Length() > 1 && !args[1]->IsObject())
			throw Poco::InvalidArgumentException("Second argument must be configuration object");

		std::string loggerName;
		if (args.Length() > 0)
		{
			loggerName = toString(args[0]);
		}

		bool isExistingLogger = Poco::Logger::has(loggerName) != 0;
		bool reconfigure = args.Length() > 2 && args[2]->BooleanValue();

		pLogger = &Poco::Logger::get(loggerName);

		if ((!isExistingLogger || reconfigure) && args.Length() > 1 && args[1]->IsObject())
		{
			v8::Local<v8::String> levelProp = v8::String::NewFromUtf8(args.GetIsolate(), "level");
			v8::Local<v8::String> patternProp = v8::String::NewFromUtf8(args.GetIsolate(), "pattern");
			v8::Local<v8::String> channelProp = v8::String::NewFromUtf8(args.GetIsolate(), "channel");
			v8::Local<v8::String> classProp = v8::String::NewFromUtf8(args.GetIsolate(), "class");

			v8::Local<v8::Object> config = args[1].As<v8::Object>();
			Poco::AutoPtr<Poco::Channel> pChannel;

			if (config->Has(levelProp))
			{
				std::string level = toString(config->Get(levelProp));
				pLogger->setLevel(level);
			}

			if (config->Has(channelProp))
			{
				v8::Local<v8::Value> channelArg = config->Get(channelProp);
				if (channelArg->IsObject())
				{
					std::string channelClass;
					v8::Local<v8::Object> channelConfig = channelArg.As<v8::Object>();
					if (channelConfig->Has(classProp))
					{
						channelClass = toString(channelConfig->Get(classProp));
					}
					else throw Poco::NotFoundException("Missing channel configuration property", "class");
					pChannel = Poco::LoggingFactory::defaultFactory().createChannel(channelClass);

					v8::Local<v8::Array> channelProps = channelConfig->GetOwnPropertyNames();
					for (unsigned i = 0; i < channelProps->Length(); i++)
					{
						std::string prop = toString(channelProps->Get(i));
						if (prop != "class")
						{
							std::string value = toString(channelConfig->Get(channelProps->Get(i)));
							pChannel->setProperty(prop, value);
						}
					}
				}
				else
				{
					std::string channelName = toString(channelArg);
					pChannel.assign(Poco::LoggingRegistry::defaultRegistry().channelForName(channelName), true);
				}
			}

			if (config->Has(patternProp))
			{
				std::string pattern = toString(config->Get(patternProp));
				Poco::AutoPtr<Poco::PatternFormatter> pPatternFormatter = new Poco::PatternFormatter(pattern);
				pChannel = new Poco::FormattingChannel(pPatternFormatter, pChannel);
			}

			pLogger->setChannel(pChannel);
		}

		LoggerWrapper wrapper;
		v8::Local<v8::Object> loggerObject(wrapper.wrapNative(args.GetIsolate(), pLogger));
		args.GetReturnValue().Set(loggerObject);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void LoggerWrapper::isLogger(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() > 0)
	{
		args.GetReturnValue().Set(Wrapper::isWrapper<Poco::Logger>(args.GetIsolate(), args[0]));
	}
	else
	{
		args.GetReturnValue().Set(false);
	}
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
							case 'O':
								if (nextArgIndex < args.Length())
								{
									// use built-in JSON.stringify()
									v8::Local<v8::Context> context = args.GetIsolate()->GetCurrentContext();
									v8::Local<v8::Object> global = context->Global();
									v8::Local<v8::Object> json = global->Get(v8::String::NewFromUtf8(args.GetIsolate(), "JSON"))->ToObject();
									if (!json.IsEmpty())
									{
										v8::Local<v8::Function> stringify = v8::Handle<v8::Function>::Cast(json->Get(v8::String::NewFromUtf8(args.GetIsolate(), "stringify")));
										if (!stringify.IsEmpty())
										{
											v8::Local<v8::Value> argv[3] = {
												args[nextArgIndex],
												v8::Null(args.GetIsolate()),
												v8::Integer::New(args.GetIsolate(), *it == 'O' ? 4 : 0)
											};
											text.append(toString(stringify->Call(json, 3, argv)));
										}
									}
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


void LoggerWrapper::dump(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	v8::HandleScope scope(args.GetIsolate());
	Poco::Logger* pLogger = Wrapper::unwrapNative<Poco::Logger>(args);
	int prio = Poco::Message::PRIO_DEBUG;
	try
	{
		std::string message = toString(args[0]);
		if (args.Length() > 2)
		{
			std::string prioStr = toString(args[2]);
			if (!Poco::NumberParser::tryParse(prioStr, prio))
			{
				prio = Poco::Logger::parseLevel(prioStr);
			}
		}
		if (Wrapper::isWrapper<BufferWrapper::Buffer>(args.GetIsolate(), args[1]))
		{
			BufferWrapper::Buffer* pBuffer = Wrapper::unwrapNativeObject<BufferWrapper::Buffer>(args[1]);
			pLogger->dump(message, pBuffer->begin(), pBuffer->size(), static_cast<Poco::Message::Priority>(prio));
		}
		else
		{
			// use built-in JSON.stringify()
			v8::Local<v8::Context> context = args.GetIsolate()->GetCurrentContext();
			v8::Local<v8::Object> global = context->Global();
			v8::Local<v8::Object> json = global->Get(v8::String::NewFromUtf8(args.GetIsolate(), "JSON"))->ToObject();
			if (!json.IsEmpty())
			{
				v8::Local<v8::Function> stringify = v8::Handle<v8::Function>::Cast(json->Get(v8::String::NewFromUtf8(args.GetIsolate(), "stringify")));
				if (!stringify.IsEmpty())
				{
					v8::Local<v8::Value> argv[3] = {
						args[1],
						v8::Null(args.GetIsolate()),
						v8::Integer::New(args.GetIsolate(), 4)
					};
					message += "\n";
					message += toString(stringify->Call(json, 3, argv));
				}
			}
			Poco::Message msg(pLogger->name(), message, static_cast<Poco::Message::Priority>(prio));
			pLogger->log(msg);
		}
	}
	catch (...)
	{
	}
}


} } } // namespace Poco::JS::Core
