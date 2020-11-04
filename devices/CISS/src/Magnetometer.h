//
// Magnetometer.h
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_CISS_Magnetometer_INCLUDED
#define IoT_CISS_Magnetometer_INCLUDED


#include "IoT/Devices/Magnetometer.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace CISS {


class Node;


class Magnetometer: public IoT::Devices::DeviceImpl<IoT::Devices::Magnetometer, Magnetometer>
{
public:
	using Ptr = Poco::SharedPtr<Magnetometer>;

	enum
	{
		CISS_SENSOR_ID = 0x81
	};

	Magnetometer(Node& node);
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
	Poco::Any getSamplingInterval(const std::string&) const;
	void setSamplingInterval(const std::string&, const Poco::Any& value);
	Poco::Any getConnected(const std::string&) const;
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;

protected:
	Node& _node;
	int _samplingInterval;
	bool _enabled;
	bool _ready;
	IoT::Devices::MagneticFieldStrength _fieldStrength;
	Poco::Any _deviceIdentifier;
};


} } // namespace IoT::CISS


#endif // IoT_CISS_Magnetometer_INCLUDED
