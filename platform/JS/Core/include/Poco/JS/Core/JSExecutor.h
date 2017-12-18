//
// JSExecutor.h
//
// Library: JS/Core
// Package: Execution
// Module:  JSExecutor
//
// Definition of the JSExecutor class.
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef JS_Core_JSExecutor_INCLUDED
#define JS_Core_JSExecutor_INCLUDED


#include "Poco/Poco.h"
#include "Poco/Thread.h"
#include "Poco/ThreadLocal.h"
#include "Poco/AutoPtr.h"
#include "Poco/SharedPtr.h"
#include "Poco/URI.h"
#include "Poco/BasicEvent.h"
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "Poco/JS/Core/ModuleRegistry.h"
#include "Poco/JS/Core/Module.h"
#include "v8.h"
#include <vector>
#include <set>


namespace Poco {
namespace JS {
namespace Core {


class JSCore_API JSExecutor: public Poco::Runnable, public Poco::RefCountedObject
	/// The JSExecutor class executes JavaScript code in a controlled
	/// environment (i.e., with a specific set of global JavaScript objects
	/// set).
{
public:
	typedef Poco::AutoPtr<JSExecutor> Ptr;

	enum 
	{
		DEFAULT_MEMORY_LIMIT = 1024*1024
	};
	
	struct ErrorInfo
	{
		std::string uri;
		std::string message;
		int lineNo;
	};

	Poco::BasicEvent<void> stopped;
		/// Fired when the executor has been stopped.
	
	Poco::BasicEvent<const ErrorInfo> scriptError;
		/// Fired when the script terminates with an error.
		/// Reports the error message as argument.

	JSExecutor(const std::string& source, const Poco::URI& sourceURI, Poco::UInt64 memoryLimit = DEFAULT_MEMORY_LIMIT);
		/// Creates the JSExecutor with the given JavaScript source, sourceURI and memoryLimit.

	JSExecutor(const std::string& source, const Poco::URI& sourceURI, const std::vector<std::string>& moduleSearchPaths, Poco::UInt64 memoryLimit = DEFAULT_MEMORY_LIMIT);
		/// Creates the JSExecutor with the given JavaScript source, sourceURI, module search paths and memoryLimit.
		
	virtual ~JSExecutor();
		/// Destroys the JSExecutor.
		
	const Poco::URI& uri() const;
		/// Returns the script's source URI.

	void call(v8::Handle<v8::Function>& function, v8::Handle<v8::Value>& receiver, int argc, v8::Handle<v8::Value> argv[]);
		/// Calls a specific function defined in the script, using the given arguments.
		///
		/// Sets up a script context scope for the call.

	void callInContext(v8::Handle<v8::Function>& function, v8::Handle<v8::Value>& receiver, int argc, v8::Handle<v8::Value> argv[]);
		/// Calls a specific function defined in the script, using the given arguments.
		///
		/// A script context scope for the call must have been set up by the caller.

	void callInContext(v8::Persistent<v8::Object>& jsObject, const std::string& method, int argc, v8::Handle<v8::Value> argv[]);
		/// Calls a specific method defined in the given object with the given arguments.
		///
		/// A script context scope for the call must have been set up by the caller.

	void call(v8::Persistent<v8::Object>& jsObject, const std::string& method, const std::string& args);
		/// Calls a specific method defined in the given object with the given arguments, which must
		/// be given as a JSON string.
		///
		/// Sets up a script context scope for the call.
		
	void call(v8::Persistent<v8::Function>& function);
		/// Calls a specific function defined in the script, without arguments.
		///
		/// Sets up a script context scope for the call.

	void call(v8::Persistent<v8::Function>& function, v8::Persistent<v8::Array>& args);
		/// Calls a specific function defined in the script, with the given arguments,
		/// which must be in a JavaScript Array.
		///
		/// Sets up a script context scope for the call.

	static Ptr current();
		/// Returns the JSExecutor for the current thread.
	
	v8::Isolate* isolate();
		/// Returns the JSExecutor's Isolate.
		
	v8::Persistent<v8::Context>& globalContext();
		/// Returns the JSExecutor's global context.

	v8::Persistent<v8::Context>& scriptContext();
		/// Returns the JSExecutor's script context.

	bool isRunning() const;
		/// Returns true if the JSExecutor is currently executing a script.
		
	virtual void stop();
		/// Stops the script's execution.
		///
		/// After calling stop(), the JSExecutor can no longer be
		/// used to execute a script by calling run() or call().
		///
		/// Will also fire the stopped event.
		
	void terminate();
		/// Terminate the currently running script.
		///
		/// Note that termination is asynchronous. The script may continue to run
		/// for some time before actually terminating.
		///
		/// After calling terminate(), the JSExecutor is still usable and
		/// execution can be resumed at a later time by calling
		/// run() or call().
		
	void cancelTerminate();
		/// Cancels a previous terminate() call.
		
	bool isTerminating() const;
		/// Returns true if the script is currently terminating due
		/// to a call to terminate().
	
	void addModuleSearchPath(const std::string& path);
		/// Adds a search path to the internal list of search paths.
		///
		/// Module search paths must be added before the script
		/// is executed.
		
	void addModuleRegistry(ModuleRegistry::Ptr pRegistry);
		/// Adds a module registry to the collection of registries.
		///
		/// Module registries must be added before the script
		/// is executed.
		
	// Poco::Runnable
	void run();
		/// Runs the script.

protected:
	virtual void setupGlobalObjectTemplate(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate);
		/// Set up global JavaScript objects in the global object template. 
		/// Can be overridded by subclasses, but overrides must call the base class method.
		///
		/// Note that only other object templates or function templates, as
		/// well as primitive values may be added to the global object template.
		/// Non-primitive types such as objects or arrays must be registered
		/// in setupGlobalObject().
		///
		/// Called before initial compilation of the script.

	virtual void setupGlobalObject(v8::Local<v8::Object>& global, v8::Isolate* pIsolate);
		/// Sets up the script's global object by adding properties to it. 
		/// Can be overridded by subclasses, but overrides must call the base class method.
		///
		/// Called before initial compilation of the script, after setupGlobalObjectTemplate().

	virtual void handleError(const ErrorInfo& errorInfo);
		/// Called when the JavaScript terminates with an error.
		
	virtual void scriptCompleted();
		/// Called after the script has completed, while still within the scope.

	static void include(const v8::FunctionCallbackInfo<v8::Value>& args);
		/// Implements the JavaScript include function to include another script.

	static void require(const v8::FunctionCallbackInfo<v8::Value>& args);
		/// Implements the JavaScript require function to import a module.

	void includeScript(const std::string& uri);
		/// Includes another script.

	void importModule(const v8::FunctionCallbackInfo<v8::Value>& args, const std::string& uri);
		/// Imports a JavaScript module.

	void importModule(const v8::FunctionCallbackInfo<v8::Value>& args, const std::string& uri, Module::Ptr pModule);
		/// Imports a native module.

	Poco::SharedPtr<std::istream> resolveModule(const std::string& uri, Poco::URI& resolvedURI);
		/// Tries to locate the script identified by uri (which may be a relative, partial URI),
		/// and returns a stream for reading the script source if the module has not been
		/// imported yet, or null if the module has already been imported.
		/// If the module URI has been successfully resolved, resolvedURI will contain
		/// the fully-qualified URI. If the module URI cannot be successfully resolved,
		/// a Poco::NotFoundException will be thrown.

	void attachToCurrentThread();
		/// Attaches the JSExecutor to the current thread. Must be called before
		/// any JavaScript code is executed if the JSExecutor is invoked
		/// from a different thread it was created in.

	void runImpl();
	void setup();
	void cleanup();
	void compile();
	void reportError(v8::TryCatch& tryCatch);
	void reportError(const ErrorInfo& errorInfo);

private:
	void init();

	JSExecutor();
	JSExecutor(const JSExecutor&);
	JSExecutor& operator = (const JSExecutor&);

protected:	
	std::string _source;
	Poco::URI _sourceURI;
	std::vector<std::string> _moduleSearchPaths;
	std::vector<ModuleRegistry::Ptr> _moduleRegistries;
	Poco::JS::Core::PooledIsolate _pooledIso;
	v8::Persistent<v8::ObjectTemplate> _globalObjectTemplate;
	v8::Persistent<v8::Context> _globalContext;
	v8::Persistent<v8::Context> _scriptContext;
	v8::Persistent<v8::Script> _script;
	std::vector<Poco::URI> _importStack;
	std::set<std::string> _imports;
	Poco::AtomicCounter _running;
	static Poco::ThreadLocal<JSExecutor*> _pCurrentExecutor;
	
	friend class RunScriptTask;
	friend class CallFunctionTask;
};


class JSCore_API TimedJSExecutor: public JSExecutor
	/// This class extends the basic JSExecutor class with a Poco::Util::Timer-based
	/// event loop, allowing the definition of timers in JavaScript code.
	///
	/// Scripts can use the setTimeout() and setInterval() JavaScript functions to
	/// define timer-based callbacks.
{
public:
	typedef Poco::AutoPtr<TimedJSExecutor> Ptr;

	TimedJSExecutor(const std::string& source, const Poco::URI& sourceURI, const std::vector<std::string>& moduleSearchPaths, Poco::UInt64 memoryLimit = JSExecutor::DEFAULT_MEMORY_LIMIT);
		/// Creates the TimedJSExecutor.
		
	~TimedJSExecutor();
		/// Destroys the TimedJSExecutor.

	void schedule(Poco::Util::TimerTask::Ptr pTask);
		/// Schedules a task using the timer-based event loop.
			
	void schedule(Poco::Util::TimerTask::Ptr pTask, const Poco::Clock& clock);
		/// Schedules a task using the timer-based event loop.
	
	// JSExecutor
	void run();
		/// Runs the script as timer task. Note that run() will return immediately.
		/// The script will be executed within the timer thread.

	void stop();
		/// Stops the executor and cancels all timer events.
	
protected:
	Poco::Util::Timer& timer();	
		/// Returns the executor's timer.

	void setupGlobalObjectTemplate(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate);
	static void setImmediate(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void setTimeout(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void setInterval(const v8::FunctionCallbackInfo<v8::Value>& args);
	static void cancelTimer(const v8::FunctionCallbackInfo<v8::Value>& args);
	
private:
	Poco::Util::Timer _timer;
	bool _stopped;
	Poco::FastMutex _mutex;
	
	friend class RunScriptTask;
	friend class StopScriptTask;
	friend class CallFunctionTask;
};


//
// inlines
//
inline const Poco::URI& JSExecutor::uri() const
{
	return _sourceURI;
}


inline v8::Isolate* JSExecutor::isolate()
{
	return _pooledIso.isolate();
}


inline v8::Persistent<v8::Context>& JSExecutor::globalContext()
{
	return _globalContext;
}


inline v8::Persistent<v8::Context>& JSExecutor::scriptContext()
{
	return _scriptContext;
}


inline bool JSExecutor::isRunning() const
{
	return !!_running;
}


inline Poco::Util::Timer& TimedJSExecutor::timer()
{
	return _timer;
}


} } } // namespace Poco::JS::Core


#endif // JS_Core_JSExecutor_INCLUDED
