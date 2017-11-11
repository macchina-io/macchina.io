//
// WebTunnelVNC.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/WebTunnel/LocalPortForwarder.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPSessionFactory.h"
#include "Poco/Net/HTTPSessionInstantiator.h"
#if defined(WEBTUNNEL_ENABLE_TLS)
#include "Poco/Net/HTTPSSessionInstantiator.h"
#include "Poco/Net/Context.h"
#include "Poco/Net/PrivateKeyPassphraseHandler.h"
#include "Poco/Net/AcceptCertificateHandler.h"
#include "Poco/Net/RejectCertificateHandler.h"
#include "Poco/Net/SSLManager.h"
#endif
#include "Poco/Util/Application.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/IntValidator.h"
#include "Poco/NumberParser.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Process.h"
#include "Poco/Format.h"
#include "Poco/String.h"
#include <iostream>
#if defined(POCO_OS_FAMILY_WINDOWS)
#include <windows.h>
#elif defined(POCO_OS_FAMILY_UNIX)
#include <termios.h>
#endif


using Poco::Util::Option;
using Poco::Util::OptionSet;
using Poco::Util::OptionCallback;
using Poco::Util::HelpFormatter;


class SSLInitializer
{
public:
	SSLInitializer()
	{
#if defined(WEBTUNNEL_ENABLE_TLS)
		Poco::Net::initializeSSL();
#endif
	}
	
	~SSLInitializer()
	{
#if defined(WEBTUNNEL_ENABLE_TLS)
		Poco::Net::uninitializeSSL();
#endif
	}
};


class WebTunnelVNC: public Poco::Util::Application
{
public:
	WebTunnelVNC(): 
		_helpRequested(false),
		_localPort(0),
		_remotePort(5900)
	{
	}
	
	~WebTunnelVNC()
	{
	}

protected:
	void initialize(Poco::Util::Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		Poco::Util::Application::initialize(self);
		Poco::Net::HTTPSessionInstantiator::registerInstantiator();
#if defined(WEBTUNNEL_ENABLE_TLS)
		Poco::Net::HTTPSSessionInstantiator::registerInstantiator();
#endif
	}
		
	void uninitialize()
	{
		Poco::Net::HTTPSessionInstantiator::unregisterInstantiator();
#if defined(WEBTUNNEL_ENABLE_TLS)
		Poco::Net::HTTPSSessionInstantiator::unregisterInstantiator();
#endif
		Poco::Util::Application::uninitialize();
	}

