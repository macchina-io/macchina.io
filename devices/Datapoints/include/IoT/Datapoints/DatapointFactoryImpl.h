//
// DatapointFactoryImpl.h
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  DatapointFactoryImpl
//
// Definition of the DatapointFactoryImpl class.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_DatapointFactoryImpl_INCLUDED
#define IoT_Datapoints_DatapointFactoryImpl_INCLUDED


#include "IoT/Datapoints/DatapointFactory.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/Util/Timer.h"
#include "Poco/Mutex.h"
#include <vector>
#include <map>


namespace IoT {
namespace Datapoints {


class IoTDatapoints_API DatapointFactoryImpl: public DatapointFactory
	/// The default implementation of DatapointFactory.
{
public:
	DatapointFactoryImpl(Poco::OSP::BundleContext::Ptr pBundleContext);
		/// Creates the DatapointFactoryImpl.

	~DatapointFactoryImpl();
		/// Destroys the DatapointFactoryImpl.

	// DatapointFactory
	ServiceID createBoolean(const BooleanDatapointParams& params);
	ServiceID createCounter(const CounterDatapointParams& params);
	ServiceID createEnum(const EnumDatapointParams& params);
	ServiceID createFlags(const FlagsDatapointParams& params);
	ServiceID createMovingAverage(const MovingAverageDatapointParams& params);
	ServiceID createScalar(const ScalarDatapointParams& params);
	ServiceID createString(const StringDatapointParams& params);
	ServiceID createVector(const VectorDatapointParams& params);
	ServiceID createComposite(const CompositeParams& params);
	void remove(const ServiceID serviceID);

protected:
	template <typename ServiceType, typename ParamsType>
	Poco::OSP::ServiceRef::Ptr createService(Poco::SharedPtr<ServiceType> pService, const std::string& id, const ParamsType& params);
	unsigned createId(unsigned type);

	enum 
	{
		ID_BOOLEAN,
		ID_COUNTER,
		ID_ENUM,
		ID_FLAGS,
		ID_MOVING_AVERAGE,
		ID_SCALAR,
		ID_STRING,
		ID_VECTOR,
		ID_COMPOSITE,
		ID_MAX
	};

private:
	Poco::OSP::BundleContext::Ptr _pBundleContext;
	std::vector<Poco::OSP::ServiceRef::Ptr> _serviceRefs;
	std::vector<unsigned> _ids;
	Poco::Util::Timer _timer;
	Poco::FastMutex _mutex;
};


} } // namespace IoT::Datapoints


#endif // IoT_Datapoints_DatapointFactoryImpl_INCLUDED
