//
// IMobileConnectionService.cpp
//
// Library: IoT/MobileConnection
// Package: Generated
// Module:  IMobileConnectionService
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/MobileConnection/IMobileConnectionService.h"


namespace IoT {
namespace MobileConnection {


IMobileConnectionService::IMobileConnectionService():
	Poco::OSP::Service(),
	dataConnected(),
	dataDisconnected()
{
}


IMobileConnectionService::~IMobileConnectionService()
{
}


bool IMobileConnectionService::isA(const std::type_info& otherType) const
{
	static const std::string name(typeid(IoT::MobileConnection::IMobileConnectionService).name());
	return name == otherType.name() || Poco::OSP::Service::isA(otherType);
}


const Poco::RemotingNG::Identifiable::TypeId& IMobileConnectionService::remoting__typeId()
{
	static const std::string REMOTING__TYPE_ID("IoT.MobileConnection.MobileConnectionService");
	return REMOTING__TYPE_ID;
}


const std::type_info& IMobileConnectionService::type() const
{
	return typeid(IMobileConnectionService);
}


} // namespace MobileConnection
} // namespace IoT

