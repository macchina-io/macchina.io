//
// jsrun.cpp
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/JSExecutor.h"
#include "Poco/JS/Core/LoggerWrapper.h"
#include "Poco/JS/Core/ConfigurationWrapper.h"
#include "Poco/JS/Core/ConsoleWrapper.h"
#include "Poco/JS/Net/HTTPRequestWrapper.h"
#include "Poco/JS/Data/SessionWrapper.h"
#include "Poco/Net/HTTPStreamFactory.h"
#include "Poco/Net/FTPStreamFactory.h"
#include "Poco/Net/HTTPSessionInstantiator.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPSStreamFactory.h"
#include "Poco/Net/HTTPSSessionInstantiator.h"
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Delegate.h"
#include "Poco/StringTokenizer.h"
#include <iostream>


using Poco::Util::Application;
using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::OptionCallback;


template <class Base>
class JSRunExecutor: public Base
{
public:
	JSRunExecutor(const std::string& source, const Poco::URI& sourceURI, const std::vector<std::string>& args, const std::vector<std::string>& modulePaths, Poco::UInt64 memoryLimit):
		Base(source, sourceURI, modulePaths, memoryLimit),
		_args(args)
	{
	}
	
protected:
	void setupGlobalObjectTemplate(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate)
	{
		Base::setupGlobalObjectTemplate(global, pIsolate);

		Poco::JS::Net::HTTPRequestWrapper httpRequestWrapper;
		global->Set(v8::String::NewFromUtf8(pIsolate, "HTTPRequest"), httpRequestWrapper.constructor(pIsolate));
	
		Poco::JS::Data::SessionWrapper sessionWrapper;
		global->Set(v8::String::NewFromUtf8(pIsolate, "DBSession"), sessionWrapper.constructor(pIsolate));
	}
	
	void setupGlobalObject(v8::Local<v8::Object>& global, v8::Isolate* pIsolate)
	{
		Base::setupGlobalObject(global, pIsolate);
	
		Poco::JS::Core::ConfigurationWrapper configurationWrapper;
		v8::Local<v8::Object> configurationObject = configurationWrapper.wrapNative(pIsolate, &Application::instance().config());
		global->Set(v8::String::NewFromUtf8(pIsolate, "config"), configurationObject);

		Poco::JS::Core::LoggerWrapper loggerWrapper;
		v8::Local<v8::Object> loggerObject = loggerWrapper.wrapNative(pIsolate, &Application::instance().logger());
		global->Set(v8::String::NewFromUtf8(pIsolate, "logger"), loggerObject);

		Poco::JS::Core::ConsoleWrapper consoleWrapper;
		v8::Local<v8::Object> consoleObject = consoleWrapper.wrapNative(pIsolate, &Poco::Logger::get("console"));
		global->Set(v8::String::NewFromUtf8(pIsolate, "console"), consoleObject);

		v8::Local<v8::Array> args = v8::Array::New(pIsolate, static_cast<int>(_args.size()));
		for (unsigned i = 0; i < _args.size(); i++)
		{
			args->Set(i, v8::String::NewFromUtf8(pIsolate, _args[i].c_str()));
		}
		global->Set(v8::String::NewFromUtf8(pIsolate, "$args"), args);
	}
	
private:
	std::vector<std::string> _args;
};


class JSRunApp: public ServerApplication
{
public:
	JSRunApp(): 
		_helpRequested(false),
		_wait(false)
	{
	}

protected:	
	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		ServerApplication::initialize(self);
		
		Poco::Net::initializeNetwork();
		Poco::Net::HTTPStreamFactory::registerFactory();
		Poco::Net::FTPStreamFactory::registerFactory();
		Poco::Net::HTTPSessionInstantiator::registerInstantiator();
		
		Poco::Net::initializeSSL();
		Poco::Net::HTTPSStreamFactory::registerFactory();
		Poco::Net::HTTPSSessionInstantiator::registerInstantiator();
		
