//
// ConfigurationWrapper.cpp
//
// Library: JS/Core
// Package: Wrappers
// Module:  ConfigurationWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/ConfigurationWrapper.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/Util/AbstractConfiguration.h"


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Core {


ConfigurationWrapper::ConfigurationWrapper()
{
}


ConfigurationWrapper::~ConfigurationWrapper()
{
}


v8::Handle<v8::ObjectTemplate> ConfigurationWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	PooledIsolate* pPooledIso = PooledIsolate::fromIsolate(pIsolate);
	poco_check_ptr (pPooledIso);
	v8::Persistent<v8::ObjectTemplate>& pooledConfigurationTemplate(pPooledIso->objectTemplate("Core.Configuration"s));
	if (pooledConfigurationTemplate.IsEmpty())
	{
		v8::Local<v8::ObjectTemplate> configurationTemplate = v8::ObjectTemplate::New(pIsolate);
		configurationTemplate->SetInternalFieldCount(1);
		configurationTemplate->Set(toV8Internalized(pIsolate, "getInt"s), v8::FunctionTemplate::New(pIsolate, getInt));
		configurationTemplate->Set(toV8Internalized(pIsolate, "getDouble"s), v8::FunctionTemplate::New(pIsolate, getDouble));
		configurationTemplate->Set(toV8Internalized(pIsolate, "getBool"s), v8::FunctionTemplate::New(pIsolate, getBool));
		configurationTemplate->Set(toV8Internalized(pIsolate, "getString"s), v8::FunctionTemplate::New(pIsolate, getString));
		configurationTemplate->Set(toV8Internalized(pIsolate, "getObject"s), v8::FunctionTemplate::New(pIsolate, getObject));
		configurationTemplate->Set(toV8Internalized(pIsolate, "has"s), v8::FunctionTemplate::New(pIsolate, has));
		configurationTemplate->Set(toV8Internalized(pIsolate, "set"s), v8::FunctionTemplate::New(pIsolate, set));
		configurationTemplate->Set(toV8Internalized(pIsolate, "keys"s), v8::FunctionTemplate::New(pIsolate, keys));
		pooledConfigurationTemplate.Reset(pIsolate, configurationTemplate);
	}
	v8::Local<v8::ObjectTemplate> localConfigurationTemplate = v8::Local<v8::ObjectTemplate>::New(pIsolate, pooledConfigurationTemplate);
	return handleScope.Escape(localConfigurationTemplate);
}


void ConfigurationWrapper::getInt(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(pIsolate, args[0]);
	try
	{
		if (args.Length() > 1 && args[1]->IsNumber())
		{
			args.GetReturnValue().Set(pConfig->getInt(key, args[1]->Int32Value(context).FromMaybe(0)));
		}
		else
		{
			args.GetReturnValue().Set(pConfig->getInt(key));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ConfigurationWrapper::getDouble(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(pIsolate, args[0]);
	try
	{
		if (args.Length() > 1 && args[1]->IsNumber())
		{
			args.GetReturnValue().Set(pConfig->getDouble(key, args[1]->NumberValue(context).FromMaybe(0.0)));
		}
		else
		{
			args.GetReturnValue().Set(pConfig->getDouble(key));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ConfigurationWrapper::getBool(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(pIsolate, args[0]);
	try
	{
		if (args.Length() > 1 && args[1]->IsBoolean())
		{
			args.GetReturnValue().Set(pConfig->getBool(key, args[1]->BooleanValue(pIsolate)));
		}
		else
		{
			args.GetReturnValue().Set(pConfig->getBool(key));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ConfigurationWrapper::getString(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(pIsolate, args[0]);
	try
	{
		if (args.Length() > 1)
		{
			returnString(args, (pConfig->getString(key, toString(pIsolate, args[1]))));
		}
		else
		{
			returnString(args, (pConfig->getString(key)));
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ConfigurationWrapper::getObject(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(pIsolate, args[0]);
	try
	{
		if (args.Length() > 1 && !pConfig->has(key))
		{
			args.GetReturnValue().Set(args[1]);
		}
		else
		{
			std::string json = pConfig->getString(key);
			v8::Local<v8::String> jsonString = toV8String(pIsolate, json);
			v8::MaybeLocal<v8::Value> maybeValue = v8::JSON::Parse(context, jsonString);
			v8::Local<v8::Value> value;
			if (!maybeValue.ToLocal(&value))
				args.GetReturnValue().Set(value);
			else
				throw Poco::DataFormatException("Invalid JSON in configuration property "s + key, json);
		}
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ConfigurationWrapper::has(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(pIsolate, args[0]);
	try
	{
		args.GetReturnValue().Set(pConfig->has(key));
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ConfigurationWrapper::set(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(pIsolate, args[0]);
	std::string value;

	if (args[1]->IsObject())
	{
		value = toString(pIsolate, v8::JSON::Stringify(context, args[1]));
	}
	else
	{
		value = toString(pIsolate, args[1]);
	}

	try
	{
		pConfig->setString(key, value);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void ConfigurationWrapper::keys(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::HandleScope scope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key;
	if (args.Length() > 0)
	{
		key = toString(pIsolate, args[0]);
	}
	try
	{
		Poco::Util::AbstractConfiguration::Keys keys;
		pConfig->keys(key, keys);
		v8::Local<v8::Array> keysArray = v8::Array::New(pIsolate, static_cast<int>(keys.size()));
		if (!keysArray.IsEmpty())
		{
			for (unsigned i = 0; i < static_cast<unsigned>(keys.size()); i++)
			{
				V8_CHECK_SET_RESULT(keysArray->Set(context, i, toV8String(pIsolate, keys[i])));
			}
		}
		args.GetReturnValue().Set(keysArray);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


} } } // namespace Poco::JS::Core
