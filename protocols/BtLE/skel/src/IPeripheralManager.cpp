//
// IPeripheralManager.cpp
//
// Library: IoT/BtLE
// Package: Generated
// Module:  IPeripheralManager
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/BtLE/IPeripheralManager.h"


namespace IoT {
namespace BtLE {


IPeripheralManager::IPeripheralManager():
	Poco::OSP::Service()

{
}


IPeripheralManager::~IPeripheralManager()
{
}


bool IPeripheralManager::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::BtLE::IPeripheralManager).name());
	return name == otherType.name() || Poco::OSP::Service::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IPeripheralManager::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.BtLE.PeripheralManager");
	return REMOTING__TYPE_ID;
}


const std::type_info& IPeripheralManager::type() const
{
	return typeid(IPeripheralManager);
}


} // namespace BtLE
} // namespace IoT

