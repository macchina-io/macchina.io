//
// PortReflector.cpp
//
// Library: WebTunnel
// Package: WebTunnel
// Module:  PortReflector
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/WebTunnel/PortReflector.h"
#include "Poco/WebTunnel/TunnelSocketImpl.h"
#include "Poco/Net/WebSocketImpl.h"
#include "Poco/Format.h"


namespace Poco {
namespace WebTunnel {


void shutdownSocket(Poco::Net::StreamSocket& socket, Poco::UInt16 statusCode)
{
	if (dynamic_cast<Poco::Net::WebSocketImpl*>(socket.impl()))
	{
		Poco::Net::WebSocket webSocket(socket);
		webSocket.shutdown(statusCode);
	}
	socket.shutdownSend();
}


PortReflector::PortReflector(int threadCount, Poco::Timespan dispatcherTimeout, int maxReadsPerWorker):
	_dispatcher(threadCount, dispatcherTimeout, maxReadsPerWorker),
	_logger(Poco::Logger::get("WebTunnel.PortReflector"))
{
}


PortReflector::~PortReflector()
{
	try
	{
		for (TargetMap::iterator it = _targetMap.begin(); it != _targetMap.end(); ++it)
		{
			abortTarget(it->second, "shutting down");
		}
		_dispatcher.stop();
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void PortReflector::addWebSocket(Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket, const std::string& targetId, Poco::UInt16 targetPort)
{
	if (_logger.debug())
	{
		_logger.debug("Adding client connection for target %s, port %hu", targetId, targetPort);
	}

	Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);

	TargetMap::iterator it = _targetMap.find(targetId);
	if (it != _targetMap.end())
	{
		TargetInfo::Ptr pTargetInfo = it->second;
		lock.unlock();
		Poco::ScopedLockWithUnlock<Poco::FastMutex> targetLock(pTargetInfo->mutex);
		if (pTargetInfo->channelMap.size() >= MAX_CHANNELS)
		{
			throw Poco::RuntimeException("Too many channels for target", targetId);
		}
		Poco::UInt16 channel = pTargetInfo->lastChannel + 1;
		while (pTargetInfo->channelMap.find(channel) != pTargetInfo->channelMap.end())
		{
			channel++;
		}
		pTargetInfo->lastChannel = channel;
		ChannelInfo::Ptr pChannelInfo = new ChannelInfo;
		pChannelInfo->state = CS_CONNECTING;
		pChannelInfo->channel = channel;
		pChannelInfo->pSocket = pWebSocket;
		pChannelInfo->pTunnelSocket = 0;
		pTargetInfo->channelMap[channel] = pChannelInfo;
		if (_logger.debug())
		{
			_logger.debug("Now %z channels to target %s", pTargetInfo->channelMap.size(), targetId);
		}
		targetLock.unlock();

		pWebSocket->setNoDelay(true);
		_dispatcher.addSocket(*pWebSocket, new WebSocketTunnelMultiplexer(*this, pTargetInfo, pChannelInfo), _clientTimeout);
		openChannel(pTargetInfo, channel, targetPort);
	}
	else throw Poco::NotFoundException(targetId);
}


void PortReflector::addStreamSocket(Poco::SharedPtr<Poco::Net::StreamSocket> pStreamSocket, const std::string& targetId, Poco::UInt16 targetPort, const std::string& initialMessage)
{
	if (_logger.debug())
	{
		_logger.debug("Adding stream socket connection for target %s, port %hu", targetId, targetPort);
	}

	Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);

	TargetMap::iterator it = _targetMap.find(targetId);
	if (it != _targetMap.end())
	{
		TargetInfo::Ptr pTargetInfo = it->second;
		lock.unlock();
		Poco::ScopedLockWithUnlock<Poco::FastMutex> targetLock(pTargetInfo->mutex);
		if (pTargetInfo->channelMap.size() >= MAX_CHANNELS)
		{
			throw Poco::RuntimeException("Too many channels for target", targetId);
		}
		Poco::UInt16 channel = pTargetInfo->lastChannel + 1;
		while (pTargetInfo->channelMap.find(channel) != pTargetInfo->channelMap.end())
		{
			channel++;
		}
		pTargetInfo->lastChannel = channel;
		ChannelInfo::Ptr pChannelInfo = new ChannelInfo;
		pChannelInfo->state = CS_CONNECTING;
		pChannelInfo->channel = channel;
		pChannelInfo->pSocket = pStreamSocket;
		pChannelInfo->pTunnelSocket = 0;
		pChannelInfo->initialMessage = initialMessage;
		pTargetInfo->channelMap[channel] = pChannelInfo;
		if (_logger.debug())
		{
			_logger.debug("Now %z channels to target %s", pTargetInfo->channelMap.size(), targetId);
		}
		targetLock.unlock();

		pStreamSocket->setNoDelay(true);
		_dispatcher.addSocket(*pStreamSocket, new StreamSocketTunnelMultiplexer(*this, pTargetInfo, pChannelInfo), _clientTimeout);
		openChannel(pTargetInfo, channel, targetPort);
	}
	else throw Poco::NotFoundException(targetId);
}


TunnelSocket PortReflector::openTunnelSocket(const std::string& targetId, Poco::UInt16 targetPort)
{
	if (_logger.information())
	{
		_logger.information("Creating TunnelSocket for target %s, port %hu", targetId, targetPort);
	}

	Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);

