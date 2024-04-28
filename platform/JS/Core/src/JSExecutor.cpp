//
// JSExecutor.cpp
//
// Library: JS/Core
// Package: Execution
// Module:  JSExecutor
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/JSExecutor.h"
#include "Poco/JS/Core/SystemWrapper.h"
#include "Poco/JS/Core/DateTimeWrapper.h"
#include "Poco/JS/Core/LocalDateTimeWrapper.h"
#include "Poco/JS/Core/ApplicationWrapper.h"
#include "Poco/JS/Core/URIWrapper.h"
#include "Poco/JS/Core/TimerWrapper.h"
#include "Poco/JS/Core/LoggerWrapper.h"
#include "Poco/JS/Core/BufferWrapper.h"
#include "Poco/JS/Core/UUIDWrapper.h"
#include "Poco/JS/Core/JSException.h"
#include "Poco/Delegate.h"
#include "Poco/URIStreamOpener.h"
#include "Poco/StreamCopier.h"
#include "libplatform/libplatform.h"
#include <memory>


using namespace std::string_literals;


namespace Poco {
namespace JS {
namespace Core {


//
// ScopedRunningCounter
//


class ScopedRunningCounter
{
public:
	ScopedRunningCounter(Poco::AtomicCounter& counter):
		_counter(counter)
	{
		++_counter;
	}

