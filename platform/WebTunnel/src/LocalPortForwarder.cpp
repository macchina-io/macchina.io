//
// LocalPortForwarder.cpp
//
// Library: WebTunnel
// Package: WebTunnel
// Module:  LocalPortForwarder
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/WebTunnel/LocalPortForwarder.h"
#include "Poco/WebTunnel/SocketDispatcher.h"
#include "Poco/WebTunnel/Protocol.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/HTTPRequest.h"
#include "Poco/Net/HTTPResponse.h"
#include "Poco/Net/HTTPClientSession.h"
#include "Poco/Net/HTTPSessionFactory.h"
#include "Poco/Net/HTTPBasicCredentials.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Format.h"
#include "Poco/Buffer.h"


namespace Poco {
namespace WebTunnel {


//
// LocalPortForwarderConnection
//


class LocalPortForwarderConnection: public Poco::Net::TCPServerConnection
{
public:
	LocalPortForwarderConnection(const Poco::Net::StreamSocket& socket, LocalPortForwarder& forwarder):
		Poco::Net::TCPServerConnection(socket),
		_forwarder(forwarder)
	{
	}

	void run()
	{
		_forwarder.forward(socket());
	}

private:
	LocalPortForwarder& _forwarder;
};


//
// LocalPortForwarderConnectionFactory
//


class LocalPortForwarderConnectionFactory: public Poco::Net::TCPServerConnectionFactory
{
public:
	LocalPortForwarderConnectionFactory(LocalPortForwarder& forwarder):
		_forwarder(forwarder)
	{
	}

	Poco::Net::TCPServerConnection* createConnection(const Poco::Net::StreamSocket& socket)
	{
		return new LocalPortForwarderConnection(socket, _forwarder);
	}

private:
	LocalPortForwarder& _forwarder;
};


//
// WebSocketFactory
//


WebSocketFactory::WebSocketFactory()
{
}


WebSocketFactory::~WebSocketFactory()
{
}


//
// DefaultWebSocketFactory
//


DefaultWebSocketFactory::DefaultWebSocketFactory()
{
}


DefaultWebSocketFactory::DefaultWebSocketFactory(const std::string& username, const std::string& password, Poco::Timespan timeout):
	_username(username),
	_password(password),
	_timeout(timeout)
{
}


DefaultWebSocketFactory::~DefaultWebSocketFactory()
{
}


Poco::Net::WebSocket* DefaultWebSocketFactory::createWebSocket(const Poco::URI& uri, Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response)
{
	Poco::SharedPtr<Poco::Net::HTTPClientSession> pSession = Poco::Net::HTTPSessionFactory::defaultFactory().createClientSession(uri);
	pSession->setTimeout(_timeout);
	if (!_username.empty())
	{
		Poco::Net::HTTPBasicCredentials creds(_username, _password);
		creds.authenticate(request);
	}
	return new Poco::Net::WebSocket(*pSession, request, response);
}


//
// BasicSocketForwarder
//


class BasicSocketForwarder: public SocketDispatcher::SocketHandler
{
public:
	BasicSocketForwarder(Poco::SharedPtr<SocketDispatcher> pDispatcher):
		_pDispatcher(pDispatcher),
		_buffer(Protocol::WT_FRAME_MAX_SIZE)
	{
	}

	void cleanupDispatcher(Poco::Net::StreamSocket& socket1, Poco::Net::StreamSocket& socket2)
	{
		if (_pDispatcher)
		{
			_pDispatcher->removeSocket(socket1);
			_pDispatcher->removeSocket(socket2);
			_pDispatcher = 0;
		}
	}

	void shutdown(Poco::Net::WebSocket& webSocket, Poco::UInt16 statusCode, Poco::Logger& logger)
	{
		try
		{
			webSocket.shutdown(statusCode);
			webSocket.shutdownSend();
		}
		catch (Poco::Exception& exc)
		{
			logger.warning("Error shutting down WebSocket: %s", exc.displayText());
		}
	}

protected:
	Poco::SharedPtr<SocketDispatcher> _pDispatcher;
	Poco::Buffer<char> _buffer;
};


//
// SocketToWebSocketForwarder
//


class StreamSocketToWebSocketForwarder: public BasicSocketForwarder
{
public:
	StreamSocketToWebSocketForwarder(Poco::SharedPtr<SocketDispatcher> pDispatcher, Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket):
		BasicSocketForwarder(pDispatcher),
		_pWebSocket(pWebSocket),
		_logger(Poco::Logger::get("WebTunnel.StreamSocketToWebSocketForwarder"))
	{
	}

