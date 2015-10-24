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
	/// The interface for general purpose input/output (GPIO)
	/// ports.
	///
	/// This class represents a single GPIO pin. 
	/// Mapping to physical pins is configured when setting up 
	/// the specific IO implementation class, typically using a 
	/// configuration file.
	///
	/// Implementations supporting dynamically changing pin directions
	/// should expose a string property named "direction" that takes the
	/// values "in" and "out".
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

