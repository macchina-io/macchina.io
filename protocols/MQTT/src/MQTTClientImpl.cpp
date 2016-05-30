//
// MQTTClientImpl.cpp
//
// $Id$
//
// Library: IoT/MQTT
// Package: MQTTClient
// Module:  MQTTClientImpl
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "MQTTClientImpl.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/Exception.h"
#include "Poco/Format.h"


extern "C" void MQTTClient_init();


namespace IoT {
namespace MQTT {


class PahoInitializer
{
public:
	static void initialize()
	{
		if (!_initialized)
		{
			MQTTClient_init();
			_initialized = true;
		}
	}
	
private:
	static bool _initialized;
};


bool PahoInitializer::_initialized(false);


class ReconnectTask: public Poco::Util::TimerTask
{
public:
	ReconnectTask(MQTTClientImpl& client):
		_client(client)
	{
	}
	
	void run()
	{
		_client.reconnect();
	}
	
private:
	MQTTClientImpl& _client;
};


MQTTClientImpl::MQTTClientImpl(const std::string& serverURI, const std::string& clientId, Persistence persistence, const std::string& persistencePath, const ConnectOptions& connectOptions):
	_clientId(clientId),
	_serverURI(serverURI),
	_options(connectOptions),
	_reconnectDelay(INITIAL_RECONNECT_DELAY),
	_logger(Poco::Logger::get("IoT.MQTTClient"))
{
	PahoInitializer::initialize();

	int rc;
	switch (persistence)
	{
	case MQTT_PERSISTENCE_NONE:
		rc = MQTTClient_create(&_mqttClient, serverURI.c_str(), clientId.c_str(), MQTTCLIENT_PERSISTENCE_NONE, 0);
		break;
	case MQTT_PERSISTENCE_FILE:
		_logger.debug("Persistence: " + persistencePath);
		rc = MQTTClient_create(&_mqttClient, serverURI.c_str(), clientId.c_str(), MQTTCLIENT_PERSISTENCE_DEFAULT, const_cast<char*>(persistencePath.c_str()));
		break;
	case MQTT_PERSISTENCE_DATABASE:
		throw Poco::NotImplementedException("Database-based persistence is not yet implemented");
	default:
		throw Poco::InvalidArgumentException("persistence");
	}
	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::SystemException("Cannot create MQTT client", errorMessage(rc), rc);
		
	MQTTClient_setCallbacks(_mqttClient, this, onConnectionLost, onMessageArrived, onMessageDelivered);
}


MQTTClientImpl::~MQTTClientImpl()
{
	try
	{
		disconnect(200);
	}
	catch (...)
	{
	}
	MQTTClient_destroy(&_mqttClient);
}


const std::string& MQTTClientImpl::id() const
{
	return _clientId;
}


const std::string& MQTTClientImpl::serverURI() const
{
	return _serverURI;
}


bool MQTTClientImpl::connected() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return MQTTClient_isConnected(_mqttClient);
}


std::vector<TopicQoS> MQTTClientImpl::subscribedTopics() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	std::vector<TopicQoS> result;
	for (std::map<std::string, int>::const_iterator it = _subscribedTopics.begin(); it != _subscribedTopics.end(); ++it)
	{
		result.push_back(TopicQoS(it->first, it->second));
	}
	
	return result;
}


Statistics MQTTClientImpl::statistics() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Statistics stats;
	
	for (std::map<std::string, int>::const_iterator it  = _receivedMessages.begin(); it != _receivedMessages.end(); ++it)
	{
		stats.receivedMessages.push_back(TopicCount(it->first, it->second));
	}

	for (std::map<std::string, int>::const_iterator it  = _publishedMessages.begin(); it != _publishedMessages.end(); ++it)
	{
		stats.publishedMessages.push_back(TopicCount(it->first, it->second));
	}
	
	return stats;
}


void MQTTClientImpl::connect()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!MQTTClient_isConnected(_mqttClient))
	{
		_receivedMessages.clear();
		_publishedMessages.clear();
		_logger.information(Poco::format("Connecting to MQTT server \"%s\"...", _serverURI));
		connectImpl(_options);
		_options.cleanSession = false; // Clean session only on first successful connect, not for reconnects
	}
}


