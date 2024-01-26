//
// PeripheralManagerRemoteObject.cpp
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralManagerRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/BtLE/PeripheralManagerRemoteObject.h"


namespace IoT {
namespace BtLE {


PeripheralManagerRemoteObject::PeripheralManagerRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::BtLE::PeripheralManager> pServiceObject):
	IoT::BtLE::IPeripheralManager(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
}


PeripheralManagerRemoteObject::~PeripheralManagerRemoteObject()
{
	try
	{
	}
	catch (...)
	{
		poco_unexpected();
	}
}


} // namespace BtLE
} // namespace IoT

