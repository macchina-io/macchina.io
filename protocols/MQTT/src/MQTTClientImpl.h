//
// MQTTClientImpl.h
//
// Library: IoT/MQTT
// Package: MQTTClient
// Module:  MQTTClientImpl
//
// Definition of the MQTTClientImpl class.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_MQTT_MQTTClientImpl_INCLUDED
#define IoT_MQTT_MQTTClientImpl_INCLUDED


#include "IoT/MQTT/MQTTClient.h"
#include "Poco/Util/Timer.h"
#include "Poco/Logger.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedUnlock.h"
#include <map>
#include "MQTTClient.h"


namespace IoT {
namespace MQTT {


class IoTMQTT_API MQTTPropertiesHolder
{
public:
	MQTTPropertiesHolder();
	explicit MQTTPropertiesHolder(MQTTProperties& mqttProps);
	explicit MQTTPropertiesHolder(const std::vector<Property>& properties);
	~MQTTPropertiesHolder();

	MQTTPropertiesHolder& operator = (const std::vector<Property>& properties);

	MQTTProperties& value();
	const MQTTProperties& value() const;
	std::vector<Property> convert() const;

private:
	MQTTProperties _mqttProps;

	MQTTPropertiesHolder(const MQTTPropertiesHolder&) = delete;
	MQTTPropertiesHolder(MQTTPropertiesHolder&&) = delete;
	MQTTPropertiesHolder& operator = (const MQTTPropertiesHolder&) = delete;
	MQTTPropertiesHolder& operator = (MQTTPropertiesHolder&&) = delete;
};


class IoTMQTT_API MQTTClientImpl: public IoT::MQTT::MQTTClient
	/// The default implementation of MQTTClient based on paho.
{
public:
	using Ptr = Poco::SharedPtr<MQTTClientImpl>;

	struct IoTMQTT_API ConnectOptions
	{
		int keepAliveInterval = 60;
			/// Keep-alive interval in seconds.

		int retryInterval = 30;
			/// Retry interval in seconds.

		int connectTimeout = 30;
			/// Connect timeout in seconds.

		int initialConnectTimeout = 0;
			/// If non-zero, and if connectRetries is also non-zero, attempt to connect
			/// first with this timeout, given in seconds.
			///
			/// See also connectRetries.
			///
			/// Warning: This is an experimental feature and may be removed in the future.

		int connectRetries = 0;
			/// Number of retries if initial connect attempt does not succeed.
			///
			/// If greater than zero:
			///
			///   - The first connect attempt to the broker will be made using
			///     initialConnectTimeout if greater than zero, otherwise connectTimeout.
			///   - If not successful, additional attempts will be made connecting to
			///     the broker, again using initialConnectTimeout, if greater than zero,
			///     or connectTimeout, otherwise. If retryConnectWithExponentialBackoff is
			///     true, the timeout will be doubled with each successive attempt.
			///   - The final attempt will be made with such a timeout so that the
			///     total timeout specified in connectTimeout will not be exceeded.
			///
			/// Therefore, connect() will never take longer than the timeout specified
			/// in connectTimeout.
			///
			/// Warning: This is an experimental feature and may be removed in the future.

		bool retryConnectWithExponentialBackoff = false;
			/// If specified, and if both connectRetries and initialConnectTimeout are
			/// greater than zero, then the connect timeout, starting with
			/// initialConnectTimeout, will be doubled after every unsuccessful
			/// connection attempt.
			///
			/// See also connectRetries.
			///
			/// Warning: This is an experimental feature and may be removed in the future.

		bool cleanSession = false;
			/// Start with a clean session.

		bool reliable = false;
			/// If set to true, only one message at a time can be "in flight".

		std::string username;
			/// Username for MQTT v3.1.

		std::string password;
			/// Password for MQTT v3.1.

		std::string willTopic;
			/// Last will topic name.

		std::string willMessage;
			/// Last will message.

		bool willRetained = false;
			/// Retained flag for will message.

		int willQoS = 0;
			/// Quality of Service level for will message (0-2).

		int maxInflightMessages = 0;
			/// Maximum number of messages in flight.

		bool cleanStart = false;
			/// MQTT V5 clean start flag.
			/// Only clears state at the beginning of the session.
			/// Must only be set of mqttVersion == 5.

		std::vector<std::string> serverURIs;
			/// Optional list of server URIs.

		int mqttVersion = 0;
			/// Sets the version of MQTT to be used on the connect. Valid values are
			/// 0, 3 and 4.
			///   * 0 = default: start with 3.1.1, and if that fails, fall back to 3.1
			///   * 3 = only try version 3.1
			///   * 4 = only try version 3.1.1
			///   * 5 = only try version 5

		std::string sslTrustStore;
			/// The file in PEM format containing the public digital certificates trusted by the client.

		bool sslDisableDefaultTrustStore = false;
			/// If true, don't load OpenSSL default CA certificates.

		std::string sslCAPath;
			/// If not empty, specifies a directory containing CA certificates in PEM format.

		std::string sslKeyStore;
			/// The file in PEM format containing the public certificate chain of the client.
			/// It may also include the client's private key.

		std::string sslPrivateKey;
			/// If not included in the sslKeyStore, this setting points to the file in PEM
			/// format containing the client's private key.

		std::string sslPrivateKeyPassword;
			/// The password to load the client's privateKey if encrypted.

		std::string sslEnabledCipherSuites;
			/// The list of cipher suites that the client will present to the server
			/// during the SSL handshake. For a full explanation of the cipher list
			/// format, please see the OpenSSL on-line documentation:
			/// http://www.openssl.org/docs/apps/ciphers.html#CIPHER_LIST_FORMAT
			/// If this setting is ommitted, its default value will be "ALL", that is,
			/// all the cipher suites -excluding those offering no encryption- will be
			/// considered. This setting can be used to set an SSL anonymous connection
			/// ("aNULL" string value, for instance).

		bool sslEnableServerCertAuth = false;
			/// Enable or disable verification of the server certificate.

		bool sslVerify = false;
			/// Enable or disable post-connect checks, including that a certificate
     		/// matches the given host name.

		int sslVersion = 0;
			/// SSL/TLS Version to use.
			///   * 0 = default
			///   * 1 = TLS 1.0
			///   * 2 = TLS 1.1
			///   * 3 = TLS 1.2
	};

	enum Persistence
	{
		MQTT_PERSISTENCE_NONE = 0,     /// In-memory persistence.
		MQTT_PERSISTENCE_FILE = 1,     /// File-based persistence.
		MQTT_PERSISTENCE_DATABASE = 2  /// Database-based persistence.
	};

	MQTTClientImpl(const std::string& serverURI, const std::string& clientId, Persistence persistence, const std::string& persistencePath, const ConnectOptions& connectOptions);
		/// Creates the MQTTClientImpl with the given server URI, client ID, persistence, persistence path
		/// and connect options.
		///
		/// For File-based persistence, the path should specify a directory.
		/// For Database-based persistence, the path should specify a SQLite database file.
		///
		/// Database-based persistence is currently not implemented.

	~MQTTClientImpl();
		/// Destroys the MQTTClientImpl.

	static std::string errorMessage(int code);
		/// Returns a message for the given error code.

	// MQTTClient
	const std::string& id() const;
	const std::string& serverURI() const;
	bool connected() const;
	ConnectionInfo connect();
	ConnectionInfo connect5(const std::vector<Property>& connectProperties, const std::vector<Property>& willProperties);
	void connectAsync();
	void connectAsync5(const std::vector<Property>& connectProperties, const std::vector<Property>& willProperties);
	void disconnect(int timeout);
	void disconnect5(int timeout, ReasonCode reason, const std::vector<Property>& properties);
	std::vector<TopicQoS> subscribedTopics() const;
	Statistics statistics() const;
	int publish(const std::string& topic, const std::string& payload, int qos);
	PublishResult publish5(const std::string& topic, const std::string& payload, int qos, bool retained, const std::vector<Property>& properties);
	int publishMessage(const std::string& topic, const Message& message);
	PublishResult publishMessage5(const std::string& topic, const Message& message);
	void subscribe(const std::string& topic, int qos);
	Response subscribe5(const std::string& topic, int qos, const SubscribeOptions& options, const std::vector<Property>& properties);
	void unsubscribe(const std::string& topic);
	Response unsubscribe5(const std::string& topic, const std::vector<Property>& properties);
	void subscribeMany(const std::vector<TopicQoS>& topicsAndQoS);
	Response subscribeMany5(const std::vector<TopicQoS>& topicsAndQoS, const SubscribeOptions& options, const std::vector<Property>& properties);
	void unsubscribeMany(const std::vector<std::string>& topics);
	Response unsubscribeMany5(const std::vector<std::string>& topics, const std::vector<Property>& properties);
	void waitForCompletion(int deliveryToken, int timeout);
	std::vector<int> pendingDeliveryTokens();
	ConnectionInfo connectionInfo() const;

protected:
	enum
	{
		INITIAL_RECONNECT_DELAY = 1000,
		MAXIMUM_RECONNECT_DELAY = 32000
	};

	void connectOnce();
	void reconnect();
	void reconnect5();
	void connectImpl(const ConnectOptions& options);
	void connect5Impl(const ConnectOptions& options, MQTTPropertiesHolder& connectProperties, MQTTPropertiesHolder& willProperties);
	void resubscribe();
	void resubscribe5();

	static void onConnectionLost(void* context, char* cause);
	static void onMessageDelivered(void* context, int token);
	static int onMessageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* message);

private:
	struct Subscription
	{
		int qos = 0;
		SubscribeOptions options;
		std::vector<Property> properties;
	};

	std::string _clientId;
	std::string _serverURI;
	ConnectOptions _options;
	MQTTPropertiesHolder _connectProperties;
	MQTTPropertiesHolder _willProperties;
	long _reconnectDelay;
	std::map<std::string, Subscription> _subscribedTopics;
	std::map<std::string, int> _receivedMessages;
	std::map<std::string, int> _publishedMessages;
	::MQTTClient _mqttClient;
	Poco::Util::Timer _timer;
	ConnectionInfo _connectionInfo;
	bool _pendingReconnect;
	Poco::Logger& _logger;
	mutable Poco::Mutex _mutex;
	mutable Poco::Mutex _statsMutex;

	friend class ReconnectTask;
	friend class Reconnect5Task;
};


//
// inlines
//
inline MQTTProperties& MQTTPropertiesHolder::value()
{
	return _mqttProps;
}


inline const MQTTProperties& MQTTPropertiesHolder::value() const
{
	return _mqttProps;
}


} } // namespace IoT::MQTT


#endif // IoT_MQTT_MQTTClientImpl_INCLUDED
