//
// CameraRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  CameraRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/CameraRemoteObject.h"
#include "IoT/Devices/CameraEventDispatcher.h"
#include "Poco/Delegate.h"
#include "Poco/RemotingNG/ORB.h"


namespace IoT {
namespace Devices {


CameraRemoteObject::CameraRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Camera> pServiceObject):
	IoT::Devices::ICamera(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
	_pServiceObject->imageCaptured += Poco::delegate(this, &CameraRemoteObject::event__imageCaptured);
	_pServiceObject->statusChanged += Poco::delegate(this, &CameraRemoteObject::event__statusChanged);
}


CameraRemoteObject::~CameraRemoteObject()
{
	try
	{
		_pServiceObject->imageCaptured -= Poco::delegate(this, &CameraRemoteObject::event__imageCaptured);
		_pServiceObject->statusChanged -= Poco::delegate(this, &CameraRemoteObject::event__statusChanged);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string CameraRemoteObject::remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable)
{
	return std::string();
}


void CameraRemoteObject::remoting__enableRemoteEvents(const std::string& protocol)
{
	Poco::RemotingNG::EventDispatcher::Ptr pEventDispatcher = new CameraEventDispatcher(this, protocol);
	Poco::RemotingNG::ORB::instance().registerEventDispatcher(remoting__getURI().toString(), pEventDispatcher);
}


bool CameraRemoteObject::remoting__hasEvents() const
{
	return true;
}


void CameraRemoteObject::event__imageCaptured(const Poco::SharedPtr < IoT::Devices::Image >& data)
{
	imageCaptured(this, data);
}


void CameraRemoteObject::event__statusChanged(const IoT::Devices::DeviceStatusChange& data)
{
	statusChanged(this, data);
}


} // namespace Devices
} // namespace IoT

