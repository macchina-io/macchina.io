//
// BundleActivator.cpp
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "IoT/ROS/BridgeClient.h"
#include "Poco/ClassLibrary.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace ROS {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);

		std::string uri = _pPrefs->configuration()->getString("ros.bridge.uri", "");
		if (!uri.empty())
		{
			_pBridgeClient = new BridgeClient(Poco::URI(uri));
			_pBridgeClientRef = _pContext->registry().registerService(BridgeClient::SERVICE_NAME, _pBridgeClient, Properties());

			_pBridgeClient->connect();
			_pBridgeClient->start();

			_pContext->logger().information("Connected to ROS bridge at %s.", uri);
		}
	}

	void stop(BundleContext::Ptr pContext)
	{
		if (_pBridgeClient)
		{
			pContext->registry().unregisterService(_pBridgeClientRef);
			_pBridgeClientRef.reset();

			_pBridgeClient->unsubscribeAll();
			_pBridgeClient->stop();
			_pBridgeClient->disconnect();
			_pBridgeClient.reset();
		}

		_pPrefs.reset();
		_pContext.reset();
	}

private:
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	BridgeClient::Ptr _pBridgeClient;
	ServiceRef::Ptr _pBridgeClientRef;
};


} } // namespace IoT::ROS


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::ROS::BundleActivator)
POCO_END_MANIFEST
