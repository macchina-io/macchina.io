//
// NetworkEnvironmentServiceEventDispatcher.h
//
// Library: IoT/NetworkEnvironment
// Package: Generated
// Module:  NetworkEnvironmentServiceEventDispatcher
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_NetworkEnvironment_NetworkEnvironmentServiceEventDispatcher_INCLUDED
#define IoT_NetworkEnvironment_NetworkEnvironmentServiceEventDispatcher_INCLUDED


#include "IoT/NetworkEnvironment/INetworkEnvironmentService.h"
#include "Poco/RemotingNG/EventDispatcher.h"


namespace IoT {
namespace NetworkEnvironment {


class NetworkEnvironmentServiceEventDispatcher: public Poco::RemotingNG::EventDispatcher
	/// The NetworkEnvironmentService can be used to get notifications
	/// about network address and network interface changes.
{
public:
	NetworkEnvironmentServiceEventDispatcher(INetworkEnvironmentService* pInterface, const Poco::RemotingNG::Identifiable::ObjectId& objectId, const std::string& protocol);
		/// Creates a NetworkEnvironmentServiceEventDispatcher.

	virtual ~NetworkEnvironmentServiceEventDispatcher();
		/// Destroys the NetworkEnvironmentServiceEventDispatcher.

	void event__networkEnvironmentChanged(const void* pSender, const IoT::NetworkEnvironment::ChangeType& data);

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

private:
	void event__networkEnvironmentChangedImpl(const std::string& subscriberURI, const IoT::NetworkEnvironment::ChangeType& data);

	static const std::string DEFAULT_NS;
	Poco::RemotingNG::Identifiable::ObjectId _objectId;
	INetworkEnvironmentService* _pInterface;
};


inline const Poco::RemotingNG::Identifiable::TypeId& NetworkEnvironmentServiceEventDispatcher::remoting__typeId() const
{
	return INetworkEnvironmentService::remoting__typeId();
}


} // namespace NetworkEnvironment
} // namespace IoT


#endif // IoT_NetworkEnvironment_NetworkEnvironmentServiceEventDispatcher_INCLUDED

