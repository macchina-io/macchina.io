//
// MobileConnectionServiceServerHelper.cpp
//
// Library: IoT/MobileConnection
// Package: Generated
// Module:  MobileConnectionServiceServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/MobileConnection/MobileConnectionServiceServerHelper.h"
#include "IoT/MobileConnection/MobileConnectionServiceEventDispatcher.h"
#include "IoT/MobileConnection/MobileConnectionServiceSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace MobileConnection {


namespace
{
	Poco::SingletonHolder<MobileConnectionServiceServerHelper> shMobileConnectionServiceServerHelper;
}


MobileConnectionServiceServerHelper::MobileConnectionServiceServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


MobileConnectionServiceServerHelper::~MobileConnectionServiceServerHelper()
{
}


void MobileConnectionServiceServerHelper::shutdown()
{
	MobileConnectionServiceServerHelper::instance().unregisterSkeleton();
	shMobileConnectionServiceServerHelper.reset();
}


Poco::AutoPtr<IoT::MobileConnection::MobileConnectionServiceRemoteObject> MobileConnectionServiceServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::MobileConnection::MobileConnectionService> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new MobileConnectionServiceRemoteObject(oid, pServiceObject);
}


void MobileConnectionServiceServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<MobileConnectionServiceRemoteObject> pRemoteObject = pIdentifiable.cast<MobileConnectionServiceRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


MobileConnectionServiceServerHelper& MobileConnectionServiceServerHelper::instance()
{
	return *shMobileConnectionServiceServerHelper.get();
}


std::string MobileConnectionServiceServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::MobileConnection::MobileConnectionServiceRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void MobileConnectionServiceServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.MobileConnection.MobileConnectionService", new MobileConnectionServiceSkeleton);
}


void MobileConnectionServiceServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void MobileConnectionServiceServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.MobileConnection.MobileConnectionService", true);
}


} // namespace MobileConnection
} // namespace IoT

