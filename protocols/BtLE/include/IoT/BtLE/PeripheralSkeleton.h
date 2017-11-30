//
// PeripheralSkeleton.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_PeripheralSkeleton_INCLUDED
#define IoT_BtLE_PeripheralSkeleton_INCLUDED


#include "IoT/BtLE/PeripheralRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace BtLE {


class PeripheralSkeleton: public Poco::RemotingNG::Skeleton
	/// This class provides a high-level interface to a Bluetooth LE peripheral
	/// device using the Bluetooth Generic Attribute Profile (GATT).
{
public:
	PeripheralSkeleton();
		/// Creates a PeripheralSkeleton.

	virtual ~PeripheralSkeleton();
		/// Destroys a PeripheralSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& PeripheralSkeleton::remoting__typeId() const
{
	return IPeripheral::remoting__typeId();
}


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_PeripheralSkeleton_INCLUDED