	TargetMap::iterator it = _targetMap.find(targetId);
	if (it != _targetMap.end())
	{
		TargetInfo::Ptr pTargetInfo = it->second;
		lock.unlock();
		Poco::ScopedLockWithUnlock<Poco::FastMutex> targetLock(pTargetInfo->mutex);
		if (pTargetInfo->channelMap.size() >= MAX_CHANNELS)
		{
			_logger.error("Too many channels for target: " + targetId);
			throw Poco::RuntimeException("Too many channels for target", targetId);
		}
		Poco::UInt16 channel = pTargetInfo->lastChannel + 1;
		while (pTargetInfo->channelMap.find(channel) != pTargetInfo->channelMap.end())
		{
			channel++;
		}
		pTargetInfo->lastChannel = channel;
		ChannelInfo::Ptr pChannelInfo = new ChannelInfo;
		pChannelInfo->state = CS_CONNECTING;
		pChannelInfo->channel = channel;
		pChannelInfo->pTunnelSocket = new TunnelSocket(new TunnelSocketImpl(*this, pTargetInfo, pChannelInfo));
		pTargetInfo->channelMap[channel] = pChannelInfo;
		if (_logger.debug())
		{
			_logger.debug("Now %z channels to target %s", pTargetInfo->channelMap.size(), targetId);
		}
		targetLock.unlock();

		openChannel(pTargetInfo, channel, targetPort);

		return *pChannelInfo->pTunnelSocket;
	}
	else throw Poco::NotFoundException(targetId);
}


void PortReflector::addServerSocket(Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket, const std::string& targetId)
{
	if (_logger.information())
	{
		_logger.information("Adding server connection to target %s", targetId);
	}
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		TargetMap::iterator it = _targetMap.find(targetId);
		if (it != _targetMap.end())
		{
			abortTarget(it->second, "device reconnected");
			_targetMap.erase(it);
		}

		TargetInfo::Ptr pTargetInfo = new TargetInfo;
		pTargetInfo->pWebSocket = pWebSocket;
		pTargetInfo->id = targetId;
		pTargetInfo->state = TS_CONNECTED;
		pTargetInfo->lastChannel = 0;
		_targetMap[targetId] = pTargetInfo;
		_dispatcher.addSocket(*pWebSocket, new TunnelDemultiplexer(*this, pTargetInfo), _serverTimeout);
	}
	serverConnected(this, targetId);
}


void PortReflector::removeServerSocket(const std::string& targetId, const std::string& reason)
{
	TargetInfo::Ptr pTargetInfo;
	{
		TargetMap::iterator it = _targetMap.find(targetId);
		if (it != _targetMap.end())
		{
			pTargetInfo = it->second;
		}
	}

	if (pTargetInfo)
	{
		removeTarget(pTargetInfo, reason);
	}
}


