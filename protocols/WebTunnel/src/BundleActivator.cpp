//
// BundleActivator.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/WebTunnel/RemotePortForwarder.h"
#include "IoT/WebTunnel/WebTunnelService.h"
#include "IoT/WebTunnel/WebTunnelServiceServerHelper.h"
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
#include "Poco/Clock.h"
#include "Poco/Mutex.h"
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


class WebTunnelServiceImpl: public WebTunnelService
{
public:
	typedef Poco::SharedPtr<WebTunnelServiceImpl> Ptr;

	WebTunnelServiceImpl() = default;
	~WebTunnelServiceImpl() = default;

	void update(Poco::WebTunnel::RemotePortForwarder* pForwarder)
	{
		Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);

		if (pForwarder && !_pForwarder)
		{
			_pForwarder = pForwarder;
			lock.unlock();
			try
			{
				connected(this);
			}
			catch (Poco::Exception& exc)
			{
				_logger.error("Unhandled exception in connected delegate: %s", exc.displayText());
			}
		}
		else if (!pForwarder && _pForwarder)
		{
			_pForwarder = pForwarder;
			lock.unlock();
			try
			{
				disconnected(this);
			}
			catch (Poco::Exception& exc)
			{
				_logger.error("Unhandled exception in disconnected delegate: %s", exc.displayText());
			}
		}
	}

	// WebTunnelService
	bool isConnected() const
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		return !!_pForwarder;
	}

	void updateProperties(const std::vector<Property>& properties)
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		if (_pForwarder)
		{
			std::map<std::string, std::string> propsMap;
			for (const auto& p: properties)
			{
				propsMap[p.name] = p.value;
			}
			_pForwarder->updateProperties(propsMap);
		}
		else throw Poco::IllegalStateException("WebTunnel connection not available");
	}

private:
	Poco::WebTunnel::RemotePortForwarder* _pForwarder = nullptr;
	mutable Poco::FastMutex _mutex;
	Poco::Logger& _logger = Poco::Logger::get("IoT.WebTunnelService");
};


