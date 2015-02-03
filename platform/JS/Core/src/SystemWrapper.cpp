//
// SystemWrapper.cpp
//
// $Id: //poco/1.4/JS/Core/src/SystemWrapper.cpp#5 $
//
// Library: JSCore
// Package: JSCore
// Module:  SystemWrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/SystemWrapper.h"
#include "Poco/Environment.h"
#include "Poco/Thread.h"

namespace Poco {
namespace JS {
namespace Core {


SystemWrapper::SystemWrapper()
{
}


SystemWrapper::~SystemWrapper()
{
}


v8::Handle<v8::ObjectTemplate> SystemWrapper::objectTemplate(v8::Isolate* pIsolate)
{
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::ObjectTemplate> loggerTemplate = v8::ObjectTemplate::New();
	loggerTemplate->SetInternalFieldCount(1);
	loggerTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "osName"), osName);
	loggerTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "osDisplayName"), osDisplayName);
	loggerTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "osArchitecture"), osArchitecture);
	loggerTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "osVersion"), osVersion);
	loggerTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "nodeName"), nodeName);
	loggerTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "nodeId"), nodeId);
	loggerTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "processorCount"), processorCount);
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "has"), v8::FunctionTemplate::New(pIsolate, has));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "get"), v8::FunctionTemplate::New(pIsolate, get));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "set"), v8::FunctionTemplate::New(pIsolate, set));
	loggerTemplate->Set(v8::String::NewFromUtf8(pIsolate, "sleep"), v8::FunctionTemplate::New(pIsolate, sleep));
	return handleScope.Escape(loggerTemplate);
}


void SystemWrapper::sleep(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	if (!args[0]->IsNumber()) return;
	double millisecs = args[0]->NumberValue();
	Poco::Thread::sleep(millisecs);
}


void SystemWrapper::get(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	std::string name = toString(args[0]);
	std::string deflt;
	if (args.Length() > 1) deflt = toString(args[1]);
	std::string value = Poco::Environment::get(name, deflt);
	returnString(args, value);
}


void SystemWrapper::has(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	std::string name = toString(args[0]);
	bool result = Poco::Environment::has(name);
	args.GetReturnValue().Set(result);
}


void SystemWrapper::set(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 2) return;
	std::string name = toString(args[0]);
	std::string value = toString(args[1]);
	Poco::Environment::set(name, value);
}


void SystemWrapper::osName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	returnString(info, Poco::Environment::osName());
}


void SystemWrapper::osDisplayName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	returnString(info, Poco::Environment::osDisplayName());
}


void SystemWrapper::osVersion(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	returnString(info, Poco::Environment::osVersion());
}


void SystemWrapper::osArchitecture(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	returnString(info, Poco::Environment::osArchitecture());
}


void SystemWrapper::nodeName(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	returnString(info, Poco::Environment::nodeName());
}


void SystemWrapper::nodeId(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	returnString(info, Poco::Environment::nodeId());
}


void SystemWrapper::processorCount(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	info.GetReturnValue().Set(Poco::Environment::processorCount());
}


} } } // namespace Poco::JS::Core