	~ScopedRunningCounter()
	{
		--_counter;
	}

private:
	Poco::AtomicCounter& _counter;
};


//
// JSExecutor
//


Poco::ThreadLocal<JSExecutor*> JSExecutor::_pCurrentExecutor;


JSExecutor::JSExecutor(const std::string& source, const Poco::URI& sourceURI, Poco::UInt64 memoryLimit):
	_source(source),
	_sourceURI(sourceURI),
	_pooledIso(memoryLimit)
{
 	init();
}


JSExecutor::JSExecutor(const std::string& source, const Poco::URI& sourceURI, const std::vector<std::string>& moduleSearchPaths, Poco::UInt64 memoryLimit):
	_source(source),
	_sourceURI(sourceURI),
	_moduleSearchPaths(moduleSearchPaths),
	_pooledIso(memoryLimit)
{
	init();
}


JSExecutor::~JSExecutor()
{
	_script.Reset();
	_scriptContext.Reset();
	_globalContext.Reset();
	_globalObjectTemplate.Reset();

	try
	{
		cleanup();
	}
	catch (Poco::Exception&)
	{
		poco_unexpected();
	}
}


void JSExecutor::init()
{
	_importStack.push_back(_sourceURI);
}


JSExecutor::Ptr JSExecutor::current()
{
	return Ptr(_pCurrentExecutor.get(), true);
}


void JSExecutor::attachToCurrentThread()
{
	*_pCurrentExecutor = this;
}


void JSExecutor::stop()
{
	terminate();

	stopped(this);

	cleanup();
}


void JSExecutor::terminate()
{
	_pooledIso.isolate()->TerminateExecution();
	_terminated.set();
}


void JSExecutor::cancelTerminate()
{
	_terminated.reset();
	_pooledIso.isolate()->CancelTerminateExecution();
}


bool JSExecutor::isTerminating() const
{
	return _pooledIso.isolate()->IsExecutionTerminating();
}


bool JSExecutor::sleep(long milliseconds)
{
	return _terminated.tryWait(milliseconds);
}


void JSExecutor::addModuleSearchPath(const std::string& path)
{
	_moduleSearchPaths.push_back(path);
}


void JSExecutor::addModuleRegistry(ModuleRegistry::Ptr pRegistry)
{
	_moduleRegistries.push_back(pRegistry);
}


void JSExecutor::setup()
{
	v8::Isolate* pIsolate = _pooledIso.isolate();
	v8::HandleScope handleScope(pIsolate);

	v8::Local<v8::Context> globalContext = v8::Context::New(pIsolate);
	v8::Context::Scope globalContextScope(globalContext);
	_globalContext.Reset(pIsolate, globalContext);

	v8::Local<v8::ObjectTemplate> globalObjectTemplate = v8::ObjectTemplate::New(pIsolate);
	setupGlobalObjectTemplate(globalObjectTemplate, pIsolate);
	_globalObjectTemplate.Reset(pIsolate, globalObjectTemplate);

	v8::Local<v8::Context> scriptContext = v8::Context::New(pIsolate, 0, globalObjectTemplate);
	_scriptContext.Reset(pIsolate, scriptContext);
}


void JSExecutor::cleanup()
{
	_importStack.clear();
	_imports.clear();

	WeakPersistentWrapperRegistry::cleanupIsolate(_pooledIso.isolate());
}


void JSExecutor::compile(v8::Local<v8::Context>& context)
{
	v8::Isolate* pIsolate = _pooledIso.isolate();
	v8::HandleScope handleScope(pIsolate);

	v8::Local<v8::String> sourceURI = Wrapper::toV8String(pIsolate, _sourceURI.toString());
	v8::Local<v8::String> source = Wrapper::toV8String(pIsolate, _source);
	v8::TryCatch tryCatch(pIsolate);
	v8::ScriptOrigin scriptOrigin(sourceURI);
	v8::MaybeLocal<v8::Script> maybeScript = v8::Script::Compile(context, source, &scriptOrigin);
	v8::Local<v8::Script> script;
	if (maybeScript.ToLocal(&script))
	{
		if (script.IsEmpty() || tryCatch.HasCaught())
		{
			reportError(pIsolate, tryCatch);
		}
		else
		{
			_script.Reset(pIsolate, script);
		}
	}
	else
	{
		reportError(pIsolate, tryCatch);
	}
}


void JSExecutor::runImpl()
{
	ScopedRunningCounter src(_running);

	attachToCurrentThread();

	v8::Isolate* pIsolate(_pooledIso.isolate());
	v8::Locker locker(pIsolate);
	v8::Isolate::Scope isoScope(pIsolate);
	v8::HandleScope handleScope(pIsolate);

	if (_globalObjectTemplate.IsEmpty())
	{
		setup();
	}

	v8::Local<v8::Context> globalContext = v8::Local<v8::Context>::New(pIsolate, _globalContext);
	v8::Context::Scope globalContextScope(globalContext);

	//v8::Local<v8::ObjectTemplate> globalObjectTemplate(v8::Local<v8::ObjectTemplate>::New(pIsolate, _globalObjectTemplate));

	v8::Local<v8::Context> scriptContext = v8::Local<v8::Context>::New(pIsolate, _scriptContext);
	v8::Context::Scope contextScope(scriptContext);

	if (_script.IsEmpty())
	{
		// Get global/root module and imports
		v8::Local<v8::Object> global = scriptContext->Global();

		v8::Local<v8::Object> moduleObject = v8::Object::New(pIsolate);
		V8_CHECK_SET_RESULT(moduleObject->Set(scriptContext, Wrapper::toV8String(pIsolate, "id"s), Wrapper::toV8String(pIsolate, _sourceURI.toString())));
		v8::Local<v8::Object> importsObject = v8::Object::New(pIsolate);
		V8_CHECK_SET_RESULT(moduleObject->Set(scriptContext, Wrapper::toV8String(pIsolate, "imports"s), importsObject));
		v8::Local<v8::Object> exportsObject = v8::Object::New(pIsolate);
		V8_CHECK_SET_RESULT(moduleObject->Set(scriptContext, Wrapper::toV8String(pIsolate, "exports"s), exportsObject));

		V8_CHECK_SET_RESULT(global->Set(scriptContext, Wrapper::toV8String(pIsolate, "module"s), moduleObject));

		setupGlobalObject(global, pIsolate);

		compile(scriptContext);
	}

	if (!_script.IsEmpty())
	{
		pIsolate->CancelTerminateExecution();
		v8::TryCatch tryCatch(pIsolate);
		v8::Local<v8::Script> script(v8::Local<v8::Script>::New(pIsolate, _script));

		v8::MaybeLocal<v8::Value> result = script->Run(scriptContext);
		if (result.IsEmpty() || tryCatch.HasCaught())
		{
			reportError(pIsolate, tryCatch);
		}
	}

	scriptCompleted();
}


void JSExecutor::run()
{
	runImpl();
}


void JSExecutor::call(v8::Handle<v8::Function>& function, v8::Handle<v8::Value>& receiver, int argc, v8::Handle<v8::Value> argv[])
{
	v8::Isolate* pIsolate = _pooledIso.isolate();
	v8::Locker locker(pIsolate);
	v8::Isolate::Scope isoScope(pIsolate);
	v8::HandleScope handleScope(pIsolate);

	v8::Local<v8::Context> context(v8::Local<v8::Context>::New(pIsolate, _scriptContext));
	v8::Context::Scope contextScope(context);

	callInContext(pIsolate, context, function, receiver, argc, argv);
}


void JSExecutor::callInContext(v8::Isolate* pIsolate, v8::Local<v8::Context>& context, v8::Handle<v8::Function>& function, v8::Handle<v8::Value>& receiver, int argc, v8::Handle<v8::Value> argv[])
{
	ScopedRunningCounter src(_running);

	attachToCurrentThread();

	v8::TryCatch tryCatch(pIsolate);
	v8::MaybeLocal<v8::Value> maybeResult = function->Call(context, receiver, argc, argv);
	if (maybeResult.IsEmpty() || tryCatch.HasCaught())
	{
		reportError(pIsolate, tryCatch);
	}
}


void JSExecutor::callInContext(v8::Isolate* pIsolate, v8::Local<v8::Context>& context, v8::Persistent<v8::Object>& jsObject, const std::string& method, int argc, v8::Handle<v8::Value> argv[])
{
	ScopedRunningCounter src(_running);

	attachToCurrentThread();

	v8::HandleScope handleScope(pIsolate);

	if (!jsObject.IsEmpty())
	{
		v8::Local<v8::String> jsMethod = Wrapper::toV8String(pIsolate, method);
		v8::Local<v8::Object> localObject(v8::Local<v8::Object>::New(pIsolate, jsObject));
		v8::Maybe<bool> hasMethod = localObject->Has(pIsolate->GetCurrentContext(), jsMethod);
		if (hasMethod.IsJust() && hasMethod.FromJust())
		{
			v8::MaybeLocal<v8::Value> maybeJSValue = localObject->Get(context, jsMethod);
			v8::Local<v8::Value> jsValue;
			if (maybeJSValue.ToLocal(&jsValue) && jsValue->IsFunction())
			{
				v8::Local<v8::Function> jsFunction = v8::Local<v8::Function>::Cast(jsValue);
				v8::TryCatch tryCatch(pIsolate);
				v8::MaybeLocal<v8::Value> maybeResult = jsFunction->Call(context, localObject, argc, argv);
				if (maybeResult.IsEmpty() || tryCatch.HasCaught())
				{
					reportError(pIsolate, tryCatch);
				}
			}
		}
	}
}


void JSExecutor::call(v8::Persistent<v8::Object>& jsObject, const std::string& method, const std::string& args)
{
	ScopedRunningCounter src(_running);

	attachToCurrentThread();

	v8::Isolate* pIsolate = _pooledIso.isolate();
	v8::Locker locker(pIsolate);
	v8::Isolate::Scope isoScope(pIsolate);
	v8::HandleScope handleScope(pIsolate);

	v8::Local<v8::Context> context(v8::Local<v8::Context>::New(pIsolate, _scriptContext));
	v8::Context::Scope contextScope(context);

	if (!jsObject.IsEmpty())
	{
		v8::Local<v8::String> jsMethod = Wrapper::toV8String(pIsolate, method);
		v8::Local<v8::String> jsArgs = Wrapper::toV8String(pIsolate, args);
		v8::Local<v8::Object> localObject(v8::Local<v8::Object>::New(pIsolate, jsObject));

		if (localObject->Has(context, jsMethod).FromMaybe(false))
		{
			v8::MaybeLocal<v8::Value> maybeJSValue = localObject->Get(context, jsMethod);
			v8::Local<v8::Value> jsValue;
			if (maybeJSValue.ToLocal(&jsValue) && jsValue->IsFunction())
			{
				v8::Local<v8::Function> jsFunction = v8::Local<v8::Function>::Cast(jsValue);

				v8::TryCatch tryCatch(pIsolate);
				v8::MaybeLocal<v8::Value> maybeJSArgs = v8::JSON::Parse(context, jsArgs);
				v8::Local<v8::Value> jsArgs;
				if (maybeJSArgs.ToLocal(&jsArgs))
				{
					v8::Local<v8::Value> argv[1] = { jsArgs };
					v8::MaybeLocal<v8::Value> maybeResult = jsFunction->Call(context, localObject, 1, argv);
					if (maybeResult.IsEmpty() || tryCatch.HasCaught())
					{
						reportError(pIsolate, tryCatch);
					}
				}
				else
				{
					ErrorInfo errorInfo;
					errorInfo.uri = _sourceURI.toString();
					errorInfo.lineNo = 0;
					errorInfo.message = "JSExecutor::call(): failed to parse JSON arguments: " + args;
					reportError(pIsolate, errorInfo);
				}
			}
		}
	}
}


void JSExecutor::call(v8::Persistent<v8::Function>& function)
{
	ScopedRunningCounter src(_running);

	attachToCurrentThread();

	v8::Isolate* pIsolate = _pooledIso.isolate();
	v8::Locker locker(pIsolate);
	v8::Isolate::Scope isoScope(pIsolate);
	v8::HandleScope handleScope(pIsolate);

	v8::Local<v8::Context> context(v8::Local<v8::Context>::New(pIsolate, _scriptContext));
	v8::Context::Scope contextScope(context);

	v8::Local<v8::Object> global = context->Global();

	v8::Local<v8::Function> localFunction(v8::Local<v8::Function>::New(pIsolate, function));
	v8::Local<v8::Value> argv[1];
	v8::TryCatch tryCatch(pIsolate);

	v8::MaybeLocal<v8::Value> maybeResult = localFunction->Call(context, global, 0, argv);
	if (maybeResult.IsEmpty() || tryCatch.HasCaught())
	{
		reportError(pIsolate, tryCatch);
	}
}


void JSExecutor::call(v8::Persistent<v8::Function>& function, v8::Persistent<v8::Array>& args)
{
	ScopedRunningCounter src(_running);

	attachToCurrentThread();

	v8::Isolate* pIsolate = _pooledIso.isolate();
	v8::Locker locker(pIsolate);
	v8::Isolate::Scope isoScope(pIsolate);
	v8::HandleScope handleScope(pIsolate);

	v8::Local<v8::Context> context(v8::Local<v8::Context>::New(pIsolate, _scriptContext));
	v8::Context::Scope contextScope(context);

	v8::Local<v8::Object> global = context->Global();

	v8::Local<v8::Function> localFunction(v8::Local<v8::Function>::New(pIsolate, function));

	v8::Local<v8::Value> argv[16];
	Poco::UInt32 argsLength = 0;
	if (!args.IsEmpty())
	{
		v8::Local<v8::Array> localArgs(v8::Local<v8::Array>::New(pIsolate, args));
		argsLength = localArgs->Length();
		if (argsLength > 16) argsLength = 16;
		for (Poco::UInt32 i = 0; i < argsLength; i++)
		{
			v8::MaybeLocal<v8::Value> maybeValue = localArgs->Get(context, i);
			v8::Local<v8::Value> value;
			if (maybeValue.ToLocal(&value))
			{
				argv[i] = value;
			}
		}
	}

	v8::TryCatch tryCatch(pIsolate);
	v8::MaybeLocal<v8::Value> maybeResult = localFunction->Call(context, global, argsLength, argv);
	if (maybeResult.IsEmpty() || tryCatch.HasCaught())
	{
		reportError(pIsolate, tryCatch);
	}
}


void JSExecutor::includeScript(v8::Isolate* pIsolate, const std::string& uri)
{
	v8::HandleScope handleScope(pIsolate);

	v8::Local<v8::Context> context(v8::Local<v8::Context>::New(pIsolate, _scriptContext));
	v8::Context::Scope contextScope(context);

	Poco::URI includeURI(_sourceURI, uri);
	std::unique_ptr<std::istream> istr(Poco::URIStreamOpener::defaultOpener().open(includeURI));
	std::string source;
	Poco::StreamCopier::copyToString(*istr, source);

	v8::Local<v8::String> sourceURI = Wrapper::toV8String(pIsolate, _sourceURI.toString());
	v8::Local<v8::String> sourceObject = Wrapper::toV8String(pIsolate, source);
	v8::TryCatch tryCatch(pIsolate);
	v8::ScriptOrigin scriptOrigin(sourceURI);
	v8::MaybeLocal<v8::Script> maybeScriptObject = v8::Script::Compile(context, sourceObject, &scriptOrigin);
	v8::Local<v8::Script> scriptObject;
	if (!tryCatch.HasCaught() && maybeScriptObject.ToLocal(&scriptObject))
	{
		v8::MaybeLocal<v8::Value> maybeResult = scriptObject->Run(context);
		if (maybeResult.IsEmpty() || tryCatch.HasCaught())
		{
			reportError(pIsolate, tryCatch);
		}
	}
	else
	{
		reportError(pIsolate, tryCatch);
	}
}


void JSExecutor::setupGlobalObjectTemplate(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate)
{
	Poco::JS::Core::DateTimeWrapper dateTimeWrapper;
	global->Set(Wrapper::toV8Internalized(pIsolate, "DateTime"s), dateTimeWrapper.constructor(pIsolate));

	Poco::JS::Core::LocalDateTimeWrapper localDateTimeWrapper;
	global->Set(Wrapper::toV8Internalized(pIsolate, "LocalDateTime"s), localDateTimeWrapper.constructor(pIsolate));

	Poco::JS::Core::BufferWrapper bufferWrapper;
	global->Set(Wrapper::toV8Internalized(pIsolate, "Buffer"s), bufferWrapper.constructor(pIsolate));

	Poco::JS::Core::UUIDWrapper uuidWrapper;
	global->Set(Wrapper::toV8Internalized(pIsolate, "UUID"s), uuidWrapper.constructor(pIsolate));

	Poco::JS::Core::LoggerWrapper loggerWrapper;
	global->Set(Wrapper::toV8Internalized(pIsolate, "Logger"s), loggerWrapper.constructor(pIsolate));

	global->Set(Wrapper::toV8Internalized(pIsolate, "include"s), v8::FunctionTemplate::New(pIsolate, include));
	global->Set(Wrapper::toV8Internalized(pIsolate, "require"s), v8::FunctionTemplate::New(pIsolate, require));
}


void JSExecutor::setupGlobalObject(v8::Local<v8::Object>& global, v8::Isolate* pIsolate)
{
	setWrapperProperty<SystemWrapper>(global, pIsolate, "system"s);
	setWrapperProperty<ApplicationWrapper>(global, pIsolate, "application"s);
	setWrapperProperty<URIWrapper>(global, pIsolate, "uri"s);
}


void JSExecutor::handleError(const ErrorInfo& errorInfo)
{
}


void JSExecutor::handleOutOfMemory(std::size_t currentHeapLimit, std::size_t initialHeapLimit)
{
	try
	{
		outOfMemory();
	}
	catch (...)
	{
	}
	stop();
}


void JSExecutor::handleMemoryWarning(std::size_t currentHeapLimit, std::size_t initialHeapLimit)
{
	try
	{
		MemoryWarning mw;
		mw.currentHeapLimit = currentHeapLimit;
		mw.initialHeapLimit = initialHeapLimit;
		memoryWarning(mw);
	}
	catch (...)
	{
	}
}


void JSExecutor::reportError(v8::Isolate* pIsolate, v8::TryCatch& tryCatch)
{
	v8::HandleScope handleScope(pIsolate);

	ErrorInfo errorInfo;
	errorInfo.uri = _sourceURI.toString();
	errorInfo.lineNo = 0;
	v8::Local<v8::Value> exception = tryCatch.Exception();
	if (tryCatch.HasTerminated())
	{
		errorInfo.message = "Terminated";
	}
	else if (!exception.IsEmpty())
	{
		v8::String::Utf8Value str(pIsolate, exception);
		errorInfo.message = *str;
		v8::Local<v8::StackTrace> stackTrace = v8::Exception::GetStackTrace(exception);
		errorInfo.stackTrace = buildStackTrace(pIsolate, stackTrace);
	}
	v8::Local<v8::Message> message = tryCatch.Message();
	if (!message.IsEmpty())
	{
		v8::String::Utf8Value str(pIsolate, message->GetScriptResourceName());
		if (*str && "undefined"s != *str && errorInfo.uri != *str)
		{
			std::string uri = *str;
			uri += " (";
			uri += errorInfo.uri;
			uri += " )";
			errorInfo.uri = uri;
		}
		errorInfo.lineNo = message->GetLineNumber(pIsolate->GetCurrentContext()).FromMaybe(0);
		if (errorInfo.stackTrace.empty())
		{
			v8::Local<v8::StackTrace> stackTrace = message->GetStackTrace();
			errorInfo.stackTrace = buildStackTrace(pIsolate, stackTrace);
		}
	}
	reportError(pIsolate, errorInfo);
}


void JSExecutor::reportError(v8::Isolate* pIsolate, const ErrorInfo& errorInfo)
{
	try
	{
		scriptError(this, errorInfo);
	}
	catch (...)
	{
	}
	handleError(errorInfo);
}


std::vector<JSExecutor::StackFrame> JSExecutor::buildStackTrace(v8::Isolate* pIsolate, v8::Local<v8::StackTrace>& stackTrace)
{
	std::vector<StackFrame> result;
	if (!stackTrace.IsEmpty())
	{
		int frameCount = stackTrace->GetFrameCount();
		for (int i = 0; i < frameCount; i++)
		{
			v8::Local<v8::StackFrame> v8Frame = stackTrace->GetFrame(pIsolate, i);
			StackFrame frame;
			frame.lineNo = v8Frame->GetLineNumber();
			frame.functionName = Wrapper::toString(pIsolate, v8Frame->GetFunctionName());
			frame.scriptName = Wrapper::toString(pIsolate, v8Frame->GetScriptName());
			result.push_back(frame);
		}
	}
	return result;
}


void JSExecutor::scriptCompleted()
{
}


void JSExecutor::include(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::EscapableHandleScope handleScope(pIsolate);

	if (args.Length() != 1) return;
	std::string uri(Poco::JS::Core::Wrapper::toString(pIsolate, args[0]));

	JSExecutor* pCurrentExecutor = _pCurrentExecutor.get();
	if (!pCurrentExecutor) return;

	try
	{
		pCurrentExecutor->includeScript(pIsolate, uri);
	}
	catch (Poco::Exception& exc)
	{
		Poco::JS::Core::Wrapper::returnException(args, exc);
	}
}


void JSExecutor::require(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::EscapableHandleScope handleScope(pIsolate);

	if (args.Length() != 1) return;
	std::string uri(Wrapper::toString(pIsolate, args[0]));

	JSExecutor* pCurrentExecutor = _pCurrentExecutor.get();
	if (!pCurrentExecutor) return;

	try
	{
		Module::Ptr pModule;
		for (std::vector<ModuleRegistry::Ptr>::const_iterator it = pCurrentExecutor->_moduleRegistries.begin(); !pModule && it != pCurrentExecutor->_moduleRegistries.end(); ++it)
		{
			pModule = (*it)->findModule(uri);
		}
		if (pModule)
		{
			pCurrentExecutor->importModule(args, uri, pModule);
		}
		else
		{
			if (uri.length() > 3 && uri.compare(uri.length() - 3, 3, ".js") != 0)
			{
				uri += ".js";
			}
			pCurrentExecutor->importModule(args, uri);
		}
	}
	catch (Poco::Exception& exc)
	{
		Poco::JS::Core::Wrapper::returnException(args, exc);
	}
}


void JSExecutor::importModule(const v8::FunctionCallbackInfo<v8::Value>& args, const std::string& uri)
{
	class ImportScope
	{
	public:
		ImportScope(std::vector<Poco::URI>& stack, const Poco::URI& uri):
			_stack(stack)
		{
			_stack.push_back(uri);
		}

		~ImportScope()
		{
			_stack.pop_back();
		}

	private:
		std::vector<Poco::URI>& _stack;
	};

	// Resolve URI
	Poco::URI moduleURI;
	Poco::SharedPtr<std::istream> pStream = resolveModule(uri, moduleURI);
	ImportScope importScope(_importStack, moduleURI);
	std::string moduleURIString = moduleURI.toString();

	// Set up import context
	v8::Isolate* pIsolate = _pooledIso.isolate();
	v8::EscapableHandleScope handleScope(pIsolate);

	v8::Local<v8::Context> scriptContext(v8::Local<v8::Context>::New(pIsolate, _scriptContext));
	v8::Context::Scope scriptContextScope(scriptContext);

	// Get global/root module and imports
	v8::Local<v8::Object> global = scriptContext->Global();
	v8::Local<v8::Object> globalModule = v8::Local<v8::Object>::Cast(global->Get(scriptContext, Wrapper::toV8String(pIsolate, "module"s)).ToLocalChecked());
	poco_assert_dbg (globalModule->IsObject());
	v8::Local<v8::Object> globalImports = v8::Local<v8::Object>::Cast(globalModule->Get(scriptContext, Wrapper::toV8String(pIsolate, "imports"s)).ToLocalChecked());
	poco_assert_dbg (globalImports->IsObject());

	// Check if we have already imported the module
	v8::Local<v8::String> jsModuleURI = Wrapper::toV8String(pIsolate, moduleURIString);
	if (globalImports->Has(scriptContext, jsModuleURI).FromMaybe(false))
	{
		poco_assert (!pStream);
		v8::MaybeLocal<v8::Value> maybeImport = globalImports->Get(scriptContext, jsModuleURI);
		v8::Local<v8::Value> import;
		if (maybeImport.ToLocal(&import))
		{
			args.GetReturnValue().Set(import);
		}
	}
	else
	{
		poco_assert (pStream);

		// Create context for import
		v8::Local<v8::ObjectTemplate> moduleTemplate(v8::Local<v8::ObjectTemplate>::New(pIsolate, _globalObjectTemplate));

		v8::Local<v8::Context> moduleContext = v8::Context::New(pIsolate, 0, moduleTemplate);
		v8::Context::Scope moduleContextScope(moduleContext);

		v8::Local<v8::Object> moduleGlobal = moduleContext->Global();

		v8::Local<v8::Object> moduleObject = v8::Object::New(pIsolate);
		V8_CHECK_SET_RESULT(moduleObject->Set(moduleContext, Wrapper::toV8String(pIsolate, "id"s), jsModuleURI));
		v8::Local<v8::Object> exportsObject = v8::Object::New(pIsolate);
		V8_CHECK_SET_RESULT(moduleObject->Set(moduleContext, Wrapper::toV8String(pIsolate, "exports"s), exportsObject));
		V8_CHECK_SET_RESULT(moduleGlobal->Set(moduleContext, Wrapper::toV8String(pIsolate, "module"s), moduleObject));
		V8_CHECK_SET_RESULT(moduleGlobal->Set(moduleContext, Wrapper::toV8String(pIsolate, "exports"s), exportsObject));

		setupGlobalObject(moduleGlobal, pIsolate);

		V8_CHECK_SET_RESULT(globalImports->Set(moduleContext, jsModuleURI, exportsObject));

		std::string source;
		Poco::StreamCopier::copyToString(*pStream, source);

		v8::Local<v8::String> sourceObject = Wrapper::toV8String(pIsolate, source);
		v8::TryCatch tryCatch(pIsolate);
		v8::ScriptOrigin scriptOrigin(jsModuleURI);
		v8::MaybeLocal<v8::Script> maybeScriptObject = v8::Script::Compile(moduleContext, sourceObject, &scriptOrigin);
		v8::Local<v8::Script> scriptObject;
		if (!tryCatch.HasCaught() && maybeScriptObject.ToLocal(&scriptObject))
		{
			v8::MaybeLocal<v8::Value> maybeResult = scriptObject->Run(moduleContext);
			if (!tryCatch.HasCaught() && !maybeResult.IsEmpty())
			{
				// Note: we cannot use the exports handle from above as the script may
				// have assigned a new object to module.exports.
				v8::MaybeLocal<v8::Value> maybeNewExportsObject = moduleObject->Get(moduleContext, Wrapper::toV8String(pIsolate, "exports"s));
				v8::Local<v8::Value> newExportsObject;
				if (maybeNewExportsObject.ToLocal(&newExportsObject))
				{
					V8_CHECK_SET_RESULT(globalImports->Set(moduleContext, jsModuleURI, newExportsObject));
					args.GetReturnValue().Set(newExportsObject);
				}
			}
			else
			{
				args.GetReturnValue().Set(tryCatch.ReThrow());
			}
		}
		else if (tryCatch.HasCaught())
		{
			args.GetReturnValue().Set(tryCatch.ReThrow());
		}
	}
}


void JSExecutor::importModule(const v8::FunctionCallbackInfo<v8::Value>& args, const std::string& uri, Module::Ptr pModule)
{
	// Set up import context
	v8::Isolate* pIsolate = _pooledIso.isolate();
	v8::HandleScope handleScope(pIsolate);

	v8::Local<v8::Context> scriptContext(v8::Local<v8::Context>::New(pIsolate, _scriptContext));
	v8::Context::Scope scriptContextScope(scriptContext);

	// Get global/root module and imports
	v8::Local<v8::Object> global = scriptContext->Global();
	v8::Local<v8::Object> globalModule = v8::Local<v8::Object>::Cast(global->Get(scriptContext, Wrapper::toV8String(pIsolate, "module"s)).ToLocalChecked());
	poco_assert_dbg (globalModule->IsObject());
	v8::Local<v8::Object> globalImports = v8::Local<v8::Object>::Cast(globalModule->Get(scriptContext, Wrapper::toV8String(pIsolate, "imports"s)).ToLocalChecked());
	poco_assert_dbg (globalImports->IsObject());

	// Check if we have already imported the module
	v8::Local<v8::String> jsModuleURI = Wrapper::toV8String(pIsolate, uri);
	if (globalImports->Has(scriptContext, jsModuleURI).FromMaybe(false))
	{
		v8::MaybeLocal<v8::Value> maybeImports = globalImports->Get(scriptContext, jsModuleURI);
		v8::Local<v8::Value> imports;
		if (maybeImports.ToLocal(&imports))
		{
			args.GetReturnValue().Set(imports);
		}
	}
	else
	{
		v8::Local<v8::Object> exportsObject = pModule->exportIt(pIsolate);
		V8_CHECK_SET_RESULT(globalImports->Set(scriptContext, jsModuleURI, exportsObject));
		args.GetReturnValue().Set(exportsObject);
	}
}


Poco::SharedPtr<std::istream> JSExecutor::resolveModule(const std::string& uri, Poco::URI& resolvedURI)
{
	poco_assert (!_importStack.empty());

	Poco::SharedPtr<std::istream> pStream;

	resolvedURI = _importStack.back();
	resolvedURI.resolve(uri);
	std::string resolvedURIString = resolvedURI.toString();

	if (_imports.find(resolvedURIString) != _imports.end())
		return pStream;

	try
	{
		pStream = Poco::URIStreamOpener::defaultOpener().open(resolvedURIString);
		_imports.insert(resolvedURIString);
		return pStream;
	}
	catch (Poco::Exception&)
	{
	}

	for (std::vector<std::string>::const_iterator it = _moduleSearchPaths.begin(); it != _moduleSearchPaths.end(); ++it)
	{
		std::string path;
		path.reserve(it->size() + 1);
		path += *it;
		if (!path.empty() && path[path.size() - 1] != '/') path += '/';
		resolvedURI = path;
		resolvedURI.resolve(uri);
		resolvedURIString = resolvedURI.toString();

		if (_imports.find(resolvedURIString) != _imports.end())
			return pStream;

		try
		{
			pStream = Poco::URIStreamOpener::defaultOpener().open(resolvedURIString);
			_imports.insert(resolvedURIString);
			return pStream;
		}
		catch (Poco::Exception&)
		{
		}
	}

	throw ModuleNotFoundException(uri);
}


//
// RunScriptTask
//


class RunScriptTask: public Poco::Util::TimerTask
{
public:
	using Ptr = Poco::AutoPtr<RunScriptTask>;

