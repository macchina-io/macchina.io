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


using namespace std::string_literals;


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


class Reconnect5Task: public Poco::Util::TimerTask
{
public:
	Reconnect5Task(MQTTClientImpl& client):
		_client(client)
	{
	}

	void run()
	{
		_client.reconnect5();
	}

private:
	MQTTClientImpl& _client;
};


namespace
{
	MQTTSubscribe_options convertOptions(const SubscribeOptions& options)
	{
		MQTTSubscribe_options mqttOpts = MQTTSubscribe_options_initializer;

		mqttOpts.noLocal = options.noLocal ? 1 : 0;
		mqttOpts.retainAsPublished = options.retainAsPublished ? 1 : 0;
		mqttOpts.retainHandling = static_cast<unsigned char>(options.retainHandling);

		return mqttOpts;
	}


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


	void cleanUpMQTTLenString(MQTTLenString& str)
	{
		std::free(str.data);
		str.data = nullptr;
	}


	MQTTProperty convertProperty(const Property& property)
	{
		MQTTProperty mqttProp;
		mqttProp.identifier = static_cast<MQTTPropertyCodes>(property.identifier);

		int type = MQTTProperty_getType(mqttProp.identifier);
		if (type < 0) throw Poco::InvalidArgumentException("invalid property identifier"s, property.identifier);

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
		if (type < 0) throw Poco::InvalidArgumentException("invalid property identifier"s, mqttProp.identifier);

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


	void cleanUpMQTTProperty(MQTTProperty& prop)
	{
		int type = MQTTProperty_getType(prop.identifier);
		if (type < 0) throw Poco::InvalidArgumentException("invalid property identifier"s, prop.identifier);

		switch (type)
		{
		case MQTTPROPERTY_TYPE_BYTE:
		case MQTTPROPERTY_TYPE_TWO_BYTE_INTEGER:
		case MQTTPROPERTY_TYPE_FOUR_BYTE_INTEGER:
		case MQTTPROPERTY_TYPE_VARIABLE_BYTE_INTEGER:
			break;

		case MQTTPROPERTY_TYPE_BINARY_DATA:
		case MQTTPROPERTY_TYPE_UTF_8_ENCODED_STRING:
			cleanUpMQTTLenString(prop.value.data);
			break;

		case MQTTPROPERTY_TYPE_UTF_8_STRING_PAIR:
			cleanUpMQTTLenString(prop.value.data);
			cleanUpMQTTLenString(prop.value.value);
			break;
		}
	}


	MQTTProperties convertProperties(const std::vector<Property>& properties)
	{
		MQTTProperties mqttProps = MQTTProperties_initializer;
		for (const auto& prop: properties)
		{
			MQTTProperty mqttProp = convertProperty(prop);
			int err = MQTTProperties_add(&mqttProps, &mqttProp);
			cleanUpMQTTProperty(mqttProp);
			if (err)
			{
				MQTTProperties_free(&mqttProps);
				throw Poco::SystemException("Failed to convert property"s, err);
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


	std::string reasonCodeToString(ReasonCode reasonCode)
	{
		if (reasonCode < 0)
		{
			return MQTTClientImpl::errorMessage(reasonCode);
		}
		else
		{
			const char* str = MQTTReasonCode_toString(static_cast<MQTTReasonCodes>(reasonCode));
			if (str)
				return std::string(str);
			else
				return Poco::format("MQTT reason code %d"s, static_cast<int>(reasonCode));
		}
	}


	Response convertResponse(const MQTTResponse& mqttResponse)
	{
		Response response;
		response.reasonCode = mqttResponse.reasonCode;
		response.reasonCodes.reserve(mqttResponse.reasonCodeCount);
		if (mqttResponse.reasonCodeCount > 1 && mqttResponse.reasonCodes)
		{
			for (int i = 0; i < mqttResponse.reasonCodeCount; i++)
			{
				response.reasonCodes.push_back(mqttResponse.reasonCodes[i]);
			}
		}
		if (mqttResponse.properties)
		{
			response.properties = convertProperties(*mqttResponse.properties);
		}
		return response;
	}


	class MQTTResponseHolder
	{
	public:
		MQTTResponseHolder()
		{
			_mqttResponse = MQTTResponse_initializer;
		}

		explicit MQTTResponseHolder(const MQTTResponse& mqttResponse):
			_mqttResponse(mqttResponse)
		{
		}

		~MQTTResponseHolder()
		{
			MQTTResponse_free(_mqttResponse);
		}

		MQTTResponseHolder& operator = (const MQTTResponse& mqttResponse)
		{
			MQTTResponse_free(_mqttResponse);
			_mqttResponse = mqttResponse;
			return *this;
		}

		bool success() const
		{
			return _mqttResponse.reasonCode == MQTTREASONCODE_SUCCESS;
		}

		ReasonCode reasonCode() const
		{
			return static_cast<ReasonCode>(_mqttResponse.reasonCode);
		}

		std::string reasonString() const
		{
			return reasonCodeToString(reasonCode());
		}

		Response convert() const
		{
			return convertResponse(_mqttResponse);
		}

		std::vector<Property> properties() const
		{
			if (_mqttResponse.properties)
			{
				return convertProperties(*_mqttResponse.properties);
			}
			else
			{
				return std::vector<Property>();
			}
		}

	private:
		MQTTResponse _mqttResponse;

		MQTTResponseHolder(const MQTTResponseHolder&) = delete;
		MQTTResponseHolder& operator = (const MQTTResponseHolder&) = delete;
	};
}


//
// MQTTPropertiesHolder
//


MQTTPropertiesHolder::MQTTPropertiesHolder()
{
	_mqttProps = MQTTProperties_initializer;
}


MQTTPropertiesHolder::MQTTPropertiesHolder(MQTTProperties& mqttProps):
	_mqttProps(mqttProps)
{
}


MQTTPropertiesHolder::MQTTPropertiesHolder(const std::vector<Property>& properties)
{
	_mqttProps = convertProperties(properties);
}


MQTTPropertiesHolder::~MQTTPropertiesHolder()
{
	MQTTProperties_free(&_mqttProps);
}


MQTTPropertiesHolder& MQTTPropertiesHolder::operator = (const std::vector<Property>& properties)
{
	MQTTProperties_free(&_mqttProps);
	_mqttProps = convertProperties(properties);
	return *this;
}


std::vector<Property> MQTTPropertiesHolder::convert() const
{
	return convertProperties(_mqttProps);
}


//
// MQTTClientImpl
//


MQTTClientImpl::MQTTClientImpl(const std::string& serverURI, const std::string& clientId, Persistence persistence, const std::string& persistencePath, const ConnectOptions& connectOptions):
	_clientId(clientId),
	_serverURI(serverURI),
	_options(connectOptions),
	_reconnectDelay(INITIAL_RECONNECT_DELAY),
	_pendingReconnect(false),
	_logger(Poco::Logger::get("IoT.MQTTClient"s))
{
	PahoInitializer::initialize();

	MQTTClient_createOptions options = MQTTClient_createOptions_initializer;
	options.MQTTVersion = connectOptions.mqttVersion;

	int rc;
	switch (persistence)
	{
	case MQTT_PERSISTENCE_NONE:
		rc = MQTTClient_createWithOptions(&_mqttClient, serverURI.c_str(), clientId.c_str(), MQTTCLIENT_PERSISTENCE_NONE, 0, &options);
		break;
	case MQTT_PERSISTENCE_FILE:
		_logger.debug("Persistence: " + persistencePath);
		rc = MQTTClient_createWithOptions(&_mqttClient, serverURI.c_str(), clientId.c_str(), MQTTCLIENT_PERSISTENCE_DEFAULT, const_cast<char*>(persistencePath.c_str()), &options);
		break;
	case MQTT_PERSISTENCE_DATABASE:
		throw Poco::NotImplementedException("Database-based persistence is not yet implemented"s);
	default:
		throw Poco::InvalidArgumentException("persistence"s);
	}
	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::SystemException("Cannot create MQTT client"s, errorMessage(rc), rc);

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
	for (const auto& p: _subscribedTopics)
	{
		result.push_back(TopicQoS(p.first, p.second.qos));
	}

	return result;
}


Statistics MQTTClientImpl::statistics() const
{
	Poco::Mutex::ScopedLock lock(_statsMutex);

	Statistics stats;

	for (const auto& p: _receivedMessages)
	{
		stats.receivedMessages.push_back(TopicCount(p.first, p.second));
	}

	for (const auto& p: _publishedMessages)
	{
		stats.publishedMessages.push_back(TopicCount(p.first, p.second));
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
		_logger.information("Connecting MQTT client \"%s\" to server \"%s\"..."s, _clientId, _serverURI);
		connectImpl(_options);
	}

	return _connectionInfo;
}


ConnectionInfo MQTTClientImpl::connect5(const std::vector<Property>& connectProperties, const std::vector<Property>& willProperties)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!MQTTClient_isConnected(_mqttClient))
	{
		{
			Poco::Mutex::ScopedLock lock(_statsMutex);
			_receivedMessages.clear();
			_publishedMessages.clear();
		}
		_connectProperties = connectProperties;
		_willProperties = willProperties;
		_logger.information("Connecting MQTT client \"%s\" to server \"%s\"..."s, _clientId, _serverURI);
		connect5Impl(_options, _connectProperties, _willProperties);
	}

	return _connectionInfo;
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
	Poco::Mutex::ScopedLock lock(_mutex);
	// MQTTProperties convConnectProperties = convertProperties(connectProperties);
	// MQTTProperties convWillProperties = convertProperties(willProperties);
	// if (MQTTClient_connect5(_mqttClient, NULL, &convConnectProperties, &convWillProperties).reasonCode != MQTTREASONCODE_SUCCESS)

	if (!MQTTClient_isConnected(_mqttClient))
	{
		_timer.schedule(new ReconnectTask(*this), Poco::Clock());
	}
}


void MQTTClientImpl::connectOnce()
{
	if (!MQTTClient_isConnected(_mqttClient))
	{
		if (_pendingReconnect)
			_logger.information("Reconnecting MQTT client \"%s\" to server \"%s\"..."s, _clientId, _serverURI);
		else
			_logger.information("Connecting MQTT client \"%s\" to server \"%s\"..."s, _clientId, _serverURI);

		if (_options.mqttVersion == MQTTVERSION_5)
		{
			connect5Impl(_options, _connectProperties, _willProperties);
		}
		else
		{
			connectImpl(_options);
		}
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
			_logger.information("Connecting MQTT client \"%s\" to server \"%s\"..."s, _clientId, _serverURI);
			connectImpl(_options);
		}
		catch (Poco::Exception& exc)
		{
			_logger.error("Failed to connect MQTT client \"%s\" to \"%s\": %s"s, _clientId, _serverURI, exc.displayText());
			if (_reconnectDelay < MAXIMUM_RECONNECT_DELAY)
				_reconnectDelay = 3*_reconnectDelay/2;

			Poco::Clock clock;
			clock += 1000*_reconnectDelay;
			_timer.schedule(new ReconnectTask(*this), clock);
		}
	}
}


void MQTTClientImpl::reconnect5()
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!MQTTClient_isConnected(_mqttClient))
	{
		_pendingReconnect = true;
		try
		{
			_logger.information("Connecting MQTTv5 client \"%s\" to server \"%s\"..."s, _clientId, _serverURI);
			connect5Impl(_options, _connectProperties, _willProperties);
		}
		catch (Poco::Exception& exc)
		{
			_logger.error("Failed to connect MQTTv5 client \"%s\" to \"%s\": %s"s, _clientId, _serverURI, exc.displayText());
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
	connectOptions.keepAliveInterval   = options.keepAliveInterval;
	connectOptions.cleansession        = options.cleanSession;
	connectOptions.reliable            = options.reliable;
	connectOptions.username            = options.username.empty() ? 0 : options.username.c_str();
	connectOptions.password            = 0; // see binarypwd
	connectOptions.binarypwd.len       = options.password.size();
	connectOptions.binarypwd.data      = options.password.empty() ? 0 : options.password.data();
	connectOptions.connectTimeout      = options.connectTimeout;
	connectOptions.retryInterval       = options.retryInterval;
	connectOptions.MQTTVersion         = options.mqttVersion;
	connectOptions.maxInflightMessages = options.maxInflightMessages;
	connectOptions.cleanstart          = options.cleanStart;

	if (options.willTopic.empty())
		connectOptions.will = 0;
	else
		connectOptions.will = &willOptions;
	connectOptions.ssl      = &sslOptions;

	std::vector<char*> serverURIs;
	for (const auto& uri: options.serverURIs)
	{
		serverURIs.push_back(const_cast<char*>(uri.c_str()));
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

	sslOptions.trustStore               = options.sslTrustStore.empty() ? 0 : options.sslTrustStore.c_str();
	sslOptions.CApath                   = options.sslCAPath.empty() ? 0 : options.sslCAPath.c_str();
	sslOptions.keyStore                 = options.sslKeyStore.empty() ? 0 : options.sslKeyStore.c_str();
	sslOptions.privateKey               = options.sslPrivateKey.empty() ? 0 : options.sslPrivateKey.c_str();
	sslOptions.privateKeyPassword       = options.sslPrivateKeyPassword.empty() ? 0 : options.sslPrivateKeyPassword.c_str();
	sslOptions.enabledCipherSuites      = options.sslEnabledCipherSuites.empty() ? 0 : options.sslEnabledCipherSuites.c_str();
	sslOptions.enableServerCertAuth     = options.sslEnableServerCertAuth;
	sslOptions.disableDefaultTrustStore = options.sslDisableDefaultTrustStore;
	sslOptions.verify                   = options.sslVerify;
	sslOptions.sslVersion               = options.sslVersion;

	Poco::Timestamp::TimeVal time = 0;
	Poco::Timestamp::TimeVal timeout = options.connectTimeout*Poco::Timestamp::resolution();

	int remainingAttempts = options.connectRetries > 0 ? options.connectRetries + 1 : 1;
	if (options.initialConnectTimeout > 0 && options.connectRetries > 0)
	{
		connectOptions.connectTimeout = options.initialConnectTimeout;
	}

	_connectionInfo.properties.clear();

	int rc = MQTTCLIENT_SUCCESS;
	int attempt = 0;
	while (remainingAttempts > 0)
	{
		if (_logger.debug())
		{
			std::string cleanMsg(options.cleanSession ? " with clean session"s : ""s);
			_logger.debug("Connecting MQTT client \"%s\" to server \"%s\"%s (timeout %d seconds)."s, _clientId, _serverURI, cleanMsg, connectOptions.connectTimeout);
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
				_logger.notice("Failed to connect at attempt %d: %s (%d) - will retry."s, attempt, errorMessage(rc), rc);
			}
		}
	}

	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::IOException(Poco::format("Cannot connect to MQTT server \"%s\""s, _serverURI), errorMessage(rc), rc);

	_logger.information("Connected to MQTT server \"%s\" (MQTT version %d)."s, _serverURI, connectOptions.returned.MQTTVersion);
	_reconnectDelay = INITIAL_RECONNECT_DELAY;
	_pendingReconnect = false;

	if (connectOptions.returned.serverURI)
	{
		_connectionInfo.serverURI = connectOptions.returned.serverURI;
	}
	_connectionInfo.sessionPresent = connectOptions.returned.sessionPresent != 0;
	_connectionInfo.mqttVersion = connectOptions.returned.MQTTVersion;

	if (_connectionInfo.sessionPresent)
	{
		_logger.debug("Session is present."s);
	}
	else
	{
		_logger.debug("Session is not present."s);
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
		_logger.warning("Failed to resubscribe client \"%s\" to previously subscribed topics: %s"s, _clientId, exc.displayText());
	}

	Poco::ScopedUnlock<Poco::Mutex> unlock(_mutex);
	ConnectionEstablishedEvent event;
	event.connectionInfo = _connectionInfo;
	connectionEstablished(this, event);
}


void MQTTClientImpl::connect5Impl(const ConnectOptions& options, MQTTPropertiesHolder& connectProperties, MQTTPropertiesHolder& willProperties)
{
	MQTTClient_willOptions willOptions = MQTTClient_willOptions_initializer;
	MQTTClient_SSLOptions sslOptions = MQTTClient_SSLOptions_initializer;
	MQTTClient_connectOptions connectOptions = MQTTClient_connectOptions_initializer;
	connectOptions.keepAliveInterval   = options.keepAliveInterval;
	connectOptions.cleansession        = options.cleanSession;
	connectOptions.reliable            = options.reliable;
	connectOptions.username            = options.username.empty() ? 0 : options.username.c_str();
	connectOptions.password            = 0; // see binarypwd
	connectOptions.binarypwd.len       = options.password.size();
	connectOptions.binarypwd.data      = options.password.empty() ? 0 : options.password.data();
	connectOptions.connectTimeout      = options.connectTimeout;
	connectOptions.retryInterval       = options.retryInterval;
	connectOptions.MQTTVersion         = options.mqttVersion;
	connectOptions.maxInflightMessages = options.maxInflightMessages;
	connectOptions.cleanstart          = options.cleanStart;

	if (options.willTopic.empty())
		connectOptions.will = 0;
	else
		connectOptions.will = &willOptions;
	connectOptions.ssl      = &sslOptions;

	std::vector<char*> serverURIs;
	for (const auto& uri: options.serverURIs)
	{
		serverURIs.push_back(const_cast<char*>(uri.c_str()));
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

	sslOptions.trustStore               = options.sslTrustStore.empty() ? 0 : options.sslTrustStore.c_str();
	sslOptions.CApath                   = options.sslCAPath.empty() ? 0 : options.sslCAPath.c_str();
	sslOptions.keyStore                 = options.sslKeyStore.empty() ? 0 : options.sslKeyStore.c_str();
	sslOptions.privateKey               = options.sslPrivateKey.empty() ? 0 : options.sslPrivateKey.c_str();
	sslOptions.privateKeyPassword       = options.sslPrivateKeyPassword.empty() ? 0 : options.sslPrivateKeyPassword.c_str();
	sslOptions.enabledCipherSuites      = options.sslEnabledCipherSuites.empty() ? 0 : options.sslEnabledCipherSuites.c_str();
	sslOptions.enableServerCertAuth     = options.sslEnableServerCertAuth;
	sslOptions.disableDefaultTrustStore = options.sslDisableDefaultTrustStore;
	sslOptions.verify                   = options.sslVerify;
	sslOptions.sslVersion               = options.sslVersion;

	Poco::Timestamp::TimeVal time = 0;
	Poco::Timestamp::TimeVal timeout = options.connectTimeout*Poco::Timestamp::resolution();

	int remainingAttempts = options.connectRetries > 0 ? options.connectRetries + 1 : 1;
	if (options.initialConnectTimeout > 0 && options.connectRetries > 0)
	{
		connectOptions.connectTimeout = options.initialConnectTimeout;
	}

	_connectionInfo.properties.clear();

	ReasonCode reasonCode = REASON_SUCCESS;
	int attempt = 0;
	while (remainingAttempts > 0)
	{
		if (_logger.debug())
		{
			std::string cleanMsg(options.cleanSession ? " with clean session"s : ""s);
			_logger.debug("Connecting MQTTv5 client \"%s\" to server \"%s\"%s (timeout %d seconds)."s, _clientId, _serverURI, cleanMsg, connectOptions.connectTimeout);
		}

		attempt++;
		remainingAttempts--;
		Poco::Timestamp ts;

		MQTTResponseHolder response(MQTTClient_connect5(_mqttClient, &connectOptions, &connectProperties.value(), &willProperties.value()));
		time += ts.elapsed();
		reasonCode = response.reasonCode();
		if (reasonCode == REASON_SUCCESS)
		{
			remainingAttempts = 0;
			_connectionInfo.properties = response.properties();
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
				_logger.notice("Failed to connect at attempt %d: %s (%d) - will retry."s, attempt, reasonCodeToString(reasonCode), reasonCode);
			}
		}
	}

	if (reasonCode != REASON_SUCCESS)
		throw Poco::IOException(Poco::format("Cannot connect to MQTTv5 server \"%s\""s, _serverURI), reasonCodeToString(reasonCode), reasonCode);

	_logger.information("Connected to MQTT server \"%s\" (MQTT version %d)."s, _serverURI, connectOptions.returned.MQTTVersion);
	_reconnectDelay = INITIAL_RECONNECT_DELAY;
	_pendingReconnect = false;

	if (connectOptions.returned.serverURI)
	{
		_connectionInfo.serverURI = connectOptions.returned.serverURI;
	}
	_connectionInfo.sessionPresent = connectOptions.returned.sessionPresent != 0;
	_connectionInfo.mqttVersion = connectOptions.returned.MQTTVersion;

	if (_connectionInfo.sessionPresent)
	{
		_logger.debug("Session is present."s);
	}
	else
	{
		_logger.debug("Session is not present."s);
	}

	try
	{
		if (!_connectionInfo.sessionPresent)
		{
			resubscribe5();
		}
	}
	catch (Poco::Exception& exc)
	{
		_logger.warning("Failed to resubscribe client \"%s\" to previously subscribed topics: %s"s, _clientId, exc.displayText());
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
			throw Poco::IOException("Failed to disconnect from MQTT server"s, errorMessage(rc), rc);
		_logger.debug("Disconnected MQTT client \"%s\" from server \"%s\"."s, _clientId, _serverURI);
		_subscribedTopics.clear();

		_connectionInfo.serverURI.clear();
		_connectionInfo.sessionPresent = false;

		lock.unlock();
		connectionClosed(this);
	}
}


void MQTTClientImpl::disconnect5(int timeout, ReasonCode reason, const std::vector<Property>& properties)
{
	Poco::ScopedLockWithUnlock<Poco::Mutex> lock(_mutex);

	if (MQTTClient_isConnected(_mqttClient))
	{
		MQTTPropertiesHolder convertedProperties(properties);
		int rc = MQTTClient_disconnect5(_mqttClient, timeout, static_cast<MQTTReasonCodes>(reason), &convertedProperties.value());
		if (rc != MQTTCLIENT_SUCCESS)
			throw Poco::IOException("Failed to disconnect from MQTT server"s, errorMessage(rc), rc);
		_logger.debug("Disconnected MQTT client \"%s\" from server \"%s\"."s, _clientId, _serverURI);
		_subscribedTopics.clear();

		_connectionInfo.serverURI.clear();
		_connectionInfo.sessionPresent = false;

		lock.unlock();
		connectionClosed(this);
	}
}


int MQTTClientImpl::publish(const std::string& topic, const std::string& payload, int qos)
{
	int token = 0;
	{
		Poco::Mutex::ScopedLock lock(_mutex);

		connectOnce();

		int rc = MQTTClient_publish(_mqttClient, topic.c_str(), static_cast<int>(payload.size()), const_cast<char*>(payload.data()), qos, 0, &token);
		if (rc != MQTTCLIENT_SUCCESS)
			throw Poco::IOException(Poco::format("Failed to publish message on topic \"%s\""s, topic), errorMessage(rc), rc);
	}

	{
		Poco::Mutex::ScopedLock lock(_statsMutex);
		_publishedMessages[topic]++;
	}

	return token;
}


PublishResult MQTTClientImpl::publish5(const std::string& topic, const std::string& payload, int qos, bool retained, const std::vector<Property>& properties)
{
	PublishResult result;

	int token = 0;
	{
		Poco::Mutex::ScopedLock lock(_mutex);

		connectOnce();
		MQTTPropertiesHolder convertedProperties(properties);
		MQTTResponseHolder mqttResponse(MQTTClient_publish5(_mqttClient, topic.c_str(), static_cast<int>(payload.size()), const_cast<char*>(payload.data()), qos, retained, &convertedProperties.value(), &token));
		if (!mqttResponse.success())
			throw Poco::IOException(Poco::format("Failed to publish message on topic \"%s\""s, topic), mqttResponse.reasonString(), mqttResponse.reasonCode());
		result.deliveryToken = token;
		result.response = mqttResponse.convert();
	}

	{
		Poco::Mutex::ScopedLock lock(_statsMutex);
		_publishedMessages[topic]++;
	}

	return result;
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
			throw Poco::IOException(Poco::format("Failed to publish message on topic \"%s\""s, topic), errorMessage(rc), rc);
	}

	{
		Poco::Mutex::ScopedLock lock(_statsMutex);
		_publishedMessages[topic]++;
	}

	return token;
}


