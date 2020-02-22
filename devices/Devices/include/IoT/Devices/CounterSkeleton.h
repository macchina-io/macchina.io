//
// CounterSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  CounterSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_CounterSkeleton_INCLUDED
#define IoT_Devices_CounterSkeleton_INCLUDED


#include "IoT/Devices/CounterRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class CounterSkeleton: public Poco::RemotingNG::Skeleton
	/// A counter counts events.
{
public:
	CounterSkeleton();
		/// Creates a CounterSkeleton.

	virtual ~CounterSkeleton();
		/// Destroys a CounterSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& CounterSkeleton::remoting__typeId() const
{
	return ICounter::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_CounterSkeleton_INCLUDED

