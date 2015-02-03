//
// WebTunnelAgent.cpp
//
// $Id: //poco/1.4/WebTunnel/samples/WebTunnelAgent/src/WebTunnelAgent.cpp#4 $
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/WebTunnel/RemotePortForwarder.h"
#include "Poco/Net/HTTPSessionFactory.h"
#include "Poco/Net/HTTPSessionInstantiator.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPBasicCredentials.h"
#include "Poco/Net/DNS.h"
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
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTaskAdapter.h"
#include "Poco/URI.h"
#include "Poco/NumberParser.h"
#include "Poco/StringTokenizer.h"
#include "Poco/SharedPtr.h"
#include "Poco/Delegate.h"
#include "Poco/Buffer.h"
#include "Poco/Event.h"
#include "Poco/Environment.h"
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


class WebTunnelAgent: public Poco::Util::ServerApplication
{
public:
	WebTunnelAgent(): 
		_helpRequested(false),
		_httpPort(0),
		_useProxy(false),
		_proxyPort(0),
		_threads(8),
		_retryDelay(1000)
	{
	}
	
	~WebTunnelAgent()
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
		_pTimer = new Poco::Util::Timer;
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
				.callback(OptionCallback<WebTunnelAgent>(this, &WebTunnelAgent::handleHelp)));

		options.addOption(
			Option("config-file", "c", "Load configuration data from a file.")
				.required(false)
				.repeatable(true)
				.argument("file")
				.callback(OptionCallback<WebTunnelAgent>(this, &WebTunnelAgent::handleConfig)));

		options.addOption(
			Option("define", "D", "Define or override a configuration property.")
				.required(false)
				.repeatable(true)
				.argument("name=value")
				.callback(OptionCallback<WebTunnelAgent>(this, &WebTunnelAgent::handleDefine)));
	}

	void handleHelp(const std::string& name, const std::string& value)
	{
		_helpRequested = true;
	}

	void handleConfig(const std::string& name, const std::string& value)
	{
		loadConfiguration(value);
	}

	void handleDefine(const std::string& name, const std::string& value)
	{
		defineProperty(value);
	}

	void displayHelp()
	{
		HelpFormatter helpFormatter(options());
		helpFormatter.setCommand(commandName());
		helpFormatter.setUsage("OPTIONS");
		helpFormatter.setHeader("\n"
			"my-devices.net WebTunnel Agent.\n"
			"Copyright (c) 2013-2014 by Applied Informatics Software Engineering GmbH.\n"
			"All rights reserved.\n\n"
			"This application is used to forward a local TCP port to remote\n"
			"clients via the my-devices.net reflector server.\n\n"
			"The following command-line options are supported:");
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

	void connect()
	{
		logger().information("Connecting to " + _reflectorURI.toString() + "...");

		_pHTTPClientSession = Poco::Net::HTTPSessionFactory::defaultFactory().createClientSession(_reflectorURI);
		_pHTTPClientSession->setTimeout(_httpTimeout);
		if (_useProxy && !_proxyHost.empty())
		{
			_pHTTPClientSession->setProxy(_proxyHost, _proxyPort);
			if (!_proxyUsername.empty())
			{
				_pHTTPClientSession->setProxyCredentials(_proxyUsername, _proxyPassword);
			}
		}

		std::string path(_reflectorURI.getPathEtc());
		if (path.empty()) path = "/";
		Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPRequest::HTTP_1_1);
		request.set(SEC_WEBSOCKET_PROTOCOL, WEBTUNNEL_PROTOCOL);
		
		if (!_username.empty())
		{
			Poco::Net::HTTPBasicCredentials creds(_username, _password);
			creds.authenticate(request);
		}
		
		if (_httpPort != 0)
		{
			request.set("X-PTTH-Set-Property", Poco::format("device;httpPort=%hu", _httpPort));
		}
		request.set("User-Agent", _userAgent);
		
		Poco::Net::HTTPResponse response;
		bool reconnect = true;
		while (reconnect)
		{
			logger().debug("Entering reconnect loop...");
			try
			{
				Poco::Net::DNS::reload();
				logger().debug("Creating WebSocket...");
				Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket = new Poco::Net::WebSocket(*_pHTTPClientSession, request, response);
				if (response.get(SEC_WEBSOCKET_PROTOCOL, "") == WEBTUNNEL_PROTOCOL)
				{
					logger().debug("WebSocket established. Creating RemotePortForwarder...");
					_pDispatcher = new Poco::WebTunnel::SocketDispatcher(_threads);
					_pForwarder = new Poco::WebTunnel::RemotePortForwarder(*_pDispatcher, pWebSocket, _host, _ports, _remoteTimeout);
					_pForwarder->setConnectTimeout(_connectTimeout);
					_pForwarder->setLocalTimeout(_localTimeout);
					_pForwarder->webSocketClosed += Poco::delegate(this, &WebTunnelAgent::onClose);
					_retryDelay = 1000;
					logger().information("WebTunnel connection established.");
					return;
				}
				else
				{
					logger().error(Poco::format("The host at %s does not support the WebTunnel protocol.", _reflectorURI.toString()));

					pWebSocket->shutdown(Poco::Net::WebSocket::WS_PROTOCOL_ERROR);
					// receive final frame from peer; ignore if none is sent.
					if (pWebSocket->poll(Poco::Timespan(2, 0), Poco::Net::Socket::SELECT_READ))
					{
						Poco::Buffer<char> buffer(1024);
						int flags;
						try
						{
							pWebSocket->receiveFrame(buffer.begin(), static_cast<int>(buffer.size()), flags);
						}
						catch (Poco::Exception&)
						{
						}
					}
					pWebSocket->close();
					reconnect = false;
				}
			}
			catch (Poco::Exception& exc)
			{
				logger().error(Poco::format("Cannot connect to reflector at %s: %s", _reflectorURI.toString(), exc.displayText()));
				if (_retryDelay < 30000)
				{
					_retryDelay *= 2;
				}
				reconnect = !_stopped.tryWait(_retryDelay);
			}
		}
	}
	
	void disconnect()
	{
		if (_pForwarder)
		{
			logger().information("Disconnecting from reflector server");

			_pForwarder->webSocketClosed -= Poco::delegate(this, &WebTunnelAgent::onClose);
			_pForwarder->stop();
			_pForwarder = 0;
			_pDispatcher = 0;
		}
		if (_pHTTPClientSession)
		{
			try
			{
				_pHTTPClientSession->abort();
			}
			catch (Poco::Exception&)
			{
			}
		}
	}
	
	void onClose(const int& reason)
	{
		logger().information("WebTunnel connection closed.");
		
		if (!_stopped.tryWait(_retryDelay))
		{
			_pTimer->schedule(new Poco::Util::TimerTaskAdapter<WebTunnelAgent>(*this, &WebTunnelAgent::reconnect), Poco::Timestamp());
		}
	}
	
	void reconnect(Poco::Util::TimerTask&)
	{
		try
		{
			disconnect();
			connect();
		}
		catch (Poco::Exception& exc)
		{
			logger().fatal(exc.displayText());	
		}
	}
			
	int main(const std::vector<std::string>& args)
	{
		if (_helpRequested)
		{
			displayHelp();
		}
		else
		{
			try
			{
				_reflectorURI = config().getString("webtunnel.reflectorURI");
				_username = config().getString("webtunnel.username", "");
				_password = config().getString("webtunnel.password", "");
				std::string host = config().getString("webtunnel.host", "localhost");
				if (!Poco::Net::IPAddress::tryParse(host, _host))
				{
					_host = Poco::Net::DNS::resolveOne(host);
				}
				std::string ports = config().getString("webtunnel.ports", "");
				Poco::StringTokenizer tok(ports, ";,", Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
				for (Poco::StringTokenizer::Iterator it = tok.begin(); it != tok.end(); ++it)
				{
					int port = Poco::NumberParser::parse(*it);
					if (port > 0 && port < 65536)
					{
						_ports.insert(static_cast<Poco::UInt16>(port));
					}
					else
					{
						logger().error(Poco::format("Out-of-range port number specified in configuration: %d", port));
						return Poco::Util::Application::EXIT_CONFIG;
					}
				}

				if (_ports.empty())
				{
					logger().error("No ports to forward.");
					return Poco::Util::Application::EXIT_CONFIG;
				}

				_localTimeout = Poco::Timespan(config().getInt("webtunnel.localTimeout", 7200), 0);
				_connectTimeout = Poco::Timespan(config().getInt("webtunnel.connectTimeout", 10), 0);
				_remoteTimeout = Poco::Timespan(config().getInt("webtunnel.remoteTimeout", 300), 0);
				_threads = config().getInt("webtunnel.threads", 8);
				_httpPort = static_cast<Poco::UInt16>(config().getInt("webtunnel.httpPort", 0));
				_userAgent = config().getString("webtunnel.userAgent", "");
				_httpTimeout = Poco::Timespan(config().getInt("http.timeout", 30), 0);
				_useProxy = config().getBool("http.proxy.enable", false);
				_proxyHost = config().getString("http.proxy.host", "");
				_proxyPort = static_cast<Poco::UInt16>(config().getInt("http.proxy.port", 80));
				_proxyUsername = config().getString("http.proxy.username", "");
				_proxyPassword = config().getString("http.proxy.password", "");

				if (_httpPort != 0 && _ports.find(_httpPort) == _ports.end())
				{
					logger().warning(Poco::format("HTTP port (%hu) not in list of forwarded ports.", _httpPort));
				}

				if (_userAgent.empty())
				{
					_userAgent = WEBTUNNEL_AGENT;
					_userAgent += " (";
					_userAgent += Poco::Environment::osName();
					_userAgent += "/";
					_userAgent += Poco::Environment::osVersion();
					_userAgent += "; ";
					_userAgent += Poco::Environment::osArchitecture();
					_userAgent += ") POCO/";
					_userAgent += Poco::format("%d.%d.%d", 
						static_cast<int>(Poco::Environment::libraryVersion() >> 24), 
						static_cast<int>((Poco::Environment::libraryVersion() >> 16) & 0xFF), 
						static_cast<int>((Poco::Environment::libraryVersion() >> 8) & 0xFF));
				}
			
	#if defined(WEBTUNNEL_ENABLE_TLS)
				bool acceptUnknownCert = config().getBool("tls.acceptUnknownCertificate", true);
				std::string cipherList = config().getString("tls.ciphers", "HIGH:!DSS:!aNULL@STRENGTH");
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

				_pTimer->schedule(new Poco::Util::TimerTaskAdapter<WebTunnelAgent>(*this, &WebTunnelAgent::reconnect), Poco::Timestamp());
			
				waitForTerminationRequest();
		
				_stopped.set();
				disconnect();
				_pTimer->cancel(true);
			}
			catch (Poco::Exception& exc)
			{
				logger().log(exc);
				return Poco::Util::Application::EXIT_SOFTWARE;
			}
		}
		return Poco::Util::Application::EXIT_OK;
	}
	
	static const std::string SEC_WEBSOCKET_PROTOCOL;
	static const std::string WEBTUNNEL_PROTOCOL;
	static const std::string WEBTUNNEL_AGENT;
	
private:
	bool _helpRequested;
	Poco::Net::IPAddress _host;
	std::set<Poco::UInt16> _ports;
	Poco::URI _reflectorURI;
	std::string _username;
	std::string _password;
	std::string _userAgent;
	Poco::UInt16 _httpPort;
	bool _useProxy;
	std::string _proxyHost;
	Poco::UInt16 _proxyPort;
	std::string _proxyUsername;
	std::string _proxyPassword;
	Poco::Timespan _localTimeout;
	Poco::Timespan _connectTimeout;
	Poco::Timespan _remoteTimeout;
	Poco::Timespan _httpTimeout;
	int _threads;
	Poco::SharedPtr<Poco::WebTunnel::SocketDispatcher> _pDispatcher;
	Poco::SharedPtr<Poco::WebTunnel::RemotePortForwarder> _pForwarder;
	Poco::SharedPtr<Poco::Net::HTTPClientSession> _pHTTPClientSession;
	Poco::Event _stopped;
	int _retryDelay;
	Poco::SharedPtr<Poco::Util::Timer> _pTimer;
	SSLInitializer _sslInitializer;
};


const std::string WebTunnelAgent::SEC_WEBSOCKET_PROTOCOL("Sec-WebSocket-Protocol");
const std::string WebTunnelAgent::WEBTUNNEL_PROTOCOL("com.appinf.webtunnel.server/1.0");
const std::string WebTunnelAgent::WEBTUNNEL_AGENT("WebTunnelAgent/1.2");


POCO_SERVER_MAIN(WebTunnelAgent)
