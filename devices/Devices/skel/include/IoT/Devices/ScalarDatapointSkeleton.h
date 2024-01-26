//
// ScalarDatapointSkeleton.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  ScalarDatapointSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_ScalarDatapointSkeleton_INCLUDED
#define IoT_Devices_ScalarDatapointSkeleton_INCLUDED


#include "IoT/Devices/ScalarDatapointRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace Devices {


class ScalarDatapointSkeleton: public Poco::RemotingNG::Skeleton
	/// A scalar datapoint holding a single numeric (double) value.
	///
	/// In addition to the methods defined in this interface,
	/// a ScalarDatapoint implementation should expose the following
	/// properties:
	///   - physicalQuantity (string): The physical quantity that is
	///     being measured by the datapoint, e.g. "temperature".
	///   - physicalUnit (string): The physical unit the measured value
	///     is being represented in (e.g. "Cel" for degree Celsius).
	///     This should use the "c/s" symbols from the Unified Code for Units of Measure
	///     (http://unitsofmeasure.org/ucum.html).
	///     See the PHYSICAL_UNIT_* strings for predefined values.
	///   - displayValue (string, optional): The current value of the datapoint,
	///     formatted as string for display purposes.
{
public:
	ScalarDatapointSkeleton();
		/// Creates a ScalarDatapointSkeleton.

	virtual ~ScalarDatapointSkeleton();
		/// Destroys a ScalarDatapointSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& ScalarDatapointSkeleton::remoting__typeId() const
{
	return IScalarDatapoint::remoting__typeId();
}


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_ScalarDatapointSkeleton_INCLUDED

