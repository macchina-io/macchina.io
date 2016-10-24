//
// MQTTClientImpl.h
//
// $Id$
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
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_MQTT_MQTTClientImpl_INCLUDED
#define IoT_MQTT_MQTTClientImpl_INCLUDED


#include "IoT/MQTT/MQTTClient.h"
#include "Poco/Util/Timer.h"
#include "Poco/Logger.h"
#include "Poco/Mutex.h"
#include "Poco/ScopedUnlock.h"
#include <map>


extern "C" {
#include "MQTTClient.h"
}


namespace IoT {
namespace MQTT {


class IoTMQTT_API MQTTClientImpl: public IoT::MQTT::MQTTClient
	/// The default implementation of MQTTClient based on paho.
{
public:
	typedef Poco::SharedPtr<MQTTClientImpl> Ptr;

	struct ConnectOptions
	{
		int keepAliveInterval;
			/// Keep-alive interval in seconds.
	
		int retryInterval;
			/// Retry interval in seconds.
		
		int connectTimeout;
			/// Connect timeout in seconds.

		bool cleanSession;
			/// Start with a clean session.
			
		bool reliable;
			/// If set to true, only one message at a time can be "in flight".

		std::string username;
			/// Username for MQTT v3.1.

		std::string password;
			/// Password for MQTT v3.1.
	
		std::string willTopic;
			/// Last will topic name.
	
		std::string willMessage;
			/// Last will message.

		bool willRetained;
			/// Retained flag for will message.
	
		int willQoS;
			/// Quality of Service level for will message (0-2).
	
		std::vector<std::string> serverURIs;
			/// Optional list of server URIs.

		int mqttVersion;
			/// Sets the version of MQTT to be used on the connect. Valid values are
			/// 0, 3 and 4.
			///   * 0 = default: start with 3.1.1, and if that fails, fall back to 3.1 
			///   * 3 = only try version 3.1  
			///   * 4 = only try version 3.1.1
			
		std::string sslTrustStore;
			/// The file in PEM format containing the public digital certificates trusted by the client.
		
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
			
		bool sslEnableServerCertAuth;
			/// Enable or disable verification of the server certificate.
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
		/// For SQLite-based persistence, the path should specify a SQLite database file.

	~MQTTClientImpl();
		/// Destroys the MQTTClientImpl.
	
	// MQTTClient
	const std::string& id() const;
	const std::string& serverURI() const;
	bool connected() const;
	ConnectionInfo connect();
	void connectAsync();
	void disconnect(int timeout);
	std::vector<TopicQoS> subscribedTopics() const;
	Statistics statistics() const;
	int publish(const std::string& topic, const std::string& payload, int qos);
	int publishMessage(const std::string& topic, const Message& message);
	void subscribe(const std::string& topic, int qos);
	void unsubscribe(const std::string& topic);
	void subscribeMany(const std::vector<TopicQoS>& topicsAndQoS);
	void unsubscribeMany(const std::vector<std::string>& topics);
	ConnectionInfo connectionInfo() const;
	
protected:
	enum 
	{
		INITIAL_RECONNECT_DELAY = 1000,
		MAXIMUM_RECONNECT_DELAY = 32000
	};
	
	void connectOnce();
	void reconnect();
	void connectImpl(const ConnectOptions& options);
	void resubscribe();

	static std::string errorMessage(int code);
	static void onConnectionLost(void* context, char* cause);
	static void onMessageDelivered(void* context, int token);
	static int onMessageArrived(void* context, char* topicName, int topicLen, MQTTClient_message* message);
	
private:
	std::string _clientId;
	std::string _serverURI;
	ConnectOptions _options;
	long _reconnectDelay;
	std::map<std::string, int> _subscribedTopics;
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
};


} } // namespace IoT::MQTT


#endif // IoT_MQTT_MQTTClientImpl_INCLUDED
