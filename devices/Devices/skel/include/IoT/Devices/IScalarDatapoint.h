//
// IScalarDatapoint.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  IScalarDatapoint
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_IScalarDatapoint_INCLUDED
#define IoT_Devices_IScalarDatapoint_INCLUDED


#include "IoT/Devices/IDatapoint.h"
#include "IoT/Devices/ScalarDatapoint.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class IScalarDatapoint: public IoT::Devices::IDatapoint
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
	using Ptr = Poco::AutoPtr<IScalarDatapoint>;

	IScalarDatapoint();
		/// Creates a IScalarDatapoint.

	virtual ~IScalarDatapoint();
		/// Destroys the IScalarDatapoint.

	virtual void clearValueChangedFilter(const std::string& subscriberURI) = 0;
		/// Clears the filter set for the valueChanged event.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual std::string remoting__enableEvents(Poco::RemotingNG::Listener::Ptr pListener, bool enable = bool(true)) = 0;
		/// Enable or disable delivery of remote events.
		///
		/// The given Listener instance must implement the Poco::RemotingNG::EventListener
		/// interface, otherwise this method will fail with a RemotingException.
		///
		/// This method is only used with Proxy objects; calling this method on a
		/// RemoteObject will do nothing.

	static const Poco::RemotingNG::Identifiable::TypeId& remoting__typeId();
		/// Returns the TypeId of the class.

	virtual void setValueChangedHysteresisFilter(const std::string& subscriberURI, double lowerThreshold, double upperThreshold) = 0;
		/// Sets a Poco::RemotingNG::HysteresisFilter for the valueChanged event.

	virtual void setValueChangedIsGreaterThanFilter(const std::string& subscriberURI, double limit) = 0;
		/// Sets a Poco::RemotingNG::GreaterThanFilter for the valueChanged event.

	virtual void setValueChangedIsGreaterThanOrEqualToFilter(const std::string& subscriberURI, double limit) = 0;
		/// Sets a Poco::RemotingNG::GreaterThanFilter for the valueChanged event.

	virtual void setValueChangedIsLessThanFilter(const std::string& subscriberURI, double limit) = 0;
		/// Sets a Poco::RemotingNG::LessThanFilter for the valueChanged event.

	virtual void setValueChangedIsLessThanOrEqualToFilter(const std::string& subscriberURI, double limit) = 0;
		/// Sets a Poco::RemotingNG::LessThanOrEqualToFilter for the valueChanged event.

	virtual void setValueChangedMinimumDeltaFilter(const std::string& subscriberURI, double delta) = 0;
		/// Sets a Poco::RemotingNG::MinimumDeltaFilter for the valueChanged event.

	virtual void setValueChangedMinimumIntervalAndDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta) = 0;
		/// Sets a Poco::RemotingNG::MinimumIntervalAndDeltaFilter for the valueChanged event.

	virtual void setValueChangedMinimumIntervalFilter(const std::string& subscriberURI, long milliseconds) = 0;
		/// Sets a Poco::RemotingNG::MinimumIntervalFilter for the valueChanged event.

	virtual void setValueChangedMinimumIntervalOrDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta) = 0;
		/// Sets a Poco::RemotingNG::MinimumIntervalOrDeltaFilter for the valueChanged event.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	virtual void update(double value) = 0;
		/// Updates the value of the datapoint and makes it valid.
		///
		/// Not all Datapoint implementations may support
		/// this method.

	virtual Poco::Optional<double> validValue() const = 0;
		/// Returns the current value held by the datapoint if
		/// it is valid, otherwise an empty value.

	virtual double value() const = 0;
		/// Returns the current value held by the datapoint,
		/// even if the datapoint has been invalidated.
		///
		/// Use validValue() to get a valid value only.

	Poco::BasicEvent<const double> validated;
	Poco::BasicEvent<const double> valueChanged;
	Poco::BasicEvent<const double> valueUpdated;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_IScalarDatapoint_INCLUDED

