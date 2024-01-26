//
// PeripheralManager.h
//
// Library: IoT/BtLE
// Package: BtLE
// Module:  PeripheralManager
//
// Definition of the PeripheralFactory class.
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_BtLE_PeripheralManager_INCLUDED
#define IoT_BtLE_PeripheralManager_INCLUDED


#include "IoT/BtLE/BtLE.h"
#include "Poco/SharedPtr.h"
#include <vector>


namespace IoT {
namespace BtLE {


//@ remote
class IoTBtLE_API PeripheralManager
	/// This class manages Peripheral objects in the service registry.
	///
	/// Given the address of a Bt LE Peripheral device, the
	/// findPeripheral() method will return an existing Peripheral object
	/// representing that device if it already exists, or otherwise
	/// create a new Peripheral object using the PeripheralFactory.
	///
	/// Once a Peripheral is no longer needed, it can be disposed by
	/// calling remove().
{
public:
	using Ptr = Poco::SharedPtr<PeripheralManager>;
	using ServiceID = std::string;

	//@ $controller={optional}
	virtual ServiceID findPeripheral(const std::string& address, const std::string& controller = std::string()) = 0;
		/// Returns the service ID of a Peripheral object for the Peripheral with the
		/// given address (e.g., "C4:BE:84:72:C5:06"), using the given controller.
		/// The controller ID may be empty if there is only one controller on the system.
		///
		/// If such a Peripheral object already exists in the service registry, the
		/// existing object's ID will be returned. Otherwise, a new Peripheral object
		/// for that address will be created (using the PeripheralFactory for the given
		/// interface) and its service ID returned.
		///
		/// The ServiceID can then be used in Poco::OSP::ServiceRegistry::findByName() 
		/// to obtain a ServiceRef for that service, and subsequently the service instance.

	virtual void removePeripheral(const ServiceID& serviceID) = 0;
		/// Removes the Peripheral with the given service ID.

	virtual ~PeripheralManager();
		/// Destroys the PeripheralFactory.
};


} } // namespace IoT::BtLE


#endif // IoT_BtLE_PeripheralManager_INCLUDED
