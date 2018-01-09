//
// LocalPortForwarder.h
//
// Library: WebTunnel
// Package: WebTunnel
// Module:  LocalPortForwarder
//
// Definition of the LocalPortForwarder class.
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef WebTunnel_LocalPortForwarder_INCLUDED
#define WebTunnel_LocalPortForwarder_INCLUDED


#include "Poco/WebTunnel/WebTunnel.h"
#include "Poco/WebTunnel/SocketDispatcher.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerParams.h"
#include "Poco/Net/ServerSocket.h"
#include "Poco/Net/StreamSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Net/WebSocket.h"
#include "Poco/URI.h"
#include "Poco/SharedPtr.h"
#include "Poco/Logger.h"


namespace Poco {
namespace WebTunnel {


class WebTunnel_API WebSocketFactory
	/// WebSocketFactory is used by LocalPortForwarder to create a
	/// Poco::Net::WebSocket instance for tunneling purposes.
	///
	/// Typically, the WebSocketFactory will set up credentials in the
	/// given Poco::Net::HTTPRequest object, then use Poco::Net::HTTPSessionFactory
	/// to create a Poco::Net::HTTPClientSession instance for connecting to
	/// the given URI.
{
public:
	typedef Poco::SharedPtr<WebSocketFactory> Ptr;

	WebSocketFactory();
		/// Creates the WebSocketFactory.

	virtual ~WebSocketFactory();
		/// Destroys the WebSocketFactory.

	virtual Poco::Net::WebSocket* createWebSocket(const Poco::URI& uri, Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response) = 0;
		/// Creates and returns a Poco::Net::WebSocket connected to
		/// the given URI, using the given request and response objects.
};


class WebTunnel_API DefaultWebSocketFactory: public WebSocketFactory
	/// The DefaultWebSocketFactory uses the Poco::Net::HTTPSessionFactory
	/// to create the Poco::Net::HTTPClientSession, and sets up the
	/// Poco::Net::HTTPRequest for HTTP Basic authentication using
	/// the given username and password. If the username is empty,
	/// no authentication is used.
{
public:
	DefaultWebSocketFactory();
		/// Creates the DefaultWebSocketFactory with no credentials.

	DefaultWebSocketFactory(const std::string& username, const std::string& password, Poco::Timespan timeout = Poco::Timespan(30, 0));
		/// Creates the DefaultWebSocketFactory using the given username
		/// and password.

	~DefaultWebSocketFactory();
		/// Destroys the DefaultWebSocketFactory.

	// WebSocketFactory
	Poco::Net::WebSocket* createWebSocket(const Poco::URI& uri, Poco::Net::HTTPRequest& request, Poco::Net::HTTPResponse& response);

private:
	std::string _username;
	std::string _password;
	Poco::Timespan _timeout;
};


class WebTunnel_API LocalPortForwarder
	/// This class forwards a local port to a remote host, using a
	/// WebSocket tunnel connection.
{
public:
	LocalPortForwarder(Poco::UInt16 localPort, Poco::UInt16 remotePort, const Poco::URI& remoteURI, WebSocketFactory::Ptr pWebSocketFactory);
		/// Creates a LocalPortForwarder, using the given localPort to
		/// forward to the given remotePort on the remote system, using a WebSocket
		/// connected to remoteURI.
		///
		/// If localPort is 0, an ephemeral port number is used. This is recommended,
		/// as it avoids conflicts with already used port numbers. The localPort() member
		/// function can be used to obtain the actual port number.
		///
		/// The forwarding socket is always bound to the localhost interface
		/// for security reasons.

	LocalPortForwarder(const Poco::Net::SocketAddress& localAddress, Poco::UInt16 remotePort, const Poco::URI& remoteURI, Poco::Net::TCPServerParams::Ptr pServerParams, WebSocketFactory::Ptr pWebSocketFactory);
		/// Creates a LocalPortForwarder, using the given local address to
		/// forward to the given remotePort on the remote system, using a WebSocket
		/// connected to remoteURI.
		///
		/// If the port number given in localAddress is 0, an ephemeral port number
		/// is used. This is recommended, as it avoids conflicts with already used
		/// port numbers. The localPort() member function can be used to obtain
		/// the actual port number.
		///
		/// The forwarding socket is bound to the address given in localAddress,
		/// which must have either a wildcard IP address, a loopback IP address,
		/// or the IP address of one of the host's network adapters.
		///
		/// The given pServerParams are passed to the Poco::Net::TCPServer handling
		/// connections to the local forwarding port.

	~LocalPortForwarder();
		/// Destroys the LocalPortForwarder, closing all open connections.

	Poco::UInt16 localPort() const;
		/// Returns the local port number.

	Poco::UInt16 remotePort() const;
		/// Returns the remote port number.

	const Poco::URI& remoteURI() const;
		/// Returns the remote host name.

	void setLocalTimeout(Poco::Timespan timeout);
		/// Sets the timeout for the local connection.

	Poco::Timespan getLocalTimeout() const;
		/// Returns the timeout for the local connection.

	void setRemoteTimeout(Poco::Timespan timeout);
		/// Sets the timeout for the remote WebSocket connection.

	Poco::Timespan getRemoteTimeout() const;
		/// Returns the timeout for the remote WebSocket connection.

protected:
	void forward(Poco::Net::StreamSocket& socket);

private:
	Poco::Net::SocketAddress _localAddr;
	Poco::UInt16 _remotePort;
	Poco::URI _remoteURI;
	Poco::Timespan _localTimeout;
	Poco::Timespan _remoteTimeout;
	int _timeoutCount;
	WebSocketFactory::Ptr _pWebSocketFactory;
	Poco::Net::ServerSocket _serverSocket;
	Poco::Net::TCPServer _tcpServer;
	Poco::SharedPtr<SocketDispatcher> _pDispatcher;
	Poco::Logger& _logger;

	LocalPortForwarder();
	LocalPortForwarder(const LocalPortForwarder&);
	LocalPortForwarder& operator = (const LocalPortForwarder&);

	static const std::string SEC_WEBSOCKET_PROTOCOL;
	static const std::string X_WEBTUNNEL_REMOTEPORT;
	static const std::string WEBTUNNEL_PROTOCOL;

	friend class LocalPortForwarderConnection;
};


//
// inlines
//
inline Poco::UInt16 LocalPortForwarder::localPort() const
{
	return _localAddr.port();
}


inline Poco::UInt16 LocalPortForwarder::remotePort() const
{
	return _remotePort;
}


inline const Poco::URI& LocalPortForwarder::remoteURI() const
{
	return _remoteURI;
}


inline Poco::Timespan LocalPortForwarder::getLocalTimeout() const
{
	return _localTimeout;
}


inline Poco::Timespan LocalPortForwarder::getRemoteTimeout() const
{
	return _remoteTimeout;
}


} } // namespace Poco::WebTunnel


#endif // WebTunnel_LocalPortForwarder_INCLUDED
