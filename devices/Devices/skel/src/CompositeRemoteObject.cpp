//
// CompositeRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  CompositeRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/CompositeRemoteObject.h"
#include "IoT/Devices/CompositeEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


CompositeRemoteObject::CompositeRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Composite> pServiceObject):
	IoT::Devices::IComposite(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->statusChanged += Poco::delegate(this, &CompositeRemoteObject::event__statusChanged);
}


CompositeRemoteObject::~CompositeRemoteObject()
{
	try
	{
		_pServiceObject->statusChanged -= Poco::delegate(this, &CompositeRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string CompositeRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void CompositeRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new CompositeEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool CompositeRemoteObject::remoting__hasEvents() const
{
	return true;
}


void CompositeRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


} // namespace Devices
} // namespace IoT

