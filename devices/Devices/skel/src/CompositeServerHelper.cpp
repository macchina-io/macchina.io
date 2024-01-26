//
// CompositeServerHelper.cpp
//
// Library: IoT/Devices
// Package: Generated
// Module:  CompositeServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/CompositeServerHelper.h"
#include "IoT/Devices/CompositeSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Devices {


namespace
{
	Poco::SingletonHolder<CompositeServerHelper> shCompositeServerHelper;
}


CompositeServerHelper::CompositeServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


CompositeServerHelper::~CompositeServerHelper()
{
}


void CompositeServerHelper::shutdown()
{
	CompositeServerHelper::instance().unregisterSkeleton();
	shCompositeServerHelper.reset();
}


Poco::AutoPtr<IoT::Devices::CompositeRemoteObject> CompositeServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Devices::Composite> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new CompositeRemoteObject(oid, pServiceObject);
}


CompositeServerHelper& CompositeServerHelper::instance()
{
	return *shCompositeServerHelper.get();
}


std::string CompositeServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Devices::CompositeRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void CompositeServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Devices.Composite", new CompositeSkeleton);
}


void CompositeServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void CompositeServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Devices.Composite", true);
}


} // namespace Devices
} // namespace IoT

