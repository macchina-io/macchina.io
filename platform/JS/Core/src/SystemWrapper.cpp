//
// SystemWrapper.cpp
//
// Library: JS/Core
// Package: Wrappers
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
#include "Poco/Process.h"
#include "Poco/Pipe.h"
#include "Poco/PipeStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Clock.h"


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
	v8::Local<v8::ObjectTemplate> systemTemplate = v8::ObjectTemplate::New(pIsolate);
	systemTemplate->SetInternalFieldCount(1);
	systemTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "osName"), osName);
	systemTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "osDisplayName"), osDisplayName);
	systemTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "osArchitecture"), osArchitecture);
	systemTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "osVersion"), osVersion);
	systemTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "nodeName"), nodeName);
	systemTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "nodeId"), nodeId);
	systemTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "processorCount"), processorCount);
	systemTemplate->SetAccessor(v8::String::NewFromUtf8(pIsolate, "clock"), clock);
	systemTemplate->Set(v8::String::NewFromUtf8(pIsolate, "has"), v8::FunctionTemplate::New(pIsolate, has));
	systemTemplate->Set(v8::String::NewFromUtf8(pIsolate, "get"), v8::FunctionTemplate::New(pIsolate, get));
	systemTemplate->Set(v8::String::NewFromUtf8(pIsolate, "set"), v8::FunctionTemplate::New(pIsolate, set));
	systemTemplate->Set(v8::String::NewFromUtf8(pIsolate, "sleep"), v8::FunctionTemplate::New(pIsolate, sleep));
	systemTemplate->Set(v8::String::NewFromUtf8(pIsolate, "exec"), v8::FunctionTemplate::New(pIsolate, exec));
	return handleScope.Escape(systemTemplate);
}


void SystemWrapper::exec(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::EscapableHandleScope handleScope(args.GetIsolate());

	if (args.Length() < 1) return;
	std::string command = toString(args[0]);
	std::string output;
	try
	{
#ifdef _WIN32
		std::string shell("cmd.exe");
		std::string shellArg("/C");
#else
		std::string shell("/bin/sh");
		std::string shellArg("-c");
#endif
		Poco::Pipe outPipe;
		Poco::Process::Args shellArgs;
		shellArgs.push_back(shellArg);
		shellArgs.push_back(command);
		Poco::ProcessHandle ph(Poco::Process::launch(shell, shellArgs, 0, &outPipe, &outPipe));
		Poco::PipeInputStream istr(outPipe);
		Poco::StreamCopier::copyToString(istr, output);
		int rc = ph.wait();

		v8::Local<v8::String> outputString(v8::String::NewFromUtf8(args.GetIsolate(), output.c_str(), v8::String::kNormalString, static_cast<int>(output.length())));
		v8::Local<v8::Value> outputStringObject = v8::StringObject::New(outputString);
		if (!outputStringObject.IsEmpty())
		{
			v8::Local<v8::Object> outputObject = outputStringObject->ToObject();
			if (!outputObject.IsEmpty())
			{
				outputObject->Set(v8::String::NewFromUtf8(args.GetIsolate(), "exitStatus"), v8::Integer::New(args.GetIsolate(), rc));
			}
		}
		args.GetReturnValue().Set(outputStringObject);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void SystemWrapper::sleep(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	if (!args[0]->IsNumber()) return;
	double millisecs = args[0]->NumberValue();
	Poco::Thread::sleep(static_cast<long>(millisecs));
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


void SystemWrapper::clock(v8::Local<v8::String> name, const v8::PropertyCallbackInfo<v8::Value>& info)
{
	Poco::Clock clock;
	info.GetReturnValue().Set(clock.microseconds()/1000000.0);
}


} } } // namespace Poco::JS::Core
