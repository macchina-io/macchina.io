//
// NetworkEnvironmentServiceRemoteObject.h
//
// Library: IoT/NetworkEnvironment
// Package: Generated
// Module:  NetworkEnvironmentServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_NetworkEnvironment_NetworkEnvironmentServiceRemoteObject_INCLUDED
#define IoT_NetworkEnvironment_NetworkEnvironmentServiceRemoteObject_INCLUDED


#include "IoT/NetworkEnvironment/INetworkEnvironmentService.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace NetworkEnvironment {


class NetworkEnvironmentServiceRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::NetworkEnvironment::INetworkEnvironmentService
	/// The NetworkEnvironmentService can be used to get notifications
	/// about network address and network interface changes.
{
public:
	typedef Poco::AutoPtr<NetworkEnvironmentServiceRemoteObject> Ptr;

	NetworkEnvironmentServiceRemoteObject();
		/// Creates a NetworkEnvironmentServiceRemoteObject.

	virtual ~NetworkEnvironmentServiceRemoteObject();
		/// Destroys the NetworkEnvironmentServiceRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& NetworkEnvironmentServiceRemoteObject::remoting__typeId() const
{
	return INetworkEnvironmentService::remoting__typeId();
}


} // namespace NetworkEnvironment
} // namespace IoT


#endif // IoT_NetworkEnvironment_NetworkEnvironmentServiceRemoteObject_INCLUDED

