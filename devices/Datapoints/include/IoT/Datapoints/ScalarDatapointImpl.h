//
// ScalarDatapointImpl.h
//
// Library: IoT/Datapoints
// Package: Datapoints
// Module:  ScalarDatapointImpl
//
// Definition of the ScalarDatapoingImpl class.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Datapoints_ScalarDatapointImpl_INCLUDED
#define IoT_Datapoints_ScalarDatapointImpl_INCLUDED


#include "IoT/Datapoints/Datapoints.h"
#include "IoT/Datapoints/Types.h"
#include "IoT/Datapoints/BasicDatapointImpl.h"
#include "IoT/Devices/ScalarDatapoint.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "Poco/Util/Timer.h"


namespace IoT {
namespace Datapoints {


class IoTDatapoints_API ScalarDatapointImpl: public BasicDatapointImpl<IoT::Devices::ScalarDatapoint, ScalarDatapointImpl>
	/// A basic implementation of a ScalarDatapoint.
{
public:
	using Interface = IoT::Devices::ScalarDatapoint;
	using Params = ScalarDatapointParams;

	ScalarDatapointImpl(const std::string& id, const Params& params, Poco::Util::Timer& timer);
		/// Creates the ScalarDatapointImpl.

	~ScalarDatapointImpl();
		/// Destroys the ScalarDatapointImpl.

	void forceUpdate(double value);
		/// Force an update, without performing an access check.

	// ScalarDatapoint
	double value() const;
	Poco::Optional<double> validValue() const;
	void update(double value);

	// Datapoint
	void invalidate();
	bool valid() const;

	ScalarDatapointImpl() = delete;

	static const std::string SYMBOLIC_NAME;
	static const std::string TYPE;

protected:
	Poco::Any getValueChangedPeriod(const std::string&) const;
	void setValueChangedPeriod(const std::string&, const Poco::Any& value);
	Poco::Any getValueChangedDelta(const std::string&) const;
	void setValueChangedDelta(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getPhysicalQuantity(const std::string&) const;
	Poco::Any getPhysicalUnit(const std::string&) const;
	Poco::Any getUpdated(const std::string&) const;
	Poco::Any getAccess(const std::string&) const;
	void unsafeUpdate(double value);

private:
	const std::string _id;
	const std::string _name;
	const std::string _physicalQuantity;
	const std::string _physicalUnit;
	const int _access;
	Poco::Timestamp _updated;
	double _value;
	bool _valid;
	int _valueChangedPeriod = 0;
	double _valueChangedDelta = 0.0;
	Poco::SharedPtr<IoT::Devices::EventModerationPolicy<double>> _pEventPolicy;
	Poco::Util::Timer& _timer;
};


} } // namespace IoT::Datapoints


#endif // IoT_Datapoints_ScalarDatapointImpl_INCLUDED
