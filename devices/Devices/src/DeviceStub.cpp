//
// DeviceStub.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  DeviceStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/DeviceStub.h"


namespace IoT {
namespace Devices {


DeviceStub::DeviceStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::Device> pServiceObject):
	IoT::Devices::DeviceRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
}


DeviceStub::~DeviceStub()
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

