//
// RotaryEncoderSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  RotaryEncoderSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_RotaryEncoderSkeleton_INCLUDED
#define IoT_Devices_RotaryEncoderSkeleton_INCLUDED


#include "IoT/Devices/RotaryEncoderRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class RotaryEncoderSkeleton: public Poco::RemotingNG::Skeleton
	/// A rotary encoder with an optional push button.
{
public:
	RotaryEncoderSkeleton();
		/// Creates a RotaryEncoderSkeleton.

	virtual ~RotaryEncoderSkeleton();
		/// Destroys a RotaryEncoderSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& RotaryEncoderSkeleton::remoting__typeId() const
{
	return IRotaryEncoder::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_RotaryEncoderSkeleton_INCLUDED

