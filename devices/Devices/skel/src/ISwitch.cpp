//
// ISwitch.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  ISwitch
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/ISwitch.h"


namespace IoT {
namespace Devices {


ISwitch::ISwitch():
	IoT::Devices::IDevice(),
	stateChanged()
{
}


ISwitch::~ISwitch()
{
}


bool ISwitch::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Devices::ISwitch).name());
	return name == otherType.name() || IoT::Devices::IDevice::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& ISwitch::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.Switch");
	return REMOTING__TYPE_ID;
}


const std::type_info& ISwitch::type() const
{
	return typeid(ISwitch);
}


} // namespace Devices
} // namespace IoT

