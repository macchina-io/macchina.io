//
// ICANEndpoint.cpp
//
// Library: IoT/CAN
// Package: Generated
// Module:  ICANEndpoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/CAN/ICANEndpoint.h"


namespace IoT {
namespace CAN {


ICANEndpoint::ICANEndpoint():
	Poco::OSP::Service(),
	frameReceived()
{
}


ICANEndpoint::~ICANEndpoint()
{
}


bool ICANEndpoint::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::CAN::ICANEndpoint).name());
	return name == otherType.name() || Poco::OSP::Service::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& ICANEndpoint::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.CAN.CANEndpoint");
	return REMOTING__TYPE_ID;
}


const std::type_info& ICANEndpoint::type() const
{
	return typeid(ICANEndpoint);
}


} // namespace CAN
} // namespace IoT