PublishResult MQTTClientImpl::publishMessage5(const std::string& topic, const Message& message)
{
	PublishResult result;
	{
		Poco::Mutex::ScopedLock lock(_mutex);

		connectOnce();

		MQTTPropertiesHolder convertedProperties(message.properties);
		MQTTResponseHolder response;
		if (message.payload.empty())
		{
			response = MQTTClient_publish5(_mqttClient, topic.c_str(), static_cast<int>(message.binaryPayload.size()), const_cast<char*>(&message.binaryPayload[0]), message.qos, message.retained, &convertedProperties.value(), &result.deliveryToken);
		}
		else
		{
			response = MQTTClient_publish5(_mqttClient, topic.c_str(), static_cast<int>(message.payload.size()), const_cast<char*>(message.payload.data()), message.qos, message.retained, &convertedProperties.value(), &result.deliveryToken);
		}
		if (!response.success())
			throw Poco::IOException(Poco::format("Failed to publish message on topic \"%s\""s, topic), response.reasonString(), response.reasonCode());
		result.response = response.convert();
	}

	{
		Poco::Mutex::ScopedLock lock(_statsMutex);
		_publishedMessages[topic]++;
	}

	return result;
}


void MQTTClientImpl::subscribe(const std::string& topic, int qos)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	connectOnce();

	int rc = MQTTClient_subscribe(_mqttClient, const_cast<char*>(topic.c_str()), qos);
	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::IOException(Poco::format("Failed to subscribe to topic \"%s\""s, topic), errorMessage(rc), rc);

	Subscription sub;
	sub.qos = qos;
	_subscribedTopics[topic] = std::move(sub);
}


