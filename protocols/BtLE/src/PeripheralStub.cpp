//
// PeripheralStub.cpp
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/BtLE/PeripheralStub.h"
#include "IoT/BtLE/PeripheralEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace BtLE {


PeripheralStub::PeripheralStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::BtLE::Peripheral> pServiceObject):
	IoT::BtLE::PeripheralRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->connected += Poco::delegate(this, &PeripheralStub::event__connected);
	_pServiceObject->disconnected += Poco::delegate(this, &PeripheralStub::event__disconnected);
	_pServiceObject->error += Poco::delegate(this, &PeripheralStub::event__error);
	_pServiceObject->indicationReceived += Poco::delegate(this, &PeripheralStub::event__indicationReceived);
	_pServiceObject->notificationReceived += Poco::delegate(this, &PeripheralStub::event__notificationReceived);
}


PeripheralStub::~PeripheralStub()
{
	try
	{
		_pServiceObject->connected -= Poco::delegate(this, &PeripheralStub::event__connected);
		_pServiceObject->disconnected -= Poco::delegate(this, &PeripheralStub::event__disconnected);
		_pServiceObject->error -= Poco::delegate(this, &PeripheralStub::event__error);
		_pServiceObject->indicationReceived -= Poco::delegate(this, &PeripheralStub::event__indicationReceived);
		_pServiceObject->notificationReceived -= Poco::delegate(this, &PeripheralStub::event__notificationReceived);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string PeripheralStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void PeripheralStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new PeripheralEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool PeripheralStub::remoting__hasEvents() const
{
	return true;
}


void PeripheralStub::event__connected()
{
	connected(this);
}


void PeripheralStub::event__disconnected()
{
	disconnected(this);
}


void PeripheralStub::event__error(const std::string& data)
{
	error(this, data);
}


void PeripheralStub::event__indicationReceived(const IoT::BtLE::Indication& data)
{
	indicationReceived(this, data);
}


void PeripheralStub::event__notificationReceived(const IoT::BtLE::Notification& data)
{
	notificationReceived(this, data);
}


} // namespace BtLE
} // namespace IoT