void PortReflector::setClientTimeout(Poco::Timespan timeout)
{
	_clientTimeout = timeout;
}


void PortReflector::setServerTimeout(Poco::Timespan timeout)
{
	_serverTimeout = timeout;
}


bool PortReflector::multiplexWebSocket(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, TargetInfo::Ptr pTargetInfo, ChannelInfo::Ptr pChannelInfo, Poco::Buffer<char>& buffer)
{
	bool expectMore = true;
	Poco::Net::WebSocket webSocket(socket);
	std::size_t hn = Protocol::writeHeader(buffer.begin(), buffer.size(), Protocol::WT_OP_DATA, 0, pChannelInfo->channel);
	int n = 0;
	try
	{
		int flags;
		n = webSocket.receiveFrame(buffer.begin() + hn, static_cast<int>(buffer.size() - hn), flags);
		if (n >= 0 && (flags & Poco::Net::WebSocket::FRAME_OP_BITMASK) == Poco::Net::WebSocket::FRAME_OP_PING)
		{
			_logger.debug("PING received from client");
			Poco::FastMutex::ScopedLock lock(pTargetInfo->webSocketMutex);
			webSocket.sendFrame(buffer.begin() + hn, n, Poco::Net::WebSocket::FRAME_FLAG_FIN | Poco::Net::WebSocket::FRAME_OP_PONG);
			return false;
		}
		else if (n <= 0 || (flags & Poco::Net::WebSocket::FRAME_OP_BITMASK) == Poco::Net::WebSocket::FRAME_OP_CLOSE)
		{
			_logger.debug("Client WebSocket closed by peer");
			if (pChannelInfo->pSocket)
			{
				_dispatcher.removeSocket(*pChannelInfo->pSocket);
			}
			if (pChannelInfo->state == CS_CONNECTED)
			{
				if (_logger.debug())
				{
					_logger.debug("Actively closing channel %hu to target %s", pChannelInfo->channel, pTargetInfo->id);
				}
				shutdownChannel(pTargetInfo, pChannelInfo);
				return false;
			}
			else return false;
		}
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Error reading from client WebSocket for channel %hu on target %s: %s", pChannelInfo->channel, pTargetInfo->id, exc.displayText());
		shutdownChannel(pTargetInfo, pChannelInfo);
		expectMore = false;
	}

	while (n > 0 && pChannelInfo->state == CS_CONNECTING)
	{
		_logger.debug("Waiting for channel to be ready...");
		if (!pChannelInfo->stateChanged.tryWait(CONNECT_TIMEOUT))
		{
			pChannelInfo->state = CS_ERROR;
			removeTarget(pTargetInfo, "connect timeout");
			throw Poco::TimeoutException();
		}
	}

	if (n > 0 && pChannelInfo->state != CS_CONNECTED)
	{
		_logger.warning("Ignoring data for unconnected channel %hu to target %s", pChannelInfo->channel, pTargetInfo->id);
		return false;
	}

	try
	{
		Poco::FastMutex::ScopedLock lock(pTargetInfo->webSocketMutex);
		pTargetInfo->pWebSocket->sendFrame(buffer.begin(), static_cast<int>(n + hn), Poco::Net::WebSocket::FRAME_BINARY);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Error sending WebSocket frame for channel %hu to target %s: %s", pChannelInfo->channel, pTargetInfo->id, exc.displayText());
		removeTarget(pTargetInfo, "send frame error");
		expectMore = false;
	}
	return expectMore;
}


