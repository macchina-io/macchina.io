//
// NetworkEnvironmentServiceSkeleton.h
//
// Library: IoT/NetworkEnvironment
// Package: Generated
// Module:  NetworkEnvironmentServiceSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_NetworkEnvironment_NetworkEnvironmentServiceSkeleton_INCLUDED
#define IoT_NetworkEnvironment_NetworkEnvironmentServiceSkeleton_INCLUDED


#include "IoT/NetworkEnvironment/NetworkEnvironmentServiceRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace NetworkEnvironment {


class NetworkEnvironmentServiceSkeleton: public Poco::RemotingNG::Skeleton
	/// The NetworkEnvironmentService can be used to get notifications
	/// about network address and network interface changes.
{
public:
	NetworkEnvironmentServiceSkeleton();
		/// Creates a NetworkEnvironmentServiceSkeleton.

	virtual ~NetworkEnvironmentServiceSkeleton();
		/// Destroys a NetworkEnvironmentServiceSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& NetworkEnvironmentServiceSkeleton::remoting__typeId() const
{
	return INetworkEnvironmentService::remoting__typeId();
}


} // namespace NetworkEnvironment
} // namespace IoT


#endif // IoT_NetworkEnvironment_NetworkEnvironmentServiceSkeleton_INCLUDED

