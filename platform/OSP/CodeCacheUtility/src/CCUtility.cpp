//
// CodeCacheUtility.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/AbstractConfiguration.h"
#include "Poco/OSP/CodeCache.h"
#include "Poco/OSP/BundleFactory.h"
#include "Poco/OSP/BundleContextFactory.h"
#include "Poco/OSP/BundleLoader.h"
#include "Poco/OSP/BundleRepository.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/SystemEvents.h"
#include "Poco/Environment.h"
#include <iostream>


using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::AbstractConfiguration;
using Poco::Util::OptionCallback;


namespace Poco {
namespace OSP {


class CodeCacheUtility: public Application
{
public:
	CodeCacheUtility():
		_showHelp(false),
		_osName(Poco::Environment::osName()),
		_osArch(Poco::Environment::osArchitecture())
	{
	}

protected:
	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		Application::initialize(self);
	}

	void defineOptions(OptionSet& options)
	{
		Application::defineOptions(options);

		options.addOption(
			Option("help", "h", "Display help information on command line arguments.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<CodeCacheUtility>(this, &CodeCacheUtility::handleHelp)));

		options.addOption(
			Option("clean", "C", "Clean code cache directory before populating it.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<CodeCacheUtility>(this, &CodeCacheUtility::handleClean)));

		options.addOption(
			Option("config-file", "f", "Load configuration data from a file.")
				.required(false)
				.repeatable(true)
				.argument("file")
				.callback(OptionCallback<CodeCacheUtility>(this, &CodeCacheUtility::handleConfig)));

		options.addOption(
			Option("osname", "n", "Specify default target operating system name (e.g., Linux).")
				.required(false)
				.repeatable(false)
				.argument("<osname>")
				.callback(OptionCallback<CodeCacheUtility>(this, &CodeCacheUtility::handleOSName)));

		options.addOption(
			Option("osarch", "a", "Specify default target operating system architecture (e.g., armv7l).")
				.required(false)
				.repeatable(false)
				.argument("<osarch>")
				.callback(OptionCallback<CodeCacheUtility>(this, &CodeCacheUtility::handleOSArch)));

		options.addOption(
			Option("bundles", "b", "Specify bundle repository paths (colon or semicolon-separated).")
				.required(true)
				.repeatable(false)
				.argument("<paths>")
				.callback(OptionCallback<CodeCacheUtility>(this, &CodeCacheUtility::handleBundles)));

		options.addOption(
			Option("cache", "c", "Specify code cache path.")
				.required(true)
				.repeatable(false)
				.argument("<paths>")
				.callback(OptionCallback<CodeCacheUtility>(this, &CodeCacheUtility::handleCache)));
	}

	void handleHelp(const std::string& name, const std::string& value)
	{
		_showHelp = true;
		displayHelp();
		stopOptionsProcessing();
	}

	void handleClean(const std::string& name, const std::string& value)
	{
		_cleanCodeCache = true;
	}

	void handleConfig(const std::string& name, const std::string& value)
	{
		loadConfiguration(value);
	}

	void handleOSName(const std::string& name, const std::string& value)
	{
		_osName = value;
	}

	void handleOSArch(const std::string& name, const std::string& value)
	{
		_osArch = value;
	}

	void handleBundles(const std::string& name, const std::string& value)
	{
		_bundleRepositoryPath = value;
	}

	void handleCache(const std::string& name, const std::string& value)
	{
		_codeCachePath = value;
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("[<option> ...]");
		helpFormatter.setHeader(
			"\n"
			"The Applied Informatics OSP Code Cache Utility.\n"
			"Copyright (c) 2017-2024 by Applied Informatics Software Engineering GmbH.\n"
			"All rights reserved.\n\n"
			"This program populates a code cache directory with the "
			"shared libraries contained in all bundles in the given "
			"bundle repository.\n\n"
			"The following command line options are supported:"
		);
		helpFormatter.setFooter(
			"For more information, please see the Open Service Platform "
			"documentation at <https://www.appinf.com/docs>."
		);
		helpFormatter.setIndent(8);
		helpFormatter.format(std::cout);
	}

	int main(const std::vector<std::string>& args)
	{
		if (_showHelp) return Application::EXIT_OK;

		CodeCache codeCache(_codeCachePath, false);
		if (_cleanCodeCache)
		{
			try
			{
				logger().information("Clearing code cache...");

				CodeCache::Lock ccLock(codeCache);
				codeCache.clear();
			}
			catch (Poco::Exception& exc)
			{
				logger().warning(std::string("Cannot clear code cache: ") + exc.displayText());
			}
		}

		try
		{
			LanguageTag languageTag;
			BundleFactory::Ptr pBundleFactory(new BundleFactory(languageTag));
			SystemEvents systemEvents;
			ServiceRegistry serviceRegistry;
			BundleContextFactory::Ptr pBundleContextFactory(new BundleContextFactory(serviceRegistry, systemEvents));
			BundleLoader bundleLoader(codeCache, pBundleFactory, pBundleContextFactory, _osName, _osArch, true);
			BundleRepository bundleRepository(_bundleRepositoryPath, bundleLoader);

			logger().information("Loading bundles...");
			bundleRepository.loadBundles();
			logger().information("Resolving bundles...");
			bundleLoader.resolveAllBundles();
			logger().information("All bundles resolved.");
		}
		catch (Poco::Exception& exc)
		{
			std::cerr << exc.displayText() << std::endl;
			return Application::EXIT_SOFTWARE;
		}

		return Application::EXIT_OK;
	}

private:
	bool _showHelp;
	std::string _osName;
	std::string _osArch;
	std::string _codeCachePath;
	std::string _bundleRepositoryPath;
	bool _cleanCodeCache;
};


} } // namespace Poco::OSP


POCO_APP_MAIN(Poco::OSP::CodeCacheUtility)
