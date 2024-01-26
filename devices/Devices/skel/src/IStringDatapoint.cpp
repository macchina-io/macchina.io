//
// IStringDatapoint.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IStringDatapoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/IStringDatapoint.h"


namespace IoT {
namespace Devices {


IStringDatapoint::IStringDatapoint():
	IoT::Devices::IDatapoint(),
	validated(),
	valueChanged(),
	valueUpdated()
{
}


IStringDatapoint::~IStringDatapoint()
{
}


bool IStringDatapoint::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Devices::IStringDatapoint).name());
	return name == otherType.name() || IoT::Devices::IDatapoint::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IStringDatapoint::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.StringDatapoint");
	return REMOTING__TYPE_ID;
}


const std::type_info& IStringDatapoint::type() const
{
	return typeid(IStringDatapoint);
}


} // namespace Devices
} // namespace IoT

