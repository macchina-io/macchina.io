//
// UDPEndpointEventDispatcher.h
//
// Library: IoT/UDP
// Package: Generated
// Module:  UDPEndpointEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_UDP_UDPEndpointEventDispatcher_INCLUDED
#define IoT_UDP_UDPEndpointEventDispatcher_INCLUDED


#include "IoT/UDP/UDPEndpointRemoteObject.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace UDP {


class UDPEndpointEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The UDPEndpoint is used to receive and send UDP packets.
{
public:
	UDPEndpointEventDispatcher(UDPEndpointRemoteObject* pRemoteObject, const std::string& protocol);
		/// Creates a UDPEndpointEventDispatcher.

	virtual ~UDPEndpointEventDispatcher();
		/// Destroys the UDPEndpointEventDispatcher.

	void event__packetReceived(const void* pSender, const IoT::UDP::Packet& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__packetReceivedImpl(const std::string& subscriberURI, const IoT::UDP::Packet& data);

	static const std::string DEFAULT_NS;
	UDPEndpointRemoteObject* _pRemoteObject;
};


inline const Poco::RemotingNG::Identifiable::TypeId& UDPEndpointEventDispatcher::remoting__typeId() const
{
	return IUDPEndpoint::remoting__typeId();
}


} // namespace UDP
} // namespace IoT


#endif // IoT_UDP_UDPEndpointEventDispatcher_INCLUDED

