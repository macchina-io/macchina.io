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
#include "Poco/Util/Timer.h"
#include "IoT/Devices/SensorServerHelper.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "Poco/SharedPtr.h"
#include "Poco/String.h"
#include "Poco/StringTokenizer.h"
#include "XBeeSensor.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace XBee {
namespace Sensor {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void createSensor(IXBeeNode::Ptr pXBeeNode, const XBeeSensor::Params& params)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Sensor> ServerHelper;

		Poco::SharedPtr<XBeeSensor> pSensor;
		if (params.physicalQuantity == "temperature")
			pSensor = new XBeeTemperatureSensor(pXBeeNode, params);
		else if (params.physicalQuantity == "humidity")
			pSensor = new XBeeHumiditySensor(pXBeeNode, params);
		else if (params.physicalQuantity == "illuminance")
			pSensor = new XBeeLightSensor(pXBeeNode, params);
		else
			throw Poco::InvalidArgumentException("Unknown sensor type", params.physicalQuantity);

		std::string oid(XBeeSensor::SYMBOLIC_NAME);
		oid += ".";
		oid += params.physicalQuantity;
		oid += '#';
		oid += params.id;

		ServerHelper::RemoteObjectPtr pSensorRemoteObject = ServerHelper::createRemoteObject(pSensor, oid);

		Properties props;
		props.set("io.macchina.device", XBeeSensor::SYMBOLIC_NAME);
		props.set("io.macchina.deviceType", XBeeSensor::TYPE);
		props.set("io.macchina.physicalQuantity", params.physicalQuantity);

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pSensorRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);

		Poco::Util::AbstractConfiguration::Keys keys;
		_pPrefs->configuration()->keys("xbee.sensors", keys);
		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string baseKey = "xbee.sensors.";
			baseKey += *it;

			std::string xBeeNode = _pPrefs->configuration()->getString(baseKey + ".node", "io.macchina.xbee#1");
			XBeeSensor::Params params;
			params.id = Poco::toUpper(_pPrefs->configuration()->getString(baseKey + ".id"));
			std::string type = _pPrefs->configuration()->getString(baseKey + ".type", "LTH");
			int lastChannel = 3;
			if (type == "LTH")
				lastChannel = 3;
			else if (type == "LT")
				lastChannel = 2;
			else
				pContext->logger().warning(Poco::format("Invalid sensor type \"%s\"; valid types are \"LT\" and \"LTH\".", type));

			for (int channel = 1; channel <= lastChannel; channel++)
			{
				params.analogChannel = channel;
				switch (params.analogChannel)
				{
				case 1:
					params.physicalQuantity = "illuminance";
					params.physicalUnit = "";
					break;
				case 2:
					params.physicalQuantity = "temperature";
					params.physicalUnit = IoT::Devices::Sensor::PHYSICAL_UNIT_DEGREES_CELSIUS;
					break;
				case 3:
					params.physicalQuantity = "humidity";
					params.physicalUnit = "%";
					break;
				}

				try
				{
					IXBeeNode::Ptr pXBeeNode = ServiceFinder::findByName<IXBeeNode>(pContext, xBeeNode);
					createSensor(pXBeeNode, params);
				}
				catch (Poco::Exception& exc)
				{
					pContext->logger().error(Poco::format("Cannot create XBee Sensor: %s", exc.displayText()));
				}
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
	}

private:
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	IXBeeNode::Ptr _pXBeeNode;
	std::vector<ServiceRef::Ptr> _serviceRefs;
};


} } } // namespace IoT::XBee::Sensor


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::XBee::Sensor::BundleActivator)
POCO_END_MANIFEST
