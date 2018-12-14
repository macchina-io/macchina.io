//
// StateSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  StateSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_StateSkeleton_INCLUDED
#define IoT_Devices_StateSkeleton_INCLUDED


#include "IoT/Devices/StateRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class StateSkeleton: public Poco::RemotingNG::Skeleton
	/// A State represents a sensor or device register that reports a state.
	///
	/// States are represented by unsigned int (Poco::UInt32) values.
	///
	/// An actual implementation should define possible states as
	/// an enum, and provide the read-only displayValue property
	/// that returns the current state as a string suitable for display.
{
public:
	StateSkeleton();
		/// Creates a StateSkeleton.

	virtual ~StateSkeleton();
		/// Destroys a StateSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& StateSkeleton::remoting__typeId() const
{
	return IState::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_StateSkeleton_INCLUDED

