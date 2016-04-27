//
// BarcodeReaderServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  BarcodeReaderServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/BarcodeReaderServerHelper.h"
#include "IoT/Devices/BarcodeReaderEventDispatcher.h"
#include "IoT/Devices/BarcodeReaderSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	static Poco::SingletonHolder<BarcodeReaderServerHelper> shBarcodeReaderServerHelper;
}


BarcodeReaderServerHelper::BarcodeReaderServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerSkeleton("IoT.Devices.BarcodeReader", new BarcodeReaderSkeleton);
}


BarcodeReaderServerHelper::~BarcodeReaderServerHelper()
{
	try
	{
		_pORB->unregisterSkeleton("IoT.Devices.BarcodeReader", true);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string BarcodeReaderServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::BarcodeReaderRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return BarcodeReaderServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


Poco::AutoPtr<IoT::Devices::BarcodeReaderRemoteObject> BarcodeReaderServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::BarcodeReader> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new BarcodeReaderRemoteObject(oid, pServiceObject);
}


void BarcodeReaderServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<BarcodeReaderRemoteObject> pRemoteObject = pIdentifiable.cast<BarcodeReaderRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


BarcodeReaderServerHelper& BarcodeReaderServerHelper::instance()
{
	return *shBarcodeReaderServerHelper.get();
}


std::string BarcodeReaderServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::BarcodeReaderRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void BarcodeReaderServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


} // namespace Devices
} // namespace IoT

