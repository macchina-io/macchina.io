//
// Accelerometer.h
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_ROS_GNSSSensor_INCLUDED
#define IoT_ROS_GNSSSensor_INCLUDED


#include "IoT/Devices/GNSSSensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace ROS {
namespace Devices {


class GNSSSensor: public IoT::Devices::DeviceImpl<IoT::Devices::GNSSSensor, GNSSSensor>
{
public:
	typedef Poco::SharedPtr<GNSSSensor> Ptr;

	GNSSSensor();
		/// Creates a GNSSSensor.

	~GNSSSensor();
		/// Destroys the GNSSSensor.

	bool isConnected() const;
		/// Returns true if the sensor's peripheral is connected.

	void update(const IoT::Devices::PositionUpdate& position, double altitude);
		/// Updates the position.

	void enable(bool enabled);
		/// Enables or disables the sensor.

	// GNSSSensor
	bool positionAvailable() const;
	IoT::Devices::LatLon position() const;
	double course() const;
	double speed() const;
	double magneticVariation() const;
	double altitude() const;
	double hdop() const;

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
	IoT::Devices::PositionUpdate _position;
	double _altitude;
};


} } } // namespace IoT::ROS::Devices


#endif // IoT_ROS_GNSSSensor_INCLUDED
