//
// PeripheralBrowserStub.cpp
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralBrowserStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/BtLE/PeripheralBrowserStub.h"
#include "IoT/BtLE/PeripheralBrowserEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace BtLE {


PeripheralBrowserStub::PeripheralBrowserStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::BtLE::PeripheralBrowser> pServiceObject):
	IoT::BtLE::PeripheralBrowserRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->browseComplete += Poco::delegate(this, &PeripheralBrowserStub::event__browseComplete);
	_pServiceObject->peripheralFound += Poco::delegate(this, &PeripheralBrowserStub::event__peripheralFound);
}


PeripheralBrowserStub::~PeripheralBrowserStub()
{
	try
	{
		_pServiceObject->browseComplete -= Poco::delegate(this, &PeripheralBrowserStub::event__browseComplete);
		_pServiceObject->peripheralFound -= Poco::delegate(this, &PeripheralBrowserStub::event__peripheralFound);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string PeripheralBrowserStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void PeripheralBrowserStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new PeripheralBrowserEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool PeripheralBrowserStub::remoting__hasEvents() const
{
	return true;
}


void PeripheralBrowserStub::event__browseComplete()
{
	browseComplete(this);
}


void PeripheralBrowserStub::event__peripheralFound(const IoT::BtLE::PeripheralInfo& data)
{
	peripheralFound(this, data);
}


} // namespace BtLE
} // namespace IoT

