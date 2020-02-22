//
// Gyroscope.h
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_ROS_Gyroscope_INCLUDED
#define IoT_ROS_Gyroscope_INCLUDED


#include "IoT/Devices/Gyroscope.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace ROS {
namespace Devices {


class Gyroscope: public IoT::Devices::DeviceImpl<IoT::Devices::Gyroscope, Gyroscope>
{
public:
	typedef Poco::SharedPtr<Gyroscope> Ptr;

	Gyroscope();
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
	IoT::Devices::Rotation _rotation;
};


} } } // namespace IoT::ROS::Devices


#endif // IoT_ROS_Gyroscope_INCLUDED
