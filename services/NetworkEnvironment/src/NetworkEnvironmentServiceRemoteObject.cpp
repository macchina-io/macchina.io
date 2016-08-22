//
// NetworkEnvironmentServiceRemoteObject.cpp
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


#include "IoT/NetworkEnvironment/NetworkEnvironmentServiceRemoteObject.h"
#include "IoT/NetworkEnvironment/NetworkEnvironmentServiceEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace NetworkEnvironment {


NetworkEnvironmentServiceRemoteObject::NetworkEnvironmentServiceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::NetworkEnvironment::NetworkEnvironmentService> pServiceObject):
	IoT::NetworkEnvironment::INetworkEnvironmentService(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->networkEnvironmentChanged += Poco::delegate(this, &NetworkEnvironmentServiceRemoteObject::event__networkEnvironmentChanged);
}


NetworkEnvironmentServiceRemoteObject::~NetworkEnvironmentServiceRemoteObject()
{
	try
	{
		_pServiceObject->networkEnvironmentChanged -= Poco::delegate(this, &NetworkEnvironmentServiceRemoteObject::event__networkEnvironmentChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string NetworkEnvironmentServiceRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void NetworkEnvironmentServiceRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new NetworkEnvironmentServiceEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool NetworkEnvironmentServiceRemoteObject::remoting__hasEvents() const
{
	return true;
}


void NetworkEnvironmentServiceRemoteObject::event__networkEnvironmentChanged(const IoT::NetworkEnvironment::ChangeType& data)
{
	networkEnvironmentChanged(this, data);
}


} // namespace NetworkEnvironment
} // namespace IoT

