//
// NetworkEnvironmentServiceStub.cpp
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


#include "IoT/NetworkEnvironment/NetworkEnvironmentServiceStub.h"
#include "IoT/NetworkEnvironment/NetworkEnvironmentServiceEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace NetworkEnvironment {


NetworkEnvironmentServiceStub::NetworkEnvironmentServiceStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::NetworkEnvironment::NetworkEnvironmentService> pServiceObject):
	IoT::NetworkEnvironment::NetworkEnvironmentServiceRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->networkEnvironmentChanged += Poco::delegate(this, &NetworkEnvironmentServiceStub::event__networkEnvironmentChanged);
}


NetworkEnvironmentServiceStub::~NetworkEnvironmentServiceStub()
{
	try
	{
		_pServiceObject->networkEnvironmentChanged -= Poco::delegate(this, &NetworkEnvironmentServiceStub::event__networkEnvironmentChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string NetworkEnvironmentServiceStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void NetworkEnvironmentServiceStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new NetworkEnvironmentServiceEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool NetworkEnvironmentServiceStub::remoting__hasEvents() const
{
	return true;
}


void NetworkEnvironmentServiceStub::event__networkEnvironmentChanged(const IoT::NetworkEnvironment::ChangeType& data)
{
	networkEnvironmentChanged(this, data);
}


} // namespace NetworkEnvironment
} // namespace IoT

