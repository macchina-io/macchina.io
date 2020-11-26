//
// MQTTClientImpl.cpp
//
// Library: IoT/MQTT
// Package: MQTTClient
// Module:  MQTTClientImpl
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "MQTTClientImpl.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/Exception.h"
#include "Poco/Format.h"


extern "C" void MQTTClient_init(void);


namespace IoT {
namespace MQTT {


class PahoInitializer
{
public:
	static void initialize()
	{
		if (!_initialized)
		{
			MQTTClient_init_options options = MQTTClient_init_options_initializer;
			MQTTClient_global_init(&options);

#ifndef _WIN32
			MQTTClient_init();
#endif
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


namespace
{
	MQTTLenString convertString(const std::string& str)
	{
		MQTTLenString result;
		result.data = reinterpret_cast<char*>(std::malloc(str.length()));
		if (result.data)
		{
			std::memcpy(result.data, str.data(), str.length());
			result.len = str.length();
		}
		return result;
	}


	MQTTProperty convertProperty(const Property& property)
	{
		MQTTProperty mqttProp;
		mqttProp.identifier = static_cast<MQTTPropertyCodes>(property.identifier);

		int type = MQTTProperty_getType(mqttProp.identifier);
		if (type < 0) throw Poco::InvalidArgumentException("invalid property identifier", property.identifier);

		switch (type)
		{
		case MQTTPROPERTY_TYPE_BYTE:
			mqttProp.value.byte = property.byteValue.value();
			break;

		case MQTTPROPERTY_TYPE_TWO_BYTE_INTEGER:
			mqttProp.value.integer2 = property.uint16Value.value();
			break;

		case MQTTPROPERTY_TYPE_FOUR_BYTE_INTEGER:
		case MQTTPROPERTY_TYPE_VARIABLE_BYTE_INTEGER:
			mqttProp.value.integer4 = property.uint32Value.value();
			break;

		case MQTTPROPERTY_TYPE_BINARY_DATA:
		case MQTTPROPERTY_TYPE_UTF_8_ENCODED_STRING:
			mqttProp.value.data = convertString(property.stringValue.value());
			break;

		case MQTTPROPERTY_TYPE_UTF_8_STRING_PAIR:
			mqttProp.value.data = convertString(property.name.value());
			mqttProp.value.value = convertString(property.stringValue.value());
			break;
		}

		return mqttProp;
	}


	Property convertProperty(const MQTTProperty& mqttProp)
	{
		Property property;
		property.identifier = static_cast<PropertyID>(mqttProp.identifier);

		int type = MQTTProperty_getType(mqttProp.identifier);
		if (type < 0) throw Poco::InvalidArgumentException("invalid property identifier", mqttProp.identifier);

		switch (type)
		{
		case MQTTPROPERTY_TYPE_BYTE:
			property.byteValue = mqttProp.value.byte;
			break;

		case MQTTPROPERTY_TYPE_TWO_BYTE_INTEGER:
			property.uint16Value = mqttProp.value.integer2;
			break;

		case MQTTPROPERTY_TYPE_FOUR_BYTE_INTEGER:
		case MQTTPROPERTY_TYPE_VARIABLE_BYTE_INTEGER:
			property.uint32Value = mqttProp.value.integer4;
			break;

		case MQTTPROPERTY_TYPE_BINARY_DATA:
		case MQTTPROPERTY_TYPE_UTF_8_ENCODED_STRING:
			property.stringValue = std::string(mqttProp.value.data.data, mqttProp.value.data.len);
			break;

		case MQTTPROPERTY_TYPE_UTF_8_STRING_PAIR:
			property.stringValue = std::string(mqttProp.value.value.data, mqttProp.value.value.len);
			property.name = std::string(mqttProp.value.data.data, mqttProp.value.data.len);
			break;
		}

		return property;
	}


	MQTTProperties convertProperties(const std::vector<Property>& properties)
	{
		MQTTProperties mqttProps = MQTTProperties_initializer;
		for (const auto& prop: properties)
		{
			MQTTProperty mqttProp = convertProperty(prop);
			int err = MQTTProperties_add(&mqttProps, &mqttProp);
			if (err)
			{
				MQTTProperties_free(&mqttProps);
				throw Poco::SystemException("Failed to convert property", err);
			}
		}
		return mqttProps;
	}


	std::vector<Property> convertProperties(const MQTTProperties& mqttProps)
	{
		std::vector<Property> result;
		for (int i = 0; i < mqttProps.count; i++)
		{
			result.push_back(convertProperty(mqttProps.array[i]));
		}
		return result;
	}
}


MQTTClientImpl::MQTTClientImpl(const std::string& serverURI, const std::string& clientId, Persistence persistence, const std::string& persistencePath, const ConnectOptions& connectOptions):
	_clientId(clientId),
	_serverURI(serverURI),
	_options(connectOptions),
	_reconnectDelay(INITIAL_RECONNECT_DELAY),
	_pendingReconnect(false),
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
	Poco::Mutex::ScopedLock lock(_statsMutex);

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


ConnectionInfo MQTTClientImpl::connect()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!MQTTClient_isConnected(_mqttClient))
	{
		{
			Poco::Mutex::ScopedLock lock(_statsMutex);
			_receivedMessages.clear();
			_publishedMessages.clear();
		}
		_logger.information(Poco::format("Connecting MQTT client \"%s\" to server \"%s\"...", _clientId, _serverURI));
		connectImpl(_options);
	}

	return _connectionInfo;
}


ConnectionInfo MQTTClientImpl::connect5(const std::vector<Property>& connectProperties, const std::vector<Property>& willProperties)
{
	// TODO
	throw Poco::NotImplementedException();
}


void MQTTClientImpl::connectAsync()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!MQTTClient_isConnected(_mqttClient))
	{
		_timer.schedule(new ReconnectTask(*this), Poco::Clock());
	}
}


void MQTTClientImpl::connectAsync5(const std::vector<Property>& connectProperties, const std::vector<Property>& willProperties)
{
	// TODO
	throw Poco::NotImplementedException();
}


void MQTTClientImpl::connectOnce()
{
	if (!MQTTClient_isConnected(_mqttClient))
	{
		if (_pendingReconnect)
			_logger.information(Poco::format("Reconnecting MQTT client \"%s\" to server \"%s\"...", _clientId, _serverURI));
		else
			_logger.information(Poco::format("Connecting MQTT client \"%s\" to server \"%s\"...", _clientId, _serverURI));
		connectImpl(_options);
	}
}


void MQTTClientImpl::reconnect()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!MQTTClient_isConnected(_mqttClient))
	{
		_pendingReconnect = true;
		try
		{
			_logger.information(Poco::format("Connecting MQTT client \"%s\" to server \"%s\"...", _clientId, _serverURI));
			connectImpl(_options);
		}
		catch (Poco::Exception& exc)
		{
			_logger.error(Poco::format("Failed to connect MQTT client \"%s\" to \"%s\": %s", _clientId, _serverURI, exc.displayText()));
			if (_reconnectDelay < MAXIMUM_RECONNECT_DELAY)
				_reconnectDelay = 3*_reconnectDelay/2;

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
	connectOptions.password          = 0; // see binarypwd
	connectOptions.binarypwd.len     = options.password.size();
	connectOptions.binarypwd.data    = options.password.empty() ? 0 : options.password.data();
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

	willOptions.topicName    = options.willTopic.c_str();
	willOptions.message      = 0; // see payload
	willOptions.payload.len  = options.willMessage.size();
	willOptions.payload.data = options.willMessage.data();
	willOptions.retained     = options.willRetained;
	willOptions.qos          = options.willQoS;

	sslOptions.trustStore           = options.sslTrustStore.empty() ? 0 : options.sslTrustStore.c_str();
	sslOptions.keyStore             = options.sslKeyStore.empty() ? 0 : options.sslKeyStore.c_str();
	sslOptions.privateKey           = options.sslPrivateKey.empty() ? 0 : options.sslPrivateKey.c_str();
	sslOptions.privateKeyPassword   = options.sslPrivateKeyPassword.empty() ? 0 : options.sslPrivateKeyPassword.c_str();
	sslOptions.enabledCipherSuites  = options.sslEnabledCipherSuites.empty() ? 0 : options.sslEnabledCipherSuites.c_str();
	sslOptions.enableServerCertAuth = options.sslEnableServerCertAuth;
	sslOptions.sslVersion           = options.sslVersion;

	Poco::Timestamp::TimeVal time = 0;
	Poco::Timestamp::TimeVal timeout = options.connectTimeout*Poco::Timestamp::resolution();

	int remainingAttempts = options.connectRetries > 0 ? options.connectRetries + 1 : 1;
	if (options.initialConnectTimeout > 0 && options.connectRetries > 0)
	{
		connectOptions.connectTimeout = options.initialConnectTimeout;
	}

	int rc = 0;
	int attempt = 0;
	while (remainingAttempts > 0)
	{
		if (_logger.debug())
		{
			std::string cleanMsg(options.cleanSession ? " with clean session" : "");
			_logger.debug("Connecting MQTT client \"%s\" to server \"%s\"%s (timeout %d seconds).", _clientId, _serverURI, cleanMsg, connectOptions.connectTimeout);
		}

		attempt++;
		remainingAttempts--;
		Poco::Timestamp ts;
		rc = MQTTClient_connect(_mqttClient, &connectOptions);
		time += ts.elapsed();
		if (rc == MQTTCLIENT_SUCCESS)
		{
			remainingAttempts = 0;
		}
		else
		{
			Poco::Timestamp::TimeVal remainingTime = timeout - time;
			int remainingSeconds = (remainingTime + Poco::Timestamp::resolution()/2)/Poco::Timestamp::resolution();
			if (remainingSeconds > 0 && options.initialConnectTimeout > 0 && options.connectRetries > 0)
			{
				if (remainingAttempts == 1)
				{
					connectOptions.connectTimeout = remainingSeconds;
				}
				else if (options.retryConnectWithExponentialBackoff && connectOptions.connectTimeout < remainingSeconds)
				{
					connectOptions.connectTimeout *= 2;
				}
				if (connectOptions.connectTimeout > remainingSeconds)
				{
					connectOptions.connectTimeout = remainingSeconds;
				}
			}
			else
			{
				remainingAttempts = 0;
			}
			if (remainingAttempts > 0)
			{
				_logger.notice("Failed to connect at attempt %d: %s (%d) - will retry.", attempt, errorMessage(rc), rc);
			}
		}
	}

	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::IOException(Poco::format("Cannot connect to MQTT server \"%s\"", _serverURI), errorMessage(rc), rc);

	_logger.information(Poco::format("Connected to MQTT server \"%s\".", _serverURI));
	_reconnectDelay = INITIAL_RECONNECT_DELAY;
	_pendingReconnect = false;

	if (connectOptions.returned.serverURI)
	{
		_connectionInfo.serverURI = connectOptions.returned.serverURI;
	}
	_connectionInfo.sessionPresent = connectOptions.returned.sessionPresent != 0;

	if (_connectionInfo.sessionPresent)
	{
		_logger.debug("Session is present.");
	}
	else
	{
		_logger.debug("Session is not present.");
	}

	try
	{
		if (!_connectionInfo.sessionPresent)
		{
			resubscribe();
		}
	}
	catch (Poco::Exception& exc)
	{
		_logger.warning(Poco::format("Failed to resubscribe client \"%s\" to previously subscribed topics: %s", _clientId, exc.displayText()));
	}

	Poco::ScopedUnlock<Poco::Mutex> unlock(_mutex);
	ConnectionEstablishedEvent event;
	event.connectionInfo = _connectionInfo;
	connectionEstablished(this, event);
}


void MQTTClientImpl::disconnect(int timeout)
{
	Poco::ScopedLockWithUnlock<Poco::Mutex> lock(_mutex);

	if (MQTTClient_isConnected(_mqttClient))
	{
		int rc = MQTTClient_disconnect(_mqttClient, timeout);
		if (rc != MQTTCLIENT_SUCCESS)
			throw Poco::IOException("Failed to disconnect from MQTT server", errorMessage(rc), rc);
		_logger.debug(Poco::format("Disconnected MQTT client \"%s\" from server \"%s\".", _clientId, _serverURI));
		_subscribedTopics.clear();

		_connectionInfo.serverURI.clear();
		_connectionInfo.sessionPresent = false;

		lock.unlock();
		connectionClosed(this);
	}
}


void MQTTClientImpl::disconnect5(int timeout, ReasonCode reason, const std::vector<Property>& properties)
{
	// TODO
	throw Poco::NotImplementedException();
}


int MQTTClientImpl::publish(const std::string& topic, const std::string& payload, int qos)
{
	int token = 0;
	{
		Poco::Mutex::ScopedLock lock(_mutex);

		connectOnce();

		int rc = MQTTClient_publish(_mqttClient, topic.c_str(), static_cast<int>(payload.size()), const_cast<char*>(payload.data()), qos, 0, &token);
		if (rc != MQTTCLIENT_SUCCESS)
			throw Poco::IOException(Poco::format("Failed to publish message on topic \"%s\"", topic), errorMessage(rc), rc);
	}

	{
		Poco::Mutex::ScopedLock lock(_statsMutex);
		_publishedMessages[topic]++;
	}

	return token;
}


int MQTTClientImpl::publish5(const std::string& topic, const std::string& payload, int qos, bool retained, const std::vector<Property>& properties)
{
	// TODO
	throw Poco::NotImplementedException();
}


int MQTTClientImpl::publishMessage(const std::string& topic, const Message& message)
{
	int token = 0;
	{
		Poco::Mutex::ScopedLock lock(_mutex);

		connectOnce();

		int rc;
		if (message.payload.empty())
		{
			rc = MQTTClient_publish(_mqttClient, topic.c_str(), static_cast<int>(message.binaryPayload.size()), const_cast<char*>(&message.binaryPayload[0]), message.qos, message.retained, &token);
		}
		else
		{
			rc = MQTTClient_publish(_mqttClient, topic.c_str(), static_cast<int>(message.payload.size()), const_cast<char*>(message.payload.data()), message.qos, message.retained, &token);
		}
		if (rc != MQTTCLIENT_SUCCESS)
			throw Poco::IOException(Poco::format("Failed to publish message on topic \"%s\"", topic), errorMessage(rc), rc);
	}

	{
		Poco::Mutex::ScopedLock lock(_statsMutex);
		_publishedMessages[topic]++;
	}

	return token;
}


int MQTTClientImpl::publishMessage5(const std::string& topic, const Message& message)
{
	// TODO
	throw Poco::NotImplementedException();
}


void MQTTClientImpl::subscribe(const std::string& topic, int qos)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	connectOnce();

	int rc = MQTTClient_subscribe(_mqttClient, const_cast<char*>(topic.c_str()), qos);
	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::IOException(Poco::format("Failed to subscribe to topic \"%s\"", topic), errorMessage(rc), rc);

	_subscribedTopics[topic] = qos;
}


