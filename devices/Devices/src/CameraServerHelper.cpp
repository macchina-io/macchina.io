//
// CameraServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  CameraServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/CameraServerHelper.h"
#include "IoT/Devices/CameraEventDispatcher.h"
#include "IoT/Devices/CameraSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	static Poco::SingletonHolder<CameraServerHelper> shCameraServerHelper;
}


CameraServerHelper::CameraServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


CameraServerHelper::~CameraServerHelper()
{
}


void CameraServerHelper::shutdown()
{
	CameraServerHelper::instance().unregisterSkeleton();
	shCameraServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::CameraRemoteObject> CameraServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Camera> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new CameraRemoteObject(oid, pServiceObject);
}


void CameraServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<CameraRemoteObject> pRemoteObject = pIdentifiable.cast<CameraRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


CameraServerHelper& CameraServerHelper::instance()
{
	return *shCameraServerHelper.get();
}


std::string CameraServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::CameraRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void CameraServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.Camera", new CameraSkeleton);
}


void CameraServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void CameraServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.Camera", true);
}


} // namespace Devices
} // namespace IoT