bool PortReflector::multiplexStreamSocket(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, TargetInfo::Ptr pTargetInfo, ChannelInfo::Ptr pChannelInfo, Poco::Buffer<char>& buffer)
{
	bool expectMore = true;
	std::size_t hn = Protocol::writeHeader(buffer.begin(), buffer.size(), Protocol::WT_OP_DATA, 0, pChannelInfo->channel);
	int n = 0;
	try
	{
		n = socket.receiveBytes(buffer.begin() + hn, static_cast<int>(buffer.size() - hn));
		if (n == 0)
		{
			_logger.debug("Client StreamSocket closed by peer");
			if (pChannelInfo->pSocket)
			{
				_dispatcher.removeSocket(*pChannelInfo->pSocket);
			}
			if (pChannelInfo->state == CS_CONNECTED)
			{
				if (_logger.debug())
				{
					_logger.debug("Actively closing channel %hu to target %s", pChannelInfo->channel, pTargetInfo->id);
				}
				shutdownChannel(pTargetInfo, pChannelInfo);
				return false;
			}
			else return false;
		}
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Error reading from client stream socket for channel %hu on target %s: %s", pChannelInfo->channel, pTargetInfo->id, exc.displayText());
		shutdownChannel(pTargetInfo, pChannelInfo);
		expectMore = false;
	}

	while (n > 0 && pChannelInfo->state == CS_CONNECTING)
	{
		_logger.debug("Waiting for channel to be ready...");
		if (!pChannelInfo->stateChanged.tryWait(CONNECT_TIMEOUT))
		{
			pChannelInfo->state = CS_ERROR;
			removeTarget(pTargetInfo, "connect timeout");
			throw Poco::TimeoutException();
		}
	}

	if (n > 0 && pChannelInfo->state != CS_CONNECTED)
	{
		_logger.warning("Ignoring data for unconnected channel %hu to target %s", pChannelInfo->channel, pTargetInfo->id);
		return false;
	}

	try
	{
		Poco::FastMutex::ScopedLock lock(pTargetInfo->webSocketMutex);
		pTargetInfo->pWebSocket->sendFrame(buffer.begin(), static_cast<int>(n + hn), Poco::Net::WebSocket::FRAME_BINARY);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Error sending WebSocket frame for channel %hu to target %s: %s", pChannelInfo->channel, pTargetInfo->id, exc.displayText());
		removeTarget(pTargetInfo, "send frame error");
		expectMore = false;
	}
	return expectMore;
}


void PortReflector::multiplexError(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, TargetInfo::Ptr pTargetInfo, ChannelInfo::Ptr pChannelInfo, Poco::Buffer<char>& buffer)
{
	_logger.error("Error receiving from client socket for channel %hu, target %s", pChannelInfo->channel, pTargetInfo->id);
	shutdownChannel(pTargetInfo, pChannelInfo);
}


void PortReflector::multiplexTimeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, TargetInfo::Ptr pTargetInfo, ChannelInfo::Ptr pChannelInfo, Poco::Buffer<char>& buffer)
{
	_logger.error("Timeout receiving from client socket for channel %hu, target %s", pChannelInfo->channel, pTargetInfo->id);
	shutdownChannel(pTargetInfo, pChannelInfo);
}


