//
// UDPEndpointSkeleton.h
//
// Library: IoT/UDP
// Package: Generated
// Module:  UDPEndpointSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_UDP_UDPEndpointSkeleton_INCLUDED
#define IoT_UDP_UDPEndpointSkeleton_INCLUDED


#include "IoT/UDP/UDPEndpointRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace UDP {


class UDPEndpointSkeleton: public Poco::RemotingNG::Skeleton
	/// The UDPEndpoint is used to receive and send UDP packets.
{
public:
	UDPEndpointSkeleton();
		/// Creates a UDPEndpointSkeleton.

	virtual ~UDPEndpointSkeleton();
		/// Destroys a UDPEndpointSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& UDPEndpointSkeleton::remoting__typeId() const
{
	return IUDPEndpoint::remoting__typeId();
}


} // namespace UDP
} // namespace IoT


#endif // IoT_UDP_UDPEndpointSkeleton_INCLUDED