Response MQTTClientImpl::subscribe5(const std::string& topic, int qos, const SubscribeOptions& options, const std::vector<Property>& properties)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	connectOnce();
	MQTTPropertiesHolder convertedProperties(properties);
	MQTTSubscribe_options convSubscribeOptions = convertOptions(options);

	MQTTResponseHolder response(MQTTClient_subscribe5(_mqttClient, const_cast<char*>(topic.c_str()), qos, &convSubscribeOptions, &convertedProperties.value()));
	if (!response.success())
		throw Poco::IOException(Poco::format("Failed to subscribe to topic \"%s\""s, topic), response.reasonString(), response.reasonCode());

	Subscription sub;
	sub.qos = qos;
	sub.options = options;
	sub.properties = properties;
	_subscribedTopics[topic] = std::move(sub);

	return response.convert();
}


void MQTTClientImpl::unsubscribe(const std::string& topic)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (MQTTClient_isConnected(_mqttClient))
	{
		int rc = MQTTClient_unsubscribe(_mqttClient, const_cast<char*>(topic.c_str()));
		if (rc != MQTTCLIENT_SUCCESS)
			throw Poco::IOException(Poco::format("Failed to unsubscribe from topic \"%s\""s, topic), errorMessage(rc), rc);
	}
	_subscribedTopics.erase(topic);
}


