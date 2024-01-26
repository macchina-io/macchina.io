//
// PeripheralManagerImpl.cpp
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  PeripheralManager
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/BtLE/PeripheralManagerImpl.h"
#include "IoT/BtLE/PeripheralFactory.h"
#include "Poco/OSP/ServiceFinder.h"
#include "IoT/BtLE/GATTPeripheral.h"
#include "IoT/BtLE/PeripheralServerHelper.h"


using namespace std::string_literals;


namespace IoT {
namespace BtLE {


PeripheralManagerImpl::PeripheralManagerImpl(Poco::OSP::ServiceRegistry& serviceRegistry):
	_serviceRegistry(serviceRegistry)
{
}


PeripheralManagerImpl::~PeripheralManagerImpl()
{
}


PeripheralManager::ServiceID PeripheralManagerImpl::findPeripheral(const std::string& address, const std::string& controller)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string query = "io.macchina.btle.address == \""s + address + "\""s;
	if (!controller.empty()) query += " && io.macchina.btle.controller == \""s + controller + "\""s;
	const auto results = _serviceRegistry.find(query);
	if (results.empty())
	{
		// TODO: Support multiple PeripheralFactory instances, identified by controller
		Poco::OSP::ServiceRef::Ptr pFactoryRef = _serviceRegistry.findByName(PeripheralFactory::SERVICE_NAME);
		if (pFactoryRef)
		{
			PeripheralFactory::Ptr pFactory = pFactoryRef->castedInstance<PeripheralFactory>();
			Peripheral::Ptr pPeripheral = pFactory->createPeripheral(address);
			return registerPeripheral(pPeripheral)->name();
		}
		else throw Poco::RuntimeException("No peripheral factory available"s);
	}
	else
	{
		return results[0]->name();
	}
}


void PeripheralManagerImpl::removePeripheral(const PeripheralManager::ServiceID& serviceID)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Poco::OSP::ServiceRef::Ptr pPeripheralRef = _serviceRegistry.findByName(serviceID);
	if (pPeripheralRef)
	{
		_serviceRegistry.unregisterService(pPeripheralRef);
	}
}


Poco::OSP::ServiceRef::Ptr PeripheralManagerImpl::registerPeripheral(IoT::BtLE::Peripheral::Ptr pPeripheral)
{
	using ServerHelper = Poco::RemotingNG::ServerHelper<IoT::BtLE::Peripheral>;

	std::string oid("io.macchina.btle.peripheral.");
	oid += pPeripheral->address();

	ServerHelper::RemoteObjectPtr pRemoteObject = ServerHelper::createRemoteObject(pPeripheral, oid);

	Poco::OSP::Properties props;
	props.set("io.macchina.btle.address", pPeripheral->address());

	return _serviceRegistry.registerService(oid, pRemoteObject, props);
}


} } // namespace IoT::BtLE