bool PortReflector::demultiplex(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, TargetInfo::Ptr pTargetInfo, Poco::Buffer<char>& buffer)
{
	int wsFlags;
	int n = 0;
	try
	{
		n = pTargetInfo->pWebSocket->receiveFrame(buffer.begin(), static_cast<int>(buffer.size()), wsFlags);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Error receiving WebSocket frame for target %s: %s", pTargetInfo->id, exc.displayText());
		removeTarget(pTargetInfo, "receive frame error");
		return false;
	}
	if (n >= 0 && (wsFlags & Poco::Net::WebSocket::FRAME_OP_BITMASK) == Poco::Net::WebSocket::FRAME_OP_PING)
	{
		try
		{
			if (_logger.debug())
			{
				_logger.debug("Received PING from " + pTargetInfo->id);
			}
			Poco::FastMutex::ScopedLock lock(pTargetInfo->webSocketMutex);
			pTargetInfo->pWebSocket->sendFrame(buffer.begin(), n, Poco::Net::WebSocket::FRAME_FLAG_FIN | Poco::Net::WebSocket::FRAME_OP_PONG);
			return false;
		}
		catch (Poco::Exception& exc)
		{
			_logger.error("Error sending PONG to %s: %s", pTargetInfo->id, exc.displayText());
			return false;
		}
	}
	else if (n > 0 && (wsFlags & Poco::Net::WebSocket::FRAME_OP_BITMASK) == Poco::Net::WebSocket::FRAME_OP_BINARY)
	{
		Poco::UInt8 opcode;
		Poco::UInt8 flags;
		Poco::UInt16 channel;
		Poco::UInt16 portOrErrorCode;
		std::size_t hn = Protocol::readHeader(buffer.begin(), buffer.size(), opcode, flags, channel, &portOrErrorCode);
		switch (opcode)
		{
		case Protocol::WT_OP_DATA:
			return forwardData(buffer.begin() + hn, n - hn, pTargetInfo, channel);
			return true;

		case Protocol::WT_OP_OPEN_CONFIRM:
			if (confirmOpenChannel(pTargetInfo, channel))
				return sendInitialMessage(pTargetInfo, channel);
			else
				return false;

		case Protocol::WT_OP_OPEN_FAULT:
			_logger.error("Failed to open channel %hu (status code %hu) to target %s", channel, portOrErrorCode, pTargetInfo->id);
			confirmCloseChannel(pTargetInfo, channel, portOrErrorCode);
			return false;

		case Protocol::WT_OP_CLOSE:
			confirmCloseChannel(pTargetInfo, channel);
			return false;

		case Protocol::WT_OP_ERROR:
			if (_logger.debug())
			{
				_logger.debug("Status %hu reported by peer. Closing channel %hu to target %s.", portOrErrorCode, channel, pTargetInfo->id);
			}
			confirmCloseChannel(pTargetInfo, channel, portOrErrorCode);
			return false;

		default:
			_logger.error("Invalid WebSocket frame received (bad channel opcode: %hu) for target %s.", static_cast<Poco::UInt16>(opcode), pTargetInfo->id);
			removeTarget(pTargetInfo, "invalid frame received");
			return false;
		}
	}
	else if (n <= 0 || (wsFlags & Poco::Net::WebSocket::FRAME_OP_BITMASK) == Poco::Net::WebSocket::FRAME_OP_CLOSE)
	{
		if (_logger.debug())
		{
			_logger.debug("Target WebSocket to %s closed by peer", pTargetInfo->id);
		}
		removeTarget(pTargetInfo, "websocket closed by peer");
		return false;
	}
	else
	{
		_logger.debug("Ignoring unsupported frame type");
		return false;
	}
}


void PortReflector::demultiplexError(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, TargetInfo::Ptr pTargetInfo, Poco::Buffer<char>& buffer)
{
	_logger.error("Error reading from tunnel to target %s", pTargetInfo->id);
	removeTarget(pTargetInfo, "tunnel error");
}


void PortReflector::demultiplexTimeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, TargetInfo::Ptr pTargetInfo, Poco::Buffer<char>& buffer)
{
	_logger.error("Timeout reading from tunnel to target %s", pTargetInfo->id);
	removeTarget(pTargetInfo, "tunnel timeout");
}


bool PortReflector::abortTarget(TargetInfo::Ptr pTargetInfo, const std::string& reason)
{
	bool connected = false;
	Poco::FastMutex::ScopedLock targetLock(pTargetInfo->mutex);
	if (pTargetInfo->state == TS_CONNECTED)
	{
		connected = true;
		_logger.notice("Aborting connection to target %s [%s]", pTargetInfo->id, reason);
		for (ChannelMap::iterator it = pTargetInfo->channelMap.begin(); it != pTargetInfo->channelMap.end(); ++it)
		{
			try
			{
				if (it->second->pSocket && it->second->state != CS_DISCONNECTED)
				{
					it->second->state = CS_DISCONNECTED;
					it->second->stateChanged.set();
					Poco::FastMutex::ScopedLock lock(it->second->socketMutex);
					shutdownSocket(*it->second->pSocket, Poco::Net::WebSocket::WS_UNEXPECTED_CONDITION);
				}
			}
			catch (Poco::Exception& exc)
			{
				_logger.warning("Error closing channel %hu for target %s: %s", it->second->channel, pTargetInfo->id, exc.displayText());
			}
			if (it->second->pSocket)
			{
				_dispatcher.removeSocket(*it->second->pSocket);
			}
		}
		_dispatcher.closeSocket(*pTargetInfo->pWebSocket);
		pTargetInfo->channelMap.clear();
		pTargetInfo->state = TS_DISCONNECTED;
	}
	return connected;
}


