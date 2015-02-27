//
// WebEventNotifierServerHelper.cpp
//
// Library: IoT/WebEvent
// Package: Generated
// Module:  WebEventNotifierServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#include "IoT/WebEvent/WebEventNotifierServerHelper.h"
#include "IoT/WebEvent/WebEventNotifierSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace WebEvent {


namespace
{
	static Poco::SingletonHolder<WebEventNotifierServerHelper> shWebEventNotifierServerHelper;
}


WebEventNotifierServerHelper::WebEventNotifierServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	_pORB->registerSkeleton("WebEventNotifier", new WebEventNotifierSkeleton);
}


WebEventNotifierServerHelper::~WebEventNotifierServerHelper()
{
	try
	{
		_pORB->unregisterSkeleton("WebEventNotifier", true);
	}
	catch (...)
	{
		poco_unexpected();
	}
}


std::string WebEventNotifierServerHelper::registerRemoteObject(Poco::AutoPtr<IoT::WebEvent::WebEventNotifierRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return WebEventNotifierServerHelper::instance().registerObjectImpl(pRemoteObject, listenerId);
}


Poco::AutoPtr<IoT::WebEvent::WebEventNotifierRemoteObject> WebEventNotifierServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::WebEvent::WebEventNotifier> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new WebEventNotifierRemoteObject(oid, pServiceObject);
}


WebEventNotifierServerHelper& WebEventNotifierServerHelper::instance()
{
	return *shWebEventNotifierServerHelper.get();
}


std::string WebEventNotifierServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::WebEvent::WebEventNotifierRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void WebEventNotifierServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


} // namespace WebEvent
} // namespace IoT

