//
// IDeviceStatusService.cpp
//
// Library: IoT/DeviceStatus
// Package: Generated
// Module:  IDeviceStatusService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/DeviceStatus/IDeviceStatusService.h"


namespace IoT {
namespace DeviceStatus {


IDeviceStatusService::IDeviceStatusService():
	Poco::OSP::Service(),
	statusChanged(),
	statusUpdated()
{
}


IDeviceStatusService::~IDeviceStatusService()
{
}


bool IDeviceStatusService::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name();
}


const Poco::RemotingNG::Identifiable::TypeId& IDeviceStatusService::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.DeviceStatus.DeviceStatusService");
	return REMOTING__TYPE_ID;
}


const std::type_info& IDeviceStatusService::type() const
{
	return typeid(IDeviceStatusService);
}


} // namespace DeviceStatus
} // namespace IoT

