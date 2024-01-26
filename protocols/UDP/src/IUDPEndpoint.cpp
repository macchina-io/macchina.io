//
// IUDPEndpoint.cpp
//
// Library: IoT/UDP
// Package: Generated
// Module:  IUDPEndpoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/UDP/IUDPEndpoint.h"


namespace IoT {
namespace UDP {


IUDPEndpoint::IUDPEndpoint():
	Poco::OSP::Service(),
	packetReceived()
{
}


IUDPEndpoint::~IUDPEndpoint()
{
}


bool IUDPEndpoint::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::UDP::IUDPEndpoint).name());
	return name == otherType.name() || Poco::OSP::Service::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IUDPEndpoint::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.UDP.UDPEndpoint");
	return REMOTING__TYPE_ID;
}


const std::type_info& IUDPEndpoint::type() const
{
	return typeid(IUDPEndpoint);
}


} // namespace UDP
} // namespace IoT

