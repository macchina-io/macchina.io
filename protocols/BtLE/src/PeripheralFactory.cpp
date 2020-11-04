//
// PeripheralFactory.cpp
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  PeripheralFactory
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/BtLE/PeripheralFactory.h"


namespace IoT {
namespace BtLE {


const std::string PeripheralFactory::SERVICE_NAME("io.macchina.btle.peripheralfactory");


const std::type_info& PeripheralFactory::type() const
{
	return typeid(PeripheralFactory);
}


bool PeripheralFactory::isA(const std::type_info& otherType) const
{
	std::string name(typeid(PeripheralFactory).name());
	return name == otherType.name() || Poco::OSP::Service::isA(otherType);
}


PeripheralFactory::~PeripheralFactory()
{
}


} } // namespace IoT::BtLE
