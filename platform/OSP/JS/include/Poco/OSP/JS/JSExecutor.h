//
// JSExecutor.h
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JS_JSExecutor_INCLUDED
#define OSP_JS_JSExecutor_INCLUDED


#include "Poco/OSP/JS/JS.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/BundleEvent.h"
#include "Poco/JS/Core/JSExecutor.h"
#include "Poco/JS/Core/PooledIsolate.h"
#include "v8.h"


namespace Poco {
namespace OSP {
namespace JS {


class OSPJS_API JSExecutor: public Poco::JS::Core::JSExecutor
	/// An extension of the Poco::JS::Core::JSExecutor for executing JavaScript
	/// code within an OSP environment.
	///
	/// Adds the following global JavaScript objects:
	///   - bundle (Poco::OSP::Bundle wrapper)
	///   - properties (bundle properties wrapper)
	///   - serviceRegistry (Poco::OSP::ServiceRegistry wrapper)
	///   - logger (bundle context logger wrapper)
	///   - HTTPRequest (HTTP request constructor)
	///   - DBSession (Database session constructor)
{
public:
	using Ptr = Poco::AutoPtr<JSExecutor>;

	JSExecutor(Poco::OSP::BundleContext::Ptr pContext, Poco::OSP::Bundle::Ptr pBundle, const std::string& source, const Poco::URI& sourceURI, const std::vector<std::string>& moduleSearchPaths, Poco::UInt64 memoryLimit);
		/// Creates the JSExecutor.

	~JSExecutor();
		/// Destroys the JSExecutor.

	Poco::OSP::Bundle::Ptr bundle() const;
		/// Returns the bundle containing the script.

	Poco::OSP::BundleContext::Ptr context() const;
		/// Returns the bundle context.

	static const std::vector<std::string> getGlobalModuleSearchPaths();
		/// Returns the global module search paths.

	static void setGlobalModuleSearchPaths(const std::vector<std::string>& searchPaths);
		/// Sets the global module search paths.

	static void setGlobalModuleRegistry(Poco::JS::Core::ModuleRegistry::Ptr pModuleRegistry);
		/// Sets the global module registry.

	static Poco::JS::Core::ModuleRegistry::Ptr getGlobalModuleRegistry();
		/// Returns the global module registry.

	static void setDefaultMemoryLimit(Poco::UInt64 memoryLimit);
		/// Sets the global default memory limit for scripts.

	static Poco::UInt64 getDefaultMemoryLimit();
		/// Returns the global default memory limit for scripts.

	static std::string formatErrorInfo(const ErrorInfo& errorInfo);
		/// Formats the given error information to a string suitable for logging.

protected:
	void setupGlobalObjectTemplate(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate);
	void setupGlobalObject(v8::Local<v8::Object>& global, v8::Isolate* pIsolate);
	void handleError(const ErrorInfo& errorInfo);
	void handleOutOfMemory(std::size_t currentHeapLimit, std::size_t initialHeapLimit);
	void handleMemoryWarning(std::size_t currentHeapLimit, std::size_t initialHeapLimit);

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::Bundle::Ptr _pBundle;

	static std::vector<std::string> _globalModuleSearchPaths;
	static Poco::JS::Core::ModuleRegistry::Ptr _globalModuleRegistry;
	static Poco::UInt64 _defaultMemoryLimit;
};


class OSPJS_API TimedJSExecutor: public Poco::JS::Core::TimedJSExecutor
	/// An extension of the Poco::JS::Core::TimedJSExecutor for executing JavaScript
	/// code within an OSP environment.
	///
	/// Will stop the executing JavaScript when the containing bundle
	/// is stopped.
	///
	/// Adds the following global JavaScript objects:
	///   - bundle (Poco::OSP::Bundle wrapper)
	///   - properties (bundle properties wrapper)
	///   - serviceRegistry (Poco::OSP::ServiceRegistry wrapper)
	///   - logger (bundle context logger wrapper)
	///   - HTTPRequest (HTTP request constructor)
	///   - DBSession (Database session constructor)
{
public:
	using Ptr = Poco::AutoPtr<TimedJSExecutor>;

	TimedJSExecutor(Poco::OSP::BundleContext::Ptr pContext, Poco::OSP::Bundle::Ptr pBundle, const std::string& source, const Poco::URI& sourceURI, const std::vector<std::string>& moduleSearchPaths, Poco::UInt64 memoryLimit);
		/// Creates the TimedJSExecutor.

	~TimedJSExecutor();
		/// Destroys the TimedJSExecutor.

	Poco::OSP::Bundle::Ptr bundle() const;
		/// Returns the bundle containing the script.

	Poco::OSP::BundleContext::Ptr context() const;
		/// Returns the bundle context.

protected:
	void setupGlobalObjectTemplate(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate);
	void setupGlobalObject(v8::Local<v8::Object>& global, v8::Isolate* pIsolate);
	void handleError(const ErrorInfo& errorInfo);
	void handleOutOfMemory(std::size_t currentHeapLimit, std::size_t initialHeapLimit);
	void handleMemoryWarning(std::size_t currentHeapLimit, std::size_t initialHeapLimit);
	void onBundleStopped(const void* pSender, Poco::OSP::BundleEvent& ev);

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::Bundle::Ptr _pBundle;
};


//
// inlines
//
inline Poco::OSP::Bundle::Ptr JSExecutor::bundle() const
{
	return _pBundle;
}


inline Poco::OSP::BundleContext::Ptr JSExecutor::context() const
{
	return _pContext;
}


inline const std::vector<std::string> JSExecutor::getGlobalModuleSearchPaths()
{
	return _globalModuleSearchPaths;
}


inline Poco::JS::Core::ModuleRegistry::Ptr JSExecutor::getGlobalModuleRegistry()
{
	return _globalModuleRegistry;
}


inline Poco::OSP::Bundle::Ptr TimedJSExecutor::bundle() const
{
	return _pBundle;
}


inline Poco::OSP::BundleContext::Ptr TimedJSExecutor::context() const
{
	return _pContext;
}


} } } // namespace Poco::OSP::JS


#endif // OSP_JS_JSExecutor_INCLUDED
