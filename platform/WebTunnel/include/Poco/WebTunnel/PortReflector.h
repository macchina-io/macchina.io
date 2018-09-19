//
// PortReflector.h
//
// Library: WebTunnel
// Package: WebTunnel
// Module:  PortReflector
//
// Definition of the PortReflector class.
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef WebTunnel_PortReflector_INCLUDED
#define WebTunnel_PortReflector_INCLUDED


#include "Poco/WebTunnel/WebTunnel.h"
#include "Poco/WebTunnel/SocketDispatcher.h"
#include "Poco/WebTunnel/TunnelSocket.h"
#include "Poco/WebTunnel/Protocol.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/SharedPtr.h"
#include "Poco/AutoPtr.h"
#include "Poco/RefCountedObject.h"
#include "Poco/BasicEvent.h"
#include "Poco/Buffer.h"
#include "Poco/Mutex.h"
#include "Poco/Event.h"
#include "Poco/Logger.h"
#include <map>


namespace Poco {
namespace WebTunnel {


class WebTunnel_API PortReflector
	/// This class forwards frames from a LocalPortForwarder
	/// WebSocket connection to RemotePortForwarder WebSocket
	/// connection and vice versa.
{
public:
	Poco::BasicEvent<const std::string> serverConnected;
		/// Fired when a server has connected.

	Poco::BasicEvent<const std::string> serverDisconnected;
		/// Fired when a server has disconnected.

	PortReflector(int threadCount, Poco::Timespan dispatcherTimeout = Poco::Timespan(5000), int maxReadsPerWorker = 10);
		/// Creates the PortReflector, using the given number of worker threads.
		///
		/// The given dispatcherTimeout is used for the SocketDispatcher's main select loop, as well as
		/// by workers to poll if more reads are possible, up to the given maximum number of reads per worker.

	~PortReflector();
		/// Destroys the PortReflector.
		///
		/// All open WebSocket connections will be closed.

	void addWebSocket(Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket, const std::string& targetId, Poco::UInt16 targetPort);
		/// Adds a client WebSocket connection for forwarding to the given target device and port.
		///
		/// The socket will be managed by the PortReflector until closed by the peer.

	void addStreamSocket(Poco::SharedPtr<Poco::Net::StreamSocket> pStreamSocket, const std::string& targetId, Poco::UInt16 targetPort, const std::string& initialMessage);
		/// Adds a client StreamSocket connection for forwarding to the given target device and port.
		/// As soon as the tunnel connection is established, the initialMessage is sent to the peer.
		///
		/// The socket will be managed by the PortReflector until closed by the peer.

	TunnelSocket openTunnelSocket(const std::string& targetId, Poco::UInt16 targetPort);
		/// Creates and returns a TunnelSocket for the given target and port number.

	void addServerSocket(Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket, const std::string& targetId);
		/// Adds a server WebSocket connection for forwarding to the given target device.
		///
		/// The WebSocket will be managed by the PortReflector until closed by the peer.

	void removeServerSocket(const std::string& targetId, const std::string& reason);
		/// Shuts down and removes the WebSocket connection for forwarding to the given
		/// target device.

	int countConnections() const;
		/// Returns the number of currently active connections.

	void setClientTimeout(Poco::Timespan timeout);
		/// Sets the timeout for client connections.

	Poco::Timespan getClientTimeout() const;
		/// Returns the timeout for client connections.

	void setServerTimeout(Poco::Timespan timeout);
		/// Sets the timeout for server/agent connections.

	Poco::Timespan getServerTimeout() const;
		/// Returns the timeout for server/agent connections.

protected:
	enum
	{
		MAX_CHANNELS = 256
	};

	enum ChannelState
	{
		CS_CONNECTING,
		CS_CONNECTED,
		CS_DISCONNECTED,
		CS_ERROR
	};

	enum TargetState
	{
		TS_CONNECTED,
		TS_DISCONNECTED
	};

	enum
	{
		CONNECT_TIMEOUT = 60000
	};

	struct ChannelInfo: public Poco::RefCountedObject
	{
		typedef Poco::AutoPtr<ChannelInfo> Ptr;

		ChannelState state;
		Poco::Event stateChanged;
		Poco::UInt16 channel;
		Poco::SharedPtr<Poco::Net::StreamSocket> pSocket;
		Poco::FastMutex socketMutex;
		Poco::SharedPtr<TunnelSocket> pTunnelSocket;
		std::string initialMessage;
	};
	typedef std::map<Poco::UInt16, ChannelInfo::Ptr> ChannelMap;

	struct TargetInfo: public Poco::RefCountedObject
	{
		typedef Poco::AutoPtr<TargetInfo> Ptr;

		std::string id;
		TargetState state;
		ChannelMap channelMap;
		Poco::UInt16 lastChannel;
		Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket;
		Poco::FastMutex webSocketMutex;
		Poco::FastMutex mutex;
	};

	typedef std::map<std::string, TargetInfo::Ptr> TargetMap;

	bool multiplexWebSocket(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, TargetInfo::Ptr pTargetInfo, ChannelInfo::Ptr pChannelInfo, Poco::Buffer<char>& buffer);
	bool multiplexStreamSocket(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, TargetInfo::Ptr pTargetInfo, ChannelInfo::Ptr pChannelInfo, Poco::Buffer<char>& buffer);
	void multiplexError(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, TargetInfo::Ptr pTargetInfo, ChannelInfo::Ptr pChannelInfo, Poco::Buffer<char>& buffer);
	void multiplexTimeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, TargetInfo::Ptr pTargetInfo, ChannelInfo::Ptr pChannelInfo, Poco::Buffer<char>& buffer);
	bool demultiplex(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, TargetInfo::Ptr pTargetInfo, Poco::Buffer<char>& buffer);
	void demultiplexError(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, TargetInfo::Ptr pTargetInfo, Poco::Buffer<char>& buffer);
	void demultiplexTimeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, TargetInfo::Ptr pTargetInfo, Poco::Buffer<char>& buffer);

