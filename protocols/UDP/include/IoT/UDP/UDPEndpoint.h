//
// UDPEndpoint.h
//
// Library: IoT/UDP
// Package: UDPEndpoint
// Module:  UDPEndpoint
///
/// Definition of the UDPEndpoint interface.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_UDP_UDPEndpoint_INCLUDED
#define IoT_UDP_UDPEndpoint_INCLUDED


#include "IoT/UDP/UDP.h"
#include "Poco/BasicEvent.h"
#include "Poco/SharedPtr.h"
#include "Poco/Nullable.h"
#include <vector>


namespace IoT {
namespace UDP {


//@ serialize
struct EndpointAddress
	/// A UDP endpoint address consisting of IP address and port number.
{
	EndpointAddress():
		port(0)
	{
	}

	std::string ipAddress;
		/// IP address in string representation (e.g., "192.168.1.42" or "fe80::e6ce:8fff:fe4a:edd0").

	Poco::UInt16 port;
		/// UDP port number.
};


//@ serialize
struct Packet
	/// A UDP packet.
{
	EndpointAddress source;
		/// Source endpoint address.

	EndpointAddress destination;
		/// Destination endpoint address.

	std::vector<char> payload;
		/// Payload data.
};


//@ remote
class IoTUDP_API UDPEndpoint
	/// The UDPEndpoint is used to receive and send UDP packets.
{
public:
	using Ptr = Poco::SharedPtr<UDPEndpoint>;

	Poco::BasicEvent<const Packet> packetReceived;
		/// Fired when an UDP packet has been received.

	UDPEndpoint();
		/// Creates the UDPEndpoint.

	virtual ~UDPEndpoint();
		/// Destroys the UDPEndpoint.

	virtual EndpointAddress address() const = 0;
		/// Returns the local address the socket of the endpoint has
		/// been bound to.

	virtual Poco::Nullable<EndpointAddress> remoteAddress() const = 0;
		/// Returns the remote address the socket of the endpoint
		/// is "connected" to, or null if the socket is not connected.
		///
		/// If a remote address has been specified in the configuration,
		/// packets can only be sent to that address and furthermore, 
		/// only packets sent from the remote address are accepted.
		///
		/// Note that UDP sockets are not actually connected, the
		/// remote address merely acts as the default destination
		/// address for sendPacket().

	//@ $destination = {optional}
	virtual void sendPacket(const std::vector<char>& payload, const EndpointAddress& destination = EndpointAddress()) = 0;
		/// Sends the given payload to the given destination address,
		/// or to the remote address, if one has been configured.
		///
		/// If the endpoint has been connected to a remote address,
		/// the destination address must be omitted.
};


} } // namespace IoT::UDP


#endif // IoT_UDP_UDPEndpoint_INCLUDED
