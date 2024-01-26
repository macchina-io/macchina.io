//
// IFlagsDatapoint.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IFlagsDatapoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/IFlagsDatapoint.h"


namespace IoT {
namespace Devices {


IFlagsDatapoint::IFlagsDatapoint():
	IoT::Devices::IDatapoint(),
	validated(),
	valueChanged(),
	valueUpdated()
{
}


IFlagsDatapoint::~IFlagsDatapoint()
{
}


bool IFlagsDatapoint::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Devices::IFlagsDatapoint).name());
	return name == otherType.name() || IoT::Devices::IDatapoint::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IFlagsDatapoint::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.FlagsDatapoint");
	return REMOTING__TYPE_ID;
}


const std::type_info& IFlagsDatapoint::type() const
{
	return typeid(IFlagsDatapoint);
}


} // namespace Devices
} // namespace IoT

