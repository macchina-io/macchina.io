//
// IDatapointFactory.h
//
// Library: IoT/Datapoints
// Package: Generated
// Module:  IDatapointFactory
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_IDatapointFactory_INCLUDED
#define IoT_Datapoints_IDatapointFactory_INCLUDED


#include "IoT/Datapoints/DatapointFactory.h"
#include "Poco/AutoPtr.h"
#include "Poco/OSP/Service.h"
#include "Poco/RemotingNG/Identifiable.h"


namespace IoT {
namespace Datapoints {


class IDatapointFactory: public Poco::OSP::Service
	/// A factory for the dynamic creation of Datapoints.
{
public:
	using Ptr = Poco::AutoPtr<IDatapointFactory>;

	IDatapointFactory();
		/// Creates a IDatapointFactory.

	virtual ~IDatapointFactory();
		/// Destroys the IDatapointFactory.

	virtual std::string createBoolean(const IoT::Datapoints::BooleanDatapointParams& params) = 0;
		/// Creates a BooleanDatapoint and returns the service ID of the
		/// newly created Datapoint.

	virtual std::string createComposite(const IoT::Datapoints::BasicDatapointParams& params) = 0;
		/// Creates a Composite and returns the service ID of the
		/// newly created Composite.

	virtual std::string createCounter(const IoT::Datapoints::CounterDatapointParams& params) = 0;
		/// Creates a CounterDatapoint and returns the service ID of the
		/// newly created Datapoint.

	virtual std::string createEnum(const IoT::Datapoints::EnumDatapointParams& params) = 0;
		/// Creates an EnumDatapoint and returns the service ID of the
		/// newly created Datapoint.

	virtual std::string createFlags(const IoT::Datapoints::FlagsDatapointParams& params) = 0;
		/// Creates an FlagsDatapoint and returns the service ID of the
		/// newly created Datapoint.

	virtual std::string createMovingAverage(const IoT::Datapoints::MovingAverageDatapointParams& params) = 0;
		/// Creates a ScalarDatapoint that implements moving average computation 
		/// and returns the service ID of the newly created Datapoint.

	virtual std::string createScalar(const IoT::Datapoints::ScalarDatapointParams& params) = 0;
		/// Creates a ScalarDatapoint and returns the service ID of the
		/// newly created Datapoint.

	virtual std::string createString(const IoT::Datapoints::StringDatapointParams& params) = 0;
		/// Creates a StringDatapoint and returns the service ID of the
		/// newly created Datapoint.

	virtual std::string createVector(const IoT::Datapoints::VectorDatapointParams& params) = 0;
		/// Creates a VectorDatapoint and returns the service ID of the
		/// newly created Datapoint.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void remove(const std::string serviceID) = 0;
		/// Removes the Datapoint (or Composite) with the given ID.
		///
		/// The Datapoint or Composite must have been created previously
		/// by calling one of the createXXX() methods.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

};


} // namespace Datapoints
} // namespace IoT


#endif // IoT_Datapoints_IDatapointFactory_INCLUDED

