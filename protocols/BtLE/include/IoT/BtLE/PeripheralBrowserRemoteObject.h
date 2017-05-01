//
// PeripheralBrowserRemoteObject.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralBrowserRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_PeripheralBrowserRemoteObject_INCLUDED
#define IoT_BtLE_PeripheralBrowserRemoteObject_INCLUDED


#include "IoT/BtLE/IPeripheralBrowser.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace BtLE {


class PeripheralBrowserRemoteObject: public virtual Poco::RemotingNG::RemoteObject, public IoT::BtLE::IPeripheralBrowser
	/// This class provides browsing for available Bluetooth LE devices.
{
public:
	typedef Poco::AutoPtr<PeripheralBrowserRemoteObject> Ptr;

	PeripheralBrowserRemoteObject();
		/// Creates a PeripheralBrowserRemoteObject.

	virtual ~PeripheralBrowserRemoteObject();
		/// Destroys the PeripheralBrowserRemoteObject.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

};


inline const Poco::RemotingNG::Identifiable::TypeId& PeripheralBrowserRemoteObject::remoting__typeId() const
{
	return IPeripheralBrowser::remoting__typeId();
}


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_PeripheralBrowserRemoteObject_INCLUDED

