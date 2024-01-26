//
// IPeripheralManager.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  IPeripheralManager
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_BtLE_IPeripheralManager_INCLUDED
#define IoT_BtLE_IPeripheralManager_INCLUDED


#include "IoT/BtLE/PeripheralManager.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"


namespace IoT {
namespace BtLE {


class IPeripheralManager: public Poco::OSP::Service
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
	using Ptr = Poco::AutoPtr<IPeripheralManager>;

	IPeripheralManager();
		/// Creates a IPeripheralManager.

	virtual ~IPeripheralManager();
		/// Destroys the IPeripheralManager.

	virtual std::string findPeripheral(const std::string& address, const std::string& controller = std::string()) = 0;
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

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void removePeripheral(const std::string& serviceID) = 0;
		/// Removes the Peripheral with the given service ID.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

};


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_IPeripheralManager_INCLUDED

