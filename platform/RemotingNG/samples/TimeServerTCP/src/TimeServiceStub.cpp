//
// TimeServiceStub.cpp
//
// Package: Generated
// Module:  TimeServiceStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2006-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "TimeServiceStub.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"
#include "TimeServiceEventDispatcher.h"


namespace Services {


TimeServiceStub::TimeServiceStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<Services::TimeService> pServiceObject):
	Services::TimeServiceRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->wakeUp += Poco::delegate(this, &TimeServiceStub::event__wakeUp);
}


TimeServiceStub::~TimeServiceStub()
{
	try
	{
		_pServiceObject->wakeUp -= Poco::delegate(this, &TimeServiceStub::event__wakeUp);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string TimeServiceStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void TimeServiceStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new TimeServiceEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool TimeServiceStub::remoting__hasEvents() const
{
	return true;
}


void TimeServiceStub::event__wakeUp(const std::string& data)
{
	wakeUp(this, data);
}


} // namespace Services