Response MQTTClientImpl::unsubscribe5(const std::string& topic, const std::vector<Property>& properties)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	MQTTResponseHolder response;
	if (MQTTClient_isConnected(_mqttClient))
	{
		MQTTPropertiesHolder convertedProperties(properties);
		response = MQTTClient_unsubscribe5(_mqttClient, const_cast<char*>(topic.c_str()), &convertedProperties.value());
		if (!response.success())
			throw Poco::IOException(Poco::format("Failed to unsubscribe from topic \"%s\""s, topic), response.reasonString(), response.reasonCode());
	}
	_subscribedTopics.erase(topic);

	return response.convert();
}


void MQTTClientImpl::subscribeMany(const std::vector<TopicQoS>& topicsAndQoS)
{
	if (topicsAndQoS.empty()) return;

	Poco::Mutex::ScopedLock lock(_mutex);

	connectOnce();

	std::vector<char*> ctopics;
	std::vector<int> qoss;
	for (const auto& t: topicsAndQoS)
	{
		ctopics.push_back(const_cast<char*>(t.topic.c_str()));
		qoss.push_back(t.qos);
	}
	int rc = MQTTClient_subscribeMany(_mqttClient, static_cast<int>(ctopics.size()), &ctopics[0], &qoss[0]);
	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::IOException("Failed to subscribe to multiple topics"s, errorMessage(rc), rc);

	for (const auto& t: topicsAndQoS)
	{
		Subscription sub;
		sub.qos = t.qos;
		_subscribedTopics[t.topic] = std::move(sub);
	}
}


