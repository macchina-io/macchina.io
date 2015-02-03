//
// ConfigurationWrapper.cpp
//
// $Id: //poco/1.4/JS/Core/src/ConfigurationWrapper.cpp#5 $
//
// Library: JSCore
// Package: JSCore
// Module:  ConfigurationWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/ConfigurationWrapper.h"
#include "Poco/Util/AbstractConfiguration.h"


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
	v8::Local<v8::ObjectTemplate> configurationTemplate = v8::ObjectTemplate::New();
	configurationTemplate->SetInternalFieldCount(1);
	configurationTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getInt"), v8::FunctionTemplate::New(pIsolate, getInt));
	configurationTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getDouble"), v8::FunctionTemplate::New(pIsolate, getDouble));
	configurationTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getBool"), v8::FunctionTemplate::New(pIsolate, getBool));
	configurationTemplate->Set(v8::String::NewFromUtf8(pIsolate, "getString"), v8::FunctionTemplate::New(pIsolate, getString));
	return handleScope.Escape(configurationTemplate);
}
	

void ConfigurationWrapper::getInt(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	v8::HandleScope scope(args.GetIsolate());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(args[0]);
	try
	{
		if (args.Length() > 1 && args[1]->IsNumber())
		{
			args.GetReturnValue().Set(pConfig->getInt(key, args[1]->Int32Value()));
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
	v8::HandleScope scope(args.GetIsolate());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(args[0]);
	try
	{
		if (args.Length() > 1 && args[1]->IsNumber())
		{
			args.GetReturnValue().Set(pConfig->getDouble(key, args[1]->NumberValue()));
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
	v8::HandleScope scope(args.GetIsolate());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(args[0]);
	try
	{
		if (args.Length() > 1 && args[1]->IsBoolean())
		{
			args.GetReturnValue().Set(pConfig->getBool(key, args[1]->BooleanValue()));
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
	v8::HandleScope scope(args.GetIsolate());
	Poco::Util::AbstractConfiguration* pConfig = Wrapper::unwrapNative<Poco::Util::AbstractConfiguration>(args);
	std::string key = toString(args[0]);
	try
	{
		if (args.Length() > 1)
		{
			returnString(args, (pConfig->getString(key, toString(args[1]))));
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



} } } // namespace Poco::JS::Core
