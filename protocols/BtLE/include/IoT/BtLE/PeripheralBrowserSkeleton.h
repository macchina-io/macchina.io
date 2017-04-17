//
// PeripheralBrowserSkeleton.h
//
// Library: IoT/BtLE
// Package: Generated
// Module:  PeripheralBrowserSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_BtLE_PeripheralBrowserSkeleton_INCLUDED
#define IoT_BtLE_PeripheralBrowserSkeleton_INCLUDED


#include "IoT/BtLE/PeripheralBrowserRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace BtLE {


class PeripheralBrowserSkeleton: public Poco::RemotingNG::Skeleton
	/// This class provides browsing for available Bluetooth LE devices.
{
public:
	PeripheralBrowserSkeleton();
		/// Creates a PeripheralBrowserSkeleton.

	virtual ~PeripheralBrowserSkeleton();
		/// Destroys a PeripheralBrowserSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& PeripheralBrowserSkeleton::remoting__typeId() const
{
	return IPeripheralBrowser::remoting__typeId();
}


} // namespace BtLE
} // namespace IoT


#endif // IoT_BtLE_PeripheralBrowserSkeleton_INCLUDED