	RunScriptTask(TimedJSExecutor* pExecutor):
		_pExecutor(pExecutor, true)
	{
	}

	void run()
	{
		_pExecutor->runImpl();
	}

private:
	TimedJSExecutor::Ptr _pExecutor;
};


//
// CallFunctionTask
//


class CallFunctionTask: public Poco::Util::TimerTask
{
public:
	using Ptr = Poco::AutoPtr<CallFunctionTask>;

	CallFunctionTask(v8::Isolate* pIsolate, TimedJSExecutor* pExecutor, v8::Handle<v8::Function> function):
		_pExecutor(pExecutor, true),
		_function(pIsolate, function)
	{
	}

	CallFunctionTask(v8::Isolate* pIsolate, TimedJSExecutor* pExecutor, v8::Handle<v8::Function> function, v8::Handle<v8::Array> arguments):
		_pExecutor(pExecutor, true),
		_function(pIsolate, function),
		_arguments(pIsolate, arguments)
	{
	}

	~CallFunctionTask()
	{
		_pExecutor.reset();
		_function.Reset();
		_arguments.Reset();
	}

	void run()
	{
		TimedJSExecutor::Ptr pExecutor = _pExecutor;
		if (!pExecutor->isTerminating())
		{
			pExecutor->call(_function, _arguments);
		}
	}

