//
// CounterRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  CounterRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/CounterRemoteObject.h"
#include "IoT/Devices/CounterEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


CounterRemoteObject::CounterRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Counter> pServiceObject):
	IoT::Devices::ICounter(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->countChanged += Poco::delegate(this, &CounterRemoteObject::event__countChanged);
	_pServiceObject->statusChanged += Poco::delegate(this, &CounterRemoteObject::event__statusChanged);
}


CounterRemoteObject::~CounterRemoteObject()
{
	try
	{
		_pServiceObject->countChanged -= Poco::delegate(this, &CounterRemoteObject::event__countChanged);
		_pServiceObject->statusChanged -= Poco::delegate(this, &CounterRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string CounterRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void CounterRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new CounterEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool CounterRemoteObject::remoting__hasEvents() const
{
	return true;
}


void CounterRemoteObject::event__countChanged(const Poco::Int32& data)
{
	countChanged(this, data);
}


void CounterRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


} // namespace Devices
} // namespace IoT