	void defineOptions(OptionSet& options)
	{
		Poco::Util::Application::defineOptions(options);
		
		options.addOption(
			Option("help", "h", "Display help information on command line arguments.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<WebTunnelVNC>(this, &WebTunnelVNC::handleHelp)));

		options.addOption(
			Option("config-file", "c", "Load configuration data from a file.")
				.required(false)
				.repeatable(true)
				.argument("file")
				.callback(OptionCallback<WebTunnelVNC>(this, &WebTunnelVNC::handleConfig)));

		options.addOption(
			Option("local-port", "L", "Specify local port number (default: ephemeral).")
				.required(false)
				.repeatable(false)
				.argument("port")
				.validator(new Poco::Util::IntValidator(1, 65535))
				.callback(OptionCallback<WebTunnelVNC>(this, &WebTunnelVNC::handleLocalPort)));

		options.addOption(
			Option("remote-port", "R", "Specify remote port number (default: VNC/5900).")
				.required(false)
				.repeatable(false)
				.argument("port")
				.validator(new Poco::Util::IntValidator(1, 65535))
				.callback(OptionCallback<WebTunnelVNC>(this, &WebTunnelVNC::handleRemotePort)));

		options.addOption(
			Option("username", "u", "Specify username for reflector server.")
				.required(false)
				.repeatable(false)
				.argument("username")
				.callback(OptionCallback<WebTunnelVNC>(this, &WebTunnelVNC::handleUsername)));

		options.addOption(
			Option("password", "p", "Specify password for reflector server.")
				.required(false)
				.repeatable(false)
				.argument("password")
				.callback(OptionCallback<WebTunnelVNC>(this, &WebTunnelVNC::handlePassword)));

		options.addOption(
			Option("define", "D", "Define or override a configuration property.")
				.required(false)
				.repeatable(true)
				.argument("name=value")
				.callback(OptionCallback<WebTunnelVNC>(this, &WebTunnelVNC::handleDefine)));
	}

	void handleHelp(const std::string& name, const std::string& value)
	{
		_helpRequested = true;
	}

	void handleConfig(const std::string& name, const std::string& value)
	{
		loadConfiguration(value);
	}
	
	void handleLocalPort(const std::string& name, const std::string& value)
	{
		_localPort = static_cast<Poco::UInt16>(Poco::NumberParser::parseUnsigned(value));
	}
	
	void handleRemotePort(const std::string& name, const std::string& value)
	{
		_remotePort = static_cast<Poco::UInt16>(Poco::NumberParser::parseUnsigned(value));
	}

	void handleUsername(const std::string& name, const std::string& value)
	{
		_username = value;
	}

	void handlePassword(const std::string& name, const std::string& value)
	{
		_password = value;
	}

	void handleDefine(const std::string& name, const std::string& value)
	{
		defineProperty(value);
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS <Remote-URI> [-- VNC-OPTIONS]");
		helpFormatter.setHeader("\n"
			"my-devices.net WebTunnel VNC Client.\n"
			"Copyright (c) 2015 by Applied Informatics Software Engineering GmbH.\n"
			"All rights reserved.\n\n"
			"This application is used to launch a VNC connection to a remote\n"
			"host via the my-devices.net reflector server.\n\n"
			"<Remote-URI> specifies the URI of the remote device via the\n"
			"reflector server, e.g.:\n"
#if defined(WEBTUNNEL_ENABLE_TLS)
			"https://8ba57423-ec1a-4f31-992f-a66c240cbfa0.my-devices.net"
#else
			"http://8ba57423-ec1a-4f31-992f-a66c240cbfa0.my-devices.net"
#endif			
			"\n\n"
			"The following command-line options are supported:"
		);
		helpFormatter.setFooter(
			"For more information, please visit the my-devices.net "
			"website at <http://www.my-devices.net>."
		);
		helpFormatter.setIndent(8);
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

	void promptLogin()
	{
		if (_username.empty())
		{
			std::cout << "my-devices.net Username: " << std::flush;
			std::getline(std::cin, _username);
		}
		if (_password.empty())
		{
			std::cout << "my-devices.net Password: " << std::flush;
			echo(false);
			std::getline(std::cin, _password);
			echo(true);
			std::cout << std::endl;
		}
	}
	
	void echo(bool status)
	{
#if defined(POCO_OS_FAMILY_WINDOWS)
		HANDLE stdIn = GetStdHandle(STD_INPUT_HANDLE);
		DWORD mode;
		GetConsoleMode(stdIn, &mode);
		mode = status ? mode | ENABLE_ECHO_INPUT : mode & ~ENABLE_ECHO_INPUT;
		SetConsoleMode(stdIn, mode);
#elif defined(POCO_OS_FAMILY_UNIX)
		struct termios tio;
		tcgetattr(0, &tio);
		tio.c_lflag = status ? tio.c_lflag | ECHO : tio.c_lflag & ~(ECHO);
		tcsetattr(0, TCSANOW, &tio);
#endif
	}

	int main(const std::vector<std::string>& args)
	{
		int rc = Poco::Util::Application::EXIT_OK;
		if (_helpRequested || args.empty())
		{
			displayHelp();
		}
		else
		{
			Poco::Timespan connectTimeout = Poco::Timespan(config().getInt("webtunnel.connectTimeout", 30), 0);
			Poco::Timespan remoteTimeout = Poco::Timespan(config().getInt("webtunnel.remoteTimeout", 300), 0);
			Poco::Timespan localTimeout = Poco::Timespan(config().getInt("webtunnel.localTimeout", 7200), 0);

#if defined(WEBTUNNEL_ENABLE_TLS)
			bool acceptUnknownCert = config().getBool("tls.acceptUnknownCertificate", true);
			std::string cipherList = config().getString("tls.ciphers", "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
			bool extendedVerification = config().getBool("tls.extendedCertificateVerification", false);
			std::string caLocation = config().getString("tls.caLocation", "");

			Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> pCertificateHandler;
			if (acceptUnknownCert)
				pCertificateHandler = new Poco::Net::AcceptCertificateHandler(false);
			else
				pCertificateHandler = new Poco::Net::RejectCertificateHandler(false);
			Poco::Net::Context::Ptr pContext = new Poco::Net::Context(Poco::Net::Context::TLSV1_CLIENT_USE, "", "", caLocation, Poco::Net::Context::VERIFY_RELAXED, 5, true, cipherList);
			pContext->enableExtendedCertificateVerification(extendedVerification);
			Poco::Net::SSLManager::instance().initializeClient(0, pCertificateHandler, pContext);
#endif

			if (config().getBool("http.proxy.enable", false))
			{
				logger().information("Proxy enable");
				Poco::Net::HTTPClientSession::ProxyConfig proxyConfig;
				proxyConfig.host = config().getString("http.proxy.host", "");
				proxyConfig.port = static_cast<Poco::UInt16>(config().getInt("http.proxy.port", 80));
				proxyConfig.username = config().getString("http.proxy.username", "");
				proxyConfig.password = config().getString("http.proxy.password", "");
				Poco::Net::HTTPClientSession::setGlobalProxyConfig(proxyConfig);
			}

			promptLogin();

			Poco::URI uri(args[0]);
			Poco::WebTunnel::LocalPortForwarder forwarder(_localPort, _remotePort, uri, new Poco::WebTunnel::DefaultWebSocketFactory(_username, _password, connectTimeout));
			forwarder.setRemoteTimeout(remoteTimeout);
			forwarder.setLocalTimeout(localTimeout);
			
			Poco::UInt16 localPort = forwarder.localPort();
			std::string defaultVNCExecutable;
#if defined(__APPLE__)
			defaultVNCExecutable = "open";
#else
			defaultVNCExecutable = "vncviewer";
#endif
			std::string vncExecutable = config().getString("vncviewer.executable", defaultVNCExecutable);
			Poco::Process::Args vncArgs;
			if (vncExecutable == "open")
			{
				vncArgs.push_back("-W");
				vncArgs.push_back("-n");
				vncArgs.push_back("vnc://localhost:" + Poco::NumberFormatter::format(static_cast<unsigned>(localPort)));
			}
			else
			{
				vncArgs.push_back("localhost:" + Poco::NumberFormatter::format(static_cast<unsigned>(localPort)));
			}
			vncArgs.insert(vncArgs.end(), ++args.begin(), args.end());
			
			logger().debug(Poco::format("Launching VNC client: %s", vncExecutable));
			Poco::ProcessHandle ph = Poco::Process::launch(vncExecutable, vncArgs);
			rc = ph.wait();
			logger().debug(Poco::format("VNC client terminated with exit code %d", rc));
		}
		return rc;
	}
	
private:
	bool _helpRequested;
	Poco::UInt16 _localPort;
	Poco::UInt16 _remotePort;
	std::string _username;
	std::string _password;
	SSLInitializer _sslInitializer;
};


POCO_APP_MAIN(WebTunnelVNC)
