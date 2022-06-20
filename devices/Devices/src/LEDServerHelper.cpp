//
// LEDServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  LEDServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/LEDServerHelper.h"
#include "IoT/Devices/LEDSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	Poco::SingletonHolder<LEDServerHelper> shLEDServerHelper;
}


LEDServerHelper::LEDServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


LEDServerHelper::~LEDServerHelper()
{
}


void LEDServerHelper::shutdown()
{
	LEDServerHelper::instance().unregisterSkeleton();
	shLEDServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::LEDRemoteObject> LEDServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::LED> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new LEDRemoteObject(oid, pServiceObject);
}


LEDServerHelper& LEDServerHelper::instance()
{
	return *shLEDServerHelper.get();
}


std::string LEDServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::LEDRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void LEDServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.LED", new LEDSkeleton);
}


void LEDServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void LEDServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.LED", true);
}


} // namespace Devices
} // namespace IoT

