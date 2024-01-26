//
// IMagnetometer.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IMagnetometer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/IMagnetometer.h"


namespace IoT {
namespace Devices {


IMagnetometer::IMagnetometer():
	IoT::Devices::IDevice(),
	fieldStrengthChanged()
{
}


IMagnetometer::~IMagnetometer()
{
}


bool IMagnetometer::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Devices::IMagnetometer).name());
	return name == otherType.name() || IoT::Devices::IDevice::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IMagnetometer::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.Magnetometer");
	return REMOTING__TYPE_ID;
}


const std::type_info& IMagnetometer::type() const
{
	return typeid(IMagnetometer);
}


} // namespace Devices
} // namespace IoT

