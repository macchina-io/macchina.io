//
// NetworkEnvironmentServiceImpl.h
//
// $Id$
//
// Library: IoT/NetworkEnvironment
// Package: NetworkEnvironment
// Module:  NetworkEnvironmentServiceImpl
//
// Definition of the NetworkEnvironmentServiceImpl class.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_NetworkEnvironment_NetworkEnvironmentServiceImpl_INCLUDED
#define IoT_NetworkEnvironment_NetworkEnvironmentServiceImpl_INCLUDED


#include "IoT/NetworkEnvironment/NetworkEnvironmentService.h"


namespace IoT {
namespace NetworkEnvironment {


class NetworkMonitorThread;


class IoTNetworkEnvironment_API NetworkEnvironmentServiceImpl: public NetworkEnvironmentService
	/// Implementation of the NetworkEnvironmentService interface.
{
public:
	typedef Poco::SharedPtr<NetworkEnvironmentServiceImpl> Ptr;

	NetworkEnvironmentServiceImpl();
		/// Creates the NetworkEnvironmentServiceImpl.

	~NetworkEnvironmentServiceImpl();
		/// Destroys the NetworkEnvironmentServiceImpl.

	// NetworkEnvironmentService
	std::string findActiveNetworkInterface(IPVersion ipVersion);
	std::vector<NetworkInterface> enumerateInterfaces(int options = 0);
	
private:
	NetworkMonitorThread* _pMonitorThread;
};


} } // namespace IoT::NetworkEnvironment


#endif // IoT_NetworkEnvironment_NetworkEnvironmentServiceImpl_INCLUDED
