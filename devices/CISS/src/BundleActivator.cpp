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
#include "IoT/Devices/SensorServerHelper.h"
#include "IoT/Devices/AccelerometerServerHelper.h"
#include "IoT/Devices/GyroscopeServerHelper.h"
#include "IoT/Devices/MagnetometerServerHelper.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "Poco/SharedPtr.h"
#include "Poco/String.h"
#include "Poco/StringTokenizer.h"
#include "Sensor.h"
#include "Accelerometer.h"
#include "Gyroscope.h"
#include "Magnetometer.h"
#include "Node.h"
#include "NPIPort.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace CISS {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void registerSensor(Poco::SharedPtr<Node> pNode, Poco::SharedPtr<Sensor> pSensor)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Sensor> ServerHelper;

		std::string symbolicName = pSensor->getPropertyString("symbolicName");
		std::string type = pSensor->getPropertyString("type");
		std::string physicalQuantity = pSensor->getPropertyString("physicalQuantity");

		std::string oid(Sensor::SYMBOLIC_NAME);
		oid += ".";
		oid += physicalQuantity;
		oid += '#';
		oid += pNode->id();

		ServerHelper::RemoteObjectPtr pSensorRemoteObject = ServerHelper::createRemoteObject(pSensor, oid);

		Properties props;
		props.set("io.macchina.device", symbolicName);
		props.set("io.macchina.deviceType", type);
		props.set("io.macchina.physicalQuantity", physicalQuantity);

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pSensorRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void registerAccelerometer(Poco::SharedPtr<Node> pNode)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Accelerometer> ServerHelper;

		Poco::SharedPtr<Accelerometer> pAccelerometer = pNode->accelerometer();

		std::string oid(Accelerometer::SYMBOLIC_NAME);
		oid += '#';
		oid += pNode->id();

		ServerHelper::RemoteObjectPtr pAccelerometerRemoteObject = ServerHelper::createRemoteObject(pAccelerometer, oid);

		Properties props;
		props.set("io.macchina.device", Accelerometer::SYMBOLIC_NAME);
		props.set("io.macchina.deviceType", Accelerometer::TYPE);

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pAccelerometerRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void registerMagnetometer(Poco::SharedPtr<Node> pNode)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Magnetometer> ServerHelper;

		Poco::SharedPtr<Magnetometer> pMagnetometer = pNode->magnetometer();

		std::string oid(Magnetometer::SYMBOLIC_NAME);
		oid += '#';
		oid += pNode->id();

		ServerHelper::RemoteObjectPtr pMagnetometerRemoteObject = ServerHelper::createRemoteObject(pMagnetometer, oid);

		Properties props;
		props.set("io.macchina.device", Magnetometer::SYMBOLIC_NAME);
		props.set("io.macchina.deviceType", Magnetometer::TYPE);

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pMagnetometerRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void registerGyroscope(Poco::SharedPtr<Node> pNode)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Gyroscope> ServerHelper;

		Poco::SharedPtr<Gyroscope> pGyroscope = pNode->gyroscope();

		std::string oid(Gyroscope::SYMBOLIC_NAME);
		oid += '#';
		oid += pNode->id();

		ServerHelper::RemoteObjectPtr pGyroscopeRemoteObject = ServerHelper::createRemoteObject(pGyroscope, oid);

		Properties props;
		props.set("io.macchina.device", Gyroscope::SYMBOLIC_NAME);
		props.set("io.macchina.deviceType", Gyroscope::TYPE);

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pGyroscopeRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);

		Poco::Util::AbstractConfiguration::Keys keys;
		_pPrefs->configuration()->keys("ciss.ports", keys);
		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string baseKey = "ciss.ports.";
			baseKey += *it;

			std::string id = _pPrefs->configuration()->getString(baseKey + ".id", *it);
			std::string device = _pPrefs->configuration()->getString(baseKey + ".device", "");
			std::string params = _pPrefs->configuration()->getString(baseKey + ".params", "8N1");
			int speed = _pPrefs->configuration()->getInt(baseKey + ".speed", 115200);

			try
			{
				pContext->logger().information(Poco::format("Creating serial port for CISS node '%s'.", device));

				Poco::SharedPtr<Poco::Serial::SerialPort> pSerialPort = new Poco::Serial::SerialPort(device, speed, params);
				Poco::SharedPtr<NPIPort> pNPIPort = new NPIPort(pSerialPort);
				_pNode = new Node(id, pNPIPort);

				registerAccelerometer(_pNode);
				registerMagnetometer(_pNode);
				registerGyroscope(_pNode);
				registerSensor(_pNode, _pNode->temperature());
				registerSensor(_pNode, _pNode->humidity());
				registerSensor(_pNode, _pNode->pressure());
				registerSensor(_pNode, _pNode->light());

				_pNode->setSamplingInterval(Node::CISS_SENSOR_ACCELEROMETER,
					_pPrefs->configuration()->getInt(baseKey + ".inertial.samplingInterval.usec",
						1000*_pPrefs->configuration()->getInt(baseKey + ".inertial.samplingInterval", 100)));

				_pNode->setEnvironmentalSamplingInterval(Node::CISS_SENSOR_ENVIRONMENTAL,
					_pPrefs->configuration()->getInt(baseKey + ".environmental.samplingInterval", 1000));

				_pNode->temperature()->enable(_pPrefs->configuration()->getBool(baseKey + ".temperature.enable", true));
				_pNode->humidity()->enable(_pPrefs->configuration()->getBool(baseKey + ".humidity.enable", true));
				_pNode->pressure()->enable(_pPrefs->configuration()->getBool(baseKey + ".pressure.enable", true));
				_pNode->light()->enable(_pPrefs->configuration()->getBool(baseKey + ".light.enable", true));

				_pNode->gyroscope()->enable(_pPrefs->configuration()->getBool(baseKey + ".gyroscope.enable", true));
				_pNode->magnetometer()->enable(_pPrefs->configuration()->getBool(baseKey + ".magnetometer.enable", true));
				_pNode->accelerometer()->enable(_pPrefs->configuration()->getBool(baseKey + ".accelerometer.enable", true));
				_pNode->setAccelerometerRange(static_cast<Poco::UInt8>(_pPrefs->configuration()->getInt(baseKey + ".accelerometer.range", 16)));
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().error(Poco::format("Cannot create serial port for CISS device '%s': %s", device, exc.displayText()));
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
		_pNode = 0;
		_pPrefs = 0;
		_pContext = 0;
	}

private:
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	std::vector<ServiceRef::Ptr> _serviceRefs;
	Poco::SharedPtr<Node> _pNode;
};


} } // namespace IoT::CISS


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::CISS::BundleActivator)
POCO_END_MANIFEST
