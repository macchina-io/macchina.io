//
// TunnelSocket.cpp
//
// Library: WebTunnel
// Package: WebTunnel
// Module:  TunnelSocket
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier:	BSL-1.0
//


#include "Poco/WebTunnel/TunnelSocket.h"
#include "Poco/WebTunnel/TunnelSocketImpl.h"


namespace Poco {
namespace WebTunnel {


TunnelSocket::TunnelSocket(const Poco::Net::Socket& socket):
	Poco::Net::StreamSocket(socket)
{
	if (!dynamic_cast<TunnelSocketImpl*>(impl()))
		throw InvalidArgumentException("Cannot assign incompatible socket");
}


TunnelSocket::TunnelSocket(TunnelSocketImpl* pImpl):
	Poco::Net::StreamSocket(pImpl)
{
}


TunnelSocket::~TunnelSocket()
{
}


TunnelSocket& TunnelSocket::operator = (const Poco::Net::Socket& socket)
{
	if (dynamic_cast<TunnelSocketImpl*>(socket.impl()))
		Socket::operator = (socket);
	else
		throw InvalidArgumentException("Cannot assign incompatible socket");
	return *this;
}


} } // namespace Poco::Net
