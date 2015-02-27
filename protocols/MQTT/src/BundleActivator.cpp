//
// BundleActivator.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "MQTTClientImpl.h"
#include "IoT/MQTT/MQTTClientServerHelper.h"
#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/ClassLibrary.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Environment.h"


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace MQTT {


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
		typedef Poco::RemotingNG::ServerHelper<IoT::MQTT::MQTTClient> ServerHelper;

		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);
		
		std::string serverURI = getStringConfig("mqtt.client.serverURI", "");
		std::string clientId = getStringConfig("mqtt.client.id", Poco::Environment::nodeId());
		std::string persistencePath = getStringConfig("mqtt.client.persistence.path", "");
		MQTTClientImpl::Persistence persistence = persistencePath.empty() ? MQTTClientImpl::MQTT_PERSISTENCE_NONE : MQTTClientImpl::MQTT_PERSISTENCE_FILE;

		if (!serverURI.empty())
		{
			MQTTClientImpl::ConnectOptions options;
			options.keepAliveInterval = getIntConfig("mqtt.client.keepAliveInterval", 60);
			options.retryInterval = getIntConfig("mqtt.client.retryInterval", 30);
			options.connectTimeout = getIntConfig("mqtt.client.connectTimeout", 20);
			options.cleanSession = getBoolConfig("mqtt.client.cleanSession", true);
			options.reliable = getBoolConfig("mqtt.client.reliable", false);
			options.username = getStringConfig("mqtt.client.username", "");
			options.password = getStringConfig("mqtt.client.password", "");
			options.willQoS = getIntConfig("mqtt.client.will.qos", 0);
			options.mqttVersion = getIntConfig("mqtt.client.mqttVersion", 0);
			Poco::StringTokenizer tok(getStringConfig("mqtt.client.serverURIs", ""), ";,", Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			options.serverURIs.assign(tok.begin(), tok.end());

			options.willTopic = getStringConfig("mqtt.client.will.topic", "");
			options.willMessage = getStringConfig("mqtt.client.will.message", "");
			options.willRetained = getBoolConfig("mqtt.client.will.retained", false);
		
			options.sslTrustStore = getStringConfig("mqtt.client.ssl.trustStore", "");
			options.sslKeyStore = getStringConfig("mqtt.client.ssl.keystore", "");
			options.sslPrivateKey = getStringConfig("mqtt.client.ssl.privateKey", "");
			options.sslPrivateKeyPassword = getStringConfig("mqtt.client.ssl.privateKeyPassword", "");
			options.sslEnabledCipherSuites = getStringConfig("mqtt.client.ssl.enabledCipherSuites", "");
			options.sslEnableServerCertAuth = getBoolConfig("mqtt.client.ssl.enableServerCertAuth", "");
		
			_pMQTTClient = new MQTTClientImpl(serverURI, clientId, persistence, persistencePath, options);
			std::string oid("io.macchina.mqtt.client");
			typename ServerHelper::RemoteObjectPtr pMQTTClientRemoteObject = ServerHelper::createRemoteObject(_pMQTTClient, oid);		
			_pServiceRef = pContext->registry().registerService(oid, pMQTTClientRemoteObject, Properties());
		}
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		if (_pMQTTClient)
		{
			try
			{
				_pMQTTClient->disconnect(200);
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().log(exc);
			}
			_pMQTTClient = 0;
		}
		if (_pServiceRef)
		{
			pContext->registry().unregisterService(_pServiceRef);
			_pServiceRef = 0;
		}
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
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	MQTTClientImpl::Ptr _pMQTTClient;
	Poco::OSP::ServiceRef::Ptr _pServiceRef;
};


} } // namespace IoT::MQTT


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::MQTT::BundleActivator)
POCO_END_MANIFEST
