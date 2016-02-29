//
// SocketFactory.cpp
//
// $Id: //poco/1.7/RemotingNG/TCP/src/SocketFactory.cpp#1 $
//
// Library: RemotingNG/TCP
// Package: TCP
// Module:  SocketFactory
//
// Copyright (c) 2006-2012, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/RemotingNG/TCP/SocketFactory.h"
#include "Poco/Net/SocketAddress.h"


namespace Poco {
namespace RemotingNG {
namespace TCP {


SocketFactory::SocketFactory()
{
}

	
SocketFactory::~SocketFactory()
{
}


Poco::Net::StreamSocket SocketFactory::createSocket(const Poco::URI& uri)
{
	Poco::Net::SocketAddress addr(uri.getHost(), uri.getPort());
	Poco::Net::StreamSocket ss(addr);
	ss.setNoDelay(true);
	return ss;
}


} } } // namespace Poco::RemotingNG::TCP
