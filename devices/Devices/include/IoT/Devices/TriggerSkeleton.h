//
// TriggerSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  TriggerSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_TriggerSkeleton_INCLUDED
#define IoT_Devices_TriggerSkeleton_INCLUDED


#include "IoT/Devices/TriggerRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class TriggerSkeleton: public Poco::RemotingNG::Skeleton
	/// The base class for triggers, such as
	/// push buttons or motion detectors.
	///
	/// In addition to the methods defined in this interface,
	/// a Trigger implementation should expose the following
	/// properties:
	///   - displayState (string, optional): The current state of the trigger,
	///     formatted as string for display purposes.
{
public:
	TriggerSkeleton();
		/// Creates a TriggerSkeleton.

	virtual ~TriggerSkeleton();
		/// Destroys a TriggerSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& TriggerSkeleton::remoting__typeId() const
{
	return ITrigger::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_TriggerSkeleton_INCLUDED

