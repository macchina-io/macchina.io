//
// ICounterDatapoint.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  ICounterDatapoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/ICounterDatapoint.h"


namespace IoT {
namespace Devices {


ICounterDatapoint::ICounterDatapoint():
	IoT::Devices::IDatapoint(),
	validated(),
	valueChanged()
{
}


ICounterDatapoint::~ICounterDatapoint()
{
}


bool ICounterDatapoint::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Devices::ICounterDatapoint).name());
	return name == otherType.name() || IoT::Devices::IDatapoint::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& ICounterDatapoint::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.CounterDatapoint");
	return REMOTING__TYPE_ID;
}


const std::type_info& ICounterDatapoint::type() const
{
	return typeid(ICounterDatapoint);
}


} // namespace Devices
} // namespace IoT

