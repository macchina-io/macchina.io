//
// BundleServer.cpp
//
// This sample demonstrates the OSP framework.
//
// Copyright (c) 2007-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/OSP/OSPSubsystem.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/SharedLibrary.h"
#include "Poco/ErrorHandler.h"
#include <iostream>


using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::OSP::OSPSubsystem;
using Poco::OSP::ServiceRegistry;


class BundleServerApplication: public ServerApplication
{
public:
	BundleServerApplication():
		_errorHandler(*this),
		_pOSP(new OSPSubsystem),
		_showHelp(false)
	{
		Poco::ErrorHandler::set(&_errorHandler);
		addSubsystem(_pOSP);
	}

	~BundleServerApplication()
	{
		// wait until all threads have terminated
		// before we completely shut down.
		Poco::ThreadPool::defaultPool().joinAll();
	}

	ServiceRegistry& serviceRegistry()
	{
		return _pOSP->serviceRegistry();
	}

protected:
	class ErrorHandler: public Poco::ErrorHandler
	{
	public:
		ErrorHandler(BundleServerApplication& app):
			_app(app)
		{
		}

		void exception(const Poco::Exception& exc)
		{
			log(exc.displayText());
		}

		void exception(const std::exception& exc)
		{
			log(exc.what());
		}

		void exception()
		{
			log("unknown exception");
		}

		void log(const std::string& message)
		{
			_app.logger().error("A thread was terminated by an unhandled exception: " + message);
		}

	private:
		BundleServerApplication& _app;
	};

	void initialize(Application& self)
	{
		// The following is a workaround for Windows so that DLLs
		// loaded from bundles will also look for DLLs in the
		// directory the .exe is located.
		Poco::SharedLibrary::setSearchPath(config().getString("application.dir"));

		loadConfiguration(); // load default configuration files, if present
		Application::initialize(self);
	}

	void defineOptions(OptionSet& options)
	{
		ServerApplication::defineOptions(options);

		options.addOption(
			Option("help", "h", "display help information on command line arguments")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<BundleServerApplication>(this, &BundleServerApplication::handleHelp)));

		options.addOption(
			Option("config-file", "c", "load configuration data from a file")
				.required(false)
				.repeatable(true)
				.argument("file")
				.callback(OptionCallback<BundleServerApplication>(this, &BundleServerApplication::handleConfig)));
	}

	void handleHelp(const std::string& name, const std::string& value)
	{
		_showHelp = true;
		displayHelp();
		stopOptionsProcessing();
		_pOSP->cancelInit();
	}

	void handleConfig(const std::string& name, const std::string& value)
	{
		loadConfiguration(value);
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("A container for Open Service Platform bundles.");
		helpFormatter.format(std::cout);
	}

	int main(const std::vector<std::string>& args)
	{
		if (!_showHelp)
		{
			waitForTerminationRequest();
		}
		return Application::EXIT_OK;
	}

private:
	ErrorHandler _errorHandler;
	OSPSubsystem* _pOSP;
	bool _showHelp;
};


POCO_SERVER_MAIN(BundleServerApplication)
