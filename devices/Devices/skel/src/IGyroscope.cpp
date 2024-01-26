//
// IGyroscope.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IGyroscope
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/IGyroscope.h"


namespace IoT {
namespace Devices {


IGyroscope::IGyroscope():
	IoT::Devices::IDevice(),
	rotationChanged()
{
}


IGyroscope::~IGyroscope()
{
}


bool IGyroscope::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Devices::IGyroscope).name());
	return name == otherType.name() || IoT::Devices::IDevice::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IGyroscope::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.Gyroscope");
	return REMOTING__TYPE_ID;
}


const std::type_info& IGyroscope::type() const
{
	return typeid(IGyroscope);
}


} // namespace Devices
} // namespace IoT

