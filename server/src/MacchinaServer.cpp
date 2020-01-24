//
// MacchinaServer.cpp
//
// The bundle container application for macchina.io
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/OSP/OSPSubsystem.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/ErrorHandler.h"
#include "Poco/Environment.h"
#include "Poco/Format.h"
#include "Poco/File.h"
#include <cstring>
#include <iostream>


using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::OSP::OSPSubsystem;
using Poco::OSP::ServiceRegistry;


class MacchinaServer: public ServerApplication
{
public:
	MacchinaServer():
		_errorHandler(*this),
		_pOSP(new OSPSubsystem),
		_showHelp(false)
	{
		Poco::ErrorHandler::set(&_errorHandler);
		addSubsystem(_pOSP);
	}

	~MacchinaServer()
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
		ErrorHandler(MacchinaServer& app):
			_app(app)
		{
		}

		void exception(const Poco::Exception& exc)
		{
			// Don't log Poco::Net::ConnectionResetException and Poco::TimeoutException -
			// getting too many of them from the web server.
			if (std::strcmp(exc.name(), "Connection reset by peer") != 0 &&
			    std::strcmp(exc.name(), "Timeout") != 0)
			{
				log(exc.displayText());
			}
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
			_app.logger().notice("A thread was terminated by an unhandled exception: " + message);
		}

	private:
		MacchinaServer& _app;
	};

	std::string loadSettings()
	{
		std::string settingsPath = config().getString("macchina.settings.path", "");
		if (!settingsPath.empty())
		{
			Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> pSettings;
			Poco::File settingsFile(settingsPath);
			if (settingsFile.exists())
			{
				pSettings = new Poco::Util::PropertyFileConfiguration(settingsPath);
			}
			else
			{
				pSettings = new Poco::Util::PropertyFileConfiguration;
			}
			config().add(pSettings, "macchina.settings", Poco::Util::Application::PRIO_DEFAULT, true);
		}
		return settingsPath;
	}

	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present

		int defaultThreadPoolCapacity = config().getInt("poco.threadPool.default.capacity", 32);
		int defaultThreadPoolCapacityDelta = defaultThreadPoolCapacity - Poco::ThreadPool::defaultPool().capacity();
		if (defaultThreadPoolCapacityDelta > 0)
		{
			Poco::ThreadPool::defaultPool().addCapacity(defaultThreadPoolCapacityDelta);
		}

		std::string settingsPath = loadSettings();

		ServerApplication::initialize(self);

		if (!settingsPath.empty() && !_showHelp)
		{
			logger().information("Settings loaded from \"%s\".", settingsPath);
		}

		if (!_showHelp)
		{
			logger().information(
				"\n"
				"\n"
				"      %%%%%%%%%%%%%%%%%%\n"
				"    %%%%%%%%%%%%%%%%%%%%%%\n"
				"    %%%%%%%%%%%%%%%%%%%%%%\n"
				"    %%%%%%%%%%%%%%%%%%%%%%\n"
				"    %%%%%%%%%%%%%%%%%%%%%%\n"
				"    %%%%%%%%%            %\n"
				"    %%%%%%%%%   %%   %%  \n"
				"    %%%%%%%%%   %%   %% \n"
				"    %%%%%%%%%   %%   %% \n"
				"    %%%%%%%%%   %%   %% \n"
				"      %%%%%%%   %%   %% \n"
				"\n"
				"    macchina.io IoT Edge Device SDK Server\n"
				"\n"
				"    Copyright (c) 2015-2020 by Applied Informatics Software Engineering GmbH.\n"
				"    All rights reserved.\n"
			);
			logger().information("System information: %s (%s) on %s, %u CPU core(s).",
				Poco::Environment::osDisplayName(),
				Poco::Environment::osVersion(),
				Poco::Environment::osArchitecture(),
				Poco::Environment::processorCount());
		}
	}

	void defineOptions(OptionSet& options)
	{
		ServerApplication::defineOptions(options);

		options.addOption(
			Option("help", "h", "Display help information on command line arguments.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<MacchinaServer>(this, &MacchinaServer::handleHelp)));

		options.addOption(
			Option("config-file", "c", "Load configuration data from a file.")
				.required(false)
				.repeatable(true)
				.argument("file")
				.callback(OptionCallback<MacchinaServer>(this, &MacchinaServer::handleConfig)));
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
		helpFormatter.setHeader(
			"\n"
			"The macchina.io IoT Edge Device SDK Server.\n"
			"Copyright (c) 2015-2020 by Applied Informatics Software Engineering GmbH.\n"
			"All rights reserved.\n\n"
			"The following command line options are supported:"
		);
		helpFormatter.setFooter(
			"For more information, please see the macchina.io "
			"documentation at <https://macchina.io/docs>."
		);
		helpFormatter.setIndent(8);
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


POCO_SERVER_MAIN(MacchinaServer)
