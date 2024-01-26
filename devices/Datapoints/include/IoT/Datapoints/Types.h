//
// Types.h
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  Types
//
// Definition of various utility types.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_Types_INCLUDED
#define IoT_Datapoints_Types_INCLUDED


#include "IoT/Datapoints/Datapoints.h"
#include "IoT/Devices/CounterDatapoint.h"
#include "IoT/Devices/EnumDatapoint.h"
#include "IoT/Devices/FlagsDatapoint.h"
#include "IoT/Devices/VectorDatapoint.h"
#include "IoT/Devices/Composite.h"
#include "Poco/Optional.h"
#include <vector>


namespace IoT {
namespace Datapoints {


enum AccessFlags
{
	ACCESS_NONE  = 0x00,
	ACCESS_READ  = 0x01,
	ACCESS_WRITE = 0x02,
	ACCESS_ALL   = ACCESS_READ | ACCESS_WRITE
};


//@ serialize
struct Tag
{
	std::string name;
	std::string value;
};


//@ serialize
struct BasicDatapointParams
	/// Parameters for creating any Datapoint.
{
	std::string name;
		/// Name of datapoint.

	//@ optional
	std::string composite;
		/// ID of parent Composite.

	//@ optional
	int access = ACCESS_ALL;
		/// Access (see AccessFlags).

	//@ optional
	std::vector<Tag> tags;
		/// Optional service properties.

	//@ optional
	std::string customData;
};


//@ serialize
struct BooleanDatapointParams: public BasicDatapointParams
	/// Parameters for creating a BooleanDatapoint.
{
	//@ optional
	Poco::Optional<bool> initialValue;
		/// Initial datapoint value.
};


//@ serialize
struct CounterDatapointParams: public BasicDatapointParams
{
	//@ optional
	Poco::Optional<Poco::UInt64> initialValue;
		/// Initial datapoint value.
};


//@ serialize
struct EnumDatapointParams: public BasicDatapointParams
{
	//@ optional
	Poco::Optional<int> initialValue;
		/// Initial datapoint value.

	std::vector<IoT::Devices::EnumValue> values;
		/// Vector of mappings of numeric values to symbolic names.
};


//@ serialize
struct FlagsDatapointParams: public BasicDatapointParams
{
	//@ optional
	Poco::Optional<std::vector<bool>> initialValue;
		/// Initial datapoint value.

	std::vector<IoT::Devices::FlagValue> values;
		/// Vector of mappings of numeric values to symbolic names.
};


//@ serialize
struct ScalarDatapointParams: public BasicDatapointParams
{
	//@ optional
	std::string physicalQuantity;
		/// The physical quantity the datapoint measures.

	//@ optional
	std::string physicalUnit;
		/// The physical unit used.

	//@ optional
	Poco::Optional<double> initialValue;
		/// Initial datapoint value.
};


//@ serialize
struct MovingAverageDatapointParams: public BasicDatapointParams
{
	//@ optional
	std::string physicalQuantity;
		/// The physical quantity the datapoint measures.

	//@ optional
	std::string physicalUnit;
		/// The physical unit used.

	//@ optional
	std::size_t windowSize = 10;
		/// Number of datapoints for moving average computation.
};


//@ serialize
struct StringDatapointParams: public BasicDatapointParams
{
	//@ optional
	Poco::Optional<std::string> initialValue;
		/// Initial datapoint value.
};


//@ serialize
struct VectorDatapointParams: public BasicDatapointParams
{
	//@ optional
	Poco::Optional<std::vector<double>> initialValue;
		/// Initial datapoint value.
};


using CompositeParams = BasicDatapointParams;


} } // namespace IoT::Datapoints


#endif // IoT_Datapoints_Types_INCLUDED
