//
// MacchinaServer.cpp
//
// The bundle container application for macchina.io
//
// Copyright (c) 2014-2024, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/OSP/OSPSubsystem.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/BundleFilter.h"
#include "Poco/DataURIStreamFactory.h"
#include "Poco/StringTokenizer.h"
#include "Poco/ErrorHandler.h"
#include "Poco/Environment.h"
#include "Poco/Format.h"
#include "Poco/File.h"
#include <set>
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
using namespace std::string_literals;


class MacchinaServer: public ServerApplication
{
public:
	MacchinaServer():
		_errorHandler(*this),
		_pOSP(new OSPSubsystem)
	{
		Poco::DataURIStreamFactory::registerFactory();
		Poco::ErrorHandler::set(&_errorHandler);
		addSubsystem(_pOSP);
	}

	~MacchinaServer()
	{
		// wait until all threads have terminated
		// before we completely shut down.
		Poco::ThreadPool::defaultPool().joinAll();
		Poco::DataURIStreamFactory::unregisterFactory();
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
			log("unknown exception"s);
		}

		void log(const std::string& message)
		{
			_app.logger().notice("A thread was terminated by an unhandled exception: "s + message);
		}

	private:
		MacchinaServer& _app;
	};

	class SkipBundleFilter: public Poco::OSP::BundleFilter
	{
	public:
		SkipBundleFilter(const std::set<std::string>& symbolicNames):
			_symbolicNames(symbolicNames)
		{
		}

		// BundleFilter
		bool accept(Poco::OSP::Bundle::Ptr pBundle)
		{
			return _symbolicNames.count(pBundle->symbolicName()) == 0;
		}

	private:
		const std::set<std::string>& _symbolicNames;
	};

	std::string loadSettings()
	{
		std::string settingsPath = config().getString("macchina.settings.path"s, ""s);
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
			config().add(pSettings, "macchina.settings"s, Poco::Util::Application::PRIO_DEFAULT, true);
		}
		return settingsPath;
	}

	void initialize(Application& self)
	{
		if (!_skipDefaultConfig)
		{
			loadConfiguration();
		}
		for (const auto& cf: _configs)
		{
			loadConfiguration(cf);
		}

		int defaultThreadPoolCapacity = config().getInt("poco.threadPool.default.capacity", 32);
		int defaultThreadPoolCapacityDelta = defaultThreadPoolCapacity - Poco::ThreadPool::defaultPool().capacity();
		if (defaultThreadPoolCapacityDelta > 0)
		{
			Poco::ThreadPool::defaultPool().addCapacity(defaultThreadPoolCapacityDelta);
		}

		std::string settingsPath = loadSettings();

		skipBundles(config().getString("osp.skipBundles"s, ""s));
		_pOSP->setBundleFilter(new SkipBundleFilter(_skippedBundles));

		ServerApplication::initialize(self);

		if (!settingsPath.empty() && !_showHelp)
		{
			logger().information("Settings loaded from \"%s\"."s, settingsPath);
		}

		if (!_showHelp)
		{
			logger().information(
				"\n"
				"\n"
				"      oooooooooooooooooo\n"
				"    oooooooooooooooooooooo\n"
				"    oooooooooooooooooooooo\n"
				"    oooooooooooooooooooooo\n"
				"    oooooooooooooooooooooo\n"
				"    ooooooooo            o\n"
				"    ooooooooo   oo   oo  \n"
				"    ooooooooo   oo   oo \n"
				"    ooooooooo   oo   oo \n"
				"    ooooooooo   oo   oo \n"
				"      ooooooo   oo   oo \n"
				"\n"
				"    macchina.io EDGE Server [GPL]\n"
				"\n"
				"    Copyright (c) 2015-2024 by Applied Informatics Software Engineering GmbH.\n"
				"    All rights reserved.\n"s
			);
			logger().information("System information: %s (%s) on %s, %u CPU core(s)."s,
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
			Option("help"s, "h"s, "Display help information on command line arguments."s)
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<MacchinaServer>(this, &MacchinaServer::handleHelp)));

		options.addOption(
			Option("config-file"s, "c"s, "Load configuration data from a file."s)
				.required(false)
				.repeatable(true)
				.argument("file"s)
				.callback(OptionCallback<MacchinaServer>(this, &MacchinaServer::handleConfig)));

		options.addOption(
			Option("skip-default-config"s, ""s, "Don't load default configuration file."s)
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<MacchinaServer>(this, &MacchinaServer::handleSkipDefaultConfig)));

		options.addOption(
			Option("skip-bundle"s, "s"s, "Skip (do not load) the bundle(s) with the given (comma-separated) symbolic name(s)."s)
				.required(false)
				.repeatable(true)
				.argument("symbolicNames"s)
				.callback(OptionCallback<MacchinaServer>(this, &MacchinaServer::handleSkipBundle)));
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
		_configs.push_back(value);
	}

	void handleSkipDefaultConfig(const std::string& name, const std::string& value)
	{
		_skipDefaultConfig = true;
	}

	void handleSkipBundle(const std::string& name, const std::string& value)
	{
		skipBundles(value);
	}

	void skipBundles(const std::string& symbolicNames)
	{
		Poco::StringTokenizer tok(symbolicNames, ",;"s, Poco::StringTokenizer::TOK_IGNORE_EMPTY | Poco::StringTokenizer::TOK_TRIM);
		_skippedBundles.insert(tok.begin(), tok.end());
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS"s);
		helpFormatter.setHeader(
			"\n"
			"The macchina.io EDGE Server [GPL].\n"
			"Copyright (c) 2015-2024 by Applied Informatics Software Engineering GmbH.\n"
			"All rights reserved.\n\n"
			"The following command line options are supported:"s
		);
		helpFormatter.setFooter(
			"For more information, please see the macchina.io "
			"documentation at <https://macchina.io/docs>."s
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
	bool _showHelp = false;
	bool _skipDefaultConfig = false;
	std::vector<std::string> _configs;
	std::set<std::string> _skippedBundles;
};


POCO_SERVER_MAIN(MacchinaServer)
