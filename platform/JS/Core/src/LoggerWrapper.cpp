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
// SPDX-License-Identifier: GPL-3.0-only
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


using namespace std::string_literals;


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
	funcTemplate->Set(toV8Internalized(pIsolate, "TRACE"s), v8::Integer::New(pIsolate, 8));
	funcTemplate->Set(toV8Internalized(pIsolate, "DEBUG"s), v8::Integer::New(pIsolate, 7));
	funcTemplate->Set(toV8Internalized(pIsolate, "INFORMATION"s), v8::Integer::New(pIsolate, 6));
	funcTemplate->Set(toV8Internalized(pIsolate, "NOTICE"s), v8::Integer::New(pIsolate, 5));
	funcTemplate->Set(toV8Internalized(pIsolate, "WARNING"s), v8::Integer::New(pIsolate, 4));
	funcTemplate->Set(toV8Internalized(pIsolate, "ERROR"s), v8::Integer::New(pIsolate, 3));
	funcTemplate->Set(toV8Internalized(pIsolate, "CRITICAL"s), v8::Integer::New(pIsolate, 2));
	funcTemplate->Set(toV8Internalized(pIsolate, "FATAL"s), v8::Integer::New(pIsolate, 1));
	funcTemplate->Set(toV8Internalized(pIsolate, "isLogger"s), v8::FunctionTemplate::New(pIsolate, isLogger));
	funcTemplate->Set(toV8Internalized(pIsolate, "setLevel"s), v8::FunctionTemplate::New(pIsolate, setLevel));
	funcTemplate->Set(toV8Internalized(pIsolate, "names"s), v8::FunctionTemplate::New(pIsolate, names));

	return handleScope.Escape(funcTemplate);
}


v8::Handle<v8::ObjectTemplate> LoggerWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	PooledIsolate* pPooledIso = PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledLoggerTemplate(pPooledIso->objectTemplate("Core.Logger"s));
	if (pooledLoggerTemplate.IsEmpty())
	{
		v8::Local<v8::ObjectTemplate> loggerTemplate = v8::ObjectTemplate::New(pIsolate);
		loggerTemplate->SetInternalFieldCount(1);
		loggerTemplate->Set(toV8Internalized(pIsolate, "trace"s), v8::FunctionTemplate::New(pIsolate, trace));
		loggerTemplate->Set(toV8Internalized(pIsolate, "debug"s), v8::FunctionTemplate::New(pIsolate, debug));
		loggerTemplate->Set(toV8Internalized(pIsolate, "information"s), v8::FunctionTemplate::New(pIsolate, information));
		loggerTemplate->Set(toV8Internalized(pIsolate, "notice"s), v8::FunctionTemplate::New(pIsolate, notice));
		loggerTemplate->Set(toV8Internalized(pIsolate, "warning"s), v8::FunctionTemplate::New(pIsolate, warning));
		loggerTemplate->Set(toV8Internalized(pIsolate, "error"s), v8::FunctionTemplate::New(pIsolate, error));
		loggerTemplate->Set(toV8Internalized(pIsolate, "critical"s), v8::FunctionTemplate::New(pIsolate, critical));
		loggerTemplate->Set(toV8Internalized(pIsolate, "fatal"s), v8::FunctionTemplate::New(pIsolate, fatal));
		loggerTemplate->Set(toV8Internalized(pIsolate, "log"s), v8::FunctionTemplate::New(pIsolate, log));
		loggerTemplate->Set(toV8Internalized(pIsolate, "dump"s), v8::FunctionTemplate::New(pIsolate, dump));
		loggerTemplate->Set(toV8Internalized(pIsolate, "close"s), v8::FunctionTemplate::New(pIsolate, close));
		loggerTemplate->SetAccessor(toV8Internalized(pIsolate, "level"s), getLevel, setLevel);
		loggerTemplate->SetAccessor(toV8Internalized(pIsolate, "name"s), getName);

		pooledLoggerTemplate.Reset(pIsolate, loggerTemplate);
	}
	v8::Local<v8::ObjectTemplate> localLoggerTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledLoggerTemplate);
	return handleScope.Escape(localLoggerTemplate);
}