void MQTTClientImpl::reconnect()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!MQTTClient_isConnected(_mqttClient))
	{
		try
		{
			_logger.information(Poco::format("Reconnecting to MQTT server \"%s\"...", _serverURI));
			connectImpl(_options);
		}
		catch (Poco::Exception& exc)
		{
			_logger.error(Poco::format("Failed to reconnect to \"%s\": %s", _serverURI, exc.displayText()));
			if (_reconnectDelay < MAXIMUM_RECONNECT_DELAY)
				_reconnectDelay *= 2;
			
			Poco::Clock clock;
			clock += 1000*_reconnectDelay;
			_timer.schedule(new ReconnectTask(*this), clock);
		}
	}
}

	
void MQTTClientImpl::connectImpl(const ConnectOptions& options)
{
	MQTTClient_willOptions willOptions = MQTTClient_willOptions_initializer;
	MQTTClient_SSLOptions sslOptions = MQTTClient_SSLOptions_initializer;
	MQTTClient_connectOptions connectOptions = MQTTClient_connectOptions_initializer;
	connectOptions.keepAliveInterval = options.keepAliveInterval;
	connectOptions.cleansession      = options.cleanSession;
	connectOptions.reliable          = options.reliable;
	connectOptions.username          = options.username.empty() ? 0 : options.username.c_str();
	connectOptions.password          = options.password.empty() ? 0 : options.password.c_str();
	connectOptions.connectTimeout    = options.connectTimeout;
	connectOptions.retryInterval     = options.retryInterval;
	connectOptions.MQTTVersion       = options.mqttVersion;
	if (options.willTopic.empty())
		connectOptions.will          = 0;
	else
		connectOptions.will          = &willOptions;
	connectOptions.ssl               = &sslOptions;

	std::vector<char*> serverURIs;
	for (std::vector<std::string>::const_iterator it = options.serverURIs.begin(); it != options.serverURIs.end(); ++it)
	{
		serverURIs.push_back(const_cast<char*>(it->c_str()));
	}
	
	connectOptions.serverURIcount = static_cast<int>(serverURIs.size());
	if (serverURIs.size())
	{
		connectOptions.serverURIs = &serverURIs[0];
	}
	else
	{
		connectOptions.serverURIs = 0;
	}
	
	willOptions.topicName = options.willTopic.c_str();
	willOptions.message   = options.willMessage.c_str();
	willOptions.retained  = options.willRetained;
	willOptions.qos       = options.willQoS;
	
	sslOptions.trustStore           = options.sslTrustStore.c_str();
	sslOptions.keyStore             = options.sslKeyStore.c_str();
	sslOptions.privateKey           = options.sslPrivateKey.c_str();
	sslOptions.privateKeyPassword   = options.sslPrivateKeyPassword.c_str();
	sslOptions.enabledCipherSuites  = options.sslEnabledCipherSuites.c_str();
	sslOptions.enableServerCertAuth = options.sslEnableServerCertAuth;
	
	int rc = MQTTClient_connect(_mqttClient, &connectOptions);
	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::IOException(Poco::format("Cannot connect to MQTT server \"%s\"", _serverURI), errorMessage(rc), rc);
		
	_logger.information(Poco::format("Connected to MQTT server \"%s\".", _serverURI));
	_reconnectDelay = INITIAL_RECONNECT_DELAY;
	
	_connectionInfo.serverURI = connectOptions.returned.serverURI;
	_connectionInfo.sessionPresent = connectOptions.returned.sessionPresent != 0;
	
	try
	{
		resubscribe();
	}
	catch (Poco::Exception& exc)
	{
		_logger.warning(Poco::format("Failed to resubscribe to previously subscribed topics: %s", exc.displayText()));
	}
}

	
void MQTTClientImpl::disconnect(int timeout)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (MQTTClient_isConnected(_mqttClient))
	{
		int rc = MQTTClient_disconnect(_mqttClient, timeout);
		if (rc != MQTTCLIENT_SUCCESS)
			throw Poco::IOException("Failed to disconnect from MQTT server", errorMessage(rc), rc);
		_logger.debug(Poco::format("Disconnected from server \"%s\".", _serverURI));
		_subscribedTopics.clear();
		
		_connectionInfo.serverURI.clear();
		_connectionInfo.sessionPresent = false;
	}
}


