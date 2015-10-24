//
// MagnetometerSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  MagnetometerSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_MagnetometerSkeleton_INCLUDED
#define IoT_Devices_MagnetometerSkeleton_INCLUDED


#include "IoT/Devices/MagnetometerRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class MagnetometerSkeleton: public Poco::RemotingNG::Skeleton
	/// The interface for three-axis Magnetometers.
{
public:
	MagnetometerSkeleton();
		/// Creates a MagnetometerSkeleton.

	virtual ~MagnetometerSkeleton();
		/// Destroys a MagnetometerSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& MagnetometerSkeleton::remoting__typeId() const
{
	return IMagnetometer::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_MagnetometerSkeleton_INCLUDED