		Poco::JS::Core::initialize();
	}
	
	void uninitialize()
	{
		ServerApplication::uninitialize();
		
		Poco::Net::HTTPSessionInstantiator::unregisterInstantiator();
		Poco::Net::HTTPStreamFactory::unregisterFactory();
		Poco::Net::FTPStreamFactory::unregisterFactory();
		Poco::Net::uninitializeNetwork();
		
		Poco::Net::HTTPSSessionInstantiator::unregisterInstantiator();
		Poco::Net::HTTPSStreamFactory::unregisterFactory();
		Poco::Net::uninitializeSSL();
		
		Poco::JS::Core::uninitialize();
	}
	
	void defineOptions(OptionSet& options)
	{
		ServerApplication::defineOptions(options);

		options.addOption(
			Option("help", "h", "Display help information on command line arguments.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<JSRunApp>(this, &JSRunApp::handleHelp)));

		options.addOption(
			Option("define", "D", "Define a configuration property.")
				.required(false)
				.repeatable(true)
				.argument("name=value")
				.callback(OptionCallback<JSRunApp>(this, &JSRunApp::handleDefine)));
				
		options.addOption(
			Option("config-file", "f", "Load configuration data from a file.")
				.required(false)
				.repeatable(true)
				.argument("file")
				.callback(OptionCallback<JSRunApp>(this, &JSRunApp::handleConfig)));

		options.addOption(
			Option("wait", "w", "Wait to be terminated by user. Lets scripts use timers and asynchronous callbacks.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<JSRunApp>(this, &JSRunApp::handleWait)));
	}
	
	void handleHelp(const std::string& name, const std::string& value)
	{
		_helpRequested = true;
		stopOptionsProcessing();
	}
	
	void handleDefine(const std::string& name, const std::string& value)
	{
		defineProperty(value);
	}
	
	void handleConfig(const std::string& name, const std::string& value)
	{
		loadConfiguration(value);
	}

	void handleWait(const std::string& name, const std::string& value)
	{
		_wait = true;
	}
		
	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("[options] <script> [-- {<script-argument>}]");
		helpFormatter.setHeader("Run JavaScript scripts.");
		helpFormatter.format(std::cout);
	}
	
	void defineProperty(const std::string& def)
	{
		std::string name;
		std::string value;
		std::string::size_type pos = def.find('=');
		if (pos != std::string::npos)
		{
			name.assign(def, 0, pos);
			value.assign(def, pos + 1, def.length() - pos);
		}
		else name = def;
		config().setString(name, value);
	}
	
	void reportError(const Poco::JS::Core::JSExecutor::ErrorInfo& errorInfo)
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
		logger().error(fullMessage);
	}

	int main(const std::vector<std::string>& args)
	{
		if (_helpRequested || args.empty())
		{
			displayHelp();
		}
		else
		{		
			std::string paths = config().getString("js.moduleSearchPaths", "");
			Poco::StringTokenizer pathsTok(paths, ",;", Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			std::vector<std::string> searchPaths(pathsTok.begin(), pathsTok.end());
	
			std::string v8Options = config().getString("js.v8.flags", "");
			Poco::StringTokenizer v8OptionsTok(v8Options, ",;", Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			for (Poco::StringTokenizer::Iterator it = v8OptionsTok.begin(); it != v8OptionsTok.end(); ++it)
			{
				v8::V8::SetFlagsFromString(it->data(), it->size());
			}
			
			Poco::UInt64 memoryLimit = static_cast<Poco::UInt64>(1024)*config().getInt("js.memoryLimit", 1024);

			try
			{
				Poco::Path path(args[0]);
				Poco::File file(args[0]);
				Poco::URI uri(path);
				std::string script;
				Poco::FileInputStream istr(path.toString());
				Poco::StreamCopier::copyToString(istr, script);
				if (_wait)
				{
					JSRunExecutor<Poco::JS::Core::TimedJSExecutor> jsExecutor(script, uri, args, searchPaths, memoryLimit);
					jsExecutor.scriptError += Poco::delegate(this, &JSRunApp::reportError);
					jsExecutor.run();
					waitForTerminationRequest();
					jsExecutor.terminate();
				}
				else
				{
					JSRunExecutor<Poco::JS::Core::JSExecutor> jsExecutor(script, uri, args, searchPaths, memoryLimit);
					jsExecutor.scriptError += Poco::delegate(this, &JSRunApp::reportError);
					jsExecutor.run();
				}
			}
			catch (Poco::Exception& exc)
			{
				logger().log(exc);
			}
		}
		return Application::EXIT_OK;
	}
	
private:
	bool _helpRequested;
	bool _wait;
};


POCO_SERVER_MAIN(JSRunApp)