Response MQTTClientImpl::subscribeMany5(const std::vector<TopicQoS>& topicsAndQoS, const SubscribeOptions& options, const std::vector<Property>& properties)
{
	if (topicsAndQoS.empty()) return Response();

	Poco::Mutex::ScopedLock lock(_mutex);

	connectOnce();

	std::vector<char*> ctopics;
	std::vector<int> qoss;
	for (const auto& t: topicsAndQoS)
	{
		ctopics.push_back(const_cast<char*>(t.topic.c_str()));
		qoss.push_back(t.qos);
	}
	MQTTPropertiesHolder convertedProperties(properties);
	MQTTSubscribe_options convSubscribeOptions = convertOptions(options);

	MQTTResponseHolder response(MQTTClient_subscribeMany5(_mqttClient, static_cast<int>(ctopics.size()), &ctopics[0], &qoss[0], &convSubscribeOptions, &convertedProperties.value()));
	if (!response.success())
		throw Poco::IOException("Failed to subscribe to multiple topics"s, response.reasonString(), response.reasonCode());

	for (const auto& t: topicsAndQoS)
	{
		Subscription sub;
		sub.qos = t.qos;
		sub.options = options;
		sub.properties = properties;
		_subscribedTopics[t.topic] = sub;
	}

	return response.convert();
}


