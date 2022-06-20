//
// UnitsOfMeasureServiceSkeleton.h
//
// Library: IoT/UnitsOfMeasure
// Package: Generated
// Module:  UnitsOfMeasureServiceSkeleton
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2018-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_UnitsOfMeasure_UnitsOfMeasureServiceSkeleton_INCLUDED
#define IoT_UnitsOfMeasure_UnitsOfMeasureServiceSkeleton_INCLUDED


#include "IoT/UnitsOfMeasure/UnitsOfMeasureServiceRemoteObject.h"
#include "Poco/RemotingNG/Skeleton.h"


namespace IoT {
namespace UnitsOfMeasure {


class UnitsOfMeasureServiceSkeleton: public Poco::RemotingNG::Skeleton
	/// The UnitsOfMeasureService service is mainly used to map
	/// [[http://unitsofmeasure.org/ucum.html Unified Code for Units of Measure]] (UCUM),
	/// codes, such as used with the IoT::Devices::Sensor interface, to display/print units.
	///
	/// It provides a programmatic interface to the
	/// [[http://unitsofmeasure.org/ucum-essence.xml UCUM-Essence XML file]]
	/// containing unit definitions.
{
public:
	UnitsOfMeasureServiceSkeleton();
		/// Creates a UnitsOfMeasureServiceSkeleton.

	virtual ~UnitsOfMeasureServiceSkeleton();
		/// Destroys a UnitsOfMeasureServiceSkeleton.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	static const std::string DEFAULT_NS;
};


inline const Poco::RemotingNG::Identifiable::TypeId& UnitsOfMeasureServiceSkeleton::remoting__typeId() const
{
	return IUnitsOfMeasureService::remoting__typeId();
}


} // namespace UnitsOfMeasure
} // namespace IoT


#endif // IoT_UnitsOfMeasure_UnitsOfMeasureServiceSkeleton_INCLUDED