void PortReflector::removeTarget(TargetInfo::Ptr pTargetInfo, const std::string& reason)
{
	try
	{
		if (abortTarget(pTargetInfo, reason))
		{
			Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);
			_targetMap.erase(pTargetInfo->id);
			lock.unlock();
			serverDisconnected(this, pTargetInfo->id);
		}
	}
	catch (Poco::Exception& exc)
	{
		_logger.log(exc);
	}
}


void PortReflector::shutdownChannel(TargetInfo::Ptr pTargetInfo, ChannelInfo::Ptr pChannelInfo)
{
	if (pChannelInfo->pSocket)
	{
		_dispatcher.removeSocket(*pChannelInfo->pSocket);
	}
	if (pChannelInfo->state != CS_DISCONNECTED)
	{
		pChannelInfo->state = CS_DISCONNECTED;
		pChannelInfo->stateChanged.set();
		try
		{
			closeChannel(pTargetInfo, pChannelInfo->channel);
		}
		catch (Poco::Exception& exc)
		{
			_logger.error("Error closing channel %hu to target %s: %s", pChannelInfo->channel, pTargetInfo->id, exc.displayText());
		}
	}
}


void PortReflector::openChannel(TargetInfo::Ptr pTargetInfo, Poco::UInt16 channel, Poco::UInt16 port)
{
	if (_logger.debug())
	{
		_logger.debug("Opening channel %hu for port %hu", channel, port);
	}
	char buffer[6];
	Protocol::writeHeader(buffer, sizeof(buffer), Protocol::WT_OP_OPEN_REQUEST, 0, channel, port);
	try
	{
		Poco::FastMutex::ScopedLock lock(pTargetInfo->webSocketMutex);
		pTargetInfo->pWebSocket->sendFrame(buffer, sizeof(buffer), Poco::Net::WebSocket::FRAME_BINARY);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Error opening channel %hu for port %hu on target %s: %s", channel, port, pTargetInfo->id, exc.displayText());
		removeTarget(pTargetInfo, "open channel error");
	}
}


void PortReflector::closeChannel(TargetInfo::Ptr pTargetInfo, Poco::UInt16 channel)
{
	if (_logger.debug())
	{
		_logger.debug("Closing channel %hu to target %s", channel, pTargetInfo->id);
	}
	char buffer[4];
	Protocol::writeHeader(buffer, sizeof(buffer), Protocol::WT_OP_CLOSE, 0, channel);
	try
	{
		Poco::FastMutex::ScopedLock lock(pTargetInfo->webSocketMutex);
		pTargetInfo->pWebSocket->sendFrame(buffer, sizeof(buffer), Poco::Net::WebSocket::FRAME_BINARY);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Error closing channel %hu on target %s: %s", channel, pTargetInfo->id, exc.displayText());
		removeTarget(pTargetInfo, "close channel error");
	}
}


bool PortReflector::confirmOpenChannel(TargetInfo::Ptr pTargetInfo, Poco::UInt16 channel)
{
	{
		Poco::FastMutex::ScopedLock lock(pTargetInfo->mutex);

		ChannelMap::iterator it = pTargetInfo->channelMap.find(channel);
		if (it != pTargetInfo->channelMap.end())
		{
			if (it->second->state == CS_CONNECTING)
			{
				if (_logger.debug())
				{
					_logger.debug("Channel %hu to target %s opened", channel, pTargetInfo->id);
				}
				it->second->state = CS_CONNECTED;
				it->second->stateChanged.set();
				return true;
			}
		}
	}

	_logger.error("Received unexpected open confirm message for channel %hu on target %s", channel, pTargetInfo->id);
	removeTarget(pTargetInfo, "unexpected open confirm");
	return false;
}