	class WebSocketTunnelMultiplexer: public SocketDispatcher::SocketHandler
	{
	public:
		WebSocketTunnelMultiplexer(PortReflector& reflector, TargetInfo::Ptr pTargetInfo, ChannelInfo::Ptr pChannelInfo):
			_reflector(reflector),
			_pTargetInfo(pTargetInfo),
			_pChannelInfo(pChannelInfo),
			_buffer(Protocol::WT_FRAME_MAX_SIZE + Protocol::WT_FRAME_HEADER_SIZE)
		{
		}

		bool readable(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
		{
			return _reflector.multiplexWebSocket(dispatcher, socket, _pTargetInfo, _pChannelInfo, _buffer);
		}

		void exception(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
		{
			_reflector.multiplexError(dispatcher, socket, _pTargetInfo, _pChannelInfo, _buffer);
		}

		void timeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
		{
			return _reflector.multiplexTimeout(dispatcher, socket, _pTargetInfo, _pChannelInfo, _buffer);
		}

	private:
		PortReflector& _reflector;
		TargetInfo::Ptr _pTargetInfo;
		ChannelInfo::Ptr _pChannelInfo;
		Poco::Buffer<char> _buffer;
	};

	class StreamSocketTunnelMultiplexer: public SocketDispatcher::SocketHandler
	{
	public:
		StreamSocketTunnelMultiplexer(PortReflector& reflector, TargetInfo::Ptr pTargetInfo, ChannelInfo::Ptr pChannelInfo):
			_reflector(reflector),
			_pTargetInfo(pTargetInfo),
			_pChannelInfo(pChannelInfo),
			_buffer(Protocol::WT_FRAME_MAX_SIZE + Protocol::WT_FRAME_HEADER_SIZE)
		{
		}

		bool readable(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
		{
			return _reflector.multiplexStreamSocket(dispatcher, socket, _pTargetInfo, _pChannelInfo, _buffer);
		}

		void exception(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
		{
			_reflector.multiplexError(dispatcher, socket, _pTargetInfo, _pChannelInfo, _buffer);
		}

		void timeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
		{
			return _reflector.multiplexTimeout(dispatcher, socket, _pTargetInfo, _pChannelInfo, _buffer);
		}

	private:
		PortReflector& _reflector;
		TargetInfo::Ptr _pTargetInfo;
		ChannelInfo::Ptr _pChannelInfo;
		Poco::Buffer<char> _buffer;
	};

	class TunnelDemultiplexer: public SocketDispatcher::SocketHandler
	{
	public:
		TunnelDemultiplexer(PortReflector& reflector, TargetInfo::Ptr pTargetInfo):
			_reflector(reflector),
			_pTargetInfo(pTargetInfo),
			_buffer(Protocol::WT_FRAME_MAX_SIZE + Protocol::WT_FRAME_HEADER_SIZE)
		{
		}

		bool readable(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
		{
			return _reflector.demultiplex(dispatcher, socket, _pTargetInfo, _buffer);
		}

		void exception(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
		{
			_reflector.demultiplexError(dispatcher, socket, _pTargetInfo, _buffer);
		}

		void timeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
		{
			_reflector.demultiplexTimeout(dispatcher, socket, _pTargetInfo, _buffer);
		}

	private:
		PortReflector& _reflector;
		TargetInfo::Ptr _pTargetInfo;
		Poco::Buffer<char> _buffer;
	};

	bool abortTarget(TargetInfo::Ptr pTargetInfo, const std::string& reason);
	void removeTarget(TargetInfo::Ptr pTargetInfo, const std::string& reason);
	void shutdownChannel(TargetInfo::Ptr pTargetInfo, ChannelInfo::Ptr pChannelInfo);
	void openChannel(TargetInfo::Ptr pTargetInfo, Poco::UInt16 channel, Poco::UInt16 port);
	void closeChannel(TargetInfo::Ptr pTargetInfo, Poco::UInt16 channel);
	bool confirmOpenChannel(TargetInfo::Ptr pTargetInfo, Poco::UInt16 channel);
	void confirmCloseChannel(TargetInfo::Ptr pTargetInfo, Poco::UInt16 channel, Poco::UInt16 errorCode = Protocol::WT_ERR_NONE);
	bool forwardData(const char* buffer, std::size_t size, TargetInfo::Ptr pTargetInfo, Poco::UInt16 channel);
	bool sendInitialMessage(TargetInfo::Ptr pTargetInfo, Poco::UInt16 channel);

	SocketDispatcher _dispatcher;
	TargetMap _targetMap;
	Poco::Timespan _clientTimeout;
	Poco::Timespan _serverTimeout;
	mutable Poco::FastMutex _mutex;
	Poco::Logger& _logger;

	friend class TunnelMultiplexer;
	friend class TunnelDemultiplexer;
	friend class TunnelSocketImpl;
};


//
// inlines
//
inline int PortReflector::countConnections() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return static_cast<int>(_targetMap.size());
}


inline Poco::Timespan PortReflector::getClientTimeout() const
{
	return _clientTimeout;
}


inline Poco::Timespan PortReflector::getServerTimeout() const
{
	return _serverTimeout;
}


} } // namespace Poco::WebTunnel


#endif // WebTunnel_LocalPortForwarder_INCLUDED
