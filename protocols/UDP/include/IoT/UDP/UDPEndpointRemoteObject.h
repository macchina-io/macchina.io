//
// UDPEndpointRemoteObject.h
//
// Library: IoT/UDP
// Package: Generated
// Module:  UDPEndpointRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_UDP_UDPEndpointRemoteObject_INCLUDED
#define IoT_UDP_UDPEndpointRemoteObject_INCLUDED


#include "IoT/UDP/IUDPEndpoint.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace UDP {


class UDPEndpointRemoteObject: public IoT::UDP::IUDPEndpoint, public Poco::RemotingNG::RemoteObject
	/// The UDPEndpoint is used to receive and send UDP packets.
{
public:
	using Ptr = Poco::AutoPtr<UDPEndpointRemoteObject>;

	UDPEndpointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::UDP::UDPEndpoint> pServiceObject);
		/// Creates a UDPEndpointRemoteObject.

	virtual ~UDPEndpointRemoteObject();
		/// Destroys the UDPEndpointRemoteObject.

	IoT::UDP::EndpointAddress address() const;
		/// Returns the local address the socket of the endpoint has
		/// been bound to.

	Poco::Nullable < IoT::UDP::EndpointAddress > remoteAddress() const;
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

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void sendPacket(const std::vector < char >& payload, const IoT::UDP::EndpointAddress& destination = IoT::UDP::EndpointAddress());
		/// Sends the given payload to the given destination address,
		/// or to the remote address, if one has been configured.
		///
		/// If the endpoint has been connected to a remote address,
		/// the destination address must be omitted.

protected:
	void event__packetReceived(const IoT::UDP::Packet& data);

private:
	Poco::SharedPtr<IoT::UDP::UDPEndpoint> _pServiceObject;
};


inline IoT::UDP::EndpointAddress UDPEndpointRemoteObject::address() const
{
	return _pServiceObject->address();
}


inline Poco::Nullable < IoT::UDP::EndpointAddress > UDPEndpointRemoteObject::remoteAddress() const
{
	return _pServiceObject->remoteAddress();
}


inline const Poco::RemotingNG::Identifiable::TypeId& UDPEndpointRemoteObject::remoting__typeId() const
{
	return IUDPEndpoint::remoting__typeId();
}


inline void UDPEndpointRemoteObject::sendPacket(const std::vector < char >& payload, const IoT::UDP::EndpointAddress& destination)
{
	_pServiceObject->sendPacket(payload, destination);
}


} // namespace UDP
} // namespace IoT


#endif // IoT_UDP_UDPEndpointRemoteObject_INCLUDED

