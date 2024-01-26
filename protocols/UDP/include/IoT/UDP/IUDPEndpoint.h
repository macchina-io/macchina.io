//
// IUDPEndpoint.h
//
// Library: IoT/UDP
// Package: Generated
// Module:  IUDPEndpoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_UDP_IUDPEndpoint_INCLUDED
#define IoT_UDP_IUDPEndpoint_INCLUDED


#include "IoT/UDP/UDPEndpoint.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace UDP {


class IUDPEndpoint: public Poco::OSP::Service
	/// The UDPEndpoint is used to receive and send UDP packets.
{
public:
	using Ptr = Poco::AutoPtr<IUDPEndpoint>;

	IUDPEndpoint();
		/// Creates a IUDPEndpoint.

	virtual ~IUDPEndpoint();
		/// Destroys the IUDPEndpoint.

	virtual IoT::UDP::EndpointAddress address() const = 0;
		/// Returns the local address the socket of the endpoint has
		/// been bound to.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual Poco::Nullable < IoT::UDP::EndpointAddress > remoteAddress() const = 0;
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

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void sendPacket(const std::vector < char >& payload, const IoT::UDP::EndpointAddress& destination = IoT::UDP::EndpointAddress()) = 0;
		/// Sends the given payload to the given destination address,
		/// or to the remote address, if one has been configured.
		///
		/// If the endpoint has been connected to a remote address,
		/// the destination address must be omitted.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < const IoT::UDP::Packet > packetReceived;
};


} // namespace UDP
} // namespace IoT


#endif // IoT_UDP_IUDPEndpoint_INCLUDED

