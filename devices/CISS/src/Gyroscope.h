//
// Gyroscope.h
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_CISS_Gyroscope_INCLUDED
#define IoT_CISS_Gyroscope_INCLUDED


#include "IoT/Devices/Gyroscope.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace CISS {


class Node;


class Gyroscope: public IoT::Devices::DeviceImpl<IoT::Devices::Gyroscope, Gyroscope>
{
public:
	using Ptr = Poco::SharedPtr<Gyroscope>;

	enum
	{
		CISS_SENSOR_ID = 0x82
	};

	Gyroscope(Node& node);
		/// Creates a Gyroscope.

	~Gyroscope();
		/// Destroys the Gyroscope.

	bool isConnected() const;
		/// Returns true if the sensor's peripheral is connected.

	void update(const IoT::Devices::Rotation& rotation);
		/// Updates the Rotation.

	void enable(bool enabled);
		/// Enables or disables the sensor.

	// Gyroscope
	IoT::Devices::Rotation rotation() const;

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
	IoT::Devices::Rotation _rotation;
	Poco::Any _deviceIdentifier;
};


} } // namespace IoT::CISS


#endif // IoT_CISS_Gyroscope_INCLUDED
