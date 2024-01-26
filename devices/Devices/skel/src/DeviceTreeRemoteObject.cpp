//
// DeviceTreeRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  DeviceTreeRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/DeviceTreeRemoteObject.h"


namespace IoT {
namespace Devices {


DeviceTreeRemoteObject::DeviceTreeRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::DeviceTree> pServiceObject):
	IoT::Devices::IDeviceTree(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
}


DeviceTreeRemoteObject::~DeviceTreeRemoteObject()
{
	try
	{
	}
	catch (...)
	{
		poco_unexpected();
	}
}


} // namespace Devices
} // namespace IoT

