//
// GyroscopeSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  GyroscopeSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_GyroscopeSkeleton_INCLUDED
#define IoT_Devices_GyroscopeSkeleton_INCLUDED


#include "IoT/Devices/GyroscopeRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class GyroscopeSkeleton: public Poco::RemotingNG::Skeleton
	/// The interface for three-axis Gyroscopes.
{
public:
	GyroscopeSkeleton();
		/// Creates a GyroscopeSkeleton.

	virtual ~GyroscopeSkeleton();
		/// Destroys a GyroscopeSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& GyroscopeSkeleton::remoting__typeId() const
{
	return IGyroscope::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_GyroscopeSkeleton_INCLUDED

