//
// BundleActivator.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceListener.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/Util/Timer.h"
#include "Poco/Delegate.h"
#include "Poco/Format.h"
#include "Poco/ClassLibrary.h"
#include "IoT/Devices/ISensor.h"
#include "IoT/MQTT/IMQTTClient.h"
#include "MQTTTask.h"


namespace Sensor2MQTT {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	void start(Poco::OSP::BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = Poco::OSP::ServiceFinder::find<Poco::OSP::PreferencesService>(pContext);

		const std::string mqttClientId = getStringConfig("sensor2mqtt.mqttClient");
		auto mqttClientRefs = pContext->registry().find(Poco::format("io.macchina.mqtt.id == \"%s\"", mqttClientId));
		if (!mqttClientRefs.empty())
		{
			_pMQTTClient = mqttClientRefs[0]->castedInstance<IoT::MQTT::IMQTTClient>();

			_pListener = pContext->registry().createListener(
				"io.macchina.physicalQuantity == \"temperature\"",
				Poco::delegate(this, &BundleActivator::onSensorRegistered),
				Poco::delegate(this, &BundleActivator::onSensorUnregistered));
		}
		else
		{
			_pContext->logger().warning("No MQTT client found.");
		}
	}

	void stop(Poco::OSP::BundleContext::Ptr pContext)
	{
		stopTask();
		_pListener.reset();
		_pSensor.reset();
		_pSensorRef.reset();
		_pMQTTClient.reset();
		_pContext.reset();
	}

protected:
	void startTask()
	{
		const std::string topic = getStringConfig("sensor2mqtt.mqttTopic");
		_pTask = new MQTTTask(_pSensor, _pMQTTClient, topic);
		long interval = 1000*getIntConfig("sensor2mqtt.interval");
		_timer.scheduleAtFixedRate(_pTask, 0, interval);
	}

	void stopTask()
	{
		if (_pTask)
		{
			_pTask->cancel();
			_pTask.reset();
		}
	}

	void onSensorRegistered(const Poco::OSP::ServiceRef::Ptr& pSensorRef)
	{
		if (!_pSensorRef)
		{
			_pContext->logger().information("Sensor registered: %s", pSensorRef->name());
			_pSensorRef = pSensorRef;
			_pSensor = pSensorRef->castedInstance<IoT::Devices::ISensor>();
			startTask();
		}
	}

	void onSensorUnregistered(const Poco::OSP::ServiceRef::Ptr& pSensorRef)
	{
		if (pSensorRef == _pSensorRef)
		{
			_pContext->logger().information("Sensor unregistered: %s", pSensorRef->name());
			_pSensor.reset();
			_pSensorRef.reset();
			stopTask();
		}
	}

	int getIntConfig(const std::string& key)
	{
		const int deflt = _pContext->thisBundle()->properties().getInt(key);
		return _pPrefs->configuration()->getInt(key, deflt);
	}

	std::string getStringConfig(const std::string& key)
	{
		const std::string deflt = _pContext->thisBundle()->properties().getString(key);
		return _pPrefs->configuration()->getString(key, deflt);
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::PreferencesService::Ptr _pPrefs;
	Poco::OSP::ServiceListener::Ptr _pListener;
	Poco::OSP::ServiceRef::Ptr _pSensorRef;
	IoT::Devices::ISensor::Ptr _pSensor;
	IoT::MQTT::IMQTTClient::Ptr _pMQTTClient;
	Poco::Util::Timer _timer;
	MQTTTask::Ptr _pTask;
};


} // namespace Sensor2MQTT


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(Sensor2MQTT::BundleActivator)
POCO_END_MANIFEST
