//
// BundleContainer.cpp
//
// This sample demonstrates the OSP framework.
//
// Copyright (c) 2007-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/OSP/OSPSubsystem.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/SharedLibrary.h"
#include <iostream>


using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;
using Poco::OSP::OSPSubsystem;
using Poco::OSP::ServiceRegistry;


class BundleContainerApplication: public Application
{
public:
	BundleContainerApplication():
		_pOSP(new OSPSubsystem),
		_showHelp(false)
	{
		addSubsystem(_pOSP);
	}

	ServiceRegistry& serviceRegistry()
	{
		return _pOSP->serviceRegistry();
	}

protected:
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
		Application::defineOptions(options);

		options.addOption(
			Option("help", "h", "display help information on command line arguments")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<BundleContainerApplication>(this, &BundleContainerApplication::handleHelp)));

		options.addOption(
			Option("config-file", "f", "load configuration data from a file")
				.required(false)
				.repeatable(true)
				.argument("file")
				.callback(OptionCallback<BundleContainerApplication>(this, &BundleContainerApplication::handleConfig)));
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
		}
		return Application::EXIT_OK;
	}

private:
	OSPSubsystem* _pOSP;
	bool _showHelp;
};


POCO_APP_MAIN(BundleContainerApplication)
