//
// PeripheralManagerRemoteObject.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralManagerRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_BtLE_PeripheralManagerRemoteObject_INCLUDED
#define IoT_BtLE_PeripheralManagerRemoteObject_INCLUDED


#include "IoT/BtLE/IPeripheralManager.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace BtLE {


class PeripheralManagerRemoteObject: public IoT::BtLE::IPeripheralManager, public Poco::RemotingNG::RemoteObject
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
	using Ptr = Poco::AutoPtr<PeripheralManagerRemoteObject>;

	PeripheralManagerRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::BtLE::PeripheralManager> pServiceObject);
		/// Creates a PeripheralManagerRemoteObject.

	virtual ~PeripheralManagerRemoteObject();
		/// Destroys the PeripheralManagerRemoteObject.

	std::string findPeripheral(const std::string& address, const std::string& controller = std::string());
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

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void removePeripheral(const std::string& serviceID);
		/// Removes the Peripheral with the given service ID.

private:
	Poco::SharedPtr<IoT::BtLE::PeripheralManager> _pServiceObject;
};


inline std::string PeripheralManagerRemoteObject::findPeripheral(const std::string& address, const std::string& controller)
{
	return _pServiceObject->findPeripheral(address, controller);
}


inline const Poco::RemotingNG::Identifiable::TypeId& PeripheralManagerRemoteObject::remoting__typeId() const
{
	return IPeripheralManager::remoting__typeId();
}


inline void PeripheralManagerRemoteObject::removePeripheral(const std::string& serviceID)
{
	_pServiceObject->removePeripheral(serviceID);
}


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_PeripheralManagerRemoteObject_INCLUDED