void MQTTClientImpl::unsubscribeMany(const std::vector<std::string>& topics)
{
	if (topics.empty()) return;

	Poco::Mutex::ScopedLock lock(_mutex);

	connectOnce();

	std::vector<char*> ctopics;
	for (const auto& t: topics)
	{
		ctopics.push_back(const_cast<char*>(t.c_str()));
	}
	int rc = MQTTClient_unsubscribeMany(_mqttClient, static_cast<int>(ctopics.size()), &ctopics[0]);
	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::IOException("Failed to unsubscribe from multiple topics"s, errorMessage(rc), rc);

	for (const auto& t: topics)
	{
		_subscribedTopics.erase(t);
	}
}


Response MQTTClientImpl::unsubscribeMany5(const std::vector<std::string>& topics, const std::vector<Property>& properties)
{
	if (topics.empty()) return Response();

	Poco::Mutex::ScopedLock lock(_mutex);

	connectOnce();

	std::vector<char*> ctopics;
	for (const auto& t: topics)
	{
		ctopics.push_back(const_cast<char*>(t.c_str()));
	}
	MQTTPropertiesHolder convertedProperties(properties);
	MQTTResponseHolder response(MQTTClient_unsubscribeMany5(_mqttClient, static_cast<int>(ctopics.size()), &ctopics[0], &convertedProperties.value()));
	if (!response.success())
		throw Poco::IOException("Failed to unsubscribe from multiple topics"s, response.reasonString(), response.reasonCode());

	for (const auto& t: topics)
	{
		_subscribedTopics.erase(t);
	}

	return response.convert();
}


