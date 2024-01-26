//
// INetworkEnvironmentService.cpp
//
// Library: IoT/NetworkEnvironment
// Package: Generated
// Module:  INetworkEnvironmentService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2016-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/NetworkEnvironment/INetworkEnvironmentService.h"


namespace IoT {
namespace NetworkEnvironment {


INetworkEnvironmentService::INetworkEnvironmentService():
	Poco::OSP::Service(),
	networkEnvironmentChanged()
{
}


INetworkEnvironmentService::~INetworkEnvironmentService()
{
}


bool INetworkEnvironmentService::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::NetworkEnvironment::INetworkEnvironmentService).name());
	return name == otherType.name() || Poco::OSP::Service::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& INetworkEnvironmentService::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.NetworkEnvironment.NetworkEnvironmentService");
	return REMOTING__TYPE_ID;
}


const std::type_info& INetworkEnvironmentService::type() const
{
	return typeid(INetworkEnvironmentService);
}


} // namespace NetworkEnvironment
} // namespace IoT

