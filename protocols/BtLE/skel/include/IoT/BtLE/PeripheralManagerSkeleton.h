//
// PeripheralManagerSkeleton.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralManagerSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017-2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_BtLE_PeripheralManagerSkeleton_INCLUDED
#define IoT_BtLE_PeripheralManagerSkeleton_INCLUDED


#include "IoT/BtLE/PeripheralManagerRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace BtLE {


class PeripheralManagerSkeleton: public Poco::RemotingNG::Skeleton
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
	PeripheralManagerSkeleton();
		/// Creates a PeripheralManagerSkeleton.

	virtual ~PeripheralManagerSkeleton();
		/// Destroys a PeripheralManagerSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& PeripheralManagerSkeleton::remoting__typeId() const
{
	return IPeripheralManager::remoting__typeId();
}


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_PeripheralManagerSkeleton_INCLUDED

