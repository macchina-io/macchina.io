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
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/TriggerServerHelper.h"
#include "IoT/Devices/TriggerEventDispatcher.h"
#include "IoT/Devices/TriggerSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	static Poco::SingletonHolder<TriggerServerHelper> shTriggerServerHelper;
}


TriggerServerHelper::TriggerServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerSkeleton("Trigger", new TriggerSkeleton);
}


TriggerServerHelper::~TriggerServerHelper()
{
	try
	{
		_pORB->unregisterSkeleton("Trigger", true);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string TriggerServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::TriggerRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return TriggerServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


Poco::AutoPtr<IoT::Devices::TriggerRemoteObject> TriggerServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Trigger> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new TriggerRemoteObject(oid, pServiceObject);
}


void TriggerServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<TriggerRemoteObject> pRemoteObject = pIdentifiable.cast<TriggerRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


TriggerServerHelper& TriggerServerHelper::instance()
{
	return *shTriggerServerHelper.get();
}


std::string TriggerServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::TriggerRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void TriggerServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


} // namespace Devices
} // namespace IoT

