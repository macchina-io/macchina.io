//
// SwitchSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  SwitchSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_SwitchSkeleton_INCLUDED
#define IoT_Devices_SwitchSkeleton_INCLUDED


#include "IoT/Devices/SwitchRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class SwitchSkeleton: public Poco::RemotingNG::Skeleton
	/// The base class for switchable things (that can
	/// be turned on and off).
	///
	/// A Switch has a current state and a target state.
	/// Depending upon the implementation, the current state
	/// and target state may be different for a short amount
	/// of time (e.g., while the device is powering on).
	///
	/// In addition to the methods defined in this interface,
	/// a Switch implementation should expose the following
	/// properties:
	///   - displayState (string, optional): The current state of the Switch,
	///     formatted as string for display purposes.
{
public:
	SwitchSkeleton();
		/// Creates a SwitchSkeleton.

	virtual ~SwitchSkeleton();
		/// Destroys a SwitchSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& SwitchSkeleton::remoting__typeId() const
{
	return ISwitch::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_SwitchSkeleton_INCLUDED