	void onExecutorStopped()
	{
		if (_pExecutor)
		{
			_pExecutor = 0;
		}
	}

private:
	TimedJSExecutor::Ptr _pExecutor;
	v8::Persistent<v8::Function> _function;
	v8::Persistent<v8::Array> _arguments;
};


//
// TimedJSExecutor
//


TimedJSExecutor::TimedJSExecutor(const std::string& source, const Poco::URI& sourceURI, const std::vector<std::string>& moduleSearchPaths, Poco::UInt64 memoryLimit):
	JSExecutor(source, sourceURI, moduleSearchPaths, memoryLimit),
	_stopped(false)
{
}


TimedJSExecutor::~TimedJSExecutor()
{
	try
	{
		stop();
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void TimedJSExecutor::run()
{
	_timer.schedule(new RunScriptTask(this), Poco::Timestamp());
}


void TimedJSExecutor::setupGlobalObjectTemplate(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate)
{
	JSExecutor::setupGlobalObjectTemplate(global, pIsolate);

	global->Set(Wrapper::toV8String(pIsolate, "setImmediate"s), v8::FunctionTemplate::New(pIsolate, setImmediate));
	global->Set(Wrapper::toV8String(pIsolate, "setTimeout"s), v8::FunctionTemplate::New(pIsolate, setTimeout));
	global->Set(Wrapper::toV8String(pIsolate, "setInterval"s), v8::FunctionTemplate::New(pIsolate, setInterval));
	global->Set(Wrapper::toV8String(pIsolate, "clearImmediate"s), v8::FunctionTemplate::New(pIsolate, cancelTimer));
	global->Set(Wrapper::toV8String(pIsolate, "clearTimeout"s), v8::FunctionTemplate::New(pIsolate, cancelTimer));
	global->Set(Wrapper::toV8String(pIsolate, "clearInterval"s), v8::FunctionTemplate::New(pIsolate, cancelTimer));
}


void TimedJSExecutor::schedule(Poco::Util::TimerTask::Ptr pTask)
{
	if (!_stopped)
	{
		_timer.schedule(pTask, Poco::Clock());
	}
}


void TimedJSExecutor::schedule(Poco::Util::TimerTask::Ptr pTask, const Poco::Clock& clock)
{
	if (!_stopped)
	{
		_timer.schedule(pTask, clock);
	}
}


void TimedJSExecutor::stop()
{
	if (!_stopped.exchange(true))
	{
		_timer.cancel(this);

		stopped(this);

		cleanup();
	}
}


void TimedJSExecutor::handleOutOfMemory(std::size_t currentHeapLimit, std::size_t initialHeapLimit)
{
	try
	{
		outOfMemory();
	}
	catch (...)
	{
	}
	terminate();
	_timer.cancelAsync(this);
}


void TimedJSExecutor::setImmediate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	if (args.Length() < 1) return;
	if (!args[0]->IsFunction()) return;
	v8::Local<v8::Function> function = args[0].As<v8::Function>();

	Poco::UInt32 argsLength = args.Length() > 1 ? args.Length() - 1 : 0;
	v8::Local<v8::Array> argsArray = v8::Array::New(pIsolate, argsLength);
	if (argsLength > 0)
	{
		for (Poco::UInt32 i = 0; i < argsLength; i++)
		{
			V8_CHECK_SET_RESULT(argsArray->Set(context, i, args[i + 1]));
		}
	}

	JSExecutor* pCurrentExecutor = _pCurrentExecutor.get();
	if (!pCurrentExecutor) return;
	TimedJSExecutor* pThis = static_cast<TimedJSExecutor*>(pCurrentExecutor);

	CallFunctionTask::Ptr pTask = new CallFunctionTask(pIsolate, pThis, function, argsArray);
	Poco::Timestamp ts;
	pThis->_timer.schedule(pTask, ts);

	TimerWrapper wrapper;
	v8::Persistent<v8::Object>& timerObject(wrapper.wrapNativePersistent(pIsolate, pTask));
	args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, timerObject));
}


void TimedJSExecutor::setTimeout(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	if (args.Length() < 1) return;
	if (!args[0]->IsFunction()) return;
	v8::Local<v8::Function> function = args[0].As<v8::Function>();

	double millisecs = 0.0;
	if (args.Length() > 1)
	{
		if (!args[1]->IsNumber()) return;
		millisecs = args[1]->NumberValue(context).FromMaybe(0.0);
	}

	Poco::UInt32 argsLength = args.Length() > 2 ? args.Length() - 2 : 0;
	v8::Local<v8::Array> argsArray = v8::Array::New(pIsolate, argsLength);
	if (argsLength > 0)
	{
		for (Poco::UInt32 i = 0; i < argsLength; i++)
		{
			V8_CHECK_SET_RESULT(argsArray->Set(context, i, args[i + 2]));
		}
	}

	JSExecutor* pCurrentExecutor = _pCurrentExecutor.get();
	if (!pCurrentExecutor) return;
	TimedJSExecutor* pThis = static_cast<TimedJSExecutor*>(pCurrentExecutor);

	CallFunctionTask::Ptr pTask = new CallFunctionTask(pIsolate, pThis, function, argsArray);
	Poco::Timestamp ts;
	ts += static_cast<Poco::Timestamp::TimeDiff>(millisecs*1000);
	pThis->_timer.schedule(pTask, ts);

	TimerWrapper wrapper;
	v8::Persistent<v8::Object>& timerObject(wrapper.wrapNativePersistent(pIsolate, pTask));
	args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, timerObject));
}


