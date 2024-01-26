//
// DatapointFactory.h
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  DatapointFactory
//
// Definition of the DatapointFactory interface.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_DatapointFactory_INCLUDED
#define IoT_Datapoints_DatapointFactory_INCLUDED


#include "IoT/Datapoints/Datapoints.h"
#include "IoT/Datapoints/Types.h"


namespace IoT {
namespace Datapoints {


//@ remote
class IoTDatapoints_API DatapointFactory
	/// A factory for the dynamic creation of Datapoints.
{
public:
	using ServiceID = std::string;

	DatapointFactory();
		/// Creates the DatapointFactory.

	virtual ~DatapointFactory();
		/// Destroys the DatapointFactory.

	virtual ServiceID createBoolean(const BooleanDatapointParams& params) = 0;
		/// Creates a BooleanDatapoint and returns the service ID of the
		/// newly created Datapoint.

	virtual ServiceID createCounter(const CounterDatapointParams& params) = 0;
		/// Creates a CounterDatapoint and returns the service ID of the
		/// newly created Datapoint.

	virtual ServiceID createEnum(const EnumDatapointParams& params) = 0;
		/// Creates an EnumDatapoint and returns the service ID of the
		/// newly created Datapoint.

	virtual ServiceID createFlags(const FlagsDatapointParams& params) = 0;
		/// Creates an FlagsDatapoint and returns the service ID of the
		/// newly created Datapoint.

	virtual ServiceID createMovingAverage(const MovingAverageDatapointParams& params) = 0;
		/// Creates a ScalarDatapoint that implements moving average computation 
		/// and returns the service ID of the newly created Datapoint.

	virtual ServiceID createScalar(const ScalarDatapointParams& params) = 0;
		/// Creates a ScalarDatapoint and returns the service ID of the
		/// newly created Datapoint.

	virtual ServiceID createString(const StringDatapointParams& params) = 0;
		/// Creates a StringDatapoint and returns the service ID of the
		/// newly created Datapoint.

	virtual ServiceID createVector(const VectorDatapointParams& params) = 0;
		/// Creates a VectorDatapoint and returns the service ID of the
		/// newly created Datapoint.

	virtual ServiceID createComposite(const CompositeParams& params) = 0;
		/// Creates a Composite and returns the service ID of the
		/// newly created Composite.

	virtual void remove(const ServiceID serviceID) = 0;
		/// Removes the Datapoint (or Composite) with the given ID.
		///
		/// The Datapoint or Composite must have been created previously
		/// by calling one of the createXXX() methods.
};


} } // namespace IoT::Datapoints


#endif // IoT_Datapoints_DatapointFactory_INCLUDED
