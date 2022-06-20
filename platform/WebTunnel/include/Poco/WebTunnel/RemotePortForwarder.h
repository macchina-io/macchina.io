//
// RemotePortForwarder.h
//
// Library: WebTunnel
// Package: WebTunnel
// Module:  RemotePortForwarder
//
// Definition of the LocalPortForwarder class.
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef WebTunnel_RemotePortForwarder_INCLUDED
#define WebTunnel_RemotePortForwarder_INCLUDED


#include "Poco/WebTunnel/WebTunnel.h"
#include "Poco/WebTunnel/SocketDispatcher.h"
#include "Poco/WebTunnel/Protocol.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/SharedPtr.h"
#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/Buffer.h"
#include "Poco/BasicEvent.h"
#include "Poco/Mutex.h"
#include "Poco/Logger.h"
#include <map>
#include <set>


namespace Poco {
namespace WebTunnel {


class WebTunnel_API SocketFactory: public Poco::RefCountedObject
	/// This class is used by RemotePortForwarder to create a StreamSocket
	/// for connecting to the target endpoint.
{
public:
	typedef Poco::AutoPtr<SocketFactory> Ptr;

	SocketFactory();
		/// Creates the SocketFactory.

	virtual ~SocketFactory();
		/// Destroys the SocketFactory.

	virtual Poco::Net::StreamSocket createSocket(const Poco::Net::SocketAddress& addr, Poco::Timespan timeout);
		/// Creates and connects a socket to the given address.
		/// If the socket cannot be connected within the given timeout,
		/// throws a Poco::TimeoutException.
		///
		/// The default implementation always creates a Poco::Net::StreamSocket.
};


class WebTunnel_API RemotePortForwarder
	/// This class forwards one or more ports to a remote host,
	/// using a shared web socket for tunneling the data.
{
public:
	enum CloseReason
	{
		RPF_CLOSE_GRACEFUL   = 0, /// Graceful shutdown, initiated by peer.
		RPF_CLOSE_UNEXPECTED = 1, /// Unexpected shutdown by peer.
		RPF_CLOSE_ERROR      = 2, /// Close due to socket exception.
		RPF_CLOSE_TIMEOUT    = 3, /// Close due to timeout.
	};

	Poco::BasicEvent<const int> webSocketClosed;
		/// Fired when the web socket has been closed.
		///
		/// The event argument will indicate the
		/// reason for the close. See the CloseReason
		/// enum for values and their meanings.

	RemotePortForwarder(SocketDispatcher& dispatcher, Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket, const Poco::Net::IPAddress& host, const std::set<Poco::UInt16>& ports, Poco::Timespan remoteTimeout = Poco::Timespan(300, 0), SocketFactory::Ptr pSocketFactory = new SocketFactory);
		/// Creates the RemotePortForwarder, using the given socket dispatcher and web socket,
		/// which is used for tunneling data. Only the port numbers given in ports will
		/// be forwarded. The web socket must have already been connected to the
		/// reflector server.

	~RemotePortForwarder();
		/// Destroys the RemotePortForwarder and closes the web socket connection.

	void stop();
		/// Stops the RemotePortForwarder.

	void setLocalTimeout(const Poco::Timespan& timeout);
		/// Sets the timeout for the forwarded local ports.

	const Poco::Timespan& getLocalTimeout() const;
		/// Returns the timeout for the forwarded local ports.

	void setConnectTimeout(const Poco::Timespan& timeout);
		/// Sets the timeout for connecting to local ports.

	const Poco::Timespan& getConnectTimeout() const;
		/// Returns the timeout for connecting to local ports.

	const Poco::Timespan& remoteTimeout() const;
		/// Returns the timeout for the remote connection.

	void updateProperties(const std::map<std::string, std::string>& props);
		/// Transmits properties (key-value pairs) to the remote peer.

protected:
	bool multiplex(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, Poco::UInt16 channel, Poco::Buffer<char>& buffer);
	void multiplexError(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, Poco::UInt16 channel, Poco::Buffer<char>& buffer);
	void multiplexTimeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, Poco::UInt16 channel, Poco::Buffer<char>& buffer);
	bool demultiplex(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, Poco::Buffer<char>& buffer);
	void demultiplexError(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, Poco::Buffer<char>& buffer);
	void demultiplexTimeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, Poco::Buffer<char>& buffer);
	bool forwardData(const char* buffer, int size, Poco::UInt16 channel);
	bool openChannel(Poco::UInt16 channel, Poco::UInt16 port);
	void removeChannel(Poco::UInt16 channel);
	void sendResponse(Poco::UInt16 channel, Poco::UInt8 opcode, Poco::UInt16 errorCode);
	void closeWebSocket(CloseReason reason, bool active);
	void pingWebSocket();

private:
	class TunnelMultiplexer: public SocketDispatcher::SocketHandler
	{
	public:
		TunnelMultiplexer(RemotePortForwarder& forwarder, Poco::UInt16 channel):
			_forwarder(forwarder),
			_channel(channel),
			_buffer(Protocol::WT_FRAME_MAX_SIZE + Protocol::WT_FRAME_HEADER_SIZE)
		{
		}

		bool readable(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
		{
			return _forwarder.multiplex(dispatcher, socket, _channel, _buffer);
		}

		void exception(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
		{
			_forwarder.multiplexError(dispatcher, socket, _channel, _buffer);
		}

		void timeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
		{
			_forwarder.multiplexTimeout(dispatcher, socket, _channel, _buffer);
		}

	private:
		RemotePortForwarder& _forwarder;
		Poco::UInt16 _channel;
		Poco::Buffer<char> _buffer;
	};

	class TunnelDemultiplexer: public SocketDispatcher::SocketHandler
	{
	public:
		TunnelDemultiplexer(RemotePortForwarder& forwarder):
			_forwarder(forwarder),
			_buffer(Protocol::WT_FRAME_MAX_SIZE + Protocol::WT_FRAME_HEADER_SIZE)
		{
		}

		bool readable(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
		{
			return _forwarder.demultiplex(dispatcher, socket, _buffer);
		}

		void exception(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
		{
			_forwarder.demultiplexError(dispatcher, socket, _buffer);
		}

		void timeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
		{
			_forwarder.demultiplexTimeout(dispatcher, socket, _buffer);
		}

	private:
		RemotePortForwarder& _forwarder;
		Poco::Buffer<char> _buffer;
	};

	typedef std::map<Poco::UInt16, Poco::Net::StreamSocket> ChannelMap;

	SocketDispatcher& _dispatcher;
	SocketFactory::Ptr _pSocketFactory;
	Poco::SharedPtr<Poco::Net::WebSocket> _pWebSocket;
	Poco::FastMutex _webSocketMutex;
	Poco::Net::IPAddress _host;
	std::set<Poco::UInt16> _ports;
	ChannelMap _channelMap;
	Poco::Timespan _connectTimeout;
	Poco::Timespan _localTimeout;
	Poco::Timespan _remoteTimeout;
	bool _timeoutCount;
	Poco::FastMutex _mutex;
	Poco::Logger& _logger;

	RemotePortForwarder();
	RemotePortForwarder(const RemotePortForwarder&);
	RemotePortForwarder& operator = (const RemotePortForwarder&);

	friend class TunnelMultiplexer;
	friend class TunnelDemultiplexer;
};


} } // namespace Poco::WebTunnel


#endif // WebTunnel_RemotePortForwarder_INCLUDED
