//
// PeripheralManagerServerHelper.cpp
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralManagerServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/BtLE/PeripheralManagerServerHelper.h"
#include "IoT/BtLE/PeripheralManagerSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace BtLE {


namespace
{
	Poco::SingletonHolder<PeripheralManagerServerHelper> shPeripheralManagerServerHelper;
}


PeripheralManagerServerHelper::PeripheralManagerServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


PeripheralManagerServerHelper::~PeripheralManagerServerHelper()
{
}


void PeripheralManagerServerHelper::shutdown()
{
	PeripheralManagerServerHelper::instance().unregisterSkeleton();
	shPeripheralManagerServerHelper.reset();
}


Poco::AutoPtr<IoT::BtLE::PeripheralManagerRemoteObject> PeripheralManagerServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::BtLE::PeripheralManager> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new PeripheralManagerRemoteObject(oid, pServiceObject);
}


PeripheralManagerServerHelper& PeripheralManagerServerHelper::instance()
{
	return *shPeripheralManagerServerHelper.get();
}


std::string PeripheralManagerServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::BtLE::PeripheralManagerRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void PeripheralManagerServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.BtLE.PeripheralManager", new PeripheralManagerSkeleton);
}


void PeripheralManagerServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void PeripheralManagerServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.BtLE.PeripheralManager", true);
}


} // namespace BtLE
} // namespace IoT

