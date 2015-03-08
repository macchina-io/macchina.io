//
// IOSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IOSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_IOSkeleton_INCLUDED
#define IoT_Devices_IOSkeleton_INCLUDED


#include "IoT/Devices/IORemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class IOSkeleton: public Poco::RemotingNG::Skeleton
	/// The base class for general purpose input/output (GPIO)
	/// devices.
	///
	/// The IO class supports up to 32 logical pins. Each logical
	/// pin is mapped to a physical pin on the hardware. Logical
	/// pins are counted from 0 to 31. Mapping to physical pins
	/// is configured when setting up the IO implementation class,
	/// typically using a configuration file.
	///
	/// Implementations that support interrupt-capable input pins
	/// should expose an int property named "stateChangedEventMask"
	/// that allows enabling interrupts for specific pins, based
	/// on the given bit mask.
	///
	/// Implementations supporting dynamically changing pin directions
	/// should expose int properties named "configureInputs" and
	/// "configureOutputs" that take a bit mask specifying affected pins.
{
public:
	IOSkeleton();
		/// Creates a IOSkeleton.

	virtual ~IOSkeleton();
		/// Destroys a IOSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& IOSkeleton::remoting__typeId() const
{
	return IIO::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IOSkeleton_INCLUDED

