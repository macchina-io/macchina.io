//
// DatapointFactoryServerHelper.cpp
//
// Library: IoT/Datapoints
// Package: Generated
// Module:  DatapointFactoryServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Datapoints/DatapointFactoryServerHelper.h"
#include "IoT/Datapoints/DatapointFactorySkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Datapoints {


namespace
{
	Poco::SingletonHolder<DatapointFactoryServerHelper> shDatapointFactoryServerHelper;
}


DatapointFactoryServerHelper::DatapointFactoryServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


DatapointFactoryServerHelper::~DatapointFactoryServerHelper()
{
}


void DatapointFactoryServerHelper::shutdown()
{
	DatapointFactoryServerHelper::instance().unregisterSkeleton();
	shDatapointFactoryServerHelper.reset();
}


Poco::AutoPtr<IoT::Datapoints::DatapointFactoryRemoteObject> DatapointFactoryServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Datapoints::DatapointFactory> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new DatapointFactoryRemoteObject(oid, pServiceObject);
}


DatapointFactoryServerHelper& DatapointFactoryServerHelper::instance()
{
	return *shDatapointFactoryServerHelper.get();
}


std::string DatapointFactoryServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Datapoints::DatapointFactoryRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void DatapointFactoryServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Datapoints.DatapointFactory", new DatapointFactorySkeleton);
}


void DatapointFactoryServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void DatapointFactoryServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Datapoints.DatapointFactory", true);
}


} // namespace Datapoints
} // namespace IoT

