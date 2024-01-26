//
// IPeripheral.cpp
//
// Library: IoT/BtLE
// Package: Generated
// Module:  IPeripheral
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/BtLE/IPeripheral.h"


namespace IoT {
namespace BtLE {


IPeripheral::IPeripheral():
	Poco::OSP::Service(),
	connected(),
	disconnected(),
	error(),
	indicationReceived(),
	notificationReceived()
{
}


IPeripheral::~IPeripheral()
{
}


bool IPeripheral::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::BtLE::IPeripheral).name());
	return name == otherType.name() || Poco::OSP::Service::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IPeripheral::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.BtLE.Peripheral");
	return REMOTING__TYPE_ID;
}


const std::type_info& IPeripheral::type() const
{
	return typeid(IPeripheral);
}


} // namespace BtLE
} // namespace IoT

