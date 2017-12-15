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
// SPDX-License-Identifier: Apache-2.0
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
#include "Poco/JS/Core/JSException.h"
#include "Poco/Delegate.h"
#include "Poco/URIStreamOpener.h"
#include "Poco/StreamCopier.h"
#include "libplatform/libplatform.h"
#include <memory>


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
}


void JSExecutor::cancelTerminate()
{
	_pooledIso.isolate()->CancelTerminateExecution();
}


bool JSExecutor::isTerminating() const
{
	return _pooledIso.isolate()->IsExecutionTerminating();
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

	v8::Local<v8::ObjectTemplate> globalObject = v8::ObjectTemplate::New(pIsolate);
	_globalObjectTemplate.Reset(pIsolate, globalObject);
	setupGlobalObjectTemplate(globalObject, pIsolate);

	v8::Local<v8::Context> scriptContext = v8::Context::New(pIsolate, 0, globalObject);
	_scriptContext.Reset(pIsolate, scriptContext);
}


void JSExecutor::cleanup()
{
	_importStack.clear();
	_imports.clear();

	WeakPersistentWrapperRegistry::cleanupIsolate(_pooledIso.isolate());
}


void JSExecutor::compile()
{
	v8::Isolate* pIsolate = _pooledIso.isolate();
	v8::HandleScope handleScope(pIsolate);

	v8::Local<v8::String> sourceURI = v8::String::NewFromUtf8(pIsolate, _sourceURI.toString().c_str());
	v8::Local<v8::String> source = v8::String::NewFromUtf8(pIsolate, _source.c_str());
	v8::TryCatch tryCatch(pIsolate);
	v8::ScriptOrigin scriptOrigin(sourceURI);
	v8::Local<v8::Script> script = v8::Script::Compile(source, &scriptOrigin);
	if (script.IsEmpty() || tryCatch.HasCaught())
	{
		reportError(tryCatch);
	}
	else
	{
		_script.Reset(pIsolate, script);
	}
}


