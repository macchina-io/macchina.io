//
// BundleActivator.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/RemotingNG/ORB.h"
#include "IoT/UDP/UDPEndpointImpl.h"
#include "IoT/UDP/UDPEndpointServerHelper.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;
using namespace std::string_literals;


namespace IoT {
namespace UDP {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	typedef Poco::RemotingNG::ServerHelper<IoT::UDP::UDPEndpoint> ServerHelper;

	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void createUDPEndpoint(const std::string& uid, const std::string& host, Poco::UInt16 port, const std::string& remoteHost, Poco::UInt16 remotePort)
	{
		UDPEndpointImpl::Ptr pUDPEndpointImpl = new UDPEndpointImpl(Poco::Net::SocketAddress(host, port));

		if (!remoteHost.empty())
		{
			pUDPEndpointImpl->connect(Poco::Net::SocketAddress(remoteHost, remotePort));
		}

		std::string symbolicName = "io.macchina.udp";
		Poco::RemotingNG::Identifiable::ObjectId oid = symbolicName;
		oid += '#';
		oid += uid;
		ServerHelper::RemoteObjectPtr pUDPEndpointRemoteObject = ServerHelper::createRemoteObject(pUDPEndpointImpl, oid);

		Properties props;
		props.set("io.macchina.protocol"s, symbolicName);
		props.set("io.macchina.udp.host"s, host);
		props.set("io.macchina.udp.port"s, Poco::NumberFormatter::format(port));

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pUDPEndpointRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);

		Poco::Util::AbstractConfiguration::Keys keys;
		_pPrefs->configuration()->keys("udp.endpoints"s, keys);
		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string baseKey = "udp.endpoints.";
			baseKey += *it;

			const std::string host = _pPrefs->configuration()->getString(baseKey + ".host"s, ""s);
			const Poco::UInt16 port = static_cast<Poco::UInt16>(_pPrefs->configuration()->getInt(baseKey + ".port"s, 0));

			const std::string remoteHost = _pPrefs->configuration()->getString(baseKey + ".remote.host"s, ""s);
			const Poco::UInt16 remotePort = static_cast<Poco::UInt16>(_pPrefs->configuration()->getInt(baseKey + ".remote.port"s, 0));

			try
			{
				pContext->logger().information("Creating UDP Endpoint %s on IP address '%s', port %hu."s, *it, host, port);

				createUDPEndpoint(*it, host, port, remoteHost, remotePort);
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().error("Cannot create UDP Endpoint %s on IP address '%s', port %hu: %s"s, *it, host, port, exc.displayText());
			}
		}
	}

	void stop(BundleContext::Ptr pContext)
	{
		for (std::vector<ServiceRef::Ptr>::iterator it = _serviceRefs.begin(); it != _serviceRefs.end(); ++it)
		{
			_pContext->registry().unregisterService(*it);
		}
		_serviceRefs.clear();
		_pPrefs.reset();
		_pContext.reset();

		ServerHelper::shutdown();
	}

private:
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	std::vector<ServiceRef::Ptr> _serviceRefs;
};


} } // namespace IoT::UDP


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::UDP::BundleActivator)
POCO_END_MANIFEST
