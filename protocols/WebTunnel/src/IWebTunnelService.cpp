//
// IWebTunnelService.cpp
//
// Library: IoT/WebTunnel
// Package: Generated
// Module:  IWebTunnelService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/WebTunnel/IWebTunnelService.h"


namespace IoT {
namespace WebTunnel {


IWebTunnelService::IWebTunnelService():
	Poco::OSP::Service(),
	connected(),
	disconnected()
{
}


IWebTunnelService::~IWebTunnelService()
{
}


bool IWebTunnelService::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name();
}


const Poco::RemotingNG::Identifiable::TypeId& IWebTunnelService::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.WebTunnel.WebTunnelService");
	return REMOTING__TYPE_ID;
}


const std::type_info& IWebTunnelService::type() const
{
	return typeid(IWebTunnelService);
}


} // namespace WebTunnel
} // namespace IoT

