//
// jsrun.cpp
//
// $Id: //poco/1.4/JS/samples/runjs/src/jsrun.cpp#2 $
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/JSExecutor.h"
#include "Poco/JS/Core/LoggerWrapper.h"
#include "Poco/JS/Core/ConfigurationWrapper.h"
#include "Poco/JS/Net/HTTPRequestWrapper.h"
#include "Poco/JS/Data/SessionWrapper.h"
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/StreamCopier.h"
#include "Poco/Delegate.h"
#include <iostream>


using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::OptionCallback;


class JSRunExecutor: public Poco::JS::Core::JSExecutor
{
public:
	JSRunExecutor(const std::string& source, const Poco::URI& sourceURI):
		Poco::JS::Core::JSExecutor(source, sourceURI)
	{
	}
	
protected:
	void registerGlobals(v8::Local<v8::ObjectTemplate>& global, v8::Isolate* pIsolate)
	{
		Poco::JS::Core::JSExecutor::registerGlobals(global, pIsolate);
	
		Poco::JS::Core::ConfigurationWrapper configurationWrapper;
		v8::Local<v8::Object> configurationObject = configurationWrapper.wrapNative(pIsolate, &Application::instance().config());
		global->Set(v8::String::NewFromUtf8(pIsolate, "config"), configurationObject);

		Poco::JS::Core::LoggerWrapper loggerWrapper;
		v8::Local<v8::Object> loggerObject = loggerWrapper.wrapNative(pIsolate, &Application::instance().logger());
		global->Set(v8::String::NewFromUtf8(pIsolate, "logger"), loggerObject);

		Poco::JS::Net::HTTPRequestWrapper httpRequestWrapper;
		global->Set(v8::String::NewFromUtf8(pIsolate, "HTTPRequest"), httpRequestWrapper.constructor(pIsolate));
	
		Poco::JS::Data::SessionWrapper sessionWrapper;
		global->Set(v8::String::NewFromUtf8(pIsolate, "DBSession"), sessionWrapper.constructor(pIsolate));
	}
};


class JSRunApp: public Application
{
public:
	JSRunApp(): _helpRequested(false)
	{
	}

protected:	
	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		Application::initialize(self);
		// add your own initialization code here
	}
	
	void uninitialize()
	{
		// add your own uninitialization code here
		Application::uninitialize();
	}
	
	void reinitialize(Application& self)
	{
		Application::reinitialize(self);
		// add your own reinitialization code here
	}
	
	void defineOptions(OptionSet& options)
	{
		Application::defineOptions(options);

		options.addOption(
			Option("help", "h", "display help information on command line arguments")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<JSRunApp>(this, &JSRunApp::handleHelp)));

		options.addOption(
			Option("define", "D", "define a configuration property")
				.required(false)
				.repeatable(true)
				.argument("name=value")
				.callback(OptionCallback<JSRunApp>(this, &JSRunApp::handleDefine)));
				
		options.addOption(
			Option("config-file", "f", "load configuration data from a file")
				.required(false)
				.repeatable(true)
				.argument("file")
				.callback(OptionCallback<JSRunApp>(this, &JSRunApp::handleConfig)));
	}
	
	void handleHelp(const std::string& name, const std::string& value)
	{
		_helpRequested = true;
		displayHelp();
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
		
	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("[options] <script>");
		helpFormatter.setHeader("This application runs JavaScript scripts.");
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
		if (!_helpRequested)
		{
			for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it)
			{
				try
				{
					Poco::Path path(*it);
					Poco::File file(*it);
					Poco::URI uri(path);
					std::string script;
					Poco::FileInputStream istr(path.toString());
					Poco::StreamCopier::copyToString(istr, script);
					JSRunExecutor jsExecutor(script, uri);
					jsExecutor.scriptError += Poco::delegate(this, &JSRunApp::reportError);
					jsExecutor.run();
				}
				catch (Poco::Exception& exc)
				{
					logger().log(exc);
				}
			}
		}
		return Application::EXIT_OK;
	}
	
private:
	bool _helpRequested;
};


POCO_APP_MAIN(JSRunApp)