	bool readable(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
	{
		int n = 0;
		try
		{
			n = socket.receiveBytes(_buffer.begin(), static_cast<int>(_buffer.size()));
		}
		catch (Poco::Exception& exc)
		{
			_logger.error("Exception while receiving data: " + exc.displayText());
			shutdown(*_pWebSocket, Poco::Net::WebSocket::WS_UNEXPECTED_CONDITION, _logger);
			cleanupDispatcher(socket, *_pWebSocket);
			return false;
		}
		if (n > 0)
		{
			try
			{
				_pWebSocket->sendFrame(_buffer.begin(), n, Poco::Net::WebSocket::FRAME_BINARY);
				return true;
			}
			catch (Poco::Exception& exc)
			{
				_logger.error("Exception while sending data: " + exc.displayText());
				cleanupDispatcher(socket, *_pWebSocket);
			}
		}
		else
		{
			_logger.debug("Closing connection");
			shutdown(*_pWebSocket, Poco::Net::WebSocket::WS_NORMAL_CLOSE, _logger);
			cleanupDispatcher(socket, *_pWebSocket);
		}
		return false;
	}

	void exception(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
	{
		shutdown(*_pWebSocket, Poco::Net::WebSocket::WS_UNEXPECTED_CONDITION, _logger);
		cleanupDispatcher(socket, *_pWebSocket);
	}

	void timeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
	{
		shutdown(*_pWebSocket, Poco::Net::WebSocket::WS_UNEXPECTED_CONDITION, _logger);
		cleanupDispatcher(socket, *_pWebSocket);
	}

private:
	Poco::SharedPtr<Poco::Net::WebSocket> _pWebSocket;
	Poco::Logger& _logger;
};


//
// WebSocketToStreamSocketForwarder
//


class WebSocketToStreamSocketForwarder: public BasicSocketForwarder
{
public:
	WebSocketToStreamSocketForwarder(Poco::SharedPtr<SocketDispatcher> pDispatcher, Poco::Net::StreamSocket streamSocket):
		BasicSocketForwarder(pDispatcher),
		_streamSocket(streamSocket),
		_timeoutCount(0),
		_logger(Poco::Logger::get("WebTunnel.WebSocketToStreamSocketForwarder"))
	{
	}

	bool readable(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
	{
		Poco::Net::WebSocket webSocket(socket);
		int flags;
		int n = 0;
		try
		{
			n = webSocket.receiveFrame(_buffer.begin(), static_cast<int>(_buffer.size()), flags);
		}
		catch (Poco::Exception& exc)
		{
			_logger.error("Exception while receiving data: " + exc.displayText());
			cleanupDispatcher(socket, _streamSocket);
			return false;
		}
		if ((flags & Poco::Net::WebSocket::FRAME_OP_BITMASK) == Poco::Net::WebSocket::FRAME_OP_PONG)
		{
			_logger.debug("PONG received");
			_timeoutCount = 0;
			return false;
		}
		if (n > 0 && (flags & Poco::Net::WebSocket::FRAME_OP_BITMASK) == Poco::Net::WebSocket::FRAME_OP_BINARY)
		{
			try
			{
				_streamSocket.sendBytes(_buffer.begin(), n);
				return true;
			}
			catch (Poco::Exception& exc)
			{
				_logger.error("Exception while sending data: " + exc.displayText());
				cleanupDispatcher(socket, _streamSocket);
				shutdown(webSocket, Poco::Net::WebSocket::WS_UNEXPECTED_CONDITION, _logger);
				return false;
			}
		}
		else if (n <= 0 || (flags & Poco::Net::WebSocket::FRAME_OP_BITMASK) == Poco::Net::WebSocket::FRAME_OP_CLOSE)
		{
			_logger.debug("Shutting down WebSocket");
			cleanupDispatcher(socket, _streamSocket);
			_streamSocket.shutdown();
		}
		else
		{
			_logger.debug("Ignoring unsupported frame type");
		}
		return false;
	}

	void exception(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
	{
		cleanupDispatcher(socket, _streamSocket);
	}

	void timeout(SocketDispatcher& dispatcher, Poco::Net::StreamSocket& socket)
	{
		_logger.debug("Timeout reading from WebSocket");
		if (_timeoutCount == 0)
		{
			_timeoutCount = 1;
			try
			{
				_logger.debug("Sending PING");
				Poco::Net::WebSocket webSocket(socket);
				webSocket.sendFrame(0, 0, Poco::Net::WebSocket::FRAME_FLAG_FIN | Poco::Net::WebSocket::FRAME_OP_PING);
			}
			catch (Poco::Exception&)
			{
				cleanupDispatcher(socket, _streamSocket);
			}
		}
		else
		{
			cleanupDispatcher(socket, _streamSocket);
		}
	}

private:
	Poco::Net::StreamSocket _streamSocket;
	int _timeoutCount;
	Poco::Logger& _logger;
};


//
// LocalPortForwarder
//


const std::string LocalPortForwarder::SEC_WEBSOCKET_PROTOCOL("Sec-WebSocket-Protocol");
const std::string LocalPortForwarder::X_WEBTUNNEL_REMOTEPORT("X-WebTunnel-RemotePort");
const std::string LocalPortForwarder::WEBTUNNEL_PROTOCOL("com.appinf.webtunnel.client/1.0");


LocalPortForwarder::LocalPortForwarder(Poco::UInt16 localPort, Poco::UInt16 remotePort, const Poco::URI& remoteURI, WebSocketFactory::Ptr pWebSocketFactory):
	_localAddr("localhost", localPort),
	_remotePort(remotePort),
	_remoteURI(remoteURI),
	_localTimeout(0),
	_remoteTimeout(300, 0),
	_pWebSocketFactory(pWebSocketFactory),
	_serverSocket(_localAddr),
	_tcpServer(new LocalPortForwarderConnectionFactory(*this), _serverSocket),
	_logger(Poco::Logger::get("WebTunnel.LocalPortForwarder"))
{
	_localAddr = _serverSocket.address();
	_tcpServer.start();
	_pDispatcher = new SocketDispatcher(10);
}


LocalPortForwarder::LocalPortForwarder(const Poco::Net::SocketAddress& localAddress, Poco::UInt16 remotePort, const Poco::URI& remoteURI, Poco::Net::TCPServerParams::Ptr pServerParams, WebSocketFactory::Ptr pWebSocketFactory):
	_localAddr(localAddress),
	_remotePort(remotePort),
	_remoteURI(remoteURI),
	_localTimeout(0),
	_remoteTimeout(300, 0),
	_pWebSocketFactory(pWebSocketFactory),
	_serverSocket(_localAddr),
	_tcpServer(new LocalPortForwarderConnectionFactory(*this), _serverSocket, pServerParams),
	_pDispatcher(new SocketDispatcher(16)),
	_logger(Poco::Logger::get("WebTunnel.LocalPortForwarder"))
{
	_localAddr = _serverSocket.address();
	_tcpServer.start();
}


LocalPortForwarder::~LocalPortForwarder()
{
	try
	{
		_tcpServer.stop();
		_pDispatcher->stop();
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void LocalPortForwarder::setLocalTimeout(Poco::Timespan timeout)
{
	_localTimeout = timeout;
}



void LocalPortForwarder::setRemoteTimeout(Poco::Timespan timeout)
{
	_remoteTimeout = timeout;
}


void LocalPortForwarder::forward(Poco::Net::StreamSocket& socket)
{
	if (_logger.debug())
	{
		_logger.debug("Local connection accepted, creating forwarding connection to %s, remote port %hu", _remoteURI.toString(), _remotePort);
	}
	try
	{
		std::string path(_remoteURI.getPathEtc());
		if (path.empty()) path = "/";
		Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, path, Poco::Net::HTTPRequest::HTTP_1_1);
		request.set(SEC_WEBSOCKET_PROTOCOL, WEBTUNNEL_PROTOCOL);
		request.set(X_WEBTUNNEL_REMOTEPORT, Poco::NumberFormatter::format(_remotePort));
		Poco::Net::HTTPResponse response;
		Poco::SharedPtr<Poco::Net::WebSocket> pWebSocket = _pWebSocketFactory->createWebSocket(_remoteURI, request, response);
		if (response.get(SEC_WEBSOCKET_PROTOCOL, "") != WEBTUNNEL_PROTOCOL)
		{
			_logger.error("The remote host does not support the WebTunnel protocol.");
			pWebSocket->shutdown(Poco::Net::WebSocket::WS_PROTOCOL_ERROR);
			pWebSocket->close();
			socket.close();
			return;
		}

		socket.setNoDelay(true);
		pWebSocket->setNoDelay(true);

		_pDispatcher->addSocket(socket, new StreamSocketToWebSocketForwarder(_pDispatcher, pWebSocket), _localTimeout);
		_pDispatcher->addSocket(*pWebSocket, new WebSocketToStreamSocketForwarder(_pDispatcher, socket), _remoteTimeout);
	}
	catch (Poco::Exception& exc)
	{
		_logger.error("Failed to open forwarding connection: %s", exc.displayText());
		socket.close();
	}
}


} } // namespace Poco::WebTunnel
