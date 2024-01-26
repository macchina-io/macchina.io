//
// TriggerServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  TriggerServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/TriggerServerHelper.h"
#include "IoT/Devices/TriggerSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	Poco::SingletonHolder<TriggerServerHelper> shTriggerServerHelper;
}


TriggerServerHelper::TriggerServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


TriggerServerHelper::~TriggerServerHelper()
{
}


void TriggerServerHelper::shutdown()
{
	TriggerServerHelper::instance().unregisterSkeleton();
	shTriggerServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::TriggerRemoteObject> TriggerServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Trigger> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new TriggerRemoteObject(oid, pServiceObject);
}


TriggerServerHelper& TriggerServerHelper::instance()
{
	return *shTriggerServerHelper.get();
}


std::string TriggerServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::TriggerRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void TriggerServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.Trigger", new TriggerSkeleton);
}


void TriggerServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void TriggerServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.Trigger", true);
}


} // namespace Devices
} // namespace IoT

