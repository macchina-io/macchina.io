//
// IScalarDatapoint.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IScalarDatapoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/IScalarDatapoint.h"


namespace IoT {
namespace Devices {


IScalarDatapoint::IScalarDatapoint():
	IoT::Devices::IDatapoint(),
	validated(),
	valueChanged(),
	valueUpdated()
{
}


IScalarDatapoint::~IScalarDatapoint()
{
}


bool IScalarDatapoint::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Devices::IScalarDatapoint).name());
	return name == otherType.name() || IoT::Devices::IDatapoint::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IScalarDatapoint::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.ScalarDatapoint");
	return REMOTING__TYPE_ID;
}


const std::type_info& IScalarDatapoint::type() const
{
	return typeid(IScalarDatapoint);
}


} // namespace Devices
} // namespace IoT

