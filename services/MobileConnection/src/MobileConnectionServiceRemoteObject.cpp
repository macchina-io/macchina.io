//
// MobileConnectionServiceRemoteObject.cpp
//
// Library: IoT/MobileConnection
// Package: Generated
// Module:  MobileConnectionServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/MobileConnection/MobileConnectionServiceRemoteObject.h"
#include "IoT/MobileConnection/MobileConnectionServiceEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace MobileConnection {


MobileConnectionServiceRemoteObject::MobileConnectionServiceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::MobileConnection::MobileConnectionService> pServiceObject):
	IoT::MobileConnection::IMobileConnectionService(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->dataConnected += Poco::delegate(this, &MobileConnectionServiceRemoteObject::event__dataConnected);
	_pServiceObject->dataDisconnected += Poco::delegate(this, &MobileConnectionServiceRemoteObject::event__dataDisconnected);
}


MobileConnectionServiceRemoteObject::~MobileConnectionServiceRemoteObject()
{
	try
	{
		_pServiceObject->dataConnected -= Poco::delegate(this, &MobileConnectionServiceRemoteObject::event__dataConnected);
		_pServiceObject->dataDisconnected -= Poco::delegate(this, &MobileConnectionServiceRemoteObject::event__dataDisconnected);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string MobileConnectionServiceRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void MobileConnectionServiceRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new MobileConnectionServiceEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool MobileConnectionServiceRemoteObject::remoting__hasEvents() const
{
	return true;
}


void MobileConnectionServiceRemoteObject::event__dataConnected()
{
	dataConnected(this);
}


void MobileConnectionServiceRemoteObject::event__dataDisconnected()
{
	dataDisconnected(this);
}


} // namespace MobileConnection
} // namespace IoT

