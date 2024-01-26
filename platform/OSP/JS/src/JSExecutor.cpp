//
// JSExecutor.cpp
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/JS/JSExecutor.h"
#include "Poco/OSP/JS/BundleWrapper.h"
#include "Poco/OSP/JS/BundleContextWrapper.h"
#include "Poco/OSP/JS/ServiceRegistryWrapper.h"
#include "Poco/JS/Core/LoggerWrapper.h"
#include "Poco/JS/Core/ConsoleWrapper.h"
#include "Poco/JS/Core/ConfigurationWrapper.h"
#include "Poco/OSP/BundleEvents.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"


using Poco::JS::Core::Wrapper;
using namespace std::string_literals;


namespace Poco {
namespace OSP {
namespace JS {


std::vector<std::string> JSExecutor::_globalModuleSearchPaths;
Poco::JS::Core::ModuleRegistry::Ptr JSExecutor::_globalModuleRegistry;
Poco::UInt64 JSExecutor::_defaultMemoryLimit(Poco::JS::Core::JSExecutor::DEFAULT_MEMORY_LIMIT);


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

	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	BundleWrapper bundleWrapper;
	v8::MaybeLocal<v8::Object> maybeBundleObject = bundleWrapper.wrapNative(pIsolate, const_cast<Poco::OSP::Bundle*>(_pBundle.get()));
	v8::Local<v8::Object> bundleObject;
	if (maybeBundleObject.ToLocal(&bundleObject))
	{
		V8_CHECK_SET_RESULT(bundleObject->Set(context, Wrapper::toV8Internalized(pIsolate, "temporaryDirectory"s), Wrapper::toV8String(pIsolate, _pContext->temporaryDirectory().toString())));
		V8_CHECK_SET_RESULT(bundleObject->Set(context, Wrapper::toV8Internalized(pIsolate, "persistentDirectory"s), Wrapper::toV8String(pIsolate, _pContext->persistentDirectory().toString())));
		V8_CHECK_SET_RESULT(global->Set(context, Wrapper::toV8Internalized(pIsolate, "bundle"s), bundleObject));

		setWrapperProperty<Poco::JS::Core::ConfigurationWrapper>(bundleObject, pIsolate, "properties"s, const_cast<Poco::Util::AbstractConfiguration*>(&_pBundle->properties()));
	}

	BundleContextWrapper bundleContextWrapper;
	v8::MaybeLocal<v8::Object> maybeBundleContextObject = bundleContextWrapper.wrapNative(pIsolate, const_cast<Poco::OSP::BundleContext*>(_pContext.get()));
	v8::Local<v8::Object> bundleContextObject;
	if (maybeBundleContextObject.ToLocal(&bundleContextObject))
	{
		V8_CHECK_SET_RESULT(bundleContextObject->Set(context, Wrapper::toV8Internalized(pIsolate, "temporaryDirectory"s), Wrapper::toV8String(pIsolate, _pContext->temporaryDirectory().toString())));
		V8_CHECK_SET_RESULT(bundleContextObject->Set(context, Wrapper::toV8Internalized(pIsolate, "persistentDirectory"s), Wrapper::toV8String(pIsolate, _pContext->persistentDirectory().toString())));
		V8_CHECK_SET_RESULT(global->Set(context, Wrapper::toV8Internalized(pIsolate, "bundleContext"s), bundleContextObject));
	}

