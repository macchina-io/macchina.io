//
// HighRateSensor.h
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_XDK_HighRateSensor_INCLUDED
#define IoT_XDK_HighRateSensor_INCLUDED


#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "IoT/BtLE/Peripheral.h"
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/SharedPtr.h"


namespace IoT {
namespace XDK {


class HighRateSensor: public IoT::Devices::DeviceImpl<IoT::Devices::Sensor, HighRateSensor>
{
public:
	using Ptr = Poco::SharedPtr<HighRateSensor>;

	struct Params
	{
		std::string physicalQuantity;
		std::string physicalUnit;
	};

	HighRateSensor(BtLE::Peripheral::Ptr pPeripheral, const Params& params);
		/// Creates a HighRateSensor.

	~HighRateSensor();
		/// Destroys the HighRateSensor.

	bool isConnected() const;
		/// Returns true if the sensor's peripheral is connected.

	void update(double value);
		/// Updates the sensor value (called from the high-prio polling task).

	// Sensor
	double value() const;
	bool ready() const;

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

protected:
	void init();
	void enable(bool enabled);
	Poco::Any getValueChangedDelta(const std::string&) const;
	void setValueChangedDelta(const std::string&, const Poco::Any& value);
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
	void onConnected();
	void onDisconnected();

protected:
	Params _params;
	mutable BtLE::Peripheral::Ptr _pPeripheral;
	bool _ready;
	bool _enabled;
	double _value;
	double _valueChangedDelta;
	Poco::SharedPtr<IoT::Devices::EventModerationPolicy<double>> _pEventPolicy;
	Poco::Any _deviceIdentifier;
	Poco::Any _physicalQuantity;
	Poco::Any _physicalUnit;
};


} } // namespace IoT::XDK


#endif // IoT_XDK_HighRateSensor_INCLUDED

