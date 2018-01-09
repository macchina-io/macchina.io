//
// MacchinaServer.cpp
//
// The launcher/watchdog for macchina.io server
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/RunnableAdapter.h"
#include "Poco/Thread.h"
#include "Poco/Event.h"
#include "Poco/ErrorHandler.h"
#include "Poco/File.h"
#include "Poco/Process.h"
#include "Poco/Format.h"
#include <iostream>


using Poco::Util::Application;
using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;
using Poco::format;


class LauncherApp: public ServerApplication
{
public:
	LauncherApp():
		_errorHandler(*this),
		_helpRequested(false),
		_stopped(false),
		_pid(0)
	{
		Poco::ErrorHandler::set(&_errorHandler);
	}

	~LauncherApp()
	{
	}

	static const std::string ETC_CONFIG;

protected:
	class ErrorHandler: public Poco::ErrorHandler
	{
	public:
		ErrorHandler(LauncherApp& app):
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
		LauncherApp& _app;
	};

	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present

		// load configuration from /etc/launcher.properties, if present (for deployment)
		Poco::File f(ETC_CONFIG);
		if (f.exists())
		{
			loadConfiguration(ETC_CONFIG);
		}

		ServerApplication::initialize(self);
	}

	void uninitialize()
	{
		ServerApplication::uninitialize();
	}

	void defineOptions(OptionSet& options)
	{
		ServerApplication::defineOptions(options);

		options.addOption(
			Option("help", "h", "Display help information on command line arguments.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<LauncherApp>(this, &LauncherApp::handleHelp)));

		options.addOption(
			Option("config-file", "c", "Load configuration data from a file.")
				.required(false)
				.repeatable(true)
				.argument("file")
				.callback(OptionCallback<LauncherApp>(this, &LauncherApp::handleConfig)));
	}

	void handleHelp(const std::string& name, const std::string& value)
	{
		_helpRequested = true;
		displayHelp();
		stopOptionsProcessing();
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("[<option> ...] -- <command>");
		helpFormatter.setHeader(
			"\n"
			"Applied Informatics Launcher for server applications.\n"
			"Copyright (c) 2011-2017 by Applied Informatics Software Engineering GmbH.\n"
			"All rights reserved.\n\n"
			"This program is used to launch server applications and "
			"to automatically relaunch them in case they terminate unexpectedly.\n\n"
			"The following command line options are supported:"
		);
		helpFormatter.setIndent(8);
		helpFormatter.format(std::cout);
	}

	void handleConfig(const std::string& name, const std::string& value)
	{
		loadConfiguration(value);
	}

	void watch()
	{
		int timeout = config().getInt("watchdog.timeout", 600000);
		int interval = config().getInt("watchdog.interval", 60000);

		while (!_stopWatching.tryWait(interval))
		{
			try
			{
				std::string path = config().getString("watchdog.file", "");
				if (!path.empty())
				{
					Poco::File f(path);
					if (f.exists())
					{
						Poco::Timestamp lastModified = f.getLastModified();
						if (lastModified.isElapsed(static_cast<Poco::Timestamp::TimeVal>(1000)*timeout))
						{
							logger().error("Watchdog is killing %s", _command);
							Poco::Process::kill(_pid);
						}
					}
				}
			}
			catch (Poco::Exception& exc)
			{
				logger().log(exc);
			}
		}
	}

	void launch()
	{
		int delay = config().getInt("relaunchDelay", 1000);
		while (!_stopped)
		{
			try
			{
				logger().information(format("Launching %s...", _command));
				Poco::ProcessHandle ph = Poco::Process::launch(_command, _args);
				_pid = ph.id();
				logger().information(format("Launched %s (%?d).", _command, _pid));
				int rc = ph.wait();
				logger().information(format("%s exited with status %d.", _command, rc));
				_pid = 0;
			}
			catch (Poco::Exception& exc)
			{
				logger().log(exc);
			}
			if (!_stopped)
			{
				logger().information(format("Waiting %d ms before relaunch...", delay));
				Poco::Timestamp ts;
				while (!_stopped && !ts.isElapsed(delay*1000))
				{
					Poco::Thread::sleep(100);
				}
			}
		}
	}

	int main(const std::vector<std::string>& args)
	{
		if (_helpRequested) return Application::EXIT_OK;
		if (args.empty())
		{
			displayHelp();
			return Application::EXIT_USAGE;
		}

		_command = args[0];
		_args.assign(args.begin() + 1, args.end());

		Poco::RunnableAdapter<LauncherApp> launchRunnable(*this, &LauncherApp::launch);
		Poco::Thread launchThread;
		launchThread.start(launchRunnable);

		Poco::RunnableAdapter<LauncherApp> watchRunnable(*this, &LauncherApp::watch);
		Poco::Thread watchThread;
		watchThread.start(watchRunnable);

		waitForTerminationRequest();

		_stopWatching.set();
		watchThread.join();

		if (_pid != 0)
		{
			logger().information(format("Stopping %s (%?d)...", _command, _pid));
			try
			{
				Poco::Process::requestTermination(_pid);
			}
			catch (Poco::Exception& exc)
			{
				logger().log(exc);
			}
		}
		_stopped = true;
		if (!launchThread.tryJoin(1000))
		{
			try
			{
				Poco::Process::kill(_pid);
			}
			catch (Poco::Exception& exc)
			{
				logger().log(exc);
			}
			launchThread.join();
		}

		return Application::EXIT_OK;
	}

private:
	ErrorHandler _errorHandler;
	bool _helpRequested;
	std::string _command;
	std::vector<std::string> _args;
	bool _stopped;
	Poco::Event _stopWatching;
	Poco::ProcessHandle::PID _pid;
};


const std::string LauncherApp::ETC_CONFIG("/etc/launcher.properties");


POCO_SERVER_MAIN(LauncherApp)

