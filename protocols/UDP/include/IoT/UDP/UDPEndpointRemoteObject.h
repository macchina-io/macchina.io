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
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
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
	typedef Poco::AutoPtr<UDPEndpointRemoteObject> Ptr;

	UDPEndpointRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::UDP::UDPEndpoint> pServiceObject);
		/// Creates a UDPEndpointRemoteObject.

	virtual ~UDPEndpointRemoteObject();
		/// Destroys the UDPEndpointRemoteObject.

	IoT::UDP::EndpointAddress address() const;
		/// Returns the socket address of this endpoint.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void sendPacket(const std::vector < char >& payload, const IoT::UDP::EndpointAddress& destination = IoT::UDP::EndpointAddress());
		/// Sends the given payload to the given destination address.
		///
		/// If the endpoint is connected to a default destination address, 
		/// the destination address can be omitted.

protected:
	void event__packetReceived(const IoT::UDP::Packet& data);

private:
	Poco::SharedPtr<IoT::UDP::UDPEndpoint> _pServiceObject;
};


inline IoT::UDP::EndpointAddress UDPEndpointRemoteObject::address() const
{
	return _pServiceObject->address();
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

