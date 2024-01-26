//
// IComposite.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  IComposite
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/IComposite.h"


namespace IoT {
namespace Devices {


IComposite::IComposite():
	IoT::Devices::IDevice()

{
}


IComposite::~IComposite()
{
}


bool IComposite::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::Devices::IComposite).name());
	return name == otherType.name() || IoT::Devices::IDevice::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IComposite::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.Devices.Composite");
	return REMOTING__TYPE_ID;
}


const std::type_info& IComposite::type() const
{
	return typeid(IComposite);
}


} // namespace Devices
} // namespace IoT

