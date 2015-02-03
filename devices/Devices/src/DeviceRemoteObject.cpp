//
// DeviceRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  DeviceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/DeviceRemoteObject.h"


namespace IoT {
namespace Devices {


DeviceRemoteObject::DeviceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Device> pServiceObject):
	IoT::Devices::IDevice(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
}


DeviceRemoteObject::~DeviceRemoteObject()
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

