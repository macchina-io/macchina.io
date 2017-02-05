//
// UDPEndpointImpl.h
//
// $Id$
//
// Library: IoT/UDP
// Package: UDPEndpoint
// Module:  UDPEndpoint
///
/// Default implementation of the UDPEndpoint interface.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_UDP_UDPEndpointImpl_INCLUDED
#define IoT_UDP_UDPEndpointImpl_INCLUDED


#include "IoT/UDP/UDPEndpoint.h"
#include "Poco/Net/DatagramSocket.h"
#include "Poco/Net/SocketAddress.h"
#include "Poco/Activity.h"
#include "Poco/Logger.h"


namespace IoT {
namespace UDP {


//@ remote
class IoTUDP_API UDPEndpointImpl: public UDPEndpoint
	/// The default implementation of UDPEndpoint
{
public:
	typedef Poco::SharedPtr<UDPEndpointImpl> Ptr;

	UDPEndpointImpl(const Poco::Net::SocketAddress& addr);
		/// Creates the UDPEndpointImpl using the given socket address.

	~UDPEndpointImpl();
		/// Destroys the UDPEndpointImpl.
		
	void connect(const Poco::Net::SocketAddress& addr);
		/// Connects the socket to the given address.
		
	const Poco::Net::DatagramSocket& socket() const;
		/// Returns the underlying socket.

	Poco::Net::DatagramSocket& socket();
		/// Returns the underlying socket.

	// UDPEndpoint
	EndpointAddress address() const;
	void sendPacket(const std::vector<char>& payload, const EndpointAddress& destination);

protected:
	void handlePackets();
	
	enum
	{
		MAX_MESSAGE_SIZE = 4096,
		POLL_TIMEOUT     = 200000
	};

private:
	Poco::Net::DatagramSocket _socket;
	Poco::Activity<UDPEndpointImpl> _handlePackets;
	Poco::Logger& _logger;
};


//
// inlines
//
inline const Poco::Net::DatagramSocket& UDPEndpointImpl::socket() const
{
	return _socket;
}


inline Poco::Net::DatagramSocket& UDPEndpointImpl::socket()
{
	return _socket;
}


} } // namespace IoT::UDP


#endif // IoT_UDP_UDPEndpointImpl_INCLUDED
