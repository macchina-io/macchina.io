//
// NetworkEnvironmentServiceStub.h
//
// Library: IoT/NetworkEnvironment
// Package: Generated
// Module:  NetworkEnvironmentServiceStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_NetworkEnvironment_NetworkEnvironmentServiceStub_INCLUDED
#define IoT_NetworkEnvironment_NetworkEnvironmentServiceStub_INCLUDED


#include "IoT/NetworkEnvironment/NetworkEnvironmentServiceRemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace NetworkEnvironment {


class NetworkEnvironmentServiceStub: public IoT::NetworkEnvironment::NetworkEnvironmentServiceRemoteObject
	/// The NetworkEnvironmentService can be used to get notifications
	/// about network address and network interface changes.
{
public:
	typedef Poco::AutoPtr<NetworkEnvironmentServiceStub> Ptr;

	NetworkEnvironmentServiceStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::NetworkEnvironment::NetworkEnvironmentService> pServiceObject);
		/// Creates a NetworkEnvironmentServiceStub.

	virtual ~NetworkEnvironmentServiceStub();
		/// Destroys the NetworkEnvironmentServiceStub.

	std::vector < IoT::NetworkEnvironment::NetworkInterface > enumerateInterfaces(int options = int(0));
		/// Returns a vector containing available network interfaces.
		/// The options parameter can be used to include non-IP interfaces or
		/// interfaces that are down.

	virtual std::string findActiveNetworkInterface(IoT::NetworkEnvironment::IPVersion ipVersion);
		/// Finds and returns the name of the first active network interface that 
		/// supports the given IP protocol version.
		///
		/// Throws a Poco::NotFoundException if no suitable network interface is found.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true));

	virtual void remoting__enableRemoteEvents(const std::string& protocol);

	virtual bool remoting__hasEvents() const;

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

protected:
	void event__networkEnvironmentChanged(const IoT::NetworkEnvironment::ChangeType& data);

private:
	Poco::SharedPtr<IoT::NetworkEnvironment::NetworkEnvironmentService> _pServiceObject;
};


inline std::vector < IoT::NetworkEnvironment::NetworkInterface > NetworkEnvironmentServiceStub::enumerateInterfaces(int options)
{
	return _pServiceObject->enumerateInterfaces(options);
}


inline std::string NetworkEnvironmentServiceStub::findActiveNetworkInterface(IoT::NetworkEnvironment::IPVersion ipVersion)
{
	return _pServiceObject->findActiveNetworkInterface(ipVersion);
}


inline const Poco::RemotingNG::Identifiable::TypeId& NetworkEnvironmentServiceStub::remoting__typeId() const
{
	return INetworkEnvironmentService::remoting__typeId();
}


} // namespace NetworkEnvironment
} // namespace IoT


#endif // IoT_NetworkEnvironment_NetworkEnvironmentServiceStub_INCLUDED

