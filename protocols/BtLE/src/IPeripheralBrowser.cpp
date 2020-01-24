//
// IPeripheralBrowser.cpp
//
// Library: IoT/BtLE
// Package: Generated
// Module:  IPeripheralBrowser
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/BtLE/IPeripheralBrowser.h"


namespace IoT {
namespace BtLE {


IPeripheralBrowser::IPeripheralBrowser():
	Poco::OSP::Service(),
	browseComplete(),
	peripheralFound()
{
}


IPeripheralBrowser::~IPeripheralBrowser()
{
}


bool IPeripheralBrowser::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name();
}


const Poco::RemotingNG::Identifiable::TypeId& IPeripheralBrowser::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.BtLE.PeripheralBrowser");
	return REMOTING__TYPE_ID;
}


const std::type_info& IPeripheralBrowser::type() const
{
	return typeid(IPeripheralBrowser);
}


} // namespace BtLE
} // namespace IoT

