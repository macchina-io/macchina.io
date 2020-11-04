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
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
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
	registerSkeleton();
}


BarcodeReaderServerHelper::~BarcodeReaderServerHelper()
{
}


void BarcodeReaderServerHelper::shutdown()
{
	BarcodeReaderServerHelper::instance().unregisterSkeleton();
	shBarcodeReaderServerHelper.reset();
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


void BarcodeReaderServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.BarcodeReader", new BarcodeReaderSkeleton);
}


void BarcodeReaderServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void BarcodeReaderServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.BarcodeReader", true);
}


} // namespace Devices
} // namespace IoT