	setWrapperProperty<ServiceRegistryWrapper>(global, pIsolate, "serviceRegistry"s, &_pContext->registry());
	setWrapperProperty<Poco::JS::Core::LoggerWrapper>(global, pIsolate, "logger"s, &_pContext->logger());
	setWrapperProperty<Poco::JS::Core::ConsoleWrapper>(global, pIsolate, "console"s, &_pContext->logger());
}


void JSExecutor::handleError(const ErrorInfo& errorInfo)
{
	const std::string fullMessage = formatErrorInfo(errorInfo);
	if (errorInfo.message == "Terminated")
		_pContext->logger().notice(fullMessage);
	else
		_pContext->logger().error(fullMessage);
}


std::string JSExecutor::formatErrorInfo(const ErrorInfo& errorInfo)
{
	std::string fullMessage(errorInfo.message);
	fullMessage += " [in \"";
	fullMessage += errorInfo.uri;
	fullMessage += "\"";
	if (errorInfo.lineNo)
	{
		fullMessage += Poco::format(", line %d"s, errorInfo.lineNo);
	}
	fullMessage += "]";

	if (!errorInfo.stackTrace.empty())
	{
		fullMessage += "\n\tStack Trace:";
		int i = 0;
		for (const auto& f: errorInfo.stackTrace)
		{
			fullMessage += Poco::format("\n\t\t#%-2d "s, i++);
			if (!f.functionName.empty())
			{
				fullMessage += f.functionName;
				fullMessage += "() ";
			}
			fullMessage += "[in \"";
			fullMessage += f.scriptName;
			fullMessage += "\"";
			if (f.lineNo)
			{
				fullMessage += Poco::format(", line %d"s, f.lineNo);
			}
			fullMessage += "]";
		}
	}
	return fullMessage;
}


void JSExecutor::handleOutOfMemory(std::size_t currentHeapLimit, std::size_t initialHeapLimit)
{
	Poco::JS::Core::JSExecutor::handleOutOfMemory(currentHeapLimit, initialHeapLimit);

	_pContext->logger().fatal("Script %s has exhausted its memory limit and has been terminated."s, uri().toString());
}


void JSExecutor::handleMemoryWarning(std::size_t currentHeapLimit, std::size_t initialHeapLimit)
{
	Poco::JS::Core::JSExecutor::handleMemoryWarning(currentHeapLimit, initialHeapLimit);

	_pContext->logger().warning("Script %s is nearing its memory limit of %z bytes. Limit temporarily increased to %z bytes."s, uri().toString(), initialHeapLimit, currentHeapLimit);
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

	v8::HandleScope handleScope(pIsolate);
	v8::Local<v8::Context> context(pIsolate->GetCurrentContext());

	BundleWrapper bundleWrapper;
	v8::MaybeLocal<v8::Object> maybeBundleObject = bundleWrapper.wrapNative(pIsolate, const_cast<Poco::OSP::Bundle*>(_pBundle.get()));
	v8::Local<v8::Object> bundleObject;
	if (maybeBundleObject.ToLocal(&bundleObject))
	{
		V8_CHECK_SET_RESULT(bundleObject->Set(context, Wrapper::toV8Internalized(pIsolate, "temporaryDirectory"s), Wrapper::toV8String(pIsolate, _pContext->temporaryDirectory().toString())));
		V8_CHECK_SET_RESULT(bundleObject->Set(context, Wrapper::toV8Internalized(pIsolate, "persistentDirectory"s), Wrapper::toV8String(pIsolate, _pContext->persistentDirectory().toString())));
		V8_CHECK_SET_RESULT(global->Set(context, Wrapper::toV8Internalized(pIsolate, "bundle"s), bundleObject));
	}

	BundleContextWrapper bundleContextWrapper;
	v8::MaybeLocal<v8::Object> maybeBundleContextObject = bundleContextWrapper.wrapNative(pIsolate, const_cast<Poco::OSP::BundleContext*>(_pContext.get()));
	v8::Local<v8::Object> bundleContextObject;
	if (maybeBundleContextObject.ToLocal(&bundleContextObject))
	{
		V8_CHECK_SET_RESULT(bundleContextObject->Set(context, Wrapper::toV8Internalized(pIsolate, "temporaryDirectory"s), Wrapper::toV8String(pIsolate, _pContext->temporaryDirectory().toString())));
		V8_CHECK_SET_RESULT(bundleContextObject->Set(context, Wrapper::toV8Internalized(pIsolate, "persistentDirectory"s), Wrapper::toV8String(pIsolate, _pContext->persistentDirectory().toString())));
		V8_CHECK_SET_RESULT(global->Set(context, Wrapper::toV8Internalized(pIsolate, "bundleContext"s), bundleContextObject));
	}

	setWrapperProperty<Poco::JS::Core::ConfigurationWrapper>(global, pIsolate, "properties"s, const_cast<Poco::Util::AbstractConfiguration*>(&_pBundle->properties()));
	setWrapperProperty<ServiceRegistryWrapper>(global, pIsolate, "serviceRegistry"s, &_pContext->registry());
	setWrapperProperty<Poco::JS::Core::LoggerWrapper>(global, pIsolate, "logger"s, &_pContext->logger());
	setWrapperProperty<Poco::JS::Core::ConsoleWrapper>(global, pIsolate, "console"s, &_pContext->logger());
}


void TimedJSExecutor::handleError(const ErrorInfo& errorInfo)
{
	const std::string fullMessage = Poco::OSP::JS::JSExecutor::formatErrorInfo(errorInfo);
	if (errorInfo.message == "Terminated")
		_pContext->logger().notice(fullMessage);
	else
		_pContext->logger().error(fullMessage);
}


void TimedJSExecutor::handleOutOfMemory(std::size_t currentHeapLimit, std::size_t initialHeapLimit)
{
	Poco::JS::Core::TimedJSExecutor::handleOutOfMemory(currentHeapLimit, initialHeapLimit);

	_pContext->logger().fatal("Script %s has exhausted its memory limit and has been terminated."s, uri().toString());
}


void TimedJSExecutor::handleMemoryWarning(std::size_t currentHeapLimit, std::size_t initialHeapLimit)
{
	Poco::JS::Core::TimedJSExecutor::handleMemoryWarning(currentHeapLimit, initialHeapLimit);

	_pContext->logger().warning("Script %s is nearing its memory limit of %z bytes. Limit temporarily increased to %z bytes."s, uri().toString(), initialHeapLimit, currentHeapLimit);
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
