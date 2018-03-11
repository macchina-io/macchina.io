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
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/CAN/ICANEndpoint.h"


namespace IoT {
namespace CAN {


ICANEndpoint::ICANEndpoint():
	Poco::OSP::Service(),
	fdFrameReceived(),
	frameReceived()
{
}


ICANEndpoint::~ICANEndpoint()
{
}


bool ICANEndpoint::isA(const std::type_info& otherType) const
{
	std::string name(type().name());
	return name == otherType.name();
}


const Poco::RemotingNG::Identifiable::TypeId& ICANEndpoint::remoting__typeId()
{
	remoting__staticInitBegin(REMOTING__TYPE_ID);
	static const std::string REMOTING__TYPE_ID("IoT.CAN.CANEndpoint");
	remoting__staticInitEnd(REMOTING__TYPE_ID);
	return REMOTING__TYPE_ID;
}


const std::type_info& ICANEndpoint::type() const
{
	return typeid(ICANEndpoint);
}


} // namespace CAN
} // namespace IoT

