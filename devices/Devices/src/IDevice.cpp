//
// IDevice.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IDevice
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/IDevice.h"


namespace IoT {
namespace Devices {


IDevice::IDevice():
	Poco::OSP::Service(),
	statusChanged()
{
}


IDevice::~IDevice()
{
}


bool IDevice::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name();
}


const Poco::RemotingNG::Identifiable::TypeId& IDevice::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.Device");
	return REMOTING__TYPE_ID;
}


const std::type_info& IDevice::type() const
{
	return typeid(IDevice);
}


} // namespace Devices
} // namespace IoT

