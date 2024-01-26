//
// RemotePortForwarder.cpp
//
// Library: WebTunnel
// Package: WebTunnel
// Module:  RemotePortForwarder
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/WebTunnel/RemotePortForwarder.h"
#include "Poco/WebTunnel/Protocol.h"
#include "Poco/Net/NetException.h"
#include "Poco/Format.h"
#include "Poco/BinaryWriter.h"
#include "Poco/MemoryStream.h"
#include "Poco/CountingStream.h"
#include <cstring>


using namespace std::string_literals;


namespace Poco {
namespace WebTunnel {


//
// SocketFactory
//


SocketFactory::SocketFactory()
{
}


SocketFactory::~SocketFactory()
{
}


Poco::Net::StreamSocket SocketFactory::createSocket(const Poco::Net::SocketAddress& addr, Poco::Timespan timeout)
{
	Poco::Net::StreamSocket streamSocket;
	streamSocket.connect(addr, timeout);
	streamSocket.setNoDelay(true);
	return streamSocket;
}


//
// RemotePortForwarder
//


RemotePortForwarder::RemotePortForwarder(SocketDispatcher& dispatcher, Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket, const Poco::Net::IPAddress& host, const std::set<Poco::UInt16>& ports, Poco::Timespan remoteTimeout, SocketFactory::Ptr pSocketFactory):
	_dispatcher(dispatcher),
	_pSocketFactory(pSocketFactory),
	_pWebSocket(pWebSocket),
	_host(host),
	_ports(ports),
	_connectTimeout(30, 0),
	_localTimeout(7200, 0),
	_remoteTimeout(remoteTimeout),
	_timeoutCount(0),
	_logger(Poco::Logger::get("WebTunnel.RemotePortForwarder"s))
{
	_dispatcher.addSocket(*pWebSocket, new TunnelDemultiplexer(*this), remoteTimeout);
}


RemotePortForwarder::~RemotePortForwarder()
{
	try
	{
		stop();
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void RemotePortForwarder::stop()
{
	if (_pWebSocket)
	{
		closeWebSocket(RPF_CLOSE_GRACEFUL, true);
	}
}


void RemotePortForwarder::setLocalTimeout(const Poco::Timespan& timeout)
{
	_localTimeout = timeout;
}


const Poco::Timespan& RemotePortForwarder::getLocalTimeout() const
{
	return _localTimeout;
}


void RemotePortForwarder::setConnectTimeout(const Poco::Timespan& timeout)
{
	_connectTimeout = timeout;
}


const Poco::Timespan& RemotePortForwarder::getConnectTimeout() const
{
	return _connectTimeout;
}


const Poco::Timespan& RemotePortForwarder::remoteTimeout() const
{
	return _remoteTimeout;
}


bool RemotePortForwarder::multiplex(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, Poco::UInt16 channel, Poco::Buffer<char>& buffer)
{
	std::size_t hn = Protocol::writeHeader(buffer.begin(), buffer.size(), Protocol::WT_OP_DATA, 0, channel);
	bool expectMore = true;
	int n = 0;
	try
	{
		n = socket.receiveBytes(buffer.begin() + hn, static_cast<int>(buffer.size() - hn));
		if (n <= 0)
		{
			if (_logger.debug())
			{
				_logger.debug("Actively closing channel %hu."s, channel);
			}
			removeChannel(channel);
			n = 0;
			hn = Protocol::writeHeader(buffer.begin(), buffer.size(), Protocol::WT_OP_CLOSE, 0, channel);
			expectMore = false;
		}
	}
	catch (Poco::Exception& exc)
	{
		removeChannel(channel);
		n = 0;
		// Workaround for some HTTPS servers that do not orderly close a TLS connection.
		if (std::strcmp(exc.name(), "SSL connection unexpectedly closed") == 0)
		{
			hn = Protocol::writeHeader(buffer.begin(), buffer.size(), Protocol::WT_OP_CLOSE, 0, channel);
		}
		else
		{
			_logger.error("Error reading from locally forwarded socket for channel %hu: %s"s, channel, exc.displayText());
			hn = Protocol::writeHeader(buffer.begin(), buffer.size(), Protocol::WT_OP_ERROR, 0, channel, Protocol::WT_ERR_SOCKET);
		}
		expectMore = false;
	}
	try
	{
		Poco::FastMutex::ScopedLock lock(_webSocketMutex);
		_pWebSocket->sendFrame(buffer.begin(), static_cast<int>(n + hn), Poco::Net::WebSocket::FRAME_BINARY);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Error sending WebSocket frame for channel %hu: %s"s, channel, exc.displayText());
		closeWebSocket(RPF_CLOSE_ERROR, false);
		expectMore = false;
	}
	return expectMore;
}


void RemotePortForwarder::multiplexError(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, Poco::UInt16 channel, Poco::Buffer<char>& buffer)
{
	_logger.error("Error reading from local socket for channel %hu"s, channel);
	removeChannel(channel);
	std::size_t hn = Protocol::writeHeader(buffer.begin(), buffer.size(), Protocol::WT_OP_ERROR, 0, channel, Protocol::WT_ERR_SOCKET);
	try
	{
		Poco::FastMutex::ScopedLock lock(_webSocketMutex);
		_pWebSocket->sendFrame(buffer.begin(), static_cast<int>(hn), Poco::Net::WebSocket::FRAME_BINARY);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Error sending WebSocket error frame for channel %hu: %s"s, channel, exc.displayText());
		closeWebSocket(RPF_CLOSE_ERROR, false);
	}
}


void RemotePortForwarder::multiplexTimeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, Poco::UInt16 channel, Poco::Buffer<char>& buffer)
{
	_logger.error("Timeout reading from local socket for channel %hu"s, channel);
	removeChannel(channel);
	std::size_t hn = Protocol::writeHeader(buffer.begin(), buffer.size(), Protocol::WT_OP_ERROR, 0, channel, Protocol::WT_ERR_TIMEOUT);
	try
	{
		Poco::FastMutex::ScopedLock lock(_webSocketMutex);
		_pWebSocket->sendFrame(buffer.begin(), static_cast<int>(hn), Poco::Net::WebSocket::FRAME_BINARY);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Error sending WebSocket error frame for channel %hu: %s"s, channel, exc.displayText());
		closeWebSocket(RPF_CLOSE_ERROR, false);
	}
}


bool RemotePortForwarder::demultiplex(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, Poco::Buffer<char>& buffer)
{
	int wsFlags;
	int n = 0;
	try
	{
		n = _pWebSocket->receiveFrame(buffer.begin(), static_cast<int>(buffer.size()), wsFlags);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Error receiving WebSocket frame: %s"s, exc.displayText());
		closeWebSocket(RPF_CLOSE_ERROR, false);
		return false;
	}
	if ((wsFlags & Poco::Net::WebSocket::FRAME_OP_BITMASK) == Poco::Net::WebSocket::FRAME_OP_PONG)
	{
		_logger.debug("PONG received"s);
		_timeoutCount = 0;
		return false;
	}
	if (n > 0 && (wsFlags & Poco::Net::WebSocket::FRAME_OP_BITMASK) == Poco::Net::WebSocket::FRAME_OP_BINARY)
	{
		Poco::UInt8 opcode;
		Poco::UInt8 flags;
		Poco::UInt16 channel;
		Poco::UInt16 portOrErrorCode;
		std::size_t hn = Protocol::readHeader(buffer.begin(), buffer.size(), opcode, flags, channel, &portOrErrorCode);
		switch (opcode)
		{
		case Protocol::WT_OP_DATA:
			return forwardData(buffer.begin() + hn, static_cast<int>(n - hn), channel);

		case Protocol::WT_OP_OPEN_REQUEST:
			return openChannel(channel, portOrErrorCode);

		case Protocol::WT_OP_CLOSE:
			if (_logger.debug())
			{
				_logger.debug("Passively closing channel %hu."s, channel);
			}
			removeChannel(channel);
			return false;

		case Protocol::WT_OP_ERROR:
			_logger.error("Status %hu reported by peer. Closing channel %hu."s, portOrErrorCode, channel);
			removeChannel(channel);
			return false;

		default:
			_logger.error("Invalid WebSocket frame received (bad opcode: %hu)."s, static_cast<Poco::UInt16>(opcode));
			sendResponse(channel, Protocol::WT_OP_ERROR, Protocol::WT_ERR_PROTOCOL);
			return false;
		}
	}
	else if (n <= 0 || (wsFlags & Poco::Net::WebSocket::FRAME_OP_BITMASK) == Poco::Net::WebSocket::FRAME_OP_CLOSE)
	{
		_logger.debug("Closing WebSocket."s);
		closeWebSocket(RPF_CLOSE_GRACEFUL, false);
		return false;
	}
	else
	{
		_logger.debug("Ignoring unsupported frame opcode."s);
		return false;
	}
}


void RemotePortForwarder::demultiplexError(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, Poco::Buffer<char>& buffer)
{
	_logger.error("Error reading from WebSocket."s);
	closeWebSocket(RPF_CLOSE_ERROR, false);
}


void RemotePortForwarder::demultiplexTimeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket, Poco::Buffer<char>& buffer)
{
	_logger.debug("Timeout reading from WebSocket."s);
	if (_timeoutCount == 0)
	{
		_timeoutCount = 1;
		try
		{
			_logger.debug("Sending PING."s);
			Poco::FastMutex::ScopedLock lock(_webSocketMutex);
			_pWebSocket->sendFrame(0, 0, Poco::Net::WebSocket::FRAME_FLAG_FIN | Poco::Net::WebSocket::FRAME_OP_PING);
		}
		catch (Poco::Exception&)
		{
			closeWebSocket(RPF_CLOSE_ERROR, false);
		}
	}
	else
	{
		closeWebSocket(RPF_CLOSE_TIMEOUT, false);
	}
}


bool RemotePortForwarder::forwardData(const char* buffer, int size, Poco::UInt16 channel)
{
	Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);
	ChannelMap::iterator it = _channelMap.find(channel);
	if (it != _channelMap.end())
	{
		Poco::Net::StreamSocket streamSocket = it->second;
		lock.unlock();
		try
		{
			streamSocket.sendBytes(buffer, size);
			return true;
		}
		catch (Poco::Exception&)
		{
			removeChannel(channel);
			sendResponse(channel, Protocol::WT_OP_ERROR, Protocol::WT_ERR_SOCKET);
		}
	}
	else
	{
		_logger.warning("Forwarding request for invalid channel: %hu."s, channel);
		lock.unlock();
		sendResponse(channel, Protocol::WT_OP_ERROR, Protocol::WT_ERR_BAD_CHANNEL);
	}
	return false;
}


bool RemotePortForwarder::openChannel(Poco::UInt16 channel, Poco::UInt16 port)
{
	if (_ports.find(port) == _ports.end())
	{
		_logger.warning("Open channel request for invalid port: %hu (channel %hu)."s, port, channel);

		sendResponse(channel, Protocol::WT_OP_OPEN_FAULT, Protocol::WT_ERR_NOT_FORWARDED);
		return false;
	}

	Poco::ScopedLockWithUnlock<Poco::FastMutex> lock(_mutex);
	ChannelMap::iterator it = _channelMap.find(channel);
	if (it == _channelMap.end())
	{
		if (_logger.debug())
		{
			_logger.debug("Opening channel %hu to port %hu."s, channel, port);
		}
		try
		{
			Poco::Net::SocketAddress addr(_host, port);
			Poco::Net::StreamSocket streamSocket(_pSocketFactory->createSocket(addr, _connectTimeout));
			SocketDispatcher::SocketHandler::Ptr pMultiplexer = new TunnelMultiplexer(*this, channel);
			
			try
			{
				// Note: we must send the WT_OP_OPEN_CONFIRM before adding the socket
				// to the dispatcher, otherwise a race condition may occur and the 
				// first data packet from the target may arrive at the server before
				// the WT_OP_OPEN_CONFIRM.
				sendResponse(channel, Protocol::WT_OP_OPEN_CONFIRM, 0);
			}
			catch (Poco::Exception& exc)
			{
				_logger.error("Failed to send open confirmation for channel %hu to port %hu: %s"s, channel, port, exc.displayText());
				return false;
			}

			_dispatcher.addSocket(streamSocket, pMultiplexer, _localTimeout);
			_channelMap[channel] = streamSocket;
		}
		catch (Poco::Net::ConnectionRefusedException& exc)
		{
			lock.unlock();
			_logger.error("Failed to open channel %hu to port %hu: %s"s, channel, port, exc.displayText());
			sendResponse(channel, Protocol::WT_OP_OPEN_FAULT, Protocol::WT_ERR_CONN_REFUSED);
			return false;
		}
		catch (Poco::TimeoutException& exc)
		{
			lock.unlock();
			_logger.error("Failed to open channel %hu to port %hu: %s"s, channel, port, exc.displayText());
			sendResponse(channel, Protocol::WT_OP_OPEN_FAULT, Protocol::WT_ERR_TIMEOUT);
			return false;
		}
		catch (Poco::Exception& exc)
		{
			lock.unlock();
			_logger.error("Failed to open channel %hu to port %hu: %s"s, channel, port, exc.displayText());
			sendResponse(channel, Protocol::WT_OP_OPEN_FAULT, Protocol::WT_ERR_SOCKET);
			return false;
		}
		return true;
	}
	else
	{
		_logger.warning("Open request for existing channel %hu to port %hu."s, channel, port);
		lock.unlock();
		sendResponse(channel, Protocol::WT_OP_OPEN_FAULT, Protocol::WT_ERR_CHANNEL_IN_USE);
		return false;
	}
}


void RemotePortForwarder::removeChannel(Poco::UInt16 channel)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	ChannelMap::iterator it = _channelMap.find(channel);
	if (it != _channelMap.end())
	{
		_dispatcher.closeSocket(it->second);
		_channelMap.erase(it);
	}
}


