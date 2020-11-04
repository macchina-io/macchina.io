//
// ICounter.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  ICounter
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/ICounter.h"


namespace IoT {
namespace Devices {


ICounter::ICounter():
	IoT::Devices::IDevice(),
	countChanged()
{
}


ICounter::~ICounter()
{
}


bool ICounter::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name();
}


const Poco::RemotingNG::Identifiable::TypeId& ICounter::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.Counter");
	return REMOTING__TYPE_ID;
}


const std::type_info& ICounter::type() const
{
	return typeid(ICounter);
}


} // namespace Devices
} // namespace IoT

