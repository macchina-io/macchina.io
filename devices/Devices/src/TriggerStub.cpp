//
// TriggerStub.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  TriggerStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/TriggerStub.h"
#include "IoT/Devices/TriggerEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


TriggerStub::TriggerStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Trigger> pServiceObject):
	IoT::Devices::TriggerRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->stateChanged += Poco::delegate(this, &TriggerStub::event__stateChanged);
}


TriggerStub::~TriggerStub()
{
	try
	{
		_pServiceObject->stateChanged -= Poco::delegate(this, &TriggerStub::event__stateChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string TriggerStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void TriggerStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new TriggerEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool TriggerStub::remoting__hasEvents() const
{
	return true;
}


void TriggerStub::event__stateChanged(const bool& data)
{
	stateChanged(this, data);
}


} // namespace Devices
} // namespace IoT