void RemotePortForwarder::sendResponse(Poco::UInt16 channel, Poco::UInt8 opcode, Poco::UInt16 errorCode)
{
	char buffer[6];
	std::size_t hn = Protocol::writeHeader(buffer, sizeof(buffer), opcode, 0, channel, errorCode);
	try
	{
		Poco::FastMutex::ScopedLock lock(_webSocketMutex);
		_pWebSocket->sendFrame(buffer, static_cast<int>(hn), Poco::Net::WebSocket::FRAME_BINARY);
	}
	catch (Poco::Exception&)
	{
		closeWebSocket(RPF_CLOSE_ERROR, false);
	}
}


void RemotePortForwarder::closeWebSocket(CloseReason reason, bool active)
{
	{
		Poco::FastMutex::ScopedLock lock(_webSocketMutex);

		if (!_pWebSocket || !_pWebSocket->impl()->initialized()) return;

		if (_logger.debug())
		{
			_logger.debug("Closing WebSocket, reason: %d, active: %b"s, static_cast<int>(reason), active);
		}
		try
		{
			_dispatcher.removeSocket(*_pWebSocket);
			if (reason == RPF_CLOSE_GRACEFUL)
			{
				try
				{
					if (active)
					{
						_pWebSocket->shutdown(Poco::Net::WebSocket::WS_NORMAL_CLOSE);
					}
				}
				catch (Poco::Exception&)
				{
				}
			}
			for (ChannelMap::iterator it = _channelMap.begin(); it != _channelMap.end(); ++it)
			{
				_dispatcher.removeSocket(it->second);
			}
			_pWebSocket->close();
			_channelMap.clear();
		}
		catch (Poco::Exception& exc)
		{
			_logger.log(exc);
		}
	}

	int eventArg = reason;
	webSocketClosed(this, eventArg);
}


