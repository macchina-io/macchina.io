//
// Accelerometer.h
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_CISS_Accelerometer_INCLUDED
#define IoT_CISS_Accelerometer_INCLUDED


#include "IoT/Devices/Accelerometer.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace CISS {


class Node;


class Accelerometer: public IoT::Devices::DeviceImpl<IoT::Devices::Accelerometer, Accelerometer>
{
public:
	typedef Poco::SharedPtr<Accelerometer> Ptr;

	enum
	{
		CISS_SENSOR_ID = 0x80
	};

	Accelerometer(Node& node);
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
	Poco::Any getSamplingInterval(const std::string&) const;
	void setSamplingInterval(const std::string&, const Poco::Any& value);
	Poco::Any getConnected(const std::string&) const;
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getRange(const std::string&) const;
	void setRange(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;

protected:
	Node& _node;
	int _range;
	int _samplingInterval;
	bool _enabled;
	bool _ready;
	IoT::Devices::Acceleration _acceleration;
	Poco::Any _deviceIdentifier;
};


} } // namespace IoT::CISS


#endif // IoT_CISS_Accelerometer_INCLUDED
