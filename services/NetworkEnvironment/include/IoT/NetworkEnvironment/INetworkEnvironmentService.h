//
// INetworkEnvironmentService.h
//
// Library: IoT/NetworkEnvironment
// Package: Generated
// Module:  INetworkEnvironmentService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_NetworkEnvironment_INetworkEnvironmentService_INCLUDED
#define IoT_NetworkEnvironment_INetworkEnvironmentService_INCLUDED


#include "IoT/NetworkEnvironment/NetworkEnvironmentService.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace NetworkEnvironment {


class INetworkEnvironmentService: public Poco::OSP::Service
	/// The NetworkEnvironmentService can be used to get notifications
	/// about network address and network interface changes.
{
public:
	typedef Poco::AutoPtr<INetworkEnvironmentService> Ptr;

	INetworkEnvironmentService();
		/// Creates a INetworkEnvironmentService.

	virtual ~INetworkEnvironmentService();
		/// Destroys the INetworkEnvironmentService.

	virtual std::vector < IoT::NetworkEnvironment::NetworkInterface > enumerateInterfaces(int options = int(0)) = 0;
		/// Returns a vector containing available network interfaces.
		/// The options parameter can be used to include non-IP interfaces or
		/// interfaces that are down.

	virtual std::string findActiveNetworkInterface(IoT::NetworkEnvironment::IPVersion ipVersion) = 0;
		/// Finds and returns the name of the first active network interface that 
		/// supports the given IP protocol version.
		///
		/// Throws a Poco::NotFoundException if no suitable network interface is found.

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

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	Poco::BasicEvent < const ChangeType > networkEnvironmentChanged;
};


} // namespace NetworkEnvironment
} // namespace IoT


#endif // IoT_NetworkEnvironment_INetworkEnvironmentService_INCLUDED

