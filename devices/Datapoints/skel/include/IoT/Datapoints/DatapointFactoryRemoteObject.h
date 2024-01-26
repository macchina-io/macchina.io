//
// DatapointFactoryRemoteObject.h
//
// Library: IoT/Datapoints
// Package: Generated
// Module:  DatapointFactoryRemoteObject
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_DatapointFactoryRemoteObject_INCLUDED
#define IoT_Datapoints_DatapointFactoryRemoteObject_INCLUDED


#include "IoT/Datapoints/IDatapointFactory.h"
#include "Poco/RemotingNG/Identifiable.h"
#include "Poco/RemotingNG/RemoteObject.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace Datapoints {


class DatapointFactoryRemoteObject: public IoT::Datapoints::IDatapointFactory, public Poco::RemotingNG::RemoteObject
	/// A factory for the dynamic creation of Datapoints.
{
public:
	using Ptr = Poco::AutoPtr<DatapointFactoryRemoteObject>;

	DatapointFactoryRemoteObject(const Poco::RemotingNG::Identifiable::ObjectId& oid, Poco::SharedPtr<IoT::Datapoints::DatapointFactory> pServiceObject);
		/// Creates a DatapointFactoryRemoteObject.

	virtual ~DatapointFactoryRemoteObject();
		/// Destroys the DatapointFactoryRemoteObject.

	std::string createBoolean(const IoT::Datapoints::BooleanDatapointParams& params);
		/// Creates a BooleanDatapoint and returns the service ID of the
		/// newly created Datapoint.

	std::string createComposite(const IoT::Datapoints::BasicDatapointParams& params);
		/// Creates a Composite and returns the service ID of the
		/// newly created Composite.

	std::string createCounter(const IoT::Datapoints::CounterDatapointParams& params);
		/// Creates a CounterDatapoint and returns the service ID of the
		/// newly created Datapoint.

	std::string createEnum(const IoT::Datapoints::EnumDatapointParams& params);
		/// Creates an EnumDatapoint and returns the service ID of the
		/// newly created Datapoint.

	std::string createFlags(const IoT::Datapoints::FlagsDatapointParams& params);
		/// Creates an FlagsDatapoint and returns the service ID of the
		/// newly created Datapoint.

	std::string createMovingAverage(const IoT::Datapoints::MovingAverageDatapointParams& params);
		/// Creates a ScalarDatapoint that implements moving average computation 
		/// and returns the service ID of the newly created Datapoint.

	std::string createScalar(const IoT::Datapoints::ScalarDatapointParams& params);
		/// Creates a ScalarDatapoint and returns the service ID of the
		/// newly created Datapoint.

	std::string createString(const IoT::Datapoints::StringDatapointParams& params);
		/// Creates a StringDatapoint and returns the service ID of the
		/// newly created Datapoint.

	std::string createVector(const IoT::Datapoints::VectorDatapointParams& params);
		/// Creates a VectorDatapoint and returns the service ID of the
		/// newly created Datapoint.

	virtual const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId() const;

	virtual void remove(const std::string serviceID);
		/// Removes the Datapoint (or Composite) with the given ID.
		///
		/// The Datapoint or Composite must have been created previously
		/// by calling one of the createXXX() methods.

private:
	Poco::SharedPtr<IoT::Datapoints::DatapointFactory> _pServiceObject;
};


inline std::string DatapointFactoryRemoteObject::createBoolean(const IoT::Datapoints::BooleanDatapointParams& params)
{
	return _pServiceObject->createBoolean(params);
}


inline std::string DatapointFactoryRemoteObject::createComposite(const IoT::Datapoints::BasicDatapointParams& params)
{
	return _pServiceObject->createComposite(params);
}


inline std::string DatapointFactoryRemoteObject::createCounter(const IoT::Datapoints::CounterDatapointParams& params)
{
	return _pServiceObject->createCounter(params);
}


inline std::string DatapointFactoryRemoteObject::createEnum(const IoT::Datapoints::EnumDatapointParams& params)
{
	return _pServiceObject->createEnum(params);
}


inline std::string DatapointFactoryRemoteObject::createFlags(const IoT::Datapoints::FlagsDatapointParams& params)
{
	return _pServiceObject->createFlags(params);
}


inline std::string DatapointFactoryRemoteObject::createMovingAverage(const IoT::Datapoints::MovingAverageDatapointParams& params)
{
	return _pServiceObject->createMovingAverage(params);
}


inline std::string DatapointFactoryRemoteObject::createScalar(const IoT::Datapoints::ScalarDatapointParams& params)
{
	return _pServiceObject->createScalar(params);
}


inline std::string DatapointFactoryRemoteObject::createString(const IoT::Datapoints::StringDatapointParams& params)
{
	return _pServiceObject->createString(params);
}


inline std::string DatapointFactoryRemoteObject::createVector(const IoT::Datapoints::VectorDatapointParams& params)
{
	return _pServiceObject->createVector(params);
}


inline const Poco::RemotingNG::Identifiable::TypeId& DatapointFactoryRemoteObject::remoting__typeId() const
{
	return IDatapointFactory::remoting__typeId();
}


inline void DatapointFactoryRemoteObject::remove(const std::string serviceID)
{
	_pServiceObject->remove(serviceID);
}


} // namespace Datapoints
} // namespace IoT


#endif // IoT_Datapoints_DatapointFactoryRemoteObject_INCLUDED

