//
// PeripheralManagerImpl.h
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  PeripheralManager
//
// Definition of the PeripheralFactoryImpl class.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_BtLE_PeripheralManagerImpl_INCLUDED
#define IoT_BtLE_PeripheralManagerImpl_INCLUDED


#include "IoT/BtLE/PeripheralManager.h"
#include "IoT/BtLE/Peripheral.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/Mutex.h"


namespace IoT {
namespace BtLE {


class IoTBtLE_API PeripheralManagerImpl: public PeripheralManager
	/// The default implementation of PeripheralManager.
{
public:
	using Ptr = Poco::SharedPtr<PeripheralManagerImpl>;

	explicit PeripheralManagerImpl(Poco::OSP::ServiceRegistry& serviceRegistry);
		/// Creates the PeripheralManagerImpl, using the given ServiceRegistry.

	~PeripheralManagerImpl();
		/// Destroys the PeripheralManagerImpl.

	// PeripheralManager
	ServiceID findPeripheral(const std::string& address, const std::string& controller);
	void removePeripheral(const ServiceID& serviceID);

protected:
	Poco::OSP::ServiceRef::Ptr registerPeripheral(IoT::BtLE::Peripheral::Ptr pPeripheral);

private:
	Poco::OSP::ServiceRegistry& _serviceRegistry;
	Poco::FastMutex _mutex;
};


} } // namespace IoT::BtLE


#endif // IoT_BtLE_PeripheralManagerImpl_INCLUDED
