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
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
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
	_pServiceObject->statusChanged += Poco::delegate(this, &BarcodeReaderRemoteObject::event__statusChanged);
}


BarcodeReaderRemoteObject::~BarcodeReaderRemoteObject()
{
	try
	{
		_pServiceObject->barcodeRead -= Poco::delegate(this, &BarcodeReaderRemoteObject::event__barcodeRead);
		_pServiceObject->statusChanged -= Poco::delegate(this, &BarcodeReaderRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string BarcodeReaderRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
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


void BarcodeReaderRemoteObject::event__barcodeRead(const IoT::Devices::BarcodeReadEvent& data)
{
	barcodeRead(this, data);
}


void BarcodeReaderRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


} // namespace Devices
} // namespace IoT

