//
// CameraSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  CameraSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_CameraSkeleton_INCLUDED
#define IoT_Devices_CameraSkeleton_INCLUDED


#include "IoT/Devices/CameraRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class CameraSkeleton: public Poco::RemotingNG::Skeleton
	/// The base class for image sensors, also known as cameras.
{
public:
	CameraSkeleton();
		/// Creates a CameraSkeleton.

	virtual ~CameraSkeleton();
		/// Destroys a CameraSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& CameraSkeleton::remoting__typeId() const
{
	return ICamera::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_CameraSkeleton_INCLUDED

