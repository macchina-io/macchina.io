//
// LEDStub.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  LEDStub
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/LEDStub.h"


namespace IoT {
namespace Devices {


LEDStub::LEDStub(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Devices::LED> pServiceObject):
	IoT::Devices::LEDRemoteObject(),
	_pServiceObject(pServiceObject)
{
	remoting__init(oid);
}


LEDStub::~LEDStub()
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

