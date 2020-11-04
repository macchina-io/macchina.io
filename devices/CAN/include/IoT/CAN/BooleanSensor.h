//
// BooleanSensor.h
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_CAN_BooleanSensor_INCLUDED
#define IoT_CAN_BooleanSensor_INCLUDED


#include "IoT/CAN/CANDevices.h"
#include "IoT/Devices/BooleanSensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace CAN {


class IoTCANDevices_API BooleanSensor: public IoT::Devices::DeviceImpl<IoT::Devices::BooleanSensor, BooleanSensor>
{
public:
	using Ptr = Poco::SharedPtr<BooleanSensor>;

	BooleanSensor(const std::string& signal);
		/// Creates a BooleanSensor.

	~BooleanSensor();
		/// Destroys the BooleanSensor.

	void update(bool state);
		/// Updates the sensor state.

	void enable(bool enabled);
		/// Enables or disables the counter.

	// BooleanSensor
	bool state() const;

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

protected:
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getSignal(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;

protected:
	bool _enabled;
	bool _state;
	Poco::Any _signal;
};


} } // namespace IoT::CAN


#endif // IoT_CAN_BooleanSensor_INCLUDED
