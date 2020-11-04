//
// ModbusMasterServerHelper.cpp
//
// Library: IoT/Modbus
// Package: Generated
// Module:  ModbusMasterServerHelper
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2015-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Modbus/ModbusMasterServerHelper.h"
#include "IoT/Modbus/ModbusMasterEventDispatcher.h"
#include "IoT/Modbus/ModbusMasterSkeleton.h"
#include "Poco/RemotingNG/URIUtility.h"
#include "Poco/SingletonHolder.h"


namespace IoT {
namespace Modbus {


namespace
{
	static Poco::SingletonHolder<ModbusMasterServerHelper> shModbusMasterServerHelper;
}


ModbusMasterServerHelper::ModbusMasterServerHelper():
	_pORB(0)
{
	_pORB = &Poco::RemotingNG::ORB::instance();
	registerSkeleton();
}


ModbusMasterServerHelper::~ModbusMasterServerHelper()
{
}


void ModbusMasterServerHelper::shutdown()
{
	ModbusMasterServerHelper::instance().unregisterSkeleton();
	shModbusMasterServerHelper.reset();
}


Poco::AutoPtr<IoT::Modbus::ModbusMasterRemoteObject> ModbusMasterServerHelper::createRemoteObjectImpl(Poco::SharedPtr<IoT::Modbus::ModbusMaster> pServiceObject, const Poco::RemotingNG::Identifiable::ObjectId& oid)
{
	return new ModbusMasterRemoteObject(oid, pServiceObject);
}


void ModbusMasterServerHelper::enableEventsImpl(const std::string& uri, const std::string& protocol)
{
	Poco::RemotingNG::Identifiable::Ptr pIdentifiable = _pORB->findObject(uri);
	Poco::AutoPtr<ModbusMasterRemoteObject> pRemoteObject = pIdentifiable.cast<ModbusMasterRemoteObject>();
	if (pRemoteObject)
	{
		pRemoteObject->remoting__enableRemoteEvents(protocol);
	}
	else throw Poco::NotFoundException("remote object", uri);
}


ModbusMasterServerHelper& ModbusMasterServerHelper::instance()
{
	return *shModbusMasterServerHelper.get();
}


std::string ModbusMasterServerHelper::registerObjectImpl(Poco::AutoPtr<IoT::Modbus::ModbusMasterRemoteObject> pRemoteObject, const std::string& listenerId)
{
	return _pORB->registerObject(pRemoteObject, listenerId);
}


void ModbusMasterServerHelper::registerSkeleton()
{
	_pORB->registerSkeleton("IoT.Modbus.ModbusMaster", new ModbusMasterSkeleton);
}


void ModbusMasterServerHelper::unregisterObjectImpl(const std::string& uri)
{
	_pORB->unregisterObject(uri);
}


void ModbusMasterServerHelper::unregisterSkeleton()
{
	_pORB->unregisterSkeleton("IoT.Modbus.ModbusMaster", true);
}


} // namespace Modbus
} // namespace IoT

