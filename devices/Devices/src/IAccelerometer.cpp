//
// IAccelerometer.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IAccelerometer
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/Devices/IAccelerometer.h"


namespace IoT {
namespace Devices {


IAccelerometer::IAccelerometer():
	IoT::Devices::IDevice(),
	accelerationChanged()
{
}


IAccelerometer::~IAccelerometer()
{
}


bool IAccelerometer::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name();
}


const Poco::RemotingNG::Identifiable::TypeId& IAccelerometer::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.Accelerometer");
	return REMOTING__TYPE_ID;
}


const std::type_info& IAccelerometer::type() const
{
	return typeid(IAccelerometer);
}


} // namespace Devices
} // namespace IoT

