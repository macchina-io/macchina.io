//
// BundleActivator.cpp
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
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
#include "IoT/Tf/MasterConnection.h"
#include "IoT/Devices/SensorServerHelper.h"
#include "IoT/Devices/TriggerServerHelper.h"
#include "IoT/Devices/RotaryEncoderServerHelper.h"
#include "IoT/Devices/GNSSSensorServerHelper.h"
#include "IoT/Devices/SwitchServerHelper.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "AmbientLightSensor.h"
#include "AirPressureSensor.h"
#include "MotionDetector.h"
#include "RotaryEncoder.h"
#include "TemperatureSensor.h"
#include "HumiditySensor.h"
#include "GNSSSensor.h"
#include "DCMotor.h"
#include <map>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace Tf {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}
	
	~BundleActivator()
	{
	}
	
	void onDeviceStateChanged(const MasterConnection::DeviceEvent& ev)
	{
		_pContext->logger().information("Device State Changed: " + ev.uid);

		switch (ev.state)
		{
		case MasterConnection::DEVICE_AVAILABLE:
		case MasterConnection::DEVICE_CONNECTED:
			if (_devices.find(ev.uid) == _devices.end())
			{
				switch (ev.type)
				{
				case AmbientLightSensor::DEVICE_IDENTIFIER:
					createDevice<AmbientLightSensor>(ev.uid);
					break;
				case MotionDetector::DEVICE_IDENTIFIER:
					createDevice<MotionDetector>(ev.uid);
					break;
				case RotaryEncoder::DEVICE_IDENTIFIER:
					createDevice<RotaryEncoder>(ev.uid);
					break;
				case TemperatureSensor::DEVICE_IDENTIFIER:
					createDevice<TemperatureSensor>(ev.uid);
					break;
				case HumiditySensor::DEVICE_IDENTIFIER:
					createDevice<HumiditySensor>(ev.uid);
					break;
				case AirPressureSensor::DEVICE_IDENTIFIER:
					createDevice<AirPressureSensor>(ev.uid);
					break;
				case GNSSSensor::DEVICE_IDENTIFIER:
					createDevice<GNSSSensor>(ev.uid);
					break;
				case DCMotor::DEVICE_IDENTIFIER:
					createDevice<DCMotor>(ev.uid);
					break;
				default:
					_pContext->logger().information(Poco::format("Detected unsupported Tinkerforge device: %hu", ev.type));
					break;
				}
			}
			break;

		case MasterConnection::DEVICE_DISCONNECTED:
			removeDevice(ev.uid);
			break;
		}
	}
	
	template <class D>
	void createDevice(const std::string& uid)
	{
		typedef Poco::RemotingNG::ServerHelper<typename D::SuperType> ServerHelper;
		
		Poco::SharedPtr<D> pDevice = new D(_pMasterConnection, uid);
		std::string symbolicName = pDevice->getPropertyString("symbolicName");
		std::string type = pDevice->getPropertyString("type");
		std::string physicalQuantity = pDevice->getPropertyString("physicalQuantity");
		Poco::RemotingNG::Identifiable::ObjectId oid = symbolicName;
		oid += '#';
		oid += uid;
		typename ServerHelper::RemoteObjectPtr pDeviceRemoteObject = ServerHelper::createRemoteObject(pDevice, oid);
		
		Properties props;
		props.set("io.macchina.device", symbolicName);
		props.set("io.macchina.deviceType", type);
		props.set("io.macchina.tf.uid", uid);
		if (!physicalQuantity.empty())
		{
			props.set("io.macchina.physicalQuantity", physicalQuantity);
		}
		
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pDeviceRemoteObject, props);
		_devices[uid] = pServiceRef;
	}
	
	void removeDevice(const std::string& uid)
	{
		DeviceMap::iterator it = _devices.find(uid);
		if (it != _devices.end())
		{
			_pContext->registry().unregisterService(it->second);
			_devices.erase(it);
		}
	}
	
	void removeDevices()
	{
		for (DeviceMap::iterator it = _devices.begin(); it != _devices.end(); ++it)
		{
			_pContext->registry().unregisterService(it->second);
		}
		_devices.clear();
	}
	
	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);
		_pMasterConnection = MasterConnection::create();
		
		std::string tfMasterHost = getStringConfig("tf.master.host", "localhost");
		Poco::UInt16 tfMasterPort = static_cast<Poco::UInt16>(getIntConfig("tf.master.port", 4223));
		
		pContext->logger().information(Poco::format("Connecting to Tinkerforge Master at %s:%hu...", tfMasterHost, tfMasterPort));
		
		_pMasterConnection->deviceStateChanged += Poco::delegate(this, &BundleActivator::onDeviceStateChanged);
		_pMasterConnection->connect(tfMasterHost, tfMasterPort);

		pContext->logger().information("Connected to Tinkerforge Master");
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		removeDevices();
		_pMasterConnection->disconnect();
		_pMasterConnection = 0;
		_pPrefs = 0;
		_pContext = 0;
	}

protected:
	bool getBoolConfig(const std::string& key)
	{
		return _pPrefs->configuration()->getBool(key, _pContext->thisBundle()->properties().getBool(key));
	}

	bool getBoolConfig(const std::string& key, bool deflt)
	{
		return _pPrefs->configuration()->getBool(key, _pContext->thisBundle()->properties().getBool(key, deflt));
	}

	int getIntConfig(const std::string& key)
	{
		return _pPrefs->configuration()->getInt(key, _pContext->thisBundle()->properties().getInt(key));
	}

	int getIntConfig(const std::string& key, int deflt)
	{
		return _pPrefs->configuration()->getInt(key, _pContext->thisBundle()->properties().getInt(key, deflt));
	}
	
	std::string getStringConfig(const std::string& key)
	{
		return _pPrefs->configuration()->getString(key, _pContext->thisBundle()->properties().getString(key));
	}
	
	std::string getStringConfig(const std::string& key, const std::string& deflt)
	{
		return _pPrefs->configuration()->getString(key, _pContext->thisBundle()->properties().getString(key, deflt));
	}
	
private:
	typedef std::map<std::string, ServiceRef::Ptr> DeviceMap;

	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	MasterConnection::Ptr _pMasterConnection;
	DeviceMap _devices;
};


} } // namespace IoT::Tf


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Tf::BundleActivator)
POCO_END_MANIFEST
