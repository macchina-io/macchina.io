//
// BundleActivator.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/WebTunnel/RemotePortForwarder.h"
#include "Poco/Net/HTTPSessionFactory.h"
#include "Poco/Net/HTTPSessionInstantiator.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPBasicCredentials.h"
#include "Poco/Net/DNS.h"
#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
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
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;
using Poco::OSP::Preferences;


namespace IoT {
namespace WebTunnel {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator():
		_useProxy(false),
		_threads(0),
		_retryDelay(1000)
	{
	}
	
	~BundleActivator()
	{
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefsService = ServiceFinder::find<PreferencesService>(pContext);
		_pPrefs = _pPrefsService->preferences(pContext->thisBundle()->symbolicName());
	
		if (getBoolConfig("webtunnel.enable", false))
		{
			try
			{
				_reflectorURI = getStringConfig("webtunnel.reflectorURI");
				_deviceName = getStringConfig("webtunnel.deviceName", "");
				_username = getStringConfig("webtunnel.username", "");
				_password = getStringConfig("webtunnel.password", "");
				std::string host = getStringConfig("webtunnel.host", "127.0.0.1");
				if (!Poco::Net::IPAddress::tryParse(host, _host))
				{
					_host = Poco::Net::DNS::resolveOne(host);
				}
				std::string ports = getStringConfig("webtunnel.ports", "");
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
						_pContext->logger().warning(Poco::format("Ignored out-of-range port number specified in configuration: %d", port));
					}
				}
			
				_httpPort = static_cast<Poco::UInt16>(_pPrefsService->configuration()->getInt("osp.web.server.port", 22080));
				_ports.insert(_httpPort);

				_localTimeout = Poco::Timespan(getIntConfig("webtunnel.localTimeout", 7200), 0);
				_connectTimeout = Poco::Timespan(getIntConfig("webtunnel.connectTimeout", 10), 0);
				_remoteTimeout = Poco::Timespan(getIntConfig("webtunnel.remoteTimeout", 300), 0);
				_threads = getIntConfig("webtunnel.threads", 4);
				_userAgent = getStringConfig("webtunnel.userAgent", "");
				_httpTimeout = Poco::Timespan(getIntConfig("webtunnel.http.timeout", 30), 0);
				_useProxy = getBoolConfig("webtunnel.http.proxy.enable", false);
				_proxyHost = getStringConfig("webtunnel.http.proxy.host", "");
				_proxyPort = static_cast<Poco::UInt16>(getIntConfig("webtunnel.http.proxy.port", 80));
				_proxyUsername = getStringConfig("webtunnel.http.proxy.username", "");
				_proxyPassword = getStringConfig("webtunnel.http.proxy.password", "");

				if (_userAgent.empty())
				{
					_userAgent = pContext->thisBundle()->symbolicName();
					_userAgent += "/";
					_userAgent += pContext->thisBundle()->version().toString();
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
		
				_pTimer = new Poco::Util::Timer;
				_pTimer->schedule(new Poco::Util::TimerTaskAdapter<BundleActivator>(*this, &BundleActivator::reconnect), Poco::Timestamp());
			}
			catch (Poco::Exception& exc)
			{
				_pContext->logger().log(exc);
			}	
		}
		else
		{
			_pContext->logger().information("WebTunnel disabled.");
		}
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		if (_pTimer)
		{
			_stopped.set();
			disconnect();
			_pTimer->cancel(true);
			_pTimer = 0;
		}

		_pPrefs = 0;
		_pPrefsService = 0;
		_pContext = 0;
	}

protected:
	bool getBoolConfig(const std::string& key)
	{
		return _pPrefs->getBool(key, _pPrefsService->configuration()->getBool(key));
	}

	bool getBoolConfig(const std::string& key, bool deflt)
	{
		return _pPrefs->getBool(key, _pPrefsService->configuration()->getBool(key, deflt));
	}

	int getIntConfig(const std::string& key)
	{
		return _pPrefs->getInt(key, _pPrefsService->configuration()->getInt(key));
	}

	int getIntConfig(const std::string& key, int deflt)
	{
		return _pPrefs->getInt(key, _pPrefsService->configuration()->getInt(key, deflt));
	}
	
	std::string getStringConfig(const std::string& key)
	{
		return _pPrefs->getString(key, _pPrefsService->configuration()->getString(key));
	}
	
	std::string getStringConfig(const std::string& key, const std::string& deflt)
	{
		return _pPrefs->getString(key, _pPrefsService->configuration()->getString(key, deflt));
	}

	void connect()
	{
		_pContext->logger().information("Connecting to " + _reflectorURI.toString() + "...");

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
		if (!_deviceName.empty())
		{
			request.set("X-PTTH-Set-Property", Poco::format("device;name=\"%s\"", _deviceName));
		}
		request.set("User-Agent", _userAgent);
		
		Poco::Net::HTTPResponse response;
		bool reconnect = true;
		while (reconnect)
		{
			_pContext->logger().debug("Entering reconnect loop...");
			try
			{
				Poco::Net::DNS::reload();
				_pContext->logger().debug("Creating WebSocket...");
				Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket = new Poco::Net::WebSocket(*_pHTTPClientSession, request, response);
				if (response.get(SEC_WEBSOCKET_PROTOCOL, "") == WEBTUNNEL_PROTOCOL)
				{
					_pContext->logger().debug("WebSocket established. Creating RemotePortForwarder...");
					_pDispatcher = new Poco::WebTunnel::SocketDispatcher(_threads);
					_pForwarder = new Poco::WebTunnel::RemotePortForwarder(*_pDispatcher, pWebSocket, _host, _ports, _remoteTimeout);
					_pForwarder->setConnectTimeout(_connectTimeout);
					_pForwarder->setLocalTimeout(_localTimeout);
					_pForwarder->webSocketClosed += Poco::delegate(this, &BundleActivator::onClose);
					_retryDelay = 1000;
					_pContext->logger().information("WebTunnel connection established.");
					return;
				}
				else
				{
					_pContext->logger().error(Poco::format("The host at %s does not support the WebTunnel protocol.", _reflectorURI.toString()));

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
				_pContext->logger().error(Poco::format("Cannot connect to reflector at %s: %s", _reflectorURI.toString(), exc.displayText()));
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
			_pContext->logger().information("Disconnecting from reflector server");

			_pForwarder->webSocketClosed -= Poco::delegate(this, &BundleActivator::onClose);
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
		_pContext->logger().information("WebTunnel connection closed.");
		
		if (!_stopped.tryWait(_retryDelay))
		{
			_pTimer->schedule(new Poco::Util::TimerTaskAdapter<BundleActivator>(*this, &BundleActivator::reconnect), Poco::Timestamp());
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
			_pContext->logger().fatal(exc.displayText());	
		}
	}

	static const std::string SEC_WEBSOCKET_PROTOCOL;
	static const std::string WEBTUNNEL_PROTOCOL;

private:
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefsService;
	Preferences::Ptr _pPrefs;
	Poco::Net::IPAddress _host;
	std::set<Poco::UInt16> _ports;
	Poco::URI _reflectorURI;
	std::string _deviceName;
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
};


const std::string BundleActivator::SEC_WEBSOCKET_PROTOCOL("Sec-WebSocket-Protocol");
const std::string BundleActivator::WEBTUNNEL_PROTOCOL("com.appinf.webtunnel.server/1.0");


} } // namespace IoT::WebTunnel


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::WebTunnel::BundleActivator)
POCO_END_MANIFEST
