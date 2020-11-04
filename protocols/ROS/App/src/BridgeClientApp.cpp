//
// BridgeClientApp.cpp
//
// A client application for ROS bridge.
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/ErrorHandler.h"
#include "Poco/URI.h"
#include "Poco/Delegate.h"
#include "IoT/ROS/BridgeClient.h"


using Poco::Util::ServerApplication;
using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::HelpFormatter;
using Poco::Util::OptionCallback;


namespace IoT {
namespace ROS {


class BridgeClientApp: public ServerApplication
{
public:
	BridgeClientApp():
		_errorHandler(*this),
		_showHelp(false)
	{
		Poco::ErrorHandler::set(&_errorHandler);
	}

	~BridgeClientApp()
	{
		// wait until all threads have terminated
		// before we completely shut down.
		Poco::ThreadPool::defaultPool().joinAll();
	}

protected:
	class ErrorHandler: public Poco::ErrorHandler
	{
	public:
		ErrorHandler(BridgeClientApp& app):
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
		BridgeClientApp& _app;
	};

	void initialize(Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		ServerApplication::initialize(self);
	}

	void defineOptions(OptionSet& options)
	{
		ServerApplication::defineOptions(options);

		options.addOption(
			Option("help", "h", "Display help information on command line arguments.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<BridgeClientApp>(this, &BridgeClientApp::handleHelp)));

		options.addOption(
			Option("config-file", "c", "Load configuration data from a file.")
				.required(false)
				.repeatable(true)
				.argument("file")
				.callback(OptionCallback<BridgeClientApp>(this, &BridgeClientApp::handleConfig)));
	}

	void handleHelp(const std::string& name, const std::string& value)
	{
		_showHelp = true;
		displayHelp();
		stopOptionsProcessing();
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
			"BridgeClientApp.\n"
			"Copyright (c) 2019 by Applied Informatics Software Engineering GmbH.\n"
			"All rights reserved.\n\n"
			"The following command line options are supported:"
		);
		helpFormatter.setIndent(8);
		helpFormatter.format(std::cout);
	}

	void onMessageReceived(const Poco::JSON::Object::Ptr& pMessage)
	{
		std::ostringstream ostr;
		pMessage->stringify(ostr, 4, 4);
		logger().information("Message received:\n%s", ostr.str());
	}

	int main(const std::vector<std::string>& args)
	{
		const std::vector<std::string>& topics = args;

		if (!_showHelp)
		{
			std::string uri = config().getString("bridge.uri");
			_pBridgeClient = new BridgeClient(Poco::URI(uri));
			logger().information("Connecting to bridge...");
			_pBridgeClient->connect();
			for (const auto& topic: topics)
			{
				logger().information("Subscribing to topic %s", topic);
				_pBridgeClient->subscribe(topic);
			}

			_pBridgeClient->messageReceived += Poco::delegate(this, &BridgeClientApp::onMessageReceived);
			_pBridgeClient->start();

			waitForTerminationRequest();

			_pBridgeClient->stop();
			_pBridgeClient->messageReceived -= Poco::delegate(this, &BridgeClientApp::onMessageReceived);

			_pBridgeClient->unsubscribeAll();

			logger().information("Disconnecting from bridge...");
			_pBridgeClient->disconnect();
		}
		return Application::EXIT_OK;
	}

private:
	ErrorHandler _errorHandler;
	bool _showHelp;
	Poco::SharedPtr<BridgeClient> _pBridgeClient;
};


} } // namespace IoT::ROS


POCO_SERVER_MAIN(IoT::ROS::BridgeClientApp)
