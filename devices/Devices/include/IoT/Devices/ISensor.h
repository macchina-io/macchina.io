//
// ISensor.h
//
// Library: IoT/Devices
// Package: Generated
// Module:  ISensor
//
// This file has been generated.
// Warning: All changes to this will be lost when the file is re-generated.
//
// Copyright (c) 2014-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
// 
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_ISensor_INCLUDED
#define IoT_Devices_ISensor_INCLUDED


#include "IoT/Devices/IDevice.h"
#include "IoT/Devices/Sensor.h"
#include "Poco/RemotingNG/Listener.h"


namespace IoT {
namespace Devices {


class ISensor: public IoT::Devices::IDevice
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
	typedef Poco::AutoPtr<ISensor> Ptr;

	ISensor();
		/// Creates a ISensor.

	virtual ~ISensor();
		/// Destroys the ISensor.

	virtual void clearValueChangedFilter(const std::string& subscriberURI) = 0;
		/// Clears the filter set for the valueChanged event.

	bool isA(const std::type_info& otherType) const;
		/// Returns true if the class is a subclass of the class given by otherType.

	virtual bool ready() const = 0;
		/// Returns true if a valid value is available.

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

	virtual void setValueChangedIsLessThanOrEqualToFilter(const std::string& subscriberURI, double limit) = 0;
		/// Sets a Poco::RemotingNG::LessThanOrEqualToFilter for the valueChanged event.

	virtual void setValueChangedIsLessThanThanFilter(const std::string& subscriberURI, double limit) = 0;
		/// Sets a Poco::RemotingNG::LessThanFilter for the valueChanged event.

	virtual void setValueChangedMinimumDeltaFilter(const std::string& subscriberURI, double delta) = 0;
		/// Sets a Poco::RemotingNG::MinimumDeltaFilter for the valueChanged event.

	virtual void setValueChangedMinimumIntervalFilter(const std::string& subscriberURI, long milliseconds) = 0;
		/// Sets a Poco::RemotingNG::MinimumIntervalFilter for the valueChanged event.

	virtual void setValueChangedMinimumIntervalOrDeltaFilter(const std::string& subscriberURI, long milliseconds, double delta) = 0;
		/// Sets a Poco::RemotingNG::MinimumIntervalOrDeltaFilter for the valueChanged event.

	const std::type_info& type() const;
		/// Returns the type information for the object's class.

	virtual double value() const = 0;
		/// Returns the current value measured by the sensor.
		///
		/// Some sensors may not be able to immediately report
		/// a valid value. Therefore, before calling value() the first time, ready() 
		/// should be called to check if a valid value is available.

	Poco::BasicEvent < const double > valueChanged;
};


} // namespace Devices
} // namespace IoT


#endif // IoT_Devices_ISensor_INCLUDED

