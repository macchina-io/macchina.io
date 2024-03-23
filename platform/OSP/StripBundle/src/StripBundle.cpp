//
// StripBundle.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Zip/ZipArchive.h"
#include "Poco/Zip/ZipManipulator.h"
#include "Poco/FileStream.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include <iostream>


using Poco::Util::Application;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::OptionCallback;


namespace Poco {
namespace OSP {


class StripBundle: public Application
{
public:
	StripBundle():
		_showHelp(false)
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
				.callback(OptionCallback<StripBundle>(this, &StripBundle::handleHelp)));
	}

	void handleHelp(const std::string& name, const std::string& value)
	{
		_showHelp = true;
		stopOptionsProcessing();
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("[<option>] [<bundle>...]");
		helpFormatter.setHeader(
			"\n"
			"The Applied Informatics OSP Strip Bundle Utility.\n"
			"Copyright (c) 2018-2024 by Applied Informatics Software Engineering GmbH.\n"
			"All rights reserved.\n\n"
			"This program removes all binaries (shared libraries) from a bundle. "
			"A typical use case is systems using a read-only file system, where "
			"the code cache is pre-populated with ccutil, and bundles do not "
			"need to contain any binaries to save space.\n"
			"The following command line options are supported:"
		);
		helpFormatter.setFooter(
			"For more information, please see the Open Service Platform "
			"documentation at <https://www.appinf.com/docs>."
		);
		helpFormatter.setIndent(8);
		helpFormatter.format(std::cout);
	}

	void strip(const std::string& bundlePath)
	{
		Poco::File f(bundlePath);
		if (f.isDirectory())
			stripDirectory(bundlePath);
		else if (f.isFile())
			stripFile(bundlePath);
	}

	void stripDirectory(const std::string& bundlePath)
	{
		Poco::Path p(bundlePath);
		p.makeDirectory();
		p.pushDirectory("bin");
		Poco::File f(p.toString());
		if (f.exists() && f.isDirectory())
		{
			f.remove(true);
		}
	}

	void stripFile(const std::string& bundlePath)
	{
		Poco::FileInputStream istr(bundlePath);
		Poco::Zip::ZipArchive arch(istr);
		istr.close();

		Poco::Zip::ZipManipulator manip(bundlePath, false);
		for (Poco::Zip::ZipArchive::FileInfos::const_iterator it = arch.fileInfoBegin(); it != arch.fileInfoEnd(); ++it)
		{
			if (it->first.compare(0, 4, "bin/") == 0)
				manip.deleteFile(it->first);
		}

		manip.commit();
	}

	int main(const std::vector<std::string>& args)
	{
		if (_showHelp || args.empty())
		{
			displayHelp();
			return Application::EXIT_OK;
		}

		try
		{
			for (std::vector<std::string>::const_iterator it = args.begin(); it != args.end(); ++it)
			{
				strip(*it);
			}
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
};


} } // namespace Poco::OSP


POCO_APP_MAIN(Poco::OSP::StripBundle)
