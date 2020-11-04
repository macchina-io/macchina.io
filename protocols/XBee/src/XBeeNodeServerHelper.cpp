//
// XBeeNodeServerHelper.cpp
//
// Library: IoT/XBee
// Package: Generated
// Module:  XBeeNodeServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/XBee/XBeeNodeServerHelper.h"
#include "IoT/XBee/XBeeNodeEventDispatcher.h"
#include "IoT/XBee/XBeeNodeSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace XBee {


namespace
{
	static Poco::SingletonHolder<XBeeNodeServerHelper> shXBeeNodeServerHelper;
}


XBeeNodeServerHelper::XBeeNodeServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


XBeeNodeServerHelper::~XBeeNodeServerHelper()
{
}


void XBeeNodeServerHelper::shutdown()
{
	XBeeNodeServerHelper::instance().unregisterSkeleton();
	shXBeeNodeServerHelper.reset();
}


Poco::AutoPtr<IoT::XBee::XBeeNodeRemoteObject> XBeeNodeServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::XBee::XBeeNode> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new XBeeNodeRemoteObject(oid, pServiceObject);
}


void XBeeNodeServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<XBeeNodeRemoteObject> pRemoteObject = pIdentifiable.cast<XBeeNodeRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


XBeeNodeServerHelper& XBeeNodeServerHelper::instance()
{
	return *shXBeeNodeServerHelper.get();
}


std::string XBeeNodeServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::XBee::XBeeNodeRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void XBeeNodeServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.XBee.XBeeNode", new XBeeNodeSkeleton);
}


void XBeeNodeServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void XBeeNodeServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.XBee.XBeeNode", true);
}


} // namespace XBee
} // namespace IoT

