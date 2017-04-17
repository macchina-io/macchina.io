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
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
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
	_pServiceObject->peripheralFound += Poco::delegate(this, &PeripheralBrowserRemoteObject::event__peripheralFound);
}


PeripheralBrowserRemoteObject::~PeripheralBrowserRemoteObject()
{
	try
	{
		_pServiceObject->browseComplete -= Poco::delegate(this, &PeripheralBrowserRemoteObject::event__browseComplete);
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
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new PeripheralBrowserEventDispatcher(this, protocol);
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


void PeripheralBrowserRemoteObject::event__peripheralFound(const IoT::BtLE::PeripheralInfo& data)
{
	peripheralFound(this, data);
}


} // namespace BtLE
} // namespace IoT

