//
// BarcodeReaderStub.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  BarcodeReaderStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/BarcodeReaderStub.h"
#include "IoT/Devices/BarcodeReaderEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


BarcodeReaderStub::BarcodeReaderStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::BarcodeReader> pServiceObject):
	IoT::Devices::BarcodeReaderRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
	_pServiceObject->barcodeRead += Poco::delegate(this, &BarcodeReaderStub::event__barcodeRead);
}


BarcodeReaderStub::~BarcodeReaderStub()
{
	try
	{
		_pServiceObject->barcodeRead -= Poco::delegate(this, &BarcodeReaderStub::event__barcodeRead);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string BarcodeReaderStub::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void BarcodeReaderStub::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new BarcodeReaderEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool BarcodeReaderStub::remoting__hasEvents() const
{
	return true;
}


void BarcodeReaderStub::event__barcodeRead(const IoT::Devices::BarcodeReadEvent& data)
{
	barcodeRead(this, data);
}


} // namespace Devices
} // namespace IoT

