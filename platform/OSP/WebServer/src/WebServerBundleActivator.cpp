//
// WebServerBundleActivator.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/OSP/Properties.h"
#include "Poco/OSP/Web/WebServerDispatcher.h"
#include "Poco/OSP/Web/WebServerRequestHandlerFactory.h"
#include "Poco/OSP/Web/WebServerService.h"
#include "Poco/Net/HTTPServer.h"
#include "Poco/Net/HTTPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/AutoPtr.h"
#include "Poco/ThreadPool.h"
#include "Poco/Format.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;
using Poco::OSP::Service;
using Poco::OSP::ServiceRef;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;
using Poco::OSP::Web::WebServerDispatcher;
using Poco::OSP::Web::WebServerRequestHandlerFactory;
using Poco::OSP::Web::WebServerService;
using Poco::Net::HTTPServer;
using Poco::Net::HTTPServerParams;
using Poco::Net::ServerSocket;
using Poco::AutoPtr;
using Poco::ThreadPool;
using Poco::format;


class StandardWebServerService: public WebServerService
{
public:
	StandardWebServerService(Poco::Net::HTTPServerParams::Ptr pParams, const Poco::Net::HTTPServer& server, const std::string& host):
		_pParams(pParams),
		_server(server),
		_host(host)
	{
	}
	
	~StandardWebServerService()
	{
	}
	
	int currentThreads() const
	{
		return _server.currentThreads();
	}

	int totalConnections() const
	{
		return _server.totalConnections();
	}
		
	int currentConnections() const
	{
		return _server.currentConnections();
	}

	int maxConcurrentConnections() const
	{
		return _server.maxConcurrentConnections();
	}
		
	int queuedConnections() const
	{	
		return _server.queuedConnections();
	}

	int refusedConnections() const
	{
		return _server.refusedConnections();
	}

	std::string host() const
	{
		return _host;
	}

	Poco::UInt16 port() const
	{
		return _server.port();
	}
	
	bool secure() const
	{
		return false;
	}
		
	Poco::Net::HTTPServerParams::Ptr params() const
	{
		return _pParams;
	}

	// Service
	const std::type_info& type() const
	{
		return typeid(StandardWebServerService);
	}
	
	bool isA(const std::type_info& otherType) const
	{
		std::string name(typeid(StandardWebServerService).name());
		return name == otherType.name() || WebServerService::isA(otherType);
	}

private:
	Poco::Net::HTTPServerParams::Ptr _pParams;
	const Poco::Net::HTTPServer& _server;
	std::string _host;
};


class WebServerBundleActivator: public BundleActivator
{
public:
	WebServerBundleActivator():
		_pHTTPServer(0)
	{
	}
	
	~WebServerBundleActivator()
	{
		delete _pHTTPServer;
	}
	
	void start(BundleContext::Ptr pContext)
	{
		ServiceRef::Ptr pPrefsRef = pContext->registry().findByName(PreferencesService::SERVICE_NAME);
		AutoPtr<PreferencesService> pPrefs = pPrefsRef->castedInstance<PreferencesService>();
		
		ServiceRef::Ptr pWebServerDispatcherRef = pContext->registry().findByName(WebServerDispatcher::SERVICE_NAME);
		if (pWebServerDispatcherRef)
		{
			AutoPtr<WebServerDispatcher> pWebServerDispatcher = pWebServerDispatcherRef->castedInstance<WebServerDispatcher>();

			// get default parameters from bundle configuration file
			std::string serverName    = pContext->thisBundle()->properties().getString("serverName", pContext->thisBundle()->name());
			std::string serverVersion = pContext->thisBundle()->version().toString();
			std::string defaultHost   = pContext->thisBundle()->properties().getString("host", "0.0.0.0");
			int defaultPort           = pContext->thisBundle()->properties().getInt("port", 22080);
			int defaultMaxQueued      = pContext->thisBundle()->properties().getInt("maxQueued", 100);
			int defaultMaxThreads     = pContext->thisBundle()->properties().getInt("maxThreads", 8);
			bool defaultKeepAlive     = pContext->thisBundle()->properties().getBool("keepAlive", true);
			int defaultKeepAliveTime  = pContext->thisBundle()->properties().getInt("keepAliveTime", 10);
			int defaultMaxKeepAlive   = pContext->thisBundle()->properties().getInt("maxKeepAlive", 10);
			
			// get parameters from global configuration file
			std::string host  = pPrefs->configuration()->getString("osp.web.server.host", defaultHost);
			int port          = pPrefs->configuration()->getInt("osp.web.server.port", defaultPort);
			int maxQueued     = pPrefs->configuration()->getInt("osp.web.server.maxQueued", defaultMaxQueued);
			int maxThreads    = pPrefs->configuration()->getInt("osp.web.server.maxThreads", defaultMaxThreads);
			bool keepAlive    = pPrefs->configuration()->getBool("osp.web.server.keepAlive", defaultKeepAlive);
			int keepAliveTime = pPrefs->configuration()->getInt("osp.web.server.keepAliveTime", defaultKeepAliveTime);
			int maxKeepAlive  = pPrefs->configuration()->getInt("osp.web.server.maxKeepAlive", defaultMaxKeepAlive);
			
			if (port != 0)
			{
				pWebServerDispatcher->threadPool().addCapacity(maxThreads);
				
				HTTPServerParams::Ptr pParams = new HTTPServerParams;
				pParams->setServerName(Poco::format("%s:%d", host, port));
				pParams->setSoftwareVersion(serverName + "/" + serverVersion);
				pParams->setKeepAlive(keepAlive);
				pParams->setKeepAliveTimeout(Poco::Timespan(keepAliveTime, 0));
				pParams->setMaxKeepAliveRequests(maxKeepAlive);
				pParams->setMaxQueued(maxQueued);
				pParams->setMaxThreads(maxThreads);
				
				pContext->logger().information(format("Starting HTTP server on port %d.", port));
				
				Poco::Net::SocketAddress addr(host, port); 
				ServerSocket svs(addr);
				_pHTTPServer = new HTTPServer(new WebServerRequestHandlerFactory(*pWebServerDispatcher, false), pWebServerDispatcher->threadPool(), svs, pParams);
				_pHTTPServer->start();
				
				Poco::OSP::Properties props;
				props.set("protocol", "http");
				props.set("host", host);
				props.set("port", format("%d", port));
				_pService = pContext->registry().registerService("osp.web.server", new StandardWebServerService(pParams, *_pHTTPServer, host), props);
			}
		}
		else
		{
			pContext->logger().error("The WebServerDispatcher service could not be found.");
		}
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		if (_pHTTPServer)
		{
			pContext->logger().information("Stopping HTTP server.");
			pContext->registry().unregisterService(_pService);
			_pService = 0;
			_pHTTPServer->stopAll();
		}
	}
	
private:
	HTTPServer* _pHTTPServer;
	ServiceRef::Ptr _pService;
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(WebServerBundleActivator)
POCO_END_MANIFEST
