//
// UnitsOfMeasureServiceServerHelper.cpp
//
// Library: IoT/UnitsOfMeasure
// Package: Generated
// Module:  UnitsOfMeasureServiceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2018-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/UnitsOfMeasure/UnitsOfMeasureServiceServerHelper.h"
#include "IoT/UnitsOfMeasure/UnitsOfMeasureServiceSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace UnitsOfMeasure {


namespace
{
	static Poco::SingletonHolder<UnitsOfMeasureServiceServerHelper> shUnitsOfMeasureServiceServerHelper;
}


UnitsOfMeasureServiceServerHelper::UnitsOfMeasureServiceServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


UnitsOfMeasureServiceServerHelper::~UnitsOfMeasureServiceServerHelper()
{
}


void UnitsOfMeasureServiceServerHelper::shutdown()
{
	UnitsOfMeasureServiceServerHelper::instance().unregisterSkeleton();
	shUnitsOfMeasureServiceServerHelper.reset();
}


Poco::AutoPtr<IoT::UnitsOfMeasure::UnitsOfMeasureServiceRemoteObject> UnitsOfMeasureServiceServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::UnitsOfMeasure::UnitsOfMeasureService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new UnitsOfMeasureServiceRemoteObject(oid, pServiceObject);
}


UnitsOfMeasureServiceServerHelper& UnitsOfMeasureServiceServerHelper::instance()
{
	return *shUnitsOfMeasureServiceServerHelper.get();
}


std::string UnitsOfMeasureServiceServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::UnitsOfMeasure::UnitsOfMeasureServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void UnitsOfMeasureServiceServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.UnitsOfMeasure.UnitsOfMeasureService", new UnitsOfMeasureServiceSkeleton);
}


void UnitsOfMeasureServiceServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void UnitsOfMeasureServiceServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.UnitsOfMeasure.UnitsOfMeasureService", true);
}


} // namespace UnitsOfMeasure
} // namespace IoT

