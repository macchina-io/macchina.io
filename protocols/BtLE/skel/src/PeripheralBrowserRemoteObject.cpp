//
// PeripheralBrowserRemoteObject.cpp
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralBrowserRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/BtLE/PeripheralBrowserRemoteObject.h"
#include "IoT/BtLE/PeripheralBrowserEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace BtLE {


PeripheralBrowserRemoteObject::PeripheralBrowserRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::BtLE::PeripheralBrowser> pServiceObject):
	IoT::BtLE::IPeripheralBrowser(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->browseComplete += Poco::delegate(this, &PeripheralBrowserRemoteObject::event__browseComplete);
	_pServiceObject->browseError += Poco::delegate(this, &PeripheralBrowserRemoteObject::event__browseError);
	_pServiceObject->browseStarted += Poco::delegate(this, &PeripheralBrowserRemoteObject::event__browseStarted);
	_pServiceObject->peripheralFound += Poco::delegate(this, &PeripheralBrowserRemoteObject::event__peripheralFound);
}


PeripheralBrowserRemoteObject::~PeripheralBrowserRemoteObject()
{
	try
	{
		_pServiceObject->browseComplete -= Poco::delegate(this, &PeripheralBrowserRemoteObject::event__browseComplete);
		_pServiceObject->browseError -= Poco::delegate(this, &PeripheralBrowserRemoteObject::event__browseError);
		_pServiceObject->browseStarted -= Poco::delegate(this, &PeripheralBrowserRemoteObject::event__browseStarted);
		_pServiceObject->peripheralFound -= Poco::delegate(this, &PeripheralBrowserRemoteObject::event__peripheralFound);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string PeripheralBrowserRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void PeripheralBrowserRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new PeripheralBrowserEventDispatcher(this, remoting__objectId(), protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool PeripheralBrowserRemoteObject::remoting__hasEvents() const
{
	return true;
}


void PeripheralBrowserRemoteObject::event__browseComplete()
{
	browseComplete(this);
}


void PeripheralBrowserRemoteObject::event__browseError(const std::string& data)
{
	browseError(this, data);
}


void PeripheralBrowserRemoteObject::event__browseStarted()
{
	browseStarted(this);
}


void PeripheralBrowserRemoteObject::event__peripheralFound(const IoT::BtLE::PeripheralInfo& data)
{
	peripheralFound(this, data);
}


} // namespace BtLE
} // namespace IoT

