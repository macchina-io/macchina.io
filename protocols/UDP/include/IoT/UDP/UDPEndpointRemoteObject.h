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
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace UDP {


class UDPEndpointRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::UDP::IUDPEndpoint
	/// The UDPEndpoint is used to receive and send UDP packets.
{
public:
	typedef Poco::AutoPtr<UDPEndpointRemoteObject> Ptr;

	UDPEndpointRemoteObject();
		/// Creates a UDPEndpointRemoteObject.

	virtual ~UDPEndpointRemoteObject();
		/// Destroys the UDPEndpointRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& UDPEndpointRemoteObject::remoting__typeId() const
{
	return IUDPEndpoint::remoting__typeId();
}


} // namespace UDP
} // namespace IoT


#endif // IoT_UDP_UDPEndpointRemoteObject_INCLUDED

