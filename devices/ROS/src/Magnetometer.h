//
// Magnetometer.h
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_ROS_Magnetometer_INCLUDED
#define IoT_ROS_Magnetometer_INCLUDED


#include "IoT/Devices/Magnetometer.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace ROS {
namespace Devices {


class Magnetometer: public IoT::Devices::DeviceImpl<IoT::Devices::Magnetometer, Magnetometer>
{
public:
	typedef Poco::SharedPtr<Magnetometer> Ptr;

	Magnetometer();
		/// Creates a Magnetometer.

	~Magnetometer();
		/// Destroys the Magnetometer.

	bool isConnected() const;
		/// Returns true if the sensor's peripheral is connected.

	void update(const IoT::Devices::MagneticFieldStrength& fieldStrength);
		/// Updates the field strength.

	void enable(bool enabled);
		/// Enables or disables the sensor.

	// Magnetometer
	IoT::Devices::MagneticFieldStrength fieldStrength() const;

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
	IoT::Devices::MagneticFieldStrength _fieldStrength;
	Poco::Any _deviceIdentifier;
};


} } } // namespace IoT::ROS::Devices


#endif // IoT_ROS_Magnetometer_INCLUDED
