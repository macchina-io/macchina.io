//
// ROSBridgeClient.cpp
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/ROS/BridgeClient.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/JSON/Parser.h"
#include "Poco/Buffer.h"
#include "Poco/MemoryStream.h"
#include "Poco/SharedPtr.h"
#include "Poco/Format.h"
#include "Poco/UUID.h"
#include "Poco/UUIDGenerator.h"
#include "Poco/Thread.h"


namespace IoT {
namespace ROS {


const std::string BridgeClient::SERVICE_NAME("ros.bridgeClient");


BridgeClient::BridgeClient(const Poco::URI& uri):
	_uri(uri),
	_logger(Poco::Logger::get("ROS.BridgeClient"))
{
}


BridgeClient::~BridgeClient()
{
	if (_pWebSocket)
	{
		try
		{
			unsubscribeAll();
		}
		catch (Poco::Exception&)
		{
		}
		try
		{
			stop();
		}
		catch (Poco::Exception&)
		{
		}
		try
		{
			disconnect();
		}
		catch (Poco::Exception&)
		{
		}
	}
}


void BridgeClient::connect()
{
	Poco::Net::HTTPClientSession session(_uri.getHost(), _uri.getPort());
	Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_GET, _uri.getPathEtc(), Poco::Net::HTTPMessage::HTTP_1_1);
	Poco::Net::HTTPResponse response;
	_pWebSocket = new Poco::Net::WebSocket(session, request, response);
}


void BridgeClient::disconnect()
{
	if (_pWebSocket)
	{
		_pWebSocket->shutdown();
		if (_pWebSocket->poll(Poco::Timespan(2, 0), Poco::Net::Socket::SELECT_READ))
		{
			Poco::Buffer<char> buffer(0);
			int flags = 0;
			_pWebSocket->receiveFrame(buffer, flags);
		}
		_pWebSocket->close();
		_pWebSocket.reset();
	}
}


bool BridgeClient::isConnected() const
{
	return !_pWebSocket.isNull();
}


std::string BridgeClient::subscribe(const std::string& topic)
{
	SubscribeOptions options;
	return subscribe(topic, options);
}


std::string BridgeClient::subscribe(const std::string& topic, const SubscribeOptions& options)
{
	poco_assert (_pWebSocket);

	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string id = subscribeImpl(topic, options);

	_subscriptions[id] = topic;

	return id;
}


void BridgeClient::unsubscribe(const std::string& topic, const std::string& id)
{
	poco_assert (_pWebSocket);

	Poco::FastMutex::ScopedLock lock(_mutex);

	unsubscribeImpl(topic, id);

	_subscriptions.erase(id);
}


Poco::JSON::Object::Ptr BridgeClient::receiveMessage(const Poco::Timespan& timeout)
{
	poco_assert (_pWebSocket);

	Poco::JSON::Object::Ptr pObject;
	if (_pWebSocket->poll(timeout, Poco::Net::Socket::SELECT_READ))
	{
		Poco::Buffer<char> buffer(0);
		int flags = 0;
		int n = _pWebSocket->receiveFrame(buffer, flags);
		if (n > 0)
		{
			Poco::MemoryInputStream stream(buffer.begin(), n);
			Poco::JSON::Parser parser;
			Poco::Dynamic::Var json = parser.parse(stream);
			pObject = json.extract<Poco::JSON::Object::Ptr>();
		}
	}
	return pObject;
}


void BridgeClient::run()
{
	while (!_stopped.tryWait(0))
	{
		try
		{
			Poco::JSON::Object::Ptr pObject = receiveMessage(Poco::Timespan(1, 0));
			if (pObject)
			{
				messageReceived(this, pObject);
			}
		}
		catch (Poco::Exception& exc)
		{
			_logger.log(exc);
		}
	}
}


void BridgeClient::start()
{
	_thread.start(*this);
}


void BridgeClient::stop()
{
	if (_thread.isRunning())
	{
		_stopped.set();
		_thread.join();
	}
}


void BridgeClient::unsubscribeAll()
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	for (const auto& sub: _subscriptions)
	{
		unsubscribeImpl(sub.second, sub.first);
	}
	_subscriptions.clear();
}


const std::type_info& BridgeClient::type() const
{
	return typeid(BridgeClient);
}


bool BridgeClient::isA(const std::type_info& otherType) const
{
	std::string name(typeid(BridgeClient).name());
	return name == otherType.name();
}


std::string BridgeClient::subscribeImpl(const std::string& topic, const SubscribeOptions& options)
{
	_logger.information("Subscribing to '%s'.", topic);

	std::string id = Poco::UUIDGenerator().createOne().toString();
	Poco::JSON::Object::Ptr pRequest = new Poco::JSON::Object;
	pRequest->set("op", std::string("subscribe"));
	pRequest->set("topic", topic);
	pRequest->set("id", id);
	if (!options.type.empty())
		pRequest->set("type", options.type);
	if (options.throttleRate)
		pRequest->set("throttle_rate", options.throttleRate);
	if (options.queueLength)
		pRequest->set("queue_length", options.queueLength);
	if (options.fragmentSize)
		pRequest->set("fragment_size", options.fragmentSize);
	if (!options.compression.empty())
		pRequest->set("compression", options.compression);

	Poco::Buffer<char> buffer(1024);
	Poco::MemoryOutputStream stream(buffer.begin(), buffer.size());
	pRequest->stringify(stream);
	_pWebSocket->sendFrame(buffer.begin(), stream.charsWritten());

	return id;
}


void BridgeClient::unsubscribeImpl(const std::string& topic, const std::string& id)
{
	_logger.information("Unsubscribing from '%s'.", topic);

	Poco::JSON::Object::Ptr pRequest = new Poco::JSON::Object;
	pRequest->set("op", std::string("unsubscribe"));
	pRequest->set("topic", topic);
	if (!id.empty())
		pRequest->set("id", id);

	Poco::Buffer<char> buffer(1024);
	Poco::MemoryOutputStream stream(buffer.begin(), buffer.size());
	pRequest->stringify(stream);
	_pWebSocket->sendFrame(buffer.begin(), stream.charsWritten());
}


} } // namespace IoT::ROS
