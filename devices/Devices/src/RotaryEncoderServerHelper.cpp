//
// RotaryEncoderServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  RotaryEncoderServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/RotaryEncoderServerHelper.h"
#include "IoT/Devices/RotaryEncoderEventDispatcher.h"
#include "IoT/Devices/RotaryEncoderSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	Poco::SingletonHolder<RotaryEncoderServerHelper> shRotaryEncoderServerHelper;
}


RotaryEncoderServerHelper::RotaryEncoderServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


RotaryEncoderServerHelper::~RotaryEncoderServerHelper()
{
}


void RotaryEncoderServerHelper::shutdown()
{
	RotaryEncoderServerHelper::instance().unregisterSkeleton();
	shRotaryEncoderServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::RotaryEncoderRemoteObject> RotaryEncoderServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::RotaryEncoder> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new RotaryEncoderRemoteObject(oid, pServiceObject);
}


void RotaryEncoderServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<RotaryEncoderRemoteObject> pRemoteObject = pIdentifiable.cast<RotaryEncoderRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


RotaryEncoderServerHelper& RotaryEncoderServerHelper::instance()
{
	return *shRotaryEncoderServerHelper.get();
}


std::string RotaryEncoderServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::RotaryEncoderRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void RotaryEncoderServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.RotaryEncoder", new RotaryEncoderSkeleton);
}


void RotaryEncoderServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void RotaryEncoderServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.RotaryEncoder", true);
}


} // namespace Devices
} // namespace IoT

