//
// IBooleanDatapoint.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IBooleanDatapoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/IBooleanDatapoint.h"


namespace IoT {
namespace Devices {


IBooleanDatapoint::IBooleanDatapoint():
	IoT::Devices::IDatapoint(),
	validated(),
	valueChanged(),
	valueUpdated()
{
}


IBooleanDatapoint::~IBooleanDatapoint()
{
}


bool IBooleanDatapoint::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Devices::IBooleanDatapoint).name());
	return name == otherType.name() || IoT::Devices::IDatapoint::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IBooleanDatapoint::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.BooleanDatapoint");
	return REMOTING__TYPE_ID;
}


const std::type_info& IBooleanDatapoint::type() const
{
	return typeid(IBooleanDatapoint);
}


} // namespace Devices
} // namespace IoT

