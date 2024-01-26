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
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/SystemWrapper.h"
#include "Poco/JS/Core/JSExecutor.h"
#include "Poco/JS/Core/AsyncFunction.h"
#include "Poco/Environment.h"
#include "Poco/Thread.h"
#include "Poco/Process.h"
#include "Poco/Pipe.h"
#include "Poco/PipeStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Clock.h"


using namespace std::string_literals;


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
	systemTemplate->SetAccessor(toV8Internalized(pIsolate, "osName"s), osName);
	systemTemplate->SetAccessor(toV8Internalized(pIsolate, "osDisplayName"s), osDisplayName);
	systemTemplate->SetAccessor(toV8Internalized(pIsolate, "osArchitecture"s), osArchitecture);
	systemTemplate->SetAccessor(toV8Internalized(pIsolate, "osVersion"s), osVersion);
	systemTemplate->SetAccessor(toV8Internalized(pIsolate, "nodeName"s), nodeName);
	systemTemplate->SetAccessor(toV8Internalized(pIsolate, "nodeId"s), nodeId);
	systemTemplate->SetAccessor(toV8Internalized(pIsolate, "processorCount"s), processorCount);
	systemTemplate->SetAccessor(toV8Internalized(pIsolate, "clock"s), clock);
	systemTemplate->Set(toV8Internalized(pIsolate, "has"s), v8::FunctionTemplate::New(pIsolate, has));
	systemTemplate->Set(toV8Internalized(pIsolate, "get"s), v8::FunctionTemplate::New(pIsolate, get));
	systemTemplate->Set(toV8Internalized(pIsolate, "set"s), v8::FunctionTemplate::New(pIsolate, set));
	systemTemplate->Set(toV8Internalized(pIsolate, "sleep"s), v8::FunctionTemplate::New(pIsolate, sleep));
	systemTemplate->Set(toV8Internalized(pIsolate, "exec"s), v8::FunctionTemplate::New(pIsolate, exec));
	systemTemplate->Set(toV8Internalized(pIsolate, "execAsync"s), v8::FunctionTemplate::New(pIsolate, execAsync));
	return handleScope.Escape(systemTemplate);
}


std::pair<std::string, int> execInShell(const std::string& command)
{
	std::pair<std::string, int> result;
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
	Poco::StreamCopier::copyToString(istr, result.first);
	result.second = ph.wait();
	return result;
}


void SystemWrapper::exec(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	if (args.Length() < 1) return;
	const std::string command = toString(pIsolate, args[0]);
	try
	{
		const auto result = execInShell(command);
		v8::Local<v8::String> outputString(toV8String(pIsolate, result.first));
		v8::Local<v8::Value> outputStringObject = v8::StringObject::New(pIsolate, outputString);
		if (!outputStringObject.IsEmpty())
		{
			v8::MaybeLocal<v8::Object> maybeOutputObject = outputStringObject->ToObject(context);
			v8::Local<v8::Object> outputObject;
			if (maybeOutputObject.ToLocal(&outputObject))
			{
				V8_CHECK_SET_RESULT(outputObject->Set(context, toV8String(pIsolate, "exitStatus"s), v8::Integer::New(pIsolate, result.second)));
			}
		}
		args.GetReturnValue().Set(outputStringObject);
	}
	catch (Poco::Exception& exc)
	{
		returnException(args, exc);
	}
}


void SystemWrapper::execAsync(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	if (args.Length() < 1) return;
	const std::string command = toString(pIsolate, args[0]);

	using ResultType = std::pair<std::string, int>;
	AsyncFunctionRunner<std::string, ResultType>::start(
		args, 
		context,
		[](const std::string& command) -> ResultType 
		{
			return execInShell(command);
		},
		[](v8::Local<v8::Context>& context, const ResultType& result) -> v8::Local<v8::Value> 
		{
			v8::Isolate* pIsolate = context->GetIsolate();
			v8::Local<v8::Object> resultObject;
			v8::Local<v8::String> outputString(Wrapper::toV8String(pIsolate, result.first));
			v8::Local<v8::Value> outputStringObject = v8::StringObject::New(pIsolate, outputString);
			if (!outputStringObject.IsEmpty())
			{
				v8::MaybeLocal<v8::Object> maybeOutputObject = outputStringObject->ToObject(context);
				if (maybeOutputObject.ToLocal(&resultObject))
				{
					V8_CHECK_SET_RESULT(resultObject->Set(context, Wrapper::toV8String(pIsolate, "exitStatus"s), v8::Integer::New(pIsolate, result.second)));
				}
			}
			return resultObject;
		},
		command
	);
}


void SystemWrapper::sleep(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	if (args.Length() < 1) return;
	if (!args[0]->IsNumber()) return;
	double millisecs = args[0]->NumberValue(pIsolate->GetCurrentContext()).FromMaybe(0.0);
	JSExecutor::Ptr pExecutor = JSExecutor::current();
	if (pExecutor->sleep(static_cast<long>(millisecs)))
	{
		returnException(args, "terminated while in system.sleep()"s);
	}
}


void SystemWrapper::get(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	if (args.Length() < 1) return;
	std::string name = toString(pIsolate, args[0]);
	std::string deflt;
	if (args.Length() > 1) deflt = toString(pIsolate, args[1]);
	std::string value = Poco::Environment::get(name, deflt);
	returnString(args, value);
}


void SystemWrapper::has(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	if (args.Length() < 1) return;
	std::string name = toString(pIsolate, args[0]);
	bool result = Poco::Environment::has(name);
	args.GetReturnValue().Set(result);
}


void SystemWrapper::set(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	if (args.Length() < 2) return;
	std::string name = toString(pIsolate, args[0]);
	std::string value = toString(pIsolate, args[1]);
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
