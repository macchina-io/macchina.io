//
// IDatapoint.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IDatapoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/IDatapoint.h"


namespace IoT {
namespace Devices {


IDatapoint::IDatapoint():
	IoT::Devices::IDevice(),
	invalidated()
{
}


IDatapoint::~IDatapoint()
{
}


bool IDatapoint::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Devices::IDatapoint).name());
	return name == otherType.name() || IoT::Devices::IDevice::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IDatapoint::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.Datapoint");
	return REMOTING__TYPE_ID;
}


const std::type_info& IDatapoint::type() const
{
	return typeid(IDatapoint);
}


} // namespace Devices
} // namespace IoT

