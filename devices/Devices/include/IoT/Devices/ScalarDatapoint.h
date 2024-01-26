//
// ScalarDatapoint.h
//
// Library: IoT/Devices
// Package: Datapoints
// Module:  ScalarDatapoint
//
// Definition of the ScalarDatapoing interface.
//
// Copyright (c) 2022, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Devices_ScalarDatapoint_INCLUDED
#define IoT_Devices_ScalarDatapoint_INCLUDED


#include "IoT/Devices/Datapoint.h"
#include "Poco/RemotingNG/EventFilter.h"
#include "Poco/BasicEvent.h"
#include "Poco/Optional.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API ScalarDatapoint: public Datapoint
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
	//@ filter=true
	Poco::BasicEvent<const double> valueChanged;
		/// Fired when the value of the Datapoint has changed.
		///
		/// Actual behavior of this event (e.g., minimum interval
		/// between fires) are implementation specific
		/// and can be configured via properties.

	Poco::BasicEvent<const double> valueUpdated;
		/// Fired when the value of the Datapoint has been updated.
		///
		/// This event is fired whenever the value of the datapoint
		/// is set with a call to update(), even if the actual
		/// value has not changed.

	Poco::BasicEvent<const double> validated;
		/// Fired when an invalid datapoint becomes valid again, by
		/// being updated with a new value. The new valud is given
		/// as event argument.

	ScalarDatapoint();
		/// Creates the ScalarDatapoint.

	~ScalarDatapoint();
		/// Destroys the ScalarDatapoint.

	virtual double value() const = 0;
		/// Returns the current value held by the datapoint,
		/// even if the datapoint has been invalidated.
		///
		/// Use validValue() to get a valid value only.

	virtual Poco::Optional<double> validValue() const = 0;
		/// Returns the current value held by the datapoint if
		/// it is value, otherwise an empty value.

	virtual void update(double value) = 0;
		/// Updates the value of the datapoint and makes it valid.
		///
		/// Not all Datapoint implementations may support
		/// this method.

	void clearValueChangedFilter(const std::string& subscriberURI);
		/// Clears the filter set for the valueChanged event.

	void setValueChangedIsGreaterThanFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::GreaterThanFilter for the valueChanged event.

	void setValueChangedIsGreaterThanOrEqualToFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::GreaterThanFilter for the valueChanged event.

	void setValueChangedIsLessThanFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::LessThanFilter for the valueChanged event.

	void setValueChangedIsLessThanOrEqualToFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::LessThanOrEqualToFilter for the valueChanged event.

	void setValueChangedMinimumDeltaFilter(const std::string& subscriberURI, double delta);
		/// Sets a Poco::RemotingNG::MinimumDeltaFilter for the valueChanged event.

	void setValueChangedMinimumIntervalFilter(const std::string& subscriberURI, long milliseconds);
		/// Sets a Poco::RemotingNG::MinimumIntervalFilter for the valueChanged event.

	void setValueChangedMinimumIntervalOrDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta);
		/// Sets a Poco::RemotingNG::MinimumIntervalOrDeltaFilter for the valueChanged event.

	void setValueChangedMinimumIntervalAndDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta);
		/// Sets a Poco::RemotingNG::MinimumIntervalAndDeltaFilter for the valueChanged event.

	void setValueChangedHysteresisFilter(const std::string& subscriberURI, double lowerThreshold, double upperThreshold);
		/// Sets a Poco::RemotingNG::HysteresisFilter for the valueChanged event.

	static std::string PHYSICAL_UNIT_DEGREES_CELSIUS;
	static std::string PHYSICAL_UNIT_DEGREES_FAHRENHEIT;
	static std::string PHYSICAL_UNIT_KELVIN;
	static std::string PHYSICAL_UNIT_METER;
	static std::string PHYSICAL_UNIT_KILOGRAM;
	static std::string PHYSICAL_UNIT_SECOND;
	static std::string PHYSICAL_UNIT_VOLT;
	static std::string PHYSICAL_UNIT_AMPERE;
	static std::string PHYSICAL_UNIT_MOL;
	static std::string PHYSICAL_UNIT_CANDELA;
	static std::string PHYSICAL_UNIT_LUX;
	static std::string PHYSICAL_UNIT_MBAR;

private:
	void setValueChangedFilter(const std::string& subscriberURI, Poco::RemotingNG::EventFilter<double>::Ptr pFilter);
};


} } // namespace IoT::Devices


#endif // IoT_Devices_ScalarDatapoint_INCLUDED
