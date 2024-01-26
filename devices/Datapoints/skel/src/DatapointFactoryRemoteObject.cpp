//
// DatapointFactoryRemoteObject.cpp
//
// Library: IoT/Datapoints
// Package: Generated
// Module:  DatapointFactoryRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Datapoints/DatapointFactoryRemoteObject.h"


namespace IoT {
namespace Datapoints {


DatapointFactoryRemoteObject::DatapointFactoryRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Datapoints::DatapointFactory> pServiceObject):
	IoT::Datapoints::IDatapointFactory(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
}


DatapointFactoryRemoteObject::~DatapointFactoryRemoteObject()
{
	try
	{
	}
	catch (...)
	{
		poco_unexpected();
	}
}


} // namespace Datapoints
} // namespace IoT

