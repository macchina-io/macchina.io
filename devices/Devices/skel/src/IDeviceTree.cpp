//
// IDeviceTree.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IDeviceTree
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/IDeviceTree.h"


namespace IoT {
namespace Devices {


IDeviceTree::IDeviceTree():
	Poco::OSP::Service()

{
}


IDeviceTree::~IDeviceTree()
{
}


bool IDeviceTree::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Devices::IDeviceTree).name());
	return name == otherType.name() || Poco::OSP::Service::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IDeviceTree::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.DeviceTree");
	return REMOTING__TYPE_ID;
}


const std::type_info& IDeviceTree::type() const
{
	return typeid(IDeviceTree);
}


} // namespace Devices
} // namespace IoT