void TimedJSExecutor::setInterval(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::Isolate* pIsolate(args.GetIsolate());
	v8::EscapableHandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	if (args.Length() < 1) return;
	if (!args[0]->IsFunction()) return;
	v8::Local<v8::Function> function = args[0].As<v8::Function>();

	double millisecs = 4.0;
	if (args.Length() > 1)
	{
		if (!args[1]->IsNumber()) return;
		millisecs = args[1]->NumberValue(context).FromMaybe(millisecs);
	}

	Poco::UInt32 argsLength = args.Length() > 2 ? args.Length() - 2 : 0;
	v8::Local<v8::Array> argsArray = v8::Array::New(pIsolate, argsLength);
	if (argsLength > 0)
	{
		for (Poco::UInt32 i = 0; i < argsLength; i++)
		{
			V8_CHECK_SET_RESULT(argsArray->Set(context, i, args[i + 2]));
		}
	}

	JSExecutor* pCurrentExecutor = _pCurrentExecutor.get();
	if (!pCurrentExecutor) return;
	TimedJSExecutor* pThis = static_cast<TimedJSExecutor*>(pCurrentExecutor);

	CallFunctionTask::Ptr pTask = new CallFunctionTask(pIsolate, pThis, function, argsArray);
	pThis->_timer.scheduleAtFixedRate(pTask, static_cast<long>(millisecs), static_cast<long>(millisecs));

	TimerWrapper wrapper;
	v8::Persistent<v8::Object>& timerObject(wrapper.wrapNativePersistent(pIsolate, pTask));
	args.GetReturnValue().Set(v8::Local<v8::Object>::New(pIsolate, timerObject));
}


void TimedJSExecutor::cancelTimer(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	if (args.Length() < 1) return;
	try
	{
		if (Wrapper::isWrapper<CallFunctionTask>(args.GetIsolate(), args[0]))
		{
			CallFunctionTask* pTimerTask = Wrapper::unwrapNativeObject<CallFunctionTask>(args[0]);
			pTimerTask->cancel();
		}
		// Note: Don't report invalid argument for compatibility with JavaScript in browsers
	}
	catch (Poco::Exception& exc)
	{
		Wrapper::returnException(args, exc);
	}
}


void initialize()
{
	static auto pPlatform = v8::platform::NewDefaultPlatform();
	v8::V8::InitializePlatform(pPlatform.get());
	v8::V8::Initialize();
}


void uninitialize()
{
	v8::V8::Dispose();
	v8::V8::ShutdownPlatform();
}


} } } // namespace Poco::JS::Core
