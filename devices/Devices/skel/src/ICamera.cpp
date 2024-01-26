//
// ICamera.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  ICamera
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/ICamera.h"


namespace IoT {
namespace Devices {


ICamera::ICamera():
	IoT::Devices::IDevice(),
	imageCaptured()
{
}


ICamera::~ICamera()
{
}


bool ICamera::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Devices::ICamera).name());
	return name == otherType.name() || IoT::Devices::IDevice::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& ICamera::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.Camera");
	return REMOTING__TYPE_ID;
}


const std::type_info& ICamera::type() const
{
	return typeid(ICamera);
}


} // namespace Devices
} // namespace IoT

