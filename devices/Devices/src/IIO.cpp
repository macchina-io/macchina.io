//
// IIO.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IIO
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/IIO.h"


namespace IoT {
namespace Devices {


IIO::IIO():
	IoT::Devices::IDevice(),
	stateChanged()
{
}


IIO::~IIO()
{
}


bool IIO::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name();
}


const Poco::RemotingNG::Identifiable::TypeId& IIO::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.IO");
	return REMOTING__TYPE_ID;
}


const std::type_info& IIO::type() const
{
	return typeid(IIO);
}


} // namespace Devices
} // namespace IoT

