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
// Copyright (c) 2017-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
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
	std::string name(type().name());
	return name == otherType.name();
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

