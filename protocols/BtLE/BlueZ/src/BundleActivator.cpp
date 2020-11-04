//
// BundleActivator.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
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
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "IoT/BtLE/PeripheralFactory.h"
#include "IoT/BtLE/GATTPeripheral.h"
#include "IoT/BtLE/PeripheralServerHelper.h"
#include "BlueZGATTClient.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace BtLE {
namespace BlueZ {


class PeripheralFactoryImpl: public IoT::BtLE::PeripheralFactory
{
public:
	PeripheralFactoryImpl(const std::string& helperPath):
		_helperPath(helperPath)
	{
	}

	IoT::BtLE::Peripheral::Ptr createPeripheral(const std::string& address)
	{
		IoT::BtLE::GATTClient::Ptr pGATTClient = new BlueZGATTClient(_helperPath);
		return new IoT::BtLE::GATTPeripheral(address, pGATTClient);
	}

private:
	std::string _helperPath;
};


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void createPeripheral(const std::string& name, IoT::BtLE::Peripheral::Ptr pPeripheral)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::BtLE::Peripheral> ServerHelper;

		std::string oid("io.macchina.btle.peripheral.");
		oid += pPeripheral->address();

		ServerHelper::RemoteObjectPtr pRemoteObject = ServerHelper::createRemoteObject(pPeripheral, oid);

		Properties props;
		props.set("io.macchina.btle.address", pPeripheral->address());
		props.set("io.macchina.btle.name", name);

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void createPeripherals()
	{
		IoT::BtLE::PeripheralFactory::Ptr pPeripheralFactory = ServiceFinder::find<IoT::BtLE::PeripheralFactory>(_pContext);

		Poco::Util::AbstractConfiguration::Keys keys;
		_pPrefs->configuration()->keys("btle.bluez.peripherals", keys);

		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string baseKey = "btle.bluez.peripherals.";
			baseKey += *it;

			std::string address = _pPrefs->configuration()->getString(baseKey + ".address");

			try
			{
				BtLE::Peripheral::Ptr pPeripheral = pPeripheralFactory->createPeripheral(address);
				createPeripheral(*it, pPeripheral);
			}
			catch (Poco::Exception& exc)
			{
				_pContext->logger().error(Poco::format("Cannot create peripheral object for device %s: %s", address, exc.displayText()));
			}
		}
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);

		std::string helperPath = _pPrefs->configuration()->getString("btle.bluez.helper", "");
		if (!helperPath.empty())
		{
			IoT::BtLE::PeripheralFactory::Ptr pFactory = new PeripheralFactoryImpl(helperPath);
			ServiceRef::Ptr pFactoryRef = _pContext->registry().registerService(IoT::BtLE::PeripheralFactory::SERVICE_NAME, pFactory, Properties());
			_serviceRefs.push_back(pFactoryRef);

			createPeripherals();
		}
		else
		{
			_pContext->logger().warning("No BlueZ helper executable path specified in configuration. PeripheralFactory will not be available.");
		}
	}

	void stop(BundleContext::Ptr pContext)
	{
		for (std::vector<ServiceRef::Ptr>::iterator it = _serviceRefs.begin(); it != _serviceRefs.end(); ++it)
		{
			_pContext->registry().unregisterService(*it);
		}
		_serviceRefs.clear();
		_pPrefs = 0;
		_pContext = 0;
	}

private:
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	std::vector<ServiceRef::Ptr> _serviceRefs;
};


} } } // namespace IoT::BtLE::BlueZ


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::BtLE::BlueZ::BundleActivator)
POCO_END_MANIFEST