int MQTTClientImpl::publish(const std::string& topic, const std::string& payload, int qos)
{
	connect();

	Poco::Mutex::ScopedLock lock(_mutex);

	int token;
	int rc = MQTTClient_publish(_mqttClient, topic.c_str(), static_cast<int>(payload.size()), const_cast<char*>(payload.data()), qos, 0, &token);
	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::IOException(Poco::format("Failed to publish message on topic \"%s\"", topic), errorMessage(rc), rc);
		
	_publishedMessages[topic]++;

	return token;
}


int MQTTClientImpl::publishMessage(const std::string& topic, const Message& message)
{
	connect();

	Poco::Mutex::ScopedLock lock(_mutex);

	int token;
	int rc = MQTTClient_publish(_mqttClient, topic.c_str(), static_cast<int>(message.payload.size()), const_cast<char*>(message.payload.data()), message.qos, message.retained, &token);
	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::IOException(Poco::format("Failed to publish message on topic \"%s\"", topic), errorMessage(rc), rc);

	_publishedMessages[topic]++;

	return token;
}


void MQTTClientImpl::subscribe(const std::string& topic, int qos)
{
	connect();

	Poco::Mutex::ScopedLock lock(_mutex);

	int rc = MQTTClient_subscribe(_mqttClient, const_cast<char*>(topic.c_str()), qos);
	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::IOException(Poco::format("Failed to subscribe to topic \"%s\"", topic), errorMessage(rc), rc);

	_subscribedTopics[topic] = qos;
}


void MQTTClientImpl::unsubscribe(const std::string& topic)
{
	connect();

	Poco::Mutex::ScopedLock lock(_mutex);

	int rc = MQTTClient_unsubscribe(_mqttClient, const_cast<char*>(topic.c_str()));
	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::IOException(Poco::format("Failed to unsubscribe from topic \"%s\"", topic), errorMessage(rc), rc);
		
	_subscribedTopics.erase(topic);
}


void MQTTClientImpl::subscribeMany(const std::vector<TopicQoS>& topicsAndQoS)
{
	if (topicsAndQoS.empty()) return;

	connect();

	Poco::Mutex::ScopedLock lock(_mutex);

	std::vector<char*> ctopics;
	std::vector<int> qoss;
	for (std::vector<TopicQoS>::const_iterator it = topicsAndQoS.begin(); it != topicsAndQoS.end(); ++it)
	{
		ctopics.push_back(const_cast<char*>(it->topic.c_str()));
		qoss.push_back(it->qos);
	}
	int rc = MQTTClient_subscribeMany(_mqttClient, static_cast<int>(ctopics.size()), &ctopics[0], &qoss[0]);
	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::IOException("Failed to subscribe to multiple topics", errorMessage(rc), rc);

	for (std::vector<TopicQoS>::const_iterator it = topicsAndQoS.begin(); it != topicsAndQoS.end(); ++it)
	{
		_subscribedTopics[it->topic] = it->qos;
	}
}


void MQTTClientImpl::unsubscribeMany(const std::vector<std::string>& topics)
{
	if (topics.empty()) return;

	connect();

	Poco::Mutex::ScopedLock lock(_mutex);

	std::vector<char*> ctopics;
	for (std::vector<std::string>::const_iterator it = topics.begin(); it != topics.end(); ++it)
	{
		ctopics.push_back(const_cast<char*>(it->c_str()));
	}
	int rc = MQTTClient_unsubscribeMany(_mqttClient, static_cast<int>(ctopics.size()), &ctopics[0]);
	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::IOException("Failed to unsubscribe from multiple topics", errorMessage(rc), rc);

	for (std::vector<std::string>::const_iterator it = topics.begin(); it != topics.end(); ++it)
	{
		_subscribedTopics.erase(*it);
	}
}


