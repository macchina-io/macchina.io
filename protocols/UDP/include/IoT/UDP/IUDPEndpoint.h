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
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
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
	typedef Poco::AutoPtr<IUDPEndpoint> Ptr;

	IUDPEndpoint();
		/// Creates a IUDPEndpoint.

	virtual ~IUDPEndpoint();
		/// Destroys the IUDPEndpoint.

	virtual IoT::UDP::EndpointAddress address() const = 0;
		/// Returns the socket address of this endpoint.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

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
		/// Sends the given payload to the given destination address.
		///
		/// If the endpoint is connected to a default destination address, 
		/// the destination address can be omitted.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < const Packet > packetReceived;
};


} // namespace UDP
} // namespace IoT


#endif // IoT_UDP_IUDPEndpoint_INCLUDED

