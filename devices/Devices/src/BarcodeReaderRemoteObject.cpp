//
// BarcodeReaderRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  BarcodeReaderRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/BarcodeReaderRemoteObject.h"
#include "IoT/Devices/BarcodeReaderEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


BarcodeReaderRemoteObject::BarcodeReaderRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::BarcodeReader> pServiceObject):
	IoT::Devices::IBarcodeReader(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->barcodeRead += Poco::delegate(this, &BarcodeReaderRemoteObject::event__barcodeRead);
}


BarcodeReaderRemoteObject::~BarcodeReaderRemoteObject()
{
	try
	{
		_pServiceObject->barcodeRead -= Poco::delegate(this, &BarcodeReaderRemoteObject::event__barcodeRead);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


void BarcodeReaderRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
}


void BarcodeReaderRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new BarcodeReaderEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool BarcodeReaderRemoteObject::remoting__hasEvents() const
{
	return true;
}


void BarcodeReaderRemoteObject::event__barcodeRead(const std::string& data)
{
	barcodeRead(this, data);
}


} // namespace Devices
} // namespace IoT

