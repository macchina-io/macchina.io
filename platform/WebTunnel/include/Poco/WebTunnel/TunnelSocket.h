//
// TunnelSocket.h
//
// Library: WebTunnel
// Package: WebTunnel
// Module:  TunnelSocket
//
// Definition of the TunnelSocket class.
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#ifndef WebTunnel_TunnelSocket_INCLUDED
#define WebTunnel_TunnelSocket_INCLUDED


#include "Poco/WebTunnel/WebTunnel.h"
#include "Poco/Net/StreamSocket.h"


namespace Poco {
namespace WebTunnel {


class TunnelSocketImpl;


class WebTunnel_API TunnelSocket: public Poco::Net::StreamSocket
	/// This class implements a StreamSocket that
	/// works with a WebTunnel channel.
{
public:
	TunnelSocket(const Poco::Net::Socket& socket);
		/// Creates a TunnelSocket from another Socket, which must be a WebSocket,
		/// otherwise a Poco::InvalidArgumentException will be thrown.

	TunnelSocket(TunnelSocketImpl* pSocketImpl);
		/// Creates a TunnelSocket with the given TunnelSocketImpl.

	virtual ~TunnelSocket();
		/// Destroys the StreamSocket.

	TunnelSocket& operator = (const Poco::Net::Socket& socket);
		/// Assignment operator.
		///
		/// The other socket must be a TunnelSocket, otherwise a Poco::InvalidArgumentException
		/// will be thrown.

private:
	TunnelSocket();
};


} } // namespace Poco::WebTunnel


#endif // WebTunnel_TunnelSocket_INCLUDED
