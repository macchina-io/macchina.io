//
// WebTunnelServiceServerHelper.cpp
//
// Library: IoT/WebTunnel
// Package: Generated
// Module:  WebTunnelServiceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2019-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/WebTunnel/WebTunnelServiceServerHelper.h"
#include "IoT/WebTunnel/WebTunnelServiceEventDispatcher.h"
#include "IoT/WebTunnel/WebTunnelServiceSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace WebTunnel {


namespace
{
	Poco::SingletonHolder<WebTunnelServiceServerHelper> shWebTunnelServiceServerHelper;
}


WebTunnelServiceServerHelper::WebTunnelServiceServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


WebTunnelServiceServerHelper::~WebTunnelServiceServerHelper()
{
}


void WebTunnelServiceServerHelper::shutdown()
{
	WebTunnelServiceServerHelper::instance().unregisterSkeleton();
	shWebTunnelServiceServerHelper.reset();
}


Poco::AutoPtr<IoT::WebTunnel::WebTunnelServiceRemoteObject> WebTunnelServiceServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::WebTunnel::WebTunnelService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new WebTunnelServiceRemoteObject(oid, pServiceObject);
}


void WebTunnelServiceServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<WebTunnelServiceRemoteObject> pRemoteObject = pIdentifiable.cast<WebTunnelServiceRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


WebTunnelServiceServerHelper& WebTunnelServiceServerHelper::instance()
{
	return *shWebTunnelServiceServerHelper.get();
}


std::string WebTunnelServiceServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::WebTunnel::WebTunnelServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void WebTunnelServiceServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.WebTunnel.WebTunnelService", new WebTunnelServiceSkeleton);
}


void WebTunnelServiceServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void WebTunnelServiceServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.WebTunnel.WebTunnelService", true);
}


} // namespace WebTunnel
} // namespace IoT

