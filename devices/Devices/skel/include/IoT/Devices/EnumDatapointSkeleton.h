//
// EnumDatapointSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  EnumDatapointSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_EnumDatapointSkeleton_INCLUDED
#define IoT_Devices_EnumDatapointSkeleton_INCLUDED


#include "IoT/Devices/EnumDatapointRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class EnumDatapointSkeleton: public Poco::RemotingNG::Skeleton
	/// The base class for datapoints holding an enumeration
	/// value (based on an int).
	///
	/// An implementation should handle conversion between an
	/// integer value and the corresponding symbolic name.
	///
	/// In addition to the methods defined in this interface,
	/// a EnumDatapoint implementation should expose the following
	/// properties:
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	EnumDatapointSkeleton();
		/// Creates a EnumDatapointSkeleton.

	virtual ~EnumDatapointSkeleton();
		/// Destroys a EnumDatapointSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& EnumDatapointSkeleton::remoting__typeId() const
{
	return IEnumDatapoint::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_EnumDatapointSkeleton_INCLUDED

