//
// PeripheralRemoteObject.cpp
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/BtLE/PeripheralRemoteObject.h"
#include "IoT/BtLE/PeripheralEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace BtLE {


PeripheralRemoteObject::PeripheralRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::BtLE::Peripheral> pServiceObject):
	IoT::BtLE::IPeripheral(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->connected += Poco::delegate(this, &PeripheralRemoteObject::event__connected);
	_pServiceObject->disconnected += Poco::delegate(this, &PeripheralRemoteObject::event__disconnected);
	_pServiceObject->error += Poco::delegate(this, &PeripheralRemoteObject::event__error);
	_pServiceObject->indicationReceived += Poco::delegate(this, &PeripheralRemoteObject::event__indicationReceived);
	_pServiceObject->notificationReceived += Poco::delegate(this, &PeripheralRemoteObject::event__notificationReceived);
}


PeripheralRemoteObject::~PeripheralRemoteObject()
{
	try
	{
		_pServiceObject->connected -= Poco::delegate(this, &PeripheralRemoteObject::event__connected);
		_pServiceObject->disconnected -= Poco::delegate(this, &PeripheralRemoteObject::event__disconnected);
		_pServiceObject->error -= Poco::delegate(this, &PeripheralRemoteObject::event__error);
		_pServiceObject->indicationReceived -= Poco::delegate(this, &PeripheralRemoteObject::event__indicationReceived);
		_pServiceObject->notificationReceived -= Poco::delegate(this, &PeripheralRemoteObject::event__notificationReceived);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string PeripheralRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void PeripheralRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new PeripheralEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool PeripheralRemoteObject::remoting__hasEvents() const
{
	return true;
}


void PeripheralRemoteObject::event__connected()
{
	connected(this);
}


void PeripheralRemoteObject::event__disconnected()
{
	disconnected(this);
}


void PeripheralRemoteObject::event__error(const std::string& data)
{
	error(this, data);
}


void PeripheralRemoteObject::event__indicationReceived(const IoT::BtLE::Indication& data)
{
	indicationReceived(this, data);
}


void PeripheralRemoteObject::event__notificationReceived(const IoT::BtLE::Notification& data)
{
	notificationReceived(this, data);
}


} // namespace BtLE
} // namespace IoT