void MQTTClientImpl::resubscribe()
{
	if (_subscribedTopics.empty()) return;

	std::vector<char*> ctopics;
	std::vector<int> qoss;
	for (const auto& p: _subscribedTopics)
	{
		ctopics.push_back(const_cast<char*>(p.first.c_str()));
		qoss.push_back(p.second.qos);
	}
	int rc = MQTTClient_subscribeMany(_mqttClient, static_cast<int>(ctopics.size()), &ctopics[0], &qoss[0]);
	if (rc != MQTTCLIENT_SUCCESS)
		throw Poco::IOException("Failed to resubscribe to topics"s, errorMessage(rc), rc);
}


void MQTTClientImpl::resubscribe5()
{
	if (_subscribedTopics.empty()) return;

	for (const auto& p: _subscribedTopics)
	{
		MQTTSubscribe_options options = convertOptions(p.second.options);
		MQTTPropertiesHolder props(p.second.properties);
		MQTTResponseHolder response(MQTTClient_subscribe5(_mqttClient, p.first.c_str(), p.second.qos, &options, &props.value()));
		if (!response.success())
			throw Poco::IOException("Failed to resubscribe to topic"s + p.first, response.reasonString(), response.reasonCode());
	}
}


std::string MQTTClientImpl::errorMessage(int code)
{
	switch (code)
	{
	case MQTTCLIENT_SUCCESS:
		return "success"s;
	case MQTTCLIENT_FAILURE:
		return "failure"s;
	case -2: // MQTTCLIENT_PERSISTENCE_ERROR
		return "persistence error"s;
	case MQTTCLIENT_DISCONNECTED:
		return "client disconnected"s;
	case MQTTCLIENT_MAX_MESSAGES_INFLIGHT:
		return "maximum number of in-flight messages exceeded"s;
	case MQTTCLIENT_BAD_UTF8_STRING:
		return "invalid UTF-8 string"s;
	case MQTTCLIENT_NULL_PARAMETER:
		return "NULL parameter"s;
	case MQTTCLIENT_TOPICNAME_TRUNCATED:
		return "topic name truncated"s;
	case MQTTCLIENT_BAD_STRUCTURE:
		return "bad structure"s;
	case MQTTCLIENT_BAD_QOS:
		return "invalid QoS value"s;
	case MQTTCLIENT_SSL_NOT_SUPPORTED:
		return "TLS not supported"s;
	case MQTTCLIENT_BAD_MQTT_VERSION:
		return "bad MQTT version"s;
	case MQTTCLIENT_BAD_PROTOCOL:
		return "bad protocol prefix"s;
	case MQTTCLIENT_BAD_MQTT_OPTION:
		return "bad MQTT option"s;
	case MQTTCLIENT_WRONG_MQTT_VERSION:
		return "wrong MQTT version"s;
	case MQTTCLIENT_0_LEN_WILL_TOPIC:
		return "zero length will topic"s;
	case 1:
		return "connection refused - unacceptable protocol version"s;
	case 2:
		return "connection refused - identifier rejected"s;
	case 3:
		return "connection refused - server unavailable"s;
	case 4:
		return "connection refused - bad username or password"s;
	case 5:
		return "connection refused - not authorized"s;
	default:
		return Poco::format("unknown error code %d"s, code);
	}
}


