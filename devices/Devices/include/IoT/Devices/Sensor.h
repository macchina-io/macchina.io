//
// Sensor.h
//
// $Id: //iot/Main/Devices/include/IoT/Devices/Sensor.h#2 $
//
// Library: IoT/Devices
// Package: Devices
// Module:  Sensor
//
// Definition of the Sensor interface.
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_Sensor_INCLUDED
#define IoT_Devices_Sensor_INCLUDED


#include "IoT/Devices/Device.h"
#include "Poco/RemotingNG/EventFilter.h"
#include "Poco/BasicEvent.h"


namespace IoT {
namespace Devices {


//@ remote
class IoTDevices_API Sensor: public Device
	/// The base class for analog sensors, such as
	/// temperature or ambient light sensors.
	///
	/// In addition to the methods defined in this interface,
	/// a Sensor implementation should expose the following
	/// properties:
	///   - physicalQuantity (string): The physical quantity that is
	///     being measured by the sensor, e.g. "temperature".
	///   - physicalUnit (string): The physical unit the measured value
	///     is being represented in (e.g. "°C"), UTF-8 encoded.
	///     See the PHYSICAL_UNIT_* strings for predefined values.
	///   - displayValue (string, optional): The current value of the sensor,
	///     formatted as string for display purposes.
{
public:
	//@ filter=true
	Poco::BasicEvent<const double> valueChanged;
		/// Fired when the state of the Sensor has changed.
		///
		/// Actual behavior of this event (e.g., minimum interval
		/// between fires) are implementation specific
		/// and can be configured via properties.
		
	Sensor();
		/// Creates the Sensor.
		
	~Sensor();
		/// Destroys the Sensor.

	virtual double value() const = 0;
		/// Returns the current value measured by the sensor.
		///
		/// Some sensors may not be able to immediately report
		/// a valid value. Therefore, before calling value() the first time, ready() 
		/// should be called to check if a valid value is available.
		
	virtual bool ready() const = 0;
		/// Returns true if a valid value is available.

	void clearValueChangedFilter(const std::string& subscriberURI);
		/// Clears the filter set for the valueChanged event.

	void setValueChangedIsGreaterThanFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::GreaterThanFilter for the valueChanged event.

	void setValueChangedIsGreaterThanOrEqualToFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::GreaterThanFilter for the valueChanged event.

	void setValueChangedIsLessThanThanFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::LessThanFilter for the valueChanged event.

	void setValueChangedIsLessThanOrEqualToFilter(const std::string& subscriberURI, double limit);
		/// Sets a Poco::RemotingNG::LessThanOrEqualToFilter for the valueChanged event.

	void setValueChangedMinimumDeltaFilter(const std::string& subscriberURI, double delta);
		/// Sets a Poco::RemotingNG::MinimumDeltaFilter for the valueChanged event.

	void setValueChangedMinimumIntervalFilter(const std::string& subscriberURI, long milliseconds);
		/// Sets a Poco::RemotingNG::MinimumIntervalFilter for the valueChanged event.
		
	void setValueChangedMinimumIntervalOrDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta);
		/// Sets a Poco::RemotingNG::MinimumIntervalOrDeltaFilter for the valueChanged event.
		
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


#endif // IoT_Devices_Sensor_INCLUDED