void LoggerWrapper::construct(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	Poco::Logger* pLogger = 0;
	try
	{
		if (args.Length() > 1 && !args[1]->IsObject())
			throw Poco::InvalidArgumentException("Second argument must be configuration object");

		std::string loggerName;
		if (args.Length() > 0)
		{
			loggerName = toString(pIsolate, args[0]);
		}

		bool isExistingLogger = !Poco::Logger::has(loggerName).isNull();
		bool reconfigure = args.Length() > 2 && args[2]->BooleanValue(pIsolate);

		pLogger = &Poco::Logger::get(loggerName);

		if ((!isExistingLogger || reconfigure) && args.Length() > 1 && args[1]->IsObject())
		{
			v8::Local<v8::String> levelProp = toV8String(pIsolate, "level"s);
			v8::Local<v8::String> patternProp = toV8String(pIsolate, "pattern"s);
			v8::Local<v8::String> channelProp = toV8String(pIsolate, "channel"s);
			v8::Local<v8::String> classProp = toV8String(pIsolate, "class"s);

			v8::Local<v8::Object> config = args[1].As<v8::Object>();
			Poco::AutoPtr<Poco::Channel> pChannel;

			if (config->Has(context, levelProp).FromMaybe(false))
			{
				std::string level = toString(pIsolate, config->Get(context, levelProp).ToLocalChecked());
				pLogger->setLevel(level);
			}

			if (config->Has(context, channelProp).FromMaybe(false))
			{
				v8::MaybeLocal<v8::Value> maybeChannelArg = config->Get(context, channelProp);
				v8::Local<v8::Value> channelArg;
				if (maybeChannelArg.ToLocal(&channelArg))
				{
					if (channelArg->IsObject())
					{
						std::string channelClass;
						v8::Local<v8::Object> channelConfig = channelArg.As<v8::Object>();
						if (channelConfig->Has(context, classProp).FromMaybe(false))
						{
							channelClass = toString(pIsolate, channelConfig->Get(context, classProp));
						}
						else throw Poco::NotFoundException("Missing channel configuration property", "class");
						pChannel = Poco::LoggingFactory::defaultFactory().createChannel(channelClass);

						v8::MaybeLocal<v8::Array> maybeChannelProps = channelConfig->GetOwnPropertyNames(context);
						v8::Local<v8::Array> channelProps;
						if (maybeChannelProps.ToLocal(&channelProps))
						{
							for (unsigned i = 0; i < channelProps->Length(); i++)
							{
								std::string prop = toString(pIsolate, channelProps->Get(context, i));
								if (prop != "class")
								{
									v8::MaybeLocal<v8::Value> maybeProp = channelProps->Get(context, i);
									v8::Local<v8::Value> jsProp;
									if (maybeProp.ToLocal(&jsProp))
									{
										std::string value = toString(pIsolate, channelConfig->Get(context, jsProp));
										pChannel->setProperty(prop, value);
									}
								}
							}
						}
					}
					else
					{
						std::string channelName = toString(pIsolate, channelArg);
						pChannel.assign(Poco::LoggingRegistry::defaultRegistry().channelForName(channelName), true);
					}
				}
			}

			if (config->Has(context, patternProp).FromMaybe(false))
			{
				std::string pattern = toString(pIsolate, config->Get(context, patternProp));
				Poco::AutoPtr<Poco::PatternFormatter> pPatternFormatter = new Poco::PatternFormatter(pattern);
				pChannel = new Poco::FormattingChannel(pPatternFormatter, pChannel);
			}

			pLogger->setChannel(pChannel);
		}

		LoggerWrapper wrapper;
		v8::MaybeLocal<v8::Object> maybeLoggerObject(wrapper.wrapNative(pIsolate, pLogger));
		v8::Local<v8::Object> loggerObject;
		if (maybeLoggerObject.ToLocal(&loggerObject))
		{
			args.GetReturnValue().Set(loggerObject);
		}
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


void LoggerWrapper::setLevel(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	if (args.Length() < 1) return;
	v8::HandleScope scope(pIsolate);
	std::string name;
	std::string levelStr;
	if (args.Length() > 1)
	{
		name = toString(pIsolate, args[0]);
		levelStr = toString(pIsolate, args[1]);
	}
	else
	{
		levelStr = toString(pIsolate, args[0]);
	}

	int level = 0;
	try
	{
		if (!Poco::NumberParser::tryParse(levelStr, level))
		{
			level = Poco::Logger::parseLevel(levelStr);
		}
		Poco::Logger::setLevel(name, level);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void LoggerWrapper::names(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	std::vector<std::string> loggerNames;
	Poco::Logger::names(loggerNames);
	v8::Local<v8::Array> namesArray = v8::Array::New(pIsolate, static_cast<int>(loggerNames.size()));
	if (!namesArray.IsEmpty())
	{
		for (unsigned i = 0; i < static_cast<unsigned>(loggerNames.size()); i++)
		{
			V8_CHECK_SET_RESULT(namesArray->Set(context, i, toV8String(pIsolate, loggerNames[i])));
		}
	}
	args.GetReturnValue().Set(namesArray);
}


void LoggerWrapper::log(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	if (args.Length() < 2) return;
	v8::HandleScope scope(pIsolate);
	const std::string prioStr = toString(pIsolate, args[0]);
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
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	if (args.Length() <= firstArgIndex) return;
	Poco::Logger* pLogger = Wrapper::unwrapNative<Poco::Logger>(args);
	try
	{
		if (pLogger->is(prio))
		{
			std::string text(prefix);
			int nextArgIndex = firstArgIndex;
			if (args[nextArgIndex]->IsString())
			{
				std::string fmt(toString(pIsolate, args[nextArgIndex]));
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
										Poco::Int64 intValue = args[nextArgIndex]->IntegerValue(context).FromMaybe(0);
										Poco::NumberFormatter::append(text, intValue);
									}
									else
									{
										text.append(toString(pIsolate, args[nextArgIndex]));
									}
								}
								nextArgIndex++;
								break;
							case 'f':
								if (nextArgIndex < args.Length())
								{
									if (args[nextArgIndex]->IsNumber())
									{
										double doubleValue = args[nextArgIndex]->NumberValue(context).FromMaybe(0.0);
										Poco::NumberFormatter::append(text, doubleValue);
									}
									else
									{
										text.append(toString(pIsolate, args[nextArgIndex]));
									}
								}
								nextArgIndex++;
								break;
							case 's':
								if (nextArgIndex < args.Length())
								{
									text.append(toString(pIsolate, args[nextArgIndex]));
								}
								nextArgIndex++;
								break;
							case 'o':
							case 'O':
								if (nextArgIndex < args.Length())
								{
									v8::Local<v8::String> gap = toV8String(pIsolate, std::string(*it == 'O' ? 4U : 0U, ' '));
									text.append(toString(pIsolate, v8::JSON::Stringify(context, args[nextArgIndex], gap)));
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
				text.append(toString(pIsolate, args[i]));
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
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	if (args.Length() < 2) return;
	Poco::Logger* pLogger = Wrapper::unwrapNative<Poco::Logger>(args);
	int prio = Poco::Message::PRIO_DEBUG;
	try
	{
		std::string message = toString(pIsolate, args[0]);
		if (args.Length() > 2)
		{
			std::string prioStr = toString(pIsolate, args[2]);
			if (!Poco::NumberParser::tryParse(prioStr, prio))
			{
				prio = Poco::Logger::parseLevel(prioStr);
			}
		}
		if (Wrapper::isWrapper<BufferWrapper::Buffer>(pIsolate, args[1]))
		{
			BufferWrapper::Buffer* pBuffer = Wrapper::unwrapNativeObject<BufferWrapper::Buffer>(args[1]);
			pLogger->dump(message, pBuffer->begin(), pBuffer->size(), static_cast<Poco::Message::Priority>(prio));
		}
		else
		{
			v8::Local<v8::String> gap = toV8String(pIsolate, std::string(4U, ' '));
			message += toString(pIsolate, v8::JSON::Stringify(context, args[1], gap));
			Poco::Message msg(pLogger->name(), message, static_cast<Poco::Message::Priority>(prio));
			pLogger->log(msg);
		}
	}
	catch (...)
	{
	}
}


void LoggerWrapper::close(const v8::FunctionCallbackInfo<v8::Value>& args)
{
    v8::HandleScope scope(args.GetIsolate());
    Poco::Logger* pLogger = Wrapper::unwrapNative<Poco::Logger>(args);
    Poco::Logger::destroy(pLogger->name());
}


void LoggerWrapper::getLevel(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Poco::Logger* pLogger = Wrapper::unwrapNative<Poco::Logger>(info);
	info.GetReturnValue().Set(pLogger->getLevel());
}


void LoggerWrapper::setLevel(v8::Local<v8::String> name, v8::Local<v8::Value> value, const v8::PropertyCallbackInfo<void>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Poco::Logger* pLogger = Wrapper::unwrapNative<Poco::Logger>(info);
	try	
	{
		const std::string levelStr = toString(pIsolate, value);
		int level = 0;
		if (!Poco::NumberParser::tryParse(levelStr, level))
		{
			level = Poco::Logger::parseLevel(levelStr);
		}
		pLogger->setLevel(level);
	}
	catch (Poco::Exception& exc)
	{
		returnException(info, exc);
	}
}


void LoggerWrapper::getName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	v8::Isolate* pIsolate(info.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Poco::Logger* pLogger = Wrapper::unwrapNative<Poco::Logger>(info);
	returnString(info, pLogger->name());
}


} } } // namespace Poco::JS::Core
