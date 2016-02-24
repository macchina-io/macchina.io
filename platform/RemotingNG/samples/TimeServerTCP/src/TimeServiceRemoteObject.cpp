//
// TimeServiceRemoteObject.cpp
//
// Package: Generated
// Module:  TimeServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "TimeServiceRemoteObject.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "TimeServiceEventDispatcher.h"


namespace Services {


TimeServiceRemoteObject::TimeServiceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<Services::TimeService> pServiceObject):
	Services::ITimeService(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->wakeUp += Poco::delegate(this, &TimeServiceRemoteObject::event__wakeUp);
}


TimeServiceRemoteObject::~TimeServiceRemoteObject()
{
	try
	{
		_pServiceObject->wakeUp -= Poco::delegate(this, &TimeServiceRemoteObject::event__wakeUp);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void TimeServiceRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
}


void TimeServiceRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new TimeServiceEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool TimeServiceRemoteObject::remoting__hasEvents() const
{
	return true;
}


void TimeServiceRemoteObject::event__wakeUp(const std::string& data)
{
	wakeUp(this, data);
}


} // namespace Services

