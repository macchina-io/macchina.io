//
// BundleActivator.cpp
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/RemotingNG/TCP/Listener.h"
#include "Poco/RemotingNG/TCP/Transport.h"
#include "Poco/RemotingNG/TCP/TransportFactory.h"
#include "Poco/RemotingNG/TCP/ConnectionManager.h"
#include "Poco/File.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"


namespace Poco {
namespace OSP {
namespace RemotingNG {
namespace TCP {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void start(Poco::OSP::BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = Poco::OSP::ServiceFinder::find<Poco::OSP::PreferencesService>(_pContext);

		Poco::RemotingNG::TCP::TransportFactory::registerFactory();

		std::string endpoint = _pPrefs->configuration()->getString("remoting.tcp.listener", "");
		if (!endpoint.empty())
		{
			if (endpoint[0] == '/')
			{
				Poco::File f(endpoint);
				if (f.exists())
				{
					pContext->logger().notice("Removing existing socket file %s", endpoint);
					f.remove();
				}
			}

			Poco::RemotingNG::TCP::Listener::Ptr pListener = new Poco::RemotingNG::TCP::Listener(endpoint);
			_listener = Poco::RemotingNG::ORB::instance().registerListener(pListener);

			_pContext->logger().information("Remoting TCP Listener ready: %s", _listener);

			std::vector<ServiceRef::Ptr> services;
			pContext->registry().find("name", services);
			for (std::vector<ServiceRef::Ptr>::iterator it = services.begin(); it != services.end(); ++it)
			{
				registerServiceWithORB(*it);
			}

			pContext->registry().serviceRegistered   += Poco::delegate(this, &BundleActivator::handleServiceRegistered);
			pContext->registry().serviceUnregistered += Poco::delegate(this, &BundleActivator::handleServiceUnregistered);

			int connectionIdleTimeout = _pPrefs->configuration()->getInt("remoting.tcp.connection.idleTimeout", 60);
			Poco::RemotingNG::TCP::ConnectionManager::defaultManager().setIdleTimeout(Poco::Timespan(connectionIdleTimeout, 0));

			int handshakeTimeout = _pPrefs->configuration()->getInt("remoting.tcp.connection.handshakeTimeout", 8);
			Poco::RemotingNG::TCP::ConnectionManager::defaultManager().setHandshakeTimeout(Poco::Timespan(handshakeTimeout, 0));
			pListener->setHandshakeTimeout(Poco::Timespan(handshakeTimeout, 0));
		}
	}

	void stop(BundleContext::Ptr pContext)
	{
		_pPrefs = 0;

		if (!_listener.empty())
		{
			Poco::RemotingNG::ORB::instance().unregisterListener(_listener, true);

			pContext->registry().serviceRegistered   -= Poco::delegate(this, &BundleActivator::handleServiceRegistered);
			pContext->registry().serviceUnregistered -= Poco::delegate(this, &BundleActivator::handleServiceUnregistered);
		}

		Poco::RemotingNG::TCP::TransportFactory::unregisterFactory();

		_pContext = 0;
	}

	void handleServiceRegistered(const void* sender, ServiceEvent& event)
	{
		_pContext->logger().information("Service registered: " + event.service()->name());
		registerServiceWithORB(event.service());
	}

	void handleServiceUnregistered(const void* sender, ServiceEvent& event)
	{
		if (event.service()->properties().has("remoting.tcp.uri"))
		{
			_pContext->logger().information("Unregistering service with ORB: %s", event.service()->name());

			std::string uri = event.service()->properties().get("remoting.tcp.uri");
			Poco::RemotingNG::ORB::instance().unregisterObject(uri);
		}
	}

	void registerServiceWithORB(ServiceRef::Ptr pServiceRef)
	{
		if (pServiceRef->properties().getBool("remoting.tcp.enable", false))
		{
			Poco::OSP::Service::Ptr pService = pServiceRef->instance();
			if (dynamic_cast<Poco::RemotingNG::RemoteObject*>(pService.get()))
			{
				Poco::RemotingNG::RemoteObject::Ptr pRemoteObject = pService.cast<Poco::RemotingNG::RemoteObject>();
				std::string uri = Poco::RemotingNG::ORB::instance().registerObject(pRemoteObject, _listener);
				pRemoteObject->remoting__enableRemoteEvents(Poco::RemotingNG::TCP::Transport::PROTOCOL);
				pServiceRef->properties().set("remoting.tcp.uri", uri);
				_pContext->logger().information("Registered service with ORB: %s", uri);
			}
		}
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::PreferencesService::Ptr _pPrefs;
	std::string _listener;
};


} } } } // namespace Poco::OSP::RemotingNG::TCP


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(Poco::OSP::RemotingNG::TCP::BundleActivator)
POCO_END_MANIFEST