void MQTTClientImpl::onConnectionLost(void* context, char* cause)
{
	MQTTClientImpl* pThis = reinterpret_cast<MQTTClientImpl*>(context);
	ConnectionLostEvent event;
	if (cause) event.cause = cause;
	try
	{
		pThis->_logger.warning("MQTT client \"%s\" has lost connection to server \"%s\"."s, pThis->_clientId, pThis->_serverURI);
		pThis->connectionLost(pThis, event);
	}
	catch (Poco::Exception& exc)
	{
		pThis->_logger.error("connectionLost event delegate leaked exception: %s"s, exc.displayText());
	}

	if (pThis->_options.mqttVersion == MQTTVERSION_5)
	{
		pThis->_timer.schedule(new Reconnect5Task(*pThis), Poco::Clock());
	}
	else
	{
		pThis->_timer.schedule(new ReconnectTask(*pThis), Poco::Clock());
	}
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
		pThis->_logger.error("messageDelivered event delegate leaked exception: %s"s, exc.displayText());
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
	event.message.properties = convertProperties(message->properties);
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
		pThis->_logger.error("messageArrived event delegate leaked exception: %s"s, exc.displayText());
		event.handled = false;
	}

	if (event.handled)
	{
		MQTTClient_freeMessage(&message);
		MQTTClient_free(topicName);
    }

	return event.handled;
}


void MQTTClientImpl::waitForCompletion(int deliveryToken, int timeout)
{
	int rc = MQTTClient_waitForCompletion(_mqttClient, deliveryToken, timeout);
	if (rc == MQTTCLIENT_SUCCESS)
	{
		return;
	}
	else if (rc == MQTTCLIENT_TIMEOUT)
	{
		throw Poco::TimeoutException();
	}
	else
	{
		throw Poco::IOException("Failed to resubscribe to topics"s, errorMessage(rc), rc);
	}
}


std::vector<int> MQTTClientImpl::pendingDeliveryTokens()
{
	std::vector<int> result;
	MQTTClient_deliveryToken* tokens = nullptr;
	int rc = MQTTClient_getPendingDeliveryTokens(_mqttClient, &tokens);
	if (rc == MQTTCLIENT_SUCCESS)
	{
		if (tokens)
		{
			try
			{
				while (*tokens)
				{
					result.push_back(*tokens++);
				}
			}
			catch (...)
			{
				free(tokens);
				throw;
			}
			free(tokens);
		}
	}
	else
	{
		Poco::IOException("Failed to resubscribe to topics"s, errorMessage(rc), rc);
	}
	return result;
}


ConnectionInfo MQTTClientImpl::connectionInfo() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _connectionInfo;
}


} } // namespace IoT::MQTT
