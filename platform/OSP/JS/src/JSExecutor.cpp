//
// JSExecutor.cpp
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/JS/JSExecutor.h"
#include "Poco/OSP/JS/BundleWrapper.h"
#include "Poco/OSP/JS/ServiceRegistryWrapper.h"
#include "Poco/JS/Core/LoggerWrapper.h"
#include "Poco/JS/Core/ConsoleWrapper.h"
#include "Poco/JS/Core/ConfigurationWrapper.h"
#include "Poco/OSP/BundleEvents.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"


namespace Poco {
namespace OSP {
namespace JS {


std::vector<std::string> JSExecutor::_globalModuleSearchPaths;
Poco::JS::Core::ModuleRegistry::Ptr JSExecutor::_globalModuleRegistry;
Poco::UInt64 JSExecutor::_defaultMemoryLimit(1024*1024);


JSExecutor::JSExecutor(Poco::OSP::BundleContext::Ptr pContext, Poco::OSP::Bundle::Ptr pBundle, const std::string& source, const Poco::URI& sourceURI, const std::vector<std::string>& moduleSearchPaths, Poco::UInt64 memoryLimit):
	Poco::JS::Core::JSExecutor(source, sourceURI, moduleSearchPaths, memoryLimit),
	_pContext(pContext),
	_pBundle(pBundle)
{
	const std::vector<std::string>& paths = getGlobalModuleSearchPaths();
	for (std::vector<std::string>::const_iterator it = paths.begin(); it != paths.end(); ++it)
	{
		addModuleSearchPath(*it);
	}
	
	if (_globalModuleRegistry)
	{
		addModuleRegistry(_globalModuleRegistry);
	}
}


JSExecutor::~JSExecutor()
{
}


void JSExecutor::setupGlobalObjectTemplate(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate)
{
	Poco::JS::Core::JSExecutor::setupGlobalObjectTemplate(global, pIsolate);
}


void JSExecutor::setupGlobalObject(v8::Local<v8::Object>& global, v8::Isolate* pIsolate)
{
	Poco::JS::Core::JSExecutor::setupGlobalObject(global, pIsolate);

	BundleWrapper bundleWrapper;
	v8::Local<v8::Object> bundleObject = bundleWrapper.wrapNative(pIsolate, const_cast<Poco::OSP::Bundle*>(_pBundle.get()));
	bundleObject->Set(v8::String::NewFromUtf8(pIsolate, "temporaryDirectory"), v8::String::NewFromUtf8(pIsolate, _pContext->temporaryDirectory().toString().c_str()));
	bundleObject->Set(v8::String::NewFromUtf8(pIsolate, "persistentDirectory"), v8::String::NewFromUtf8(pIsolate, _pContext->persistentDirectory().toString().c_str()));
	global->Set(v8::String::NewFromUtf8(pIsolate, "bundle"), bundleObject);

	Poco::JS::Core::ConfigurationWrapper configurationWrapper;
	v8::Local<v8::Object> configurationObject = configurationWrapper.wrapNative(pIsolate, const_cast<Poco::Util::AbstractConfiguration*>(&_pBundle->properties()));
	bundleObject->Set(v8::String::NewFromUtf8(pIsolate, "properties"), configurationObject);

	ServiceRegistryWrapper serviceRegistryWrapper;
	v8::Local<v8::Object> serviceRegistryObject = serviceRegistryWrapper.wrapNative(pIsolate, &_pContext->registry());
	global->Set(v8::String::NewFromUtf8(pIsolate, "serviceRegistry"), serviceRegistryObject);

	Poco::JS::Core::LoggerWrapper loggerWrapper;
	v8::Local<v8::Object> loggerObject = loggerWrapper.wrapNative(pIsolate, &_pContext->logger());
	global->Set(v8::String::NewFromUtf8(pIsolate, "logger"), loggerObject);

	Poco::JS::Core::ConsoleWrapper consoleWrapper;
	v8::Local<v8::Object> consoleObject = consoleWrapper.wrapNative(pIsolate, &_pContext->logger());
	global->Set(v8::String::NewFromUtf8(pIsolate, "console"), consoleObject);
}


void JSExecutor::handleError(const ErrorInfo& errorInfo)
{
	std::string fullMessage(errorInfo.message);
	fullMessage += " [in \"";
	fullMessage += errorInfo.uri;
	fullMessage += "\"";
	if (errorInfo.lineNo)
	{
		fullMessage += Poco::format(", line %d", errorInfo.lineNo);
	}
	fullMessage += "]";

	if (errorInfo.message == "Terminated")
		_pContext->logger().notice(fullMessage);
	else
		_pContext->logger().error(fullMessage);
}


void JSExecutor::setGlobalModuleSearchPaths(const std::vector<std::string>& searchPaths)
{
	_globalModuleSearchPaths = searchPaths;
}


void JSExecutor::setGlobalModuleRegistry(Poco::JS::Core::ModuleRegistry::Ptr pModuleRegistry)
{
	_globalModuleRegistry = pModuleRegistry;
}


void JSExecutor::setDefaultMemoryLimit(Poco::UInt64 memoryLimit)
{
	_defaultMemoryLimit = memoryLimit;
}


Poco::UInt64 JSExecutor::getDefaultMemoryLimit()
{
	return _defaultMemoryLimit;
}


TimedJSExecutor::TimedJSExecutor(Poco::OSP::BundleContext::Ptr pContext, Poco::OSP::Bundle::Ptr pBundle, const std::string& source, const Poco::URI& sourceURI, const std::vector<std::string>& moduleSearchPaths, Poco::UInt64 memoryLimit):
	Poco::JS::Core::TimedJSExecutor(source, sourceURI, moduleSearchPaths, memoryLimit),
	_pContext(pContext),
	_pBundle(pBundle)
{
	const std::vector<std::string>& paths = Poco::OSP::JS::JSExecutor::getGlobalModuleSearchPaths();
	for (std::vector<std::string>::const_iterator it = paths.begin(); it != paths.end(); ++it)
	{
		addModuleSearchPath(*it);
	}

	if (Poco::OSP::JS::JSExecutor::getGlobalModuleRegistry())
	{
		addModuleRegistry(Poco::OSP::JS::JSExecutor::getGlobalModuleRegistry());
	}

	pContext->events().bundleStopped += Poco::delegate(this, &TimedJSExecutor::onBundleStopped);
}


TimedJSExecutor::~TimedJSExecutor()
{
	try
	{
		_pContext->events().bundleStopped -= Poco::delegate(this, &TimedJSExecutor::onBundleStopped);
		stop();
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void TimedJSExecutor::setupGlobalObjectTemplate(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate)
{
	Poco::JS::Core::TimedJSExecutor::setupGlobalObjectTemplate(global, pIsolate);
}


void TimedJSExecutor::setupGlobalObject(v8::Local<v8::Object>& global, v8::Isolate* pIsolate)
{
	Poco::JS::Core::JSExecutor::setupGlobalObject(global, pIsolate);

	BundleWrapper bundleWrapper;
	v8::Local<v8::Object> bundleObject = bundleWrapper.wrapNative(pIsolate, const_cast<Poco::OSP::Bundle*>(_pBundle.get()));
	bundleObject->Set(v8::String::NewFromUtf8(pIsolate, "temporaryDirectory"), v8::String::NewFromUtf8(pIsolate, _pContext->temporaryDirectory().toString().c_str()));
	bundleObject->Set(v8::String::NewFromUtf8(pIsolate, "persistentDirectory"), v8::String::NewFromUtf8(pIsolate, _pContext->persistentDirectory().toString().c_str()));
	global->Set(v8::String::NewFromUtf8(pIsolate, "bundle"), bundleObject);

	Poco::JS::Core::ConfigurationWrapper configurationWrapper;
	v8::Local<v8::Object> configurationObject = configurationWrapper.wrapNative(pIsolate, const_cast<Poco::Util::AbstractConfiguration*>(&_pBundle->properties()));
	bundleObject->Set(v8::String::NewFromUtf8(pIsolate, "properties"), configurationObject);

	ServiceRegistryWrapper serviceRegistryWrapper;
	v8::Local<v8::Object> serviceRegistryObject = serviceRegistryWrapper.wrapNative(pIsolate, &_pContext->registry());
	global->Set(v8::String::NewFromUtf8(pIsolate, "serviceRegistry"), serviceRegistryObject);

	Poco::JS::Core::LoggerWrapper loggerWrapper;
	v8::Local<v8::Object> loggerObject = loggerWrapper.wrapNative(pIsolate, &_pContext->logger());
	global->Set(v8::String::NewFromUtf8(pIsolate, "logger"), loggerObject);

	Poco::JS::Core::ConsoleWrapper consoleWrapper;
	v8::Local<v8::Object> consoleObject = consoleWrapper.wrapNative(pIsolate, &_pContext->logger());
	global->Set(v8::String::NewFromUtf8(pIsolate, "console"), consoleObject);
}


void TimedJSExecutor::handleError(const ErrorInfo& errorInfo)
{
	std::string fullMessage(errorInfo.message);
	fullMessage += " [in \"";
	fullMessage += errorInfo.uri;
	fullMessage += "\"";
	if (errorInfo.lineNo)
	{
		fullMessage += Poco::format(", line %d", errorInfo.lineNo);
	}
	fullMessage += "]";

	if (errorInfo.message == "Terminated")
		_pContext->logger().notice(fullMessage);
	else
		_pContext->logger().error(fullMessage);
}


void TimedJSExecutor::onBundleStopped(const void* pSender, Poco::OSP::BundleEvent& ev)
{
	if (ev.bundle() == _pBundle)
	{
		TimedJSExecutor::Ptr pThis(this, true);
		stop();
	}
}


} } } // namespace Poco::OSP::JS
