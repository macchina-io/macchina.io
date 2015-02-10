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
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
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
	static Poco::SingletonHolder<RotaryEncoderServerHelper> shRotaryEncoderServerHelper;
}


RotaryEncoderServerHelper::RotaryEncoderServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerSkeleton("RotaryEncoder", new RotaryEncoderSkeleton);
}


RotaryEncoderServerHelper::~RotaryEncoderServerHelper()
{
	try
	{
		_pORB->unregisterSkeleton("RotaryEncoder", true);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string RotaryEncoderServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::Devices::RotaryEncoderRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return RotaryEncoderServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
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


void RotaryEncoderServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


} // namespace Devices
} // namespace IoT