void MQTTClientImpl::resubscribe()
{
	if (_subscribedTopics.empty()) return;

	std::vector<char*> ctopics;
	std::vector<int> qoss;
	for (std::map<std::string, int>::const_iterator it = _subscribedTopics.begin(); it != _subscribedTopics.end(); ++it)
	{
		ctopics.push_back(const_cast<char*>(it->first.c_str()));
		qoss.push_back(it->second);
	}
	int rc = MQTTClient_subscribeMany(_mqttClient, static_cast<int>(ctopics.size()), &ctopics[0], &qoss[0]);
	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::IOException("Failed to resubscribe to topics", errorMessage(rc), rc);
}


std::string MQTTClientImpl::errorMessage(int code)
{
	switch (code)
	{
	case MQTTCLIENT_SUCCESS:
		return "success";
	case MQTTCLIENT_FAILURE:
		return "unspecified error";
	case -2:
		return "persistence error";
	case MQTTCLIENT_DISCONNECTED:
		return "client disconnected";
	case MQTTCLIENT_MAX_MESSAGES_INFLIGHT:
		return "maximum number of in-flight messages exceeded";
	case MQTTCLIENT_BAD_UTF8_STRING:
		return "invalid UTF-8 string";
	case MQTTCLIENT_NULL_PARAMETER:
		return "NULL parameter";
	case MQTTCLIENT_TOPICNAME_TRUNCATED:
		return "topic name truncated";
	case MQTTCLIENT_BAD_STRUCTURE:
		return "bad structure";
	case MQTTCLIENT_BAD_QOS:
		return "invalid QoS value";
	case 1:
		return "connection refused - unacceptable protocol version";
	case 2:
		return "connection refused - identifier rejected";
	case 3:
		return "connection refused - server unavailable";
	case 4:
		return "connection refused - bad username or password";
	case 5:
		return "connection refused - not authorized";
	default:
		return Poco::format("unknown error code %d", code);
	}
}


void MQTTClientImpl::onConnectionLost(void* context, char* cause)
{
	MQTTClientImpl* pThis = reinterpret_cast<MQTTClientImpl*>(context);
	ConnectionLostEvent event;
	if (cause) event.cause = cause;
	try
	{
		pThis->_logger.warning("Connection to MQTT server lost.");
		pThis->connectionLost(pThis, event);
	}
	catch (Poco::Exception& exc)
	{
		pThis->_logger.error("connectionLost event delegate leaked exception: " + exc.displayText());
	}
	
	pThis->_timer.schedule(new ReconnectTask(*pThis), Poco::Clock());
}


void MQTTClientImpl::onMessageDelivered(void* context, int token)
{
	MQTTClientImpl* pThis = reinterpret_cast<MQTTClientImpl*>(context);
	MessageDeliveredEvent event;
	event.token = token;
	try
	{
		pThis->messageDelivered(pThis, event);
	}
	catch (Poco::Exception& exc)
	{
		pThis->_logger.error("messageDelivered event delegate leaked exception: " + exc.displayText());
	}
}


int MQTTClientImpl::onMessageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* message)
{
	MQTTClientImpl* pThis = reinterpret_cast<MQTTClientImpl*>(context);
	MessageArrivedEvent event;
	if (topicName)
	{
		if (topicLen == 0)
			event.topic.assign(topicName);
		else
			event.topic.assign(topicName, static_cast<std::string::size_type>(topicLen));
	}
	if (message->payload && message->payloadlen) event.message.payload.assign(static_cast<char*>(message->payload), static_cast<std::string::size_type>(message->payloadlen));
	event.message.qos = message->qos;
	event.message.retained = message->retained;
	event.dup = message->dup;
	event.handled = true;
	
	{
		Poco::Mutex::ScopedLock lock(pThis->_mutex);
		pThis->_receivedMessages[event.topic]++;
	}
	
	try
	{
		pThis->messageArrived(pThis, event);
	}
	catch (Poco::Exception& exc)
	{
		pThis->_logger.error("messageArrived event delegate leaked exception: " + exc.displayText());
		event.handled = false;
	}
	
 	MQTTClient_freeMessage(&message);
    MQTTClient_free(topicName);
	
	return event.handled;
}


ConnectionInfo MQTTClientImpl::connectionInfo() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _connectionInfo;
}


} } // namespace IoT::MQTT