void PortReflector::confirmCloseChannel(TargetInfo::Ptr pTargetInfo, Poco::UInt16 channel, Poco::UInt16 errorCode)
{
	Poco::FastMutex::ScopedLock lock(pTargetInfo->mutex);

	if (_logger.debug())
	{
		_logger.debug("Confirming close channel %hu to target %s (status code %hu)", channel, pTargetInfo->id, errorCode);
	}
	ChannelMap::iterator it = pTargetInfo->channelMap.find(channel);
	if (it != pTargetInfo->channelMap.end())
	{
		it->second->state = CS_DISCONNECTED;
		it->second->stateChanged.set();
		try
		{
			if (it->second->pSocket)
			{
				shutdownSocket(*it->second->pSocket, Poco::Net::WebSocket::WS_NORMAL_CLOSE);
			}
			else if (it->second->pTunnelSocket)
			{
				static_cast<TunnelSocketImpl*>(it->second->pTunnelSocket->impl())->enqueueClose(errorCode);
			}
		}
		catch (Poco::Exception& exc)
		{
			_logger.warning("Error closing client WebSocket for channel %hu: %s", channel, exc.displayText());
		}
		if (it->second->pSocket)
		{
			_dispatcher.closeSocket(*it->second->pSocket);
			it->second->pSocket = 0;
		}
		it->second->pTunnelSocket = 0;
		pTargetInfo->channelMap.erase(it);
	}
}


bool PortReflector::forwardData(const char* buffer, std::size_t size, TargetInfo::Ptr pTargetInfo, Poco::UInt16 channel)
{
	Poco::ScopedLockWithUnlock<Poco::FastMutex> targetLock(pTargetInfo->mutex);

	ChannelMap::iterator it = pTargetInfo->channelMap.find(channel);
	if (it != pTargetInfo->channelMap.end() && it->second->state == CS_CONNECTED)
	{
		ChannelInfo::Ptr pChannelInfo = it->second;
		targetLock.unlock();
		try
		{
			if (pChannelInfo->pSocket)
			{
				Poco::FastMutex::ScopedLock lock(pChannelInfo->socketMutex);
				pChannelInfo->pSocket->sendBytes(buffer, static_cast<int>(size));
			}
			else if (pChannelInfo->pTunnelSocket)
			{
				static_cast<TunnelSocketImpl*>(pChannelInfo->pTunnelSocket->impl())->enqueueBytes(buffer, static_cast<int>(size));
			}
			return true;
		}
		catch (Poco::Exception& exc)
		{
			_logger.error("Error forwarding data for channel %hu, target %s: ", channel, pTargetInfo->id, exc.displayText());
			shutdownChannel(pTargetInfo, pChannelInfo);
		}
	}
	else
	{
		targetLock.unlock();
		_logger.error("Received unexpected data message for channel %hu on target %s", channel, pTargetInfo->id);
	}
	return false;
}


bool PortReflector::sendInitialMessage(TargetInfo::Ptr pTargetInfo, Poco::UInt16 channel)
{
	ChannelMap::iterator it = pTargetInfo->channelMap.find(channel);
	if (it != pTargetInfo->channelMap.end())
	{
		if (!it->second->initialMessage.empty())
		{
			Poco::Buffer<char> buffer(it->second->initialMessage.size() + 8);
			std::size_t hn = Protocol::writeHeader(buffer.begin(), buffer.size(), Protocol::WT_OP_DATA, 0, channel);
			std::memcpy(buffer.begin() + hn, it->second->initialMessage.data(), it->second->initialMessage.size());
			try
			{
				Poco::FastMutex::ScopedLock lock(pTargetInfo->webSocketMutex);
				pTargetInfo->pWebSocket->sendFrame(buffer.begin(), static_cast<int>(it->second->initialMessage.size() + hn), Poco::Net::WebSocket::FRAME_BINARY);
			}
			catch (Poco::Exception& exc)
			{
				_logger.error("Error sending WebSocket frame for channel %hu to target %s: %s", channel, pTargetInfo->id, exc.displayText());
				removeTarget(pTargetInfo, "send frame error");
				return false;
			}
		}
	}
	return true;
}


} } // namespace Poco::WebTunnel
