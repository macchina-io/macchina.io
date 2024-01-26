//
// IVectorDatapoint.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IVectorDatapoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/IVectorDatapoint.h"


namespace IoT {
namespace Devices {


IVectorDatapoint::IVectorDatapoint():
	IoT::Devices::IDatapoint(),
	validated(),
	valueChanged(),
	valueUpdated()
{
}


IVectorDatapoint::~IVectorDatapoint()
{
}


bool IVectorDatapoint::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Devices::IVectorDatapoint).name());
	return name == otherType.name() || IoT::Devices::IDatapoint::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IVectorDatapoint::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.VectorDatapoint");
	return REMOTING__TYPE_ID;
}


const std::type_info& IVectorDatapoint::type() const
{
	return typeid(IVectorDatapoint);
}


} // namespace Devices
} // namespace IoT

