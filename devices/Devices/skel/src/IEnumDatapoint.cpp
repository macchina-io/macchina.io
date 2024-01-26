//
// IEnumDatapoint.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IEnumDatapoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/IEnumDatapoint.h"


namespace IoT {
namespace Devices {


IEnumDatapoint::IEnumDatapoint():
	IoT::Devices::IDatapoint(),
	validated(),
	valueChanged(),
	valueUpdated()
{
}


IEnumDatapoint::~IEnumDatapoint()
{
}


bool IEnumDatapoint::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Devices::IEnumDatapoint).name());
	return name == otherType.name() || IoT::Devices::IDatapoint::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IEnumDatapoint::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.EnumDatapoint");
	return REMOTING__TYPE_ID;
}


const std::type_info& IEnumDatapoint::type() const
{
	return typeid(IEnumDatapoint);
}


} // namespace Devices
} // namespace IoT

