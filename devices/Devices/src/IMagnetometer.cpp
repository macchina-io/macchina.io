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
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
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
	std::string name(type().name());
	return name == otherType.name();
}


const Poco::RemotingNG::Identifiable::TypeId& IMagnetometer::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("Magnetometer");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


const std::type_info& IMagnetometer::type() const
{
	return typeid(IMagnetometer);
}


} // namespace Devices
} // namespace IoT

