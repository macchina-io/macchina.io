//
// BundleActivator.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
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
#include "Poco/NumberFormatter.h"


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;
using namespace std::string_literals;


namespace IoT {
namespace MQTT {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	typedef Poco::RemotingNG::ServerHelper<IoT::MQTT::MQTTClient> ServerHelper;

	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void createClient(const std::string& baseConfig, const std::string& id)
	{
		std::string serverURI = getStringConfig(baseConfig + ".serverURI"s, ""s);
		std::string clientId = getStringConfig(baseConfig + ".clientId"s, ""s);
		std::string persistencePath = getStringConfig(baseConfig + ".persistence.path"s, ""s);
		MQTTClientImpl::Persistence persistence = persistencePath.empty() ? MQTTClientImpl::MQTT_PERSISTENCE_NONE : MQTTClientImpl::MQTT_PERSISTENCE_FILE;

		if (!serverURI.empty())
		{
			MQTTClientImpl::ConnectOptions options;
			options.keepAliveInterval = getIntConfig(baseConfig + ".keepAliveInterval"s, 60);
			options.retryInterval = getIntConfig(baseConfig + ".retryInterval"s, 30);
			options.connectTimeout = getIntConfig(baseConfig + ".connectTimeout"s, 30);
			options.initialConnectTimeout = getIntConfig(baseConfig + ".initialConnectTimeout"s, 0);
			options.connectRetries = getIntConfig(baseConfig + ".connectRetries"s, 0);
			options.retryConnectWithExponentialBackoff = getBoolConfig(baseConfig + ".retryConnectWithExponentialBackoff"s, false);
			options.cleanSession = getBoolConfig(baseConfig + ".cleanSession"s, false);
			options.cleanStart = getBoolConfig(baseConfig + ".cleanStart"s, false);
			options.maxInflightMessages = getIntConfig(baseConfig + ".maxInflightMessages"s, 0);
			options.reliable = getBoolConfig(baseConfig + ".reliable"s, false);
			options.username = getStringConfig(baseConfig + ".username"s, "");
			options.password = getStringConfig(baseConfig + ".password"s, "");
			options.mqttVersion = getIntConfig(baseConfig + ".mqttVersion"s, 0);

			if (options.mqttVersion == 5 && options.cleanSession)
			{
				_pContext->logger().warning("Cannot enable cleanSession for MQTT version 5 client %s. Use cleanStart instead."s, id);
				options.cleanSession = false;
			}
			if (options.mqttVersion < 5 && options.cleanStart)
			{
				_pContext->logger().warning("Cannot enable cleanStart for MQTT version 3.x client %s. Use cleanSession instead."s, id);
				options.cleanStart = false;
			}

			Poco::StringTokenizer tok(getStringConfig(baseConfig + ".serverURIs"s, ""s), ";,"s, Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
			options.serverURIs.assign(tok.begin(), tok.end());

			options.willTopic = getStringConfig(baseConfig + ".will.topic"s, ""s);
			options.willMessage = getStringConfig(baseConfig + ".will.message"s, ""s);
			options.willQoS = getIntConfig(baseConfig + ".will.qos"s, 0);
			options.willRetained = getBoolConfig(baseConfig + ".will.retained"s, false);

			options.sslTrustStore = getStringConfig(baseConfig + ".ssl.trustStore"s, ""s);
			options.sslDisableDefaultTrustStore = getBoolConfig(baseConfig + ".ssl.disableDefaultTrustStore"s, false);
			options.sslCAPath = getStringConfig(baseConfig + ".ssl.caPath"s, ""s);
			options.sslKeyStore = getStringConfig(baseConfig + ".ssl.keyStore"s, ""s);
			options.sslPrivateKey = getStringConfig(baseConfig + ".ssl.privateKey"s, ""s);
			options.sslPrivateKeyPassword = getStringConfig(baseConfig + ".ssl.privateKeyPassword"s, ""s);
			options.sslEnabledCipherSuites = getStringConfig(baseConfig + ".ssl.enabledCipherSuites"s, ""s);
			options.sslEnableServerCertAuth = getBoolConfig(baseConfig + ".ssl.enableServerCertAuth", false);
			options.sslVerify = getBoolConfig(baseConfig + ".ssl.verify"s, false);
			options.sslVersion = 0;
			std::string sslVersion = getStringConfig(baseConfig + ".ssl.version"s, ""s);
			if (Poco::icompare(sslVersion, "default"s) == 0)
				options.sslVersion = 0;
			else if (Poco::icompare(sslVersion, "tls1.0"s) == 0)
				options.sslVersion = 1;
			else if (Poco::icompare(sslVersion, "tls1.1"s) == 0)
				options.sslVersion = 2;
			else if (Poco::icompare(sslVersion, "tls1.2"s) == 0)
				options.sslVersion = 3;

			MQTTClientImpl::Ptr pMQTTClient = new MQTTClientImpl(serverURI, clientId, persistence, persistencePath, options);
			std::string oid(Poco::format("io.macchina.mqtt.client#%z"s, _clients.size()));
			ServerHelper::RemoteObjectPtr pMQTTClientRemoteObject = ServerHelper::createRemoteObject(pMQTTClient, oid);
			Poco::OSP::Properties props;
			props.set("io.macchina.protocol"s, "io.macchina.mqtt"s);
			props.set("io.macchina.mqtt.clientId"s, clientId);
			props.set("io.macchina.mqtt.serverURI"s, serverURI);
			props.set("io.macchina.mqtt.id"s, id);
			props.set("io.macchina.mqtt.version"s, Poco::NumberFormatter::format(options.mqttVersion));
			Poco::OSP::ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pMQTTClientRemoteObject, props);

			_clients.push_back(pMQTTClient);
			_serviceRefs.push_back(pServiceRef);
		}
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);

		Poco::Util::AbstractConfiguration::Keys keys;
		_pPrefs->configuration()->keys("mqtt.clients"s, keys);
		for (const auto& k: keys)
		{
			std::string baseKey = "mqtt.clients.";
			baseKey += k;
			createClient(baseKey, k);
		}
	}

	void stop(BundleContext::Ptr pContext)
	{
		for (const auto& pRef: _serviceRefs)
		{
			pContext->registry().unregisterService(pRef);
		}
		_serviceRefs.clear();
		for (auto& pClient: _clients)
		{
			try
			{
				pClient->disconnect(200);
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().log(exc);
			}
		}
		_clients.clear();

		ServerHelper::shutdown();
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
	std::vector<MQTTClientImpl::Ptr> _clients;
	std::vector<Poco::OSP::ServiceRef::Ptr> _serviceRefs;
};


} } // namespace IoT::MQTT


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::MQTT::BundleActivator)
POCO_END_MANIFEST
