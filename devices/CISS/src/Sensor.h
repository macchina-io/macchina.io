//
// Sensor.h
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_CISS_Sensor_INCLUDED
#define IoT_CISS_Sensor_INCLUDED


#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace CISS {


class Node;


class Sensor: public IoT::Devices::DeviceImpl<IoT::Devices::Sensor, Sensor>
{
public:
	using Ptr = Poco::SharedPtr<Sensor>;

	Sensor(Node& node, Poco::UInt8 id, Poco::UInt8 streamId, const std::string& physicalQuantity, const std::string& physicalUnit);
		/// Creates a Sensor.

	~Sensor();
		/// Destroys the Sensor.

	bool isConnected() const;
		/// Returns true if the sensor's peripheral is connected.

	void update(double value);
		/// Updates the sensor value (called from the high-prio polling task).

	void enable(bool enabled);
		/// Enables or disables the sensor.

	// Sensor
	double value() const;
	bool ready() const;

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

protected:
	Poco::Any getValueChangedDelta(const std::string&) const;
	void setValueChangedDelta(const std::string&, const Poco::Any& value);
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
	Poco::Any getPhysicalQuantity(const std::string&) const;
	Poco::Any getPhysicalUnit(const std::string&) const;

protected:
	Node& _node;
	Poco::UInt8 _sensorId;
	Poco::UInt8 _streamId;
	bool _ready;
	bool _enabled;
	double _value;
	double _valueChangedDelta;
	int _samplingInterval;
	Poco::SharedPtr<IoT::Devices::EventModerationPolicy<double>> _pEventPolicy;
	Poco::Any _deviceIdentifier;
	Poco::Any _physicalQuantity;
	Poco::Any _physicalUnit;
};


} } // namespace IoT::CISS


#endif // IoT_CISS_Sensor_INCLUDED
