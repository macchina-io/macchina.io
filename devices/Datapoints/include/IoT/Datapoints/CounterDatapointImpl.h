//
// CounterDatapointImpl.h
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  CounterDatapointImpl
//
// Definition of the CounterDatapointImpl class.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_CounterDatapointImpl_INCLUDED
#define IoT_Datapoints_CounterDatapointImpl_INCLUDED


#include "IoT/Datapoints/Datapoints.h"
#include "IoT/Datapoints/Types.h"
#include "IoT/Datapoints/BasicDatapointImpl.h"
#include "IoT/Devices/CounterDatapoint.h"


namespace IoT {
namespace Datapoints {


class IoTDatapoints_API CounterDatapointImpl: public BasicDatapointImpl<IoT::Devices::CounterDatapoint, CounterDatapointImpl>
	/// A basic implementation of a CounterDatapoint.
{
public:
	using Interface = IoT::Devices::CounterDatapoint;
	using Params = CounterDatapointParams;

	CounterDatapointImpl(const std::string& id, const Params& params);
		/// Creates the ScalarDatapointImpl.

	~CounterDatapointImpl();
		/// Destroys the ScalarDatapointImpl.

	CounterType forceIncrement(CounterType delta = 1);
		/// Force an update, without performing an access check.

	CounterType forceReset(CounterType value = 0);
		/// Force a reset, without performing an access check.

	// CounterDatapoint
	CounterType value() const;
	Poco::Optional<CounterType> validValue() const;
	CounterType increment(CounterType delta = 1);
	CounterType reset(CounterType value = 0);

	// Datapoint
	void invalidate();
	bool valid() const;

	CounterDatapointImpl() = delete;

	static const std::string SYMBOLIC_NAME;
	static const std::string TYPE;

protected:
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getUpdated(const std::string&) const;
	Poco::Any getAccess(const std::string&) const;
	CounterType unsafeIncrement(CounterType value);
	CounterType unsafeReset(CounterType value);

private:
	const std::string _id;
	const std::string _name;
	const int _access;
	Poco::Timestamp _updated;
	CounterType _value;
	bool _valid;
	mutable Poco::Mutex _mutex;
};


} } // namespace IoT::Datapoints


#endif // IoT_Datapoints_CounterDatapointImpl_INCLUDED
