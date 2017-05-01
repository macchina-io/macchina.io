//
// PeripheralRemoteObject.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_PeripheralRemoteObject_INCLUDED
#define IoT_BtLE_PeripheralRemoteObject_INCLUDED


#include "IoT/BtLE/IPeripheral.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace BtLE {


class PeripheralRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::BtLE::IPeripheral
	/// This class provides a high-level interface to a Bluetooth LE peripheral
	/// device using the Bluetooth Generic Attribute Profile (GATT).
{
public:
	typedef Poco::AutoPtr<PeripheralRemoteObject> Ptr;

	PeripheralRemoteObject();
		/// Creates a PeripheralRemoteObject.

	virtual ~PeripheralRemoteObject();
		/// Destroys the PeripheralRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& PeripheralRemoteObject::remoting__typeId() const
{
	return IPeripheral::remoting__typeId();
}


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_PeripheralRemoteObject_INCLUDED

