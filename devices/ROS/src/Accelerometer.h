//
// Accelerometer.h
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_ROS_Accelerometer_INCLUDED
#define IoT_ROS_Accelerometer_INCLUDED


#include "IoT/Devices/Accelerometer.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace ROS {
namespace Devices {


class Accelerometer: public IoT::Devices::DeviceImpl<IoT::Devices::Accelerometer, Accelerometer>
{
public:
	typedef Poco::SharedPtr<Accelerometer> Ptr;

	Accelerometer();
		/// Creates a Accelerometer.

	~Accelerometer();
		/// Destroys the Accelerometer.

	bool isConnected() const;
		/// Returns true if the sensor's peripheral is connected.

	void update(const IoT::Devices::Acceleration& acceleration);
		/// Updates the acceleration.

	void enable(bool enabled);
		/// Enables or disables the sensor.

	// Accelerometer
	IoT::Devices::Acceleration acceleration() const;

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

protected:
	Poco::Any getConnected(const std::string&) const;
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;

protected:
	bool _enabled;
	bool _ready;
	IoT::Devices::Acceleration _acceleration;
};


} } } // namespace IoT::ROS::Devices


#endif // IoT_ROS_Accelerometer_INCLUDED
