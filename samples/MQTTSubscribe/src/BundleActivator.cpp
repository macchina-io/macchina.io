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
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"
#include "IoT/MQTT/IMQTTClient.h"


namespace MQTTSubscribe {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	void start(Poco::OSP::BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = Poco::OSP::ServiceFinder::find<Poco::OSP::PreferencesService>(pContext);

		const std::string clientId = getStringConfig("mqttSubscribe.clientId");
		const int qos = getIntConfig("mqttSubscribe.qos");
		_topic = getStringConfig("mqttSubscribe.topic");
		auto mqttClientRefs = pContext->registry().find(Poco::format("io.macchina.mqtt.id == \"%s\"", clientId));
		if (!mqttClientRefs.empty())
		{
			_pMQTTClient = mqttClientRefs[0]->castedInstance<IoT::MQTT::IMQTTClient>();

			_pMQTTClient->messageArrived += Poco::delegate(this, &BundleActivator::onMessageArrived);

			_pMQTTClient->subscribe(_topic, qos);
		}
		else
		{
			_pContext->logger().warning("No MQTT client found.");
		}
	}

	void stop(Poco::OSP::BundleContext::Ptr pContext)
	{
		if (_pMQTTClient)
		{
			_pMQTTClient->unsubscribe(_topic);
			_pMQTTClient->messageArrived -= Poco::delegate(this, &BundleActivator::onMessageArrived);
		}
		_pMQTTClient.reset();
		_pContext.reset();
	}

protected:
	void onMessageArrived(const IoT::MQTT::MessageArrivedEvent& event)
	{
		_pContext->logger().information("MQTT message arrived with topic: %s, qos: %d, payload: %s",
			event.topic, event.message.qos, event.message.payload);
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
	IoT::MQTT::IMQTTClient::Ptr _pMQTTClient;
	std::string _topic;
};


} // namespace MQTTSubscribe


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(MQTTSubscribe::BundleActivator)
POCO_END_MANIFEST
