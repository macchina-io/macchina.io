//
// BridgeClient.h
//
// A client for ROS bridge.
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_ROS_BridgeClient_INCLUDED
#define IoT_ROS_BridgeClient_INCLUDED


#include "IoT/ROS/ROS.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/JSON/Object.h"
#include "Poco/OSP/Service.h"
#include "Poco/URI.h"
#include "Poco/BasicEvent.h"
#include "Poco/AutoPtr.h"
#include "Poco/SharedPtr.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Event.h"
#include "Poco/Mutex.h"
#include "Poco/Logger.h"


namespace IoT {
namespace ROS {


class IoTROS_API BridgeClient: public Poco::OSP::Service, public Poco::Runnable
{
public:
	typedef Poco::AutoPtr<BridgeClient> Ptr;

	struct SubscribeOptions
	{
		std::string type;
		int throttleRate = 0;
		int queueLength = 0;
		int fragmentSize = 0;
		std::string compression;
	};

	Poco::BasicEvent<const Poco::JSON::Object::Ptr> messageReceived;
		/// Fired when an event message has been received.

	BridgeClient(const Poco::URI& uri);
		/// Creates the BridgeClient for the given URI.

	~BridgeClient();
		/// Destroys the BridgeClient.

	void connect();

	void disconnect();

	bool isConnected() const;

	std::string subscribe(const std::string& topic);

	std::string subscribe(const std::string& topic, const SubscribeOptions& options);

	void unsubscribe(const std::string& topic, const std::string& id = std::string());

	void unsubscribeAll();

	Poco::JSON::Object::Ptr receiveMessage(const Poco::Timespan& timeout);

	void start();

	void stop();

	// Service
	const std::type_info& type() const;
	bool isA(const std::type_info& otherType) const;

	// Runnable
	void run();

	static const std::string SERVICE_NAME;

protected:
	std::string subscribeImpl(const std::string& topic, const SubscribeOptions& options);
	void unsubscribeImpl(const std::string& topic, const std::string& id);

private:
	Poco::URI _uri;
	Poco::SharedPtr<Poco::Net::WebSocket> _pWebSocket;
	Poco::Thread _thread;
	Poco::Event _stopped;
	Poco::Logger& _logger;
	std::map<std::string, std::string> _subscriptions;
	Poco::FastMutex _mutex;
};


} } // namespace IoT::ROS


#endif // IoT_ROS_BridgeClient_INCLUDED
