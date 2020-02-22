//
// UnitsOfMeasureServiceRemoteObject.cpp
//
// Library: IoT/UnitsOfMeasure
// Package: Generated
// Module:  UnitsOfMeasureServiceRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2018-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/UnitsOfMeasure/UnitsOfMeasureServiceRemoteObject.h"


namespace IoT {
namespace UnitsOfMeasure {


UnitsOfMeasureServiceRemoteObject::UnitsOfMeasureServiceRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::UnitsOfMeasure::UnitsOfMeasureService> pServiceObject):
	IoT::UnitsOfMeasure::IUnitsOfMeasureService(),
	Poco::RemotingNG::RemoteObject(oid),
	_pServiceObject(pServiceObject)
{
}


UnitsOfMeasureServiceRemoteObject::~UnitsOfMeasureServiceRemoteObject()
{
	try
	{
	}
	catch (...)
	{
		poco_unexpected();
	}
}


} // namespace UnitsOfMeasure
} // namespace IoT

