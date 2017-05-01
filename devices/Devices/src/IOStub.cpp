//
// IOStub.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IOStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/IOStub.h"
#include "IoT/Devices/IOEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


IOStub::IOStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::IO> pServiceObject):
	IoT::Devices::IORemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->stateChanged += Poco::delegate(this, &IOStub::event__stateChanged);
}


IOStub::~IOStub()
{
	try
	{
		_pServiceObject->stateChanged -= Poco::delegate(this, &IOStub::event__stateChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string IOStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void IOStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new IOEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool IOStub::remoting__hasEvents() const
{
	return true;
}


void IOStub::event__stateChanged(const bool& data)
{
	stateChanged(this, data);
}


} // namespace Devices
} // namespace IoT