void MQTTClientImpl::subscribe5(const std::string& topic, int qos, const SubscribeOptions& options, const std::vector<Property>& properties)
{
	// TODO
	throw Poco::NotImplementedException();
}


void MQTTClientImpl::unsubscribe(const std::string& topic)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (MQTTClient_isConnected(_mqttClient))
	{
		int rc = MQTTClient_unsubscribe(_mqttClient, const_cast<char*>(topic.c_str()));
		if (rc != MQTTCLIENT_SUCCESS)
			throw Poco::IOException(Poco::format("Failed to unsubscribe from topic \"%s\"", topic), errorMessage(rc), rc);
	}
	_subscribedTopics.erase(topic);
}


void MQTTClientImpl::unsubscribe5(const std::string& topic, const std::vector<Property>& properties)
{
	// TODO
	throw Poco::NotImplementedException();
}


void MQTTClientImpl::subscribeMany(const std::vector<TopicQoS>& topicsAndQoS)
{
	if (topicsAndQoS.empty()) return;

	Poco::Mutex::ScopedLock lock(_mutex);

	connectOnce();

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


void MQTTClientImpl::subscribeMany5(const std::vector<TopicQoS>& topicsAndQoS, const SubscribeOptions& options, const std::vector<Property>& properties)
{
	// TODO
	throw Poco::NotImplementedException();
}


void MQTTClientImpl::unsubscribeMany(const std::vector<std::string>& topics)
{
	if (topics.empty()) return;

	Poco::Mutex::ScopedLock lock(_mutex);

	connectOnce();

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


void MQTTClientImpl::unsubscribeMany5(const std::vector<std::string>& topics, const std::vector<Property>& properties)
{
	// TODO
	throw Poco::NotImplementedException();
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
		return "failure";
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
		pThis->_logger.warning("MQTT client \"%s\" has lost connection to server \"%s\".", pThis->_clientId, pThis->_serverURI);
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
		Poco::Mutex::ScopedLock lock(pThis->_statsMutex);
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

	if (event.handled)
	{
		MQTTClient_freeMessage(&message);
		MQTTClient_free(topicName);
    }

	return event.handled;
}


ConnectionInfo MQTTClientImpl::connectionInfo() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _connectionInfo;
}


} } // namespace IoT::MQTT