typedef Poco::RemotingNG::ServerHelper<WebTunnelService> ServerHelper;


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator():
		_httpPort(80),
		_vncPort(0),
		_useProxy(false),
		_proxyPort(0),
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

				_vncPort = static_cast<Poco::UInt16>(getIntConfig("webtunnel.vncPort", 0));
				if (_vncPort != 0 && _ports.find(_vncPort) == _ports.end())
				{
					_pContext->logger().warning(Poco::format("Specified vncPort %hu not in list of forwarded ports (webtunnel.ports) - ignored.", _vncPort));
					_vncPort = 0;
				}

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

				_pWebTunnelService = new WebTunnelServiceImpl;
				ServerHelper::RemoteObjectPtr pWebTunnelServiceRemoteObject = ServerHelper::createRemoteObject(_pWebTunnelService, WebTunnelService::SERVICE_NAME);
				Poco::OSP::Properties props;
				props.set("io.macchina.protocol", "io.macchina.webtunnel");
				props.set("io.macchina.webtunnel.serverURI", _reflectorURI.toString());
				_pServiceRef = _pContext->registry().registerService(WebTunnelService::SERVICE_NAME, pWebTunnelServiceRemoteObject, props);

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
			_pTimer.reset();
		}

		pContext->registry().unregisterService(_pServiceRef);
		_pServiceRef.reset();
		_pWebTunnelService.reset();

		_pPrefs.reset();
		_pPrefsService.reset();
		_pContext.reset();
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
		Poco::Net::HTTPResponse response;
		request.set(SEC_WEBSOCKET_PROTOCOL, WEBTUNNEL_PROTOCOL);

		if (_httpPort != 0)
		{
			request.add("X-PTTH-Set-Property", Poco::format("device;httpPort=%hu", _httpPort));
		}
		if (_vncPort != 0)
		{
			request.add("X-PTTH-Set-Property", Poco::format("device;vncPort=%hu", _vncPort));
		}
		if (!_deviceName.empty())
		{
			request.add("X-PTTH-Set-Property", Poco::format("device;name=\"%s\"", _deviceName));
		}
		request.set("User-Agent", _userAgent);

		try
		{
			Poco::Net::DNS::reload();

			// Note: Obtain username/password as late as possible. Reason: The username
			// may contain ${system.nodeId} (Ethernet address), which may not be available
			// by the time we launch, as the network interface may not be up yet.
			std::string username = getStringConfig("webtunnel.username", "");
			std::string password = getStringConfig("webtunnel.password", "");
			if (!username.empty())
			{
				Poco::Net::HTTPBasicCredentials creds(username, password);
				creds.authenticate(request);
			}

			_pContext->logger().debug("Creating WebSocket...");
			Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket = new Poco::Net::WebSocket(*_pHTTPClientSession, request, response);
			if (response.get(SEC_WEBSOCKET_PROTOCOL, "") == WEBTUNNEL_PROTOCOL)
			{
				_pContext->logger().debug("WebSocket established. Creating RemotePortForwarder...");
				pWebSocket->setNoDelay(true);
				_retryDelay = 1000;
				_pDispatcher = new Poco::WebTunnel::SocketDispatcher(_threads);
				_pForwarder = new Poco::WebTunnel::RemotePortForwarder(*_pDispatcher, pWebSocket, _host, _ports, _remoteTimeout);
				_pForwarder->webSocketClosed += Poco::delegate(this, &BundleActivator::onClose);
				_pForwarder->setConnectTimeout(_connectTimeout);
				_pForwarder->setLocalTimeout(_localTimeout);
				_pContext->logger().information("WebTunnel connection established.");

				_pWebTunnelService->update(_pForwarder);

				return;
			}
			else
			{
				std::string msg(Poco::format("The host at %s does not support the WebTunnel protocol.", _reflectorURI.toString()));
				_pContext->logger().error(msg);

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
				_retryDelay = 30000;
			}
		}
		catch (Poco::Exception& exc)
		{
			std::string msg = response.get("X-PTTH-Error", exc.displayText());
			_pContext->logger().error(Poco::format("Cannot connect to reflector at %s: %s", _reflectorURI.toString(), msg));
			if (_retryDelay < 30000)
			{
				_retryDelay *= 2;
			}
		}
		scheduleReconnect();
	}

	void disconnect()
	{
		if (_pForwarder)
		{
			_pContext->logger().information("Disconnecting from reflector server");

			_pWebTunnelService->update(nullptr);

			_pForwarder->webSocketClosed -= Poco::delegate(this, &BundleActivator::onClose);
			_pForwarder->stop();
			_pDispatcher->reset();
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
		_pWebTunnelService->update(nullptr);
		scheduleReconnect();
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

	void scheduleReconnect()
	{
		if (!_stopped.tryWait(1))
		{
			Poco::Clock nextClock;
			nextClock += static_cast<Poco::Clock::ClockDiff>(_retryDelay)*1000;
			_pTimer->schedule(new Poco::Util::TimerTaskAdapter<BundleActivator>(*this, &BundleActivator::reconnect), nextClock);
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
	std::string _userAgent;
	Poco::UInt16 _httpPort;
	Poco::UInt16 _vncPort;
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
	WebTunnelServiceImpl::Ptr _pWebTunnelService;
	Poco::OSP::ServiceRef::Ptr _pServiceRef;
};


const std::string BundleActivator::SEC_WEBSOCKET_PROTOCOL("Sec-WebSocket-Protocol");
const std::string BundleActivator::WEBTUNNEL_PROTOCOL("com.appinf.webtunnel.server/1.0");


} } // namespace IoT::WebTunnel


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::WebTunnel::BundleActivator)
POCO_END_MANIFEST