void JSExecutor::runImpl()
{
	ScopedRunningCounter src(_running);

	attachToCurrentThread();

	v8::Isolate* pIsolate = _pooledIso.isolate();
	v8::Locker locker(pIsolate);
	v8::Isolate::Scope isoScope(pIsolate);
	v8::HandleScope handleScope(pIsolate);

	if (_globalObjectTemplate.IsEmpty())
	{
		setup();
	}

	v8::Local<v8::Context> globalContext = v8::Local<v8::Context>::New(pIsolate, _globalContext);
	v8::Context::Scope globalContextScope(globalContext);

	v8::Local<v8::ObjectTemplate> global(v8::Local<v8::ObjectTemplate>::New(pIsolate, _globalObjectTemplate));

	v8::Local<v8::Context> scriptContext = v8::Local<v8::Context>::New(pIsolate, _scriptContext);
	v8::Context::Scope contextScope(scriptContext);

	if (_script.IsEmpty())
	{
		// Get global/root module and imports
		v8::Local<v8::Object> global = scriptContext->Global();

		v8::Local<v8::Object> moduleObject = v8::Object::New(pIsolate);
		moduleObject->Set(v8::String::NewFromUtf8(pIsolate, "id"), v8::String::NewFromUtf8(pIsolate, _sourceURI.toString().c_str()));
		v8::Local<v8::Object> importsObject = v8::Object::New(pIsolate);
		moduleObject->Set(v8::String::NewFromUtf8(pIsolate, "imports"), importsObject);
		v8::Local<v8::Object> exportsObject = v8::Object::New(pIsolate);
		moduleObject->Set(v8::String::NewFromUtf8(pIsolate, "exports"), exportsObject);
		global->Set(v8::String::NewFromUtf8(pIsolate, "module"), moduleObject);

		setupGlobalObject(global, pIsolate);

		compile();
	}

	if (!_script.IsEmpty())
	{
		pIsolate->CancelTerminateExecution();
		v8::TryCatch tryCatch(pIsolate);
		v8::Local<v8::Script> script(v8::Local<v8::Script>::New(pIsolate, _script));

		v8::Local<v8::Value> result = script->Run();
		if (result.IsEmpty() || tryCatch.HasCaught())
		{
			reportError(tryCatch);
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

	callInContext(function, receiver, argc, argv);
}


void JSExecutor::callInContext(v8::Handle<v8::Function>& function, v8::Handle<v8::Value>& receiver, int argc, v8::Handle<v8::Value> argv[])
{
	ScopedRunningCounter src(_running);

	attachToCurrentThread();

	v8::Isolate* pIsolate = _pooledIso.isolate();
	v8::TryCatch tryCatch(pIsolate);
	function->Call(receiver, argc, argv);
	if (tryCatch.HasCaught())
	{
		reportError(tryCatch);
	}
}


void JSExecutor::callInContext(v8::Persistent<v8::Object>& jsObject, const std::string& method, int argc, v8::Handle<v8::Value> argv[])
{
	ScopedRunningCounter src(_running);

	attachToCurrentThread();

	v8::Isolate* pIsolate = _pooledIso.isolate();

	v8::HandleScope handleScope(pIsolate);

	v8::Local<v8::String> jsMethod = v8::String::NewFromUtf8(pIsolate, method.c_str());

	v8::Local<v8::Object> localObject(v8::Local<v8::Object>::New(pIsolate, jsObject));

	v8::Maybe<bool> hasMethod = localObject->Has(pIsolate->GetCurrentContext(), jsMethod);
	if (hasMethod.IsJust() && hasMethod.FromJust())
	{
		v8::Local<v8::Value> jsValue = localObject->Get(jsMethod);
		if (jsValue->IsFunction())
		{
			v8::Local<v8::Function> jsFunction = v8::Local<v8::Function>::Cast(jsValue);

			v8::TryCatch tryCatch(pIsolate);
			jsFunction->Call(localObject, argc, argv);
			if (tryCatch.HasCaught())
			{
				reportError(tryCatch);
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

	v8::Local<v8::String> jsMethod = v8::String::NewFromUtf8(pIsolate, method.c_str());
	v8::Local<v8::String> jsArgs = v8::String::NewFromUtf8(pIsolate, args.c_str());

	v8::Local<v8::Object> localObject(v8::Local<v8::Object>::New(pIsolate, jsObject));

	if (localObject->Has(jsMethod))
	{
		v8::Local<v8::Value> jsValue = localObject->Get(jsMethod);
		if (jsValue->IsFunction())
		{
			v8::Local<v8::Function> jsFunction = v8::Local<v8::Function>::Cast(jsValue);

			v8::TryCatch tryCatch(pIsolate);
			v8::MaybeLocal<v8::Value> maybeArgs = v8::JSON::Parse(pIsolate, jsArgs);
			if (!maybeArgs.IsEmpty())
			{
				v8::Local<v8::Value> argv[1] = { maybeArgs.ToLocalChecked() };
				jsFunction->Call(localObject, 1, argv);
				if (tryCatch.HasCaught())
				{
					reportError(tryCatch);
				}
			}
			else
			{
				ErrorInfo errorInfo;
				errorInfo.uri = _sourceURI.toString();
				errorInfo.lineNo = 0;
				errorInfo.message = "JSExecutor::call(): failed to parse JSON arguments: " + args;
				reportError(errorInfo);
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

	localFunction->Call(global, 0, argv);
	if (tryCatch.HasCaught())
	{
		reportError(tryCatch);
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
			argv[i] = localArgs->Get(i);
		}
	}

	v8::TryCatch tryCatch(pIsolate);
	localFunction->Call(global, argsLength, argv);
	if (tryCatch.HasCaught())
	{
		reportError(tryCatch);
	}
}


void JSExecutor::includeScript(const std::string& uri)
{
	v8::Isolate* pIsolate = _pooledIso.isolate();
	v8::HandleScope handleScope(pIsolate);

	v8::Local<v8::Context> context(v8::Local<v8::Context>::New(pIsolate, _scriptContext));
	v8::Context::Scope contextScope(context);

	Poco::URI includeURI(_sourceURI, uri);
#if __cplusplus < 201103L
	std::auto_ptr<std::istream> istr(Poco::URIStreamOpener::defaultOpener().open(includeURI));
#else
	std::unique_ptr<std::istream> istr(Poco::URIStreamOpener::defaultOpener().open(includeURI));
#endif
	std::string source;
	Poco::StreamCopier::copyToString(*istr, source);

	v8::Local<v8::String> sourceURI = v8::String::NewFromUtf8(pIsolate, includeURI.toString().c_str());
	v8::Local<v8::String> sourceObject = v8::String::NewFromUtf8(pIsolate, source.c_str());
	v8::TryCatch tryCatch(pIsolate);
	v8::ScriptOrigin scriptOrigin(sourceURI);
	v8::Local<v8::Script> scriptObject = v8::Script::Compile(sourceObject, &scriptOrigin);
	if (scriptObject.IsEmpty() || tryCatch.HasCaught())
	{
		reportError(tryCatch);
	}
	else
	{
		v8::Local<v8::Value> result = scriptObject->Run();
		if (result.IsEmpty() || tryCatch.HasCaught())
		{
			reportError(tryCatch);
		}
	}
}


void JSExecutor::setupGlobalObjectTemplate(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate)
{
	Poco::JS::Core::DateTimeWrapper dateTimeWrapper;
	global->Set(v8::String::NewFromUtf8(pIsolate, "DateTime"), dateTimeWrapper.constructor(pIsolate));

	Poco::JS::Core::LocalDateTimeWrapper localDateTimeWrapper;
	global->Set(v8::String::NewFromUtf8(pIsolate, "LocalDateTime"), localDateTimeWrapper.constructor(pIsolate));

	Poco::JS::Core::BufferWrapper bufferWrapper;
	global->Set(v8::String::NewFromUtf8(pIsolate, "Buffer"), bufferWrapper.constructor(pIsolate));

	Poco::JS::Core::LoggerWrapper loggerWrapper;
	global->Set(v8::String::NewFromUtf8(pIsolate, "Logger"), loggerWrapper.constructor(pIsolate));

	global->Set(v8::String::NewFromUtf8(pIsolate, "include"), v8::FunctionTemplate::New(pIsolate, include));
	global->Set(v8::String::NewFromUtf8(pIsolate, "require"), v8::FunctionTemplate::New(pIsolate, require));
}


void JSExecutor::setupGlobalObject(v8::Local<v8::Object>& global, v8::Isolate* pIsolate)
{
	Poco::JS::Core::SystemWrapper systemWrapper;
	v8::Local<v8::Object> systemObject = systemWrapper.wrapNative(pIsolate);
	global->Set(v8::String::NewFromUtf8(pIsolate, "system"), systemObject);

	Poco::JS::Core::ApplicationWrapper applicationWrapper;
	v8::Local<v8::Object> applicationObject = applicationWrapper.wrapNative(pIsolate);
	global->Set(v8::String::NewFromUtf8(pIsolate, "application"), applicationObject);

	Poco::JS::Core::URIWrapper uriWrapper;
	v8::Local<v8::Object> uriObject = uriWrapper.wrapNative(pIsolate);
	global->Set(v8::String::NewFromUtf8(pIsolate, "uri"), uriObject);
}


void JSExecutor::handleError(const ErrorInfo& errorInfo)
{
}


void JSExecutor::reportError(v8::TryCatch& tryCatch)
{
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
		v8::String::Utf8Value str(exception);
		errorInfo.message = *str;
	}
	v8::Local<v8::Message> message = tryCatch.Message();
	if (!message.IsEmpty())
	{
		v8::String::Utf8Value str(message->GetScriptResourceName());
		errorInfo.uri = *str;
		errorInfo.lineNo = message->GetLineNumber();
	}
	reportError(errorInfo);
}


void JSExecutor::reportError(const ErrorInfo& errorInfo)
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


void JSExecutor::scriptCompleted()
{
}


void JSExecutor::include(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::EscapableHandleScope handleScope(args.GetIsolate());

	if (args.Length() != 1) return;
	std::string uri(Poco::JS::Core::Wrapper::toString(args[0]));

	JSExecutor* pCurrentExecutor = _pCurrentExecutor.get();
	if (!pCurrentExecutor) return;

	try
	{
		pCurrentExecutor->includeScript(uri);
	}
	catch (Poco::Exception& exc)
	{
		Poco::JS::Core::Wrapper::returnException(args, exc);
	}
}


void JSExecutor::require(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::EscapableHandleScope handleScope(args.GetIsolate());

	if (args.Length() != 1) return;
	std::string uri(Poco::JS::Core::Wrapper::toString(args[0]));

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
	v8::Local<v8::Object> globalModule = v8::Local<v8::Object>::Cast(global->Get(v8::String::NewFromUtf8(pIsolate, "module")));
	poco_assert_dbg (globalModule->IsObject());
	v8::Local<v8::Object> globalImports = v8::Local<v8::Object>::Cast(globalModule->Get(v8::String::NewFromUtf8(pIsolate, "imports")));
	poco_assert_dbg (globalImports->IsObject());

	// Check if we have already imported the module
	v8::Local<v8::String> jsModuleURI = v8::String::NewFromUtf8(pIsolate, moduleURIString.c_str());
	if (globalImports->Has(jsModuleURI))
	{
		poco_assert (!pStream);
		args.GetReturnValue().Set(globalImports->Get(jsModuleURI));
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
		moduleObject->Set(v8::String::NewFromUtf8(pIsolate, "id"), jsModuleURI);
		v8::Local<v8::Object> exportsObject = v8::Object::New(pIsolate);
		moduleObject->Set(v8::String::NewFromUtf8(pIsolate, "exports"), exportsObject);
		moduleGlobal->Set(v8::String::NewFromUtf8(pIsolate, "module"), moduleObject);
		moduleGlobal->Set(v8::String::NewFromUtf8(pIsolate, "exports"), exportsObject);

		setupGlobalObject(moduleGlobal, pIsolate);

		globalImports->Set(jsModuleURI, exportsObject);

		std::string source;
		Poco::StreamCopier::copyToString(*pStream, source);

		v8::Local<v8::String> sourceObject = v8::String::NewFromUtf8(pIsolate, source.c_str());
		v8::TryCatch tryCatch(pIsolate);
		v8::ScriptOrigin scriptOrigin(jsModuleURI);
		v8::Local<v8::Script> scriptObject = v8::Script::Compile(sourceObject, &scriptOrigin);
		if (scriptObject.IsEmpty() || tryCatch.HasCaught())
		{
			args.GetReturnValue().Set(tryCatch.ReThrow());
		}
		else
		{
			v8::Local<v8::Value> result = scriptObject->Run();
			if (result.IsEmpty() || tryCatch.HasCaught())
			{
				args.GetReturnValue().Set(tryCatch.ReThrow());
			}
			else
			{
				// Note: we cannot use the exports handle from above as the script may
				// have assigned a new object to module.exports.
				v8::Local<v8::Value> newExportsObject = moduleObject->Get(v8::String::NewFromUtf8(pIsolate, "exports"));
				globalImports->Set(jsModuleURI, newExportsObject);
				args.GetReturnValue().Set(newExportsObject);
			}
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
	v8::Local<v8::Object> globalModule = v8::Local<v8::Object>::Cast(global->Get(v8::String::NewFromUtf8(pIsolate, "module")));
	poco_assert_dbg (globalModule->IsObject());
	v8::Local<v8::Object> globalImports = v8::Local<v8::Object>::Cast(globalModule->Get(v8::String::NewFromUtf8(pIsolate, "imports")));
	poco_assert_dbg (globalImports->IsObject());

	// Check if we have already imported the module
	v8::Local<v8::String> jsModuleURI = v8::String::NewFromUtf8(pIsolate, uri.c_str());
	if (globalImports->Has(jsModuleURI))
	{
		args.GetReturnValue().Set(globalImports->Get(jsModuleURI));
	}
	else
	{
		v8::Local<v8::Object> exportsObject = pModule->exportIt(pIsolate);
		globalImports->Set(jsModuleURI, exportsObject);
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
	typedef Poco::AutoPtr<RunScriptTask> Ptr;

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
// StopScriptTask
//


class StopScriptTask: public Poco::Util::TimerTask
{
public:
	typedef Poco::AutoPtr<StopScriptTask> Ptr;

	StopScriptTask(TimedJSExecutor* pExecutor):
		_pExecutor(pExecutor, true)
	{
	}

	void run()
	{
		_pExecutor->_timer.cancel(false);
		_stopped.set();
	}

	void wait()
	{
		_pExecutor->terminate();
		while (!_stopped.tryWait(200))
		{
			_pExecutor->terminate();
		}
	}

private:
	TimedJSExecutor::Ptr _pExecutor;
	Poco::Event _stopped;
};


//
// CallFunctionTask
//


class CallFunctionTask: public Poco::Util::TimerTask
{
public:
	typedef Poco::AutoPtr<CallFunctionTask> Ptr;

	CallFunctionTask(v8::Isolate* pIsolate, TimedJSExecutor* pExecutor, v8::Handle<v8::Function> function):
		_pExecutor(pExecutor, true),
		_function(pIsolate, function)
	{
		_pExecutor->stopped += Poco::delegate(this, &CallFunctionTask::onExecutorStopped);
	}

	CallFunctionTask(v8::Isolate* pIsolate, TimedJSExecutor* pExecutor, v8::Handle<v8::Function> function, v8::Handle<v8::Array> arguments):
		_pExecutor(pExecutor, true),
		_function(pIsolate, function),
		_arguments(pIsolate, arguments)
	{
		_pExecutor->stopped += Poco::delegate(this, &CallFunctionTask::onExecutorStopped);
	}

	~CallFunctionTask()
	{
		try
		{
			if (_pExecutor)
			{
				_pExecutor->stopped -= Poco::delegate(this, &CallFunctionTask::onExecutorStopped);
				_pExecutor = 0;
			}
		}
		catch (...)
		{
			poco_unexpected();
		}
		_function.Reset();
		_arguments.Reset();
	}

	void run()
	{
		TimedJSExecutor::Ptr pExecutor = _pExecutor;
		if (pExecutor)
		{
			pExecutor->call(_function, _arguments);
		}
	}

	void onExecutorStopped()
	{
		if (_pExecutor)
		{
			_pExecutor->stopped -= Poco::delegate(this, &CallFunctionTask::onExecutorStopped);
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

	global->Set(v8::String::NewFromUtf8(pIsolate, "setImmediate"), v8::FunctionTemplate::New(pIsolate, setImmediate));
	global->Set(v8::String::NewFromUtf8(pIsolate, "setTimeout"), v8::FunctionTemplate::New(pIsolate, setTimeout));
	global->Set(v8::String::NewFromUtf8(pIsolate, "setInterval"), v8::FunctionTemplate::New(pIsolate, setInterval));
	global->Set(v8::String::NewFromUtf8(pIsolate, "clearImmediate"), v8::FunctionTemplate::New(pIsolate, cancelTimer));
	global->Set(v8::String::NewFromUtf8(pIsolate, "clearTimeout"), v8::FunctionTemplate::New(pIsolate, cancelTimer));
	global->Set(v8::String::NewFromUtf8(pIsolate, "clearInterval"), v8::FunctionTemplate::New(pIsolate, cancelTimer));
}


void TimedJSExecutor::schedule(Poco::Util::TimerTask::Ptr pTask)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (!_stopped)
	{
		_timer.schedule(pTask, Poco::Clock());
	}
}


void TimedJSExecutor::schedule(Poco::Util::TimerTask::Ptr pTask, const Poco::Clock& clock)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (!_stopped)
	{
		_timer.schedule(pTask, clock);
	}
}


void TimedJSExecutor::stop()
{
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		if (_stopped) return;

		_stopped = true;
	}

	StopScriptTask::Ptr pStopTask = new StopScriptTask(this);
	_timer.schedule(pStopTask, Poco::Clock());
	pStopTask->wait();
	pStopTask = 0;

	stopped(this);

	cleanup();
}


void TimedJSExecutor::setImmediate(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::EscapableHandleScope handleScope(args.GetIsolate());

	if (args.Length() < 1) return;
	if (!args[0]->IsFunction()) return;
	v8::Local<v8::Function> function = args[0].As<v8::Function>();

	Poco::UInt32 argsLength = args.Length() > 1 ? args.Length() - 1 : 0;
	v8::Local<v8::Array> argsArray = v8::Array::New(args.GetIsolate(), argsLength);
	if (argsLength > 0)
	{
		for (Poco::UInt32 i = 0; i < argsLength; i++)
		{
			argsArray->Set(i, args[i + 1]);
		}
	}

	JSExecutor* pCurrentExecutor = _pCurrentExecutor.get();
	if (!pCurrentExecutor) return;
	TimedJSExecutor* pThis = static_cast<TimedJSExecutor*>(pCurrentExecutor);

	CallFunctionTask::Ptr pTask = new CallFunctionTask(args.GetIsolate(), pThis, function, argsArray);
	Poco::Timestamp ts;
	pThis->_timer.schedule(pTask, ts);
	TimerWrapper wrapper;
	v8::Persistent<v8::Object> timerObject(args.GetIsolate(), wrapper.wrapNativePersistent(args.GetIsolate(), pTask));
	args.GetReturnValue().Set(timerObject);
}


void TimedJSExecutor::setTimeout(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::EscapableHandleScope handleScope(args.GetIsolate());

	if (args.Length() < 2) return;
	if (!args[0]->IsFunction()) return;
	v8::Local<v8::Function> function = args[0].As<v8::Function>();
	if (!args[1]->IsNumber()) return;
	double millisecs = args[1]->NumberValue();

	Poco::UInt32 argsLength = args.Length() > 2 ? args.Length() - 2 : 0;
	v8::Local<v8::Array> argsArray = v8::Array::New(args.GetIsolate(), argsLength);
	if (argsLength > 0)
	{
		for (Poco::UInt32 i = 0; i < argsLength; i++)
		{
			argsArray->Set(i, args[i + 2]);
		}
	}

	JSExecutor* pCurrentExecutor = _pCurrentExecutor.get();
	if (!pCurrentExecutor) return;
	TimedJSExecutor* pThis = static_cast<TimedJSExecutor*>(pCurrentExecutor);

	CallFunctionTask::Ptr pTask = new CallFunctionTask(args.GetIsolate(), pThis, function, argsArray);
	Poco::Timestamp ts;
	ts += static_cast<Poco::Timestamp::TimeDiff>(millisecs*1000);
	pThis->_timer.schedule(pTask, ts);
	TimerWrapper wrapper;
	v8::Persistent<v8::Object> timerObject(args.GetIsolate(), wrapper.wrapNativePersistent(args.GetIsolate(), pTask));
	args.GetReturnValue().Set(timerObject);
}


void TimedJSExecutor::setInterval(const v8::FunctionCallbackInfo<v8::Value>& args)
{
	v8::EscapableHandleScope handleScope(args.GetIsolate());

	if (args.Length() < 2) return;
	if (!args[0]->IsFunction()) return;
	v8::Local<v8::Function> function = args[0].As<v8::Function>();
	if (!args[1]->IsNumber()) return;
	double millisecs = args[1]->NumberValue();

	Poco::UInt32 argsLength = args.Length() > 2 ? args.Length() - 2 : 0;
	v8::Local<v8::Array> argsArray = v8::Array::New(args.GetIsolate(), argsLength);
	if (argsLength > 0)
	{
		for (Poco::UInt32 i = 0; i < argsLength; i++)
		{
			argsArray->Set(i, args[i + 2]);
		}
	}

	JSExecutor* pCurrentExecutor = _pCurrentExecutor.get();
	if (!pCurrentExecutor) return;
	TimedJSExecutor* pThis = static_cast<TimedJSExecutor*>(pCurrentExecutor);

	CallFunctionTask::Ptr pTask = new CallFunctionTask(args.GetIsolate(), pThis, function, argsArray);
	pThis->_timer.scheduleAtFixedRate(pTask, static_cast<long>(millisecs), static_cast<long>(millisecs));
	TimerWrapper wrapper;
	v8::Persistent<v8::Object> timerObject(args.GetIsolate(), wrapper.wrapNativePersistent(args.GetIsolate(), pTask));
	args.GetReturnValue().Set(timerObject);
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
		else throw Poco::InvalidArgumentException("Invalid object passed to clearImmediate(), clearTimer() or clearTimeout()");
	}
	catch (Poco::Exception& exc)
	{
		Wrapper::returnException(args, exc);
	}
}


void initialize()
{
	v8::V8::InitializePlatform(v8::platform::CreateDefaultPlatform());
	v8::V8::Initialize();
}


void uninitialize()
{
	v8::V8::Dispose();
	v8::V8::ShutdownPlatform();
}


} } } // namespace Poco::JS::Core
