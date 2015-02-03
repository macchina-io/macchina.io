//
// WebTunnelClient.cpp
//
// $Id: //poco/1.4/WebTunnel/samples/WebTunnelClient/src/WebTunnelClient.cpp#7 $
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/WebTunnel/LocalPortForwarder.h"
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
#include "Poco/Util/ServerApplication.h"
#include "Poco/Util/Option.h"
#include "Poco/Util/OptionSet.h"
#include "Poco/Util/HelpFormatter.h"
#include "Poco/Util/IntValidator.h"
#include "Poco/NumberParser.h"
#include <iostream>


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


class WebTunnelClient: public Poco::Util::ServerApplication
{
public:
	WebTunnelClient(): 
		_helpRequested(false),
		_localPort(0),
		_remotePort(0)
	{
	}
	
	~WebTunnelClient()
	{
	}

protected:
	void initialize(Poco::Util::Application& self)
	{
		loadConfiguration(); // load default configuration files, if present
		Poco::Util::ServerApplication::initialize(self);
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
		Poco::Util::ServerApplication::uninitialize();
	}

	void defineOptions(OptionSet& options)
	{
		Poco::Util::ServerApplication::defineOptions(options);
		
		options.addOption(
			Option("help", "h", "Display help information on command line arguments.")
				.required(false)
				.repeatable(false)
				.callback(OptionCallback<WebTunnelClient>(this, &WebTunnelClient::handleHelp)));

		options.addOption(
			Option("config-file", "c", "Load configuration data from a file.")
				.required(false)
				.repeatable(true)
				.argument("file")
				.callback(OptionCallback<WebTunnelClient>(this, &WebTunnelClient::handleConfig)));

		options.addOption(
			Option("local-port", "L", "Specify local port number (required).")
				.required(false)
				.repeatable(true)
				.argument("port")
				.validator(new Poco::Util::IntValidator(1, 65535))
				.callback(OptionCallback<WebTunnelClient>(this, &WebTunnelClient::handleLocalPort)));

		options.addOption(
			Option("remote-port", "R", "Specify remote port number (required).")
				.required(false)
				.repeatable(true)
				.argument("port")
				.validator(new Poco::Util::IntValidator(1, 65535))
				.callback(OptionCallback<WebTunnelClient>(this, &WebTunnelClient::handleRemotePort)));

		options.addOption(
			Option("username", "u", "Specify username for reflector server (required).")
				.required(false)
				.repeatable(true)
				.argument("username")
				.callback(OptionCallback<WebTunnelClient>(this, &WebTunnelClient::handleUsername)));

		options.addOption(
			Option("password", "p", "Specify password for reflector server (required).")
				.required(false)
				.repeatable(true)
				.argument("password")
				.callback(OptionCallback<WebTunnelClient>(this, &WebTunnelClient::handlePassword)));

		options.addOption(
			Option("define", "D", "Define or override a configuration property.")
				.required(false)
				.repeatable(true)
				.argument("name=value")
				.callback(OptionCallback<WebTunnelClient>(this, &WebTunnelClient::handleDefine)));
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
		helpFormatter.setUsage("OPTIONS <Remote-URI>");
		helpFormatter.setHeader("\n"
			"my-devices.net WebTunnel Client.\n"
			"Copyright (c) 2013 by Applied Informatics Software Engineering GmbH.\n"
			"All rights reserved.\n\n"
			"This application is used to forward a remote TCP port to the local\n"
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
		
	int main(const std::vector<std::string>& args)
	{
		if (_helpRequested || args.size() != 1)
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

			Poco::URI uri(args[0]);
			Poco::WebTunnel::LocalPortForwarder forwarder(_localPort, _remotePort, uri, new Poco::WebTunnel::DefaultWebSocketFactory(_username, _password, connectTimeout));
			forwarder.setRemoteTimeout(remoteTimeout);
			forwarder.setLocalTimeout(localTimeout);

			waitForTerminationRequest();
		}
		return Poco::Util::Application::EXIT_OK;
	}
	
private:
	bool _helpRequested;
	Poco::UInt16 _localPort;
	Poco::UInt16 _remotePort;
	std::string _username;
	std::string _password;
	SSLInitializer _sslInitializer;
};


POCO_SERVER_MAIN(WebTunnelClient)