namespace
{
	void writeProperties(Poco::BinaryWriter& writer, const std::map<std::string, std::string>& props)
	{
		writer << static_cast<Poco::UInt8>(props.size());
		for (std::map<std::string, std::string>::const_iterator it = props.begin(); it != props.end(); ++it)
		{
			writer << it->first << it->second;
		}
	}
}


void RemotePortForwarder::updateProperties(const std::map<std::string, std::string>& props)
{
	poco_assert (props.size() < 256);

	Poco::CountingOutputStream counterStream;
	Poco::BinaryWriter counterWriter(counterStream, Poco::BinaryWriter::NETWORK_BYTE_ORDER);
	writeProperties(counterWriter, props);
	std::size_t payloadSize = counterStream.chars();

	Poco::Buffer<char> buffer(payloadSize + Protocol::WT_FRAME_HEADER_SIZE);
	std::size_t offset = Protocol::writeHeader(buffer.begin(), buffer.size(), Protocol::WT_OP_PROP_UPDATE, 0, 0);
	Poco::MemoryOutputStream bufferStream(buffer.begin() + offset, buffer.size() - offset);
	Poco::BinaryWriter bufferWriter(bufferStream, Poco::BinaryWriter::NETWORK_BYTE_ORDER);
	writeProperties(bufferWriter, props);

	Poco::FastMutex::ScopedLock lock(_webSocketMutex);
	_pWebSocket->sendFrame(buffer.begin(), static_cast<int>(payloadSize + Protocol::WT_FRAME_HEADER_SIZE), Poco::Net::WebSocket::FRAME_BINARY);
}


} } // namespace Poco::WebTunnel
