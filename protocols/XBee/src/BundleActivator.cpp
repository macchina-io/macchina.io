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
#include "Poco/RemotingNG/ORB.h"
#include "IoT/XBee/XBeeNodeImpl.h"
#include "IoT/XBee/XBeeNodeServerHelper.h"
#include "Poco/Serial/SerialPort.h"
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


namespace IoT {
namespace XBee {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	typedef Poco::RemotingNG::ServerHelper<IoT::XBee::XBeeNode> ServerHelper;

	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void createXBeeNode(const std::string& uid, Poco::SharedPtr<Poco::Serial::SerialPort> pSerialPort, int options)
	{
		Poco::SharedPtr<XBeeNode> pXBeeNode = new XBeeNodeImpl(new XBeePort(pSerialPort));
		std::string symbolicName = "io.macchina.xbee";
		Poco::RemotingNG::Identifiable::ObjectId oid = symbolicName;
		oid += '#';
		oid += uid;
		ServerHelper::RemoteObjectPtr pXBeeNodeRemoteObject = ServerHelper::createRemoteObject(pXBeeNode, oid);

		Properties props;
		props.set("io.macchina.protocol", symbolicName);
		props.set("io.macchina.xbee.device", pSerialPort->device());

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pXBeeNodeRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);

		Poco::Util::AbstractConfiguration::Keys keys;
		_pPrefs->configuration()->keys("xbee.ports", keys);
		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string baseKey = "xbee.ports.";
			baseKey += *it;

			std::string device = _pPrefs->configuration()->getString(baseKey + ".device", "");
			std::string params = _pPrefs->configuration()->getString(baseKey + ".params", "8N1");
			int speed = _pPrefs->configuration()->getInt(baseKey + ".speed", 38400);
			int options = 0;
			if (_pPrefs->configuration()->getBool(baseKey + ".escape", false))
			{
				options |= XBeeNodeImpl::XBEE_OPTION_ESCAPE_FRAMES;
			}

			try
			{
				pContext->logger().information(Poco::format("Creating serial port for XBee device '%s'.", device));

				Poco::SharedPtr<Poco::Serial::SerialPort> pSerialPort = new Poco::Serial::SerialPort(device, speed, params);
				createXBeeNode(*it, pSerialPort, options);
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().error(Poco::format("Cannot create serial port for XBee device '%s': %s", device, exc.displayText()));
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
		_pPrefs = 0;
		_pContext = 0;

		ServerHelper::shutdown();
	}

private:
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	std::vector<ServiceRef::Ptr> _serviceRefs;
};


} } // namespace IoT::XBee


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::XBee::BundleActivator)
POCO_END_MANIFEST
