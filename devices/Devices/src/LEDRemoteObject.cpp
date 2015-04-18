//
// LEDRemoteObject.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  LEDRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/LEDRemoteObject.h"


namespace IoT {
namespace Devices {


LEDRemoteObject::LEDRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::LED> pServiceObject):
	IoT::Devices::ILED(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
}


LEDRemoteObject::~LEDRemoteObject()
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

