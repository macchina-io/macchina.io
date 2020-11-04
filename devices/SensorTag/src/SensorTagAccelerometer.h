//
// SensorTagAccelerometer.h
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_SensorTag_SensorTagAccelerometer_INCLUDED
#define IoT_SensorTag_SensorTagAccelerometer_INCLUDED


#include "IoT/Devices/Accelerometer.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/BtLE/Peripheral.h"
#include "Poco/SharedPtr.h"
#include "Poco/Logger.h"


namespace IoT {
namespace SensorTag {


class SensorTagAccelerometer: public IoT::Devices::DeviceImpl<IoT::Devices::Accelerometer, SensorTagAccelerometer>
{
public:
	using Ptr = Poco::SharedPtr<SensorTagAccelerometer>;

	struct Params
	{
		std::string serviceUUID;
		std::string controlUUID;
		std::string periodUUID;
		std::string notifUUID;
		std::string dataUUID;
	};

	SensorTagAccelerometer(BtLE::Peripheral::Ptr pPeripheral, const Params& params);
		/// Creates a SensorTagAccelerometer.

	~SensorTagAccelerometer();
		/// Destroys the SensorTagAccelerometer.

	bool isConnected() const;
		/// Returns true if the sensor's peripheral is connected.

	// Accelerometer
	IoT::Devices::Acceleration acceleration() const;

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

protected:
	virtual void enable(bool enabled) = 0;
	virtual void update(const std::vector<char>& data) = 0;
	Poco::Any getConnected(const std::string&) const;
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	virtual Poco::Any getEnabled(const std::string&) const = 0;
	virtual void setEnabled(const std::string&, const Poco::Any& value) = 0;
	virtual Poco::Any getWakeOnMotion(const std::string&) const = 0;
	virtual void setWakeOnMotion(const std::string&, const Poco::Any& value) = 0;
	virtual Poco::Any getRange(const std::string&) const = 0;
	virtual void setRange(const std::string&, const Poco::Any& value) = 0;
	virtual Poco::Any getValueChangedPeriod(const std::string&) const = 0;
	virtual void setValueChangedPeriod(const std::string&, const Poco::Any& value) = 0;
	void onConnected();
	void onDisconnected();
	void onNotificationReceived(const BtLE::Notification& nf);

protected:
	Params _params;
	mutable BtLE::Peripheral::Ptr _pPeripheral;
	BtLE::Characteristic _controlChar;
	BtLE::Characteristic _dataChar;
	BtLE::Characteristic _periodChar;
	Poco::UInt16 _notifHandle;
	bool _ready;
	bool _enabled;
	IoT::Devices::Acceleration _acceleration;
	Poco::Any _deviceIdentifier;
	Poco::Logger& _logger;
};


class SensorTag1Accelerometer: public SensorTagAccelerometer
{
public:
	SensorTag1Accelerometer(BtLE::Peripheral::Ptr pPeripheral, const Params& params);
		/// Creates a SensorTag2Accelerometer.

	~SensorTag1Accelerometer();
		/// Destroys the SensorTag2Accelerometer.

protected:
	void update(const std::vector<char>& data);
	void enable(bool enable);
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getWakeOnMotion(const std::string&) const;
	void setWakeOnMotion(const std::string&, const Poco::Any& value);
	Poco::Any getRange(const std::string&) const;
	void setRange(const std::string&, const Poco::Any& value);
	Poco::Any getValueChangedPeriod(const std::string&) const;
	void setValueChangedPeriod(const std::string&, const Poco::Any& value);
};


class SensorTag2Accelerometer: public SensorTagAccelerometer
{
public:
	SensorTag2Accelerometer(BtLE::Peripheral::Ptr pPeripheral, const Params& params);
		/// Creates a SensorTag2Accelerometer.

	~SensorTag2Accelerometer();
		/// Destroys the SensorTag2Accelerometer.

protected:
	void configure(Poco::UInt16 bits, Poco::UInt16 mask);
	void update(const std::vector<char>& data);
	void enable(bool enable);
	Poco::Any getEnabled(const std::string&) const;
	void setEnabled(const std::string&, const Poco::Any& value);
	Poco::Any getWakeOnMotion(const std::string&) const;
	void setWakeOnMotion(const std::string&, const Poco::Any& value);
	Poco::Any getRange(const std::string&) const;
	void setRange(const std::string&, const Poco::Any& value);
	Poco::Any getValueChangedPeriod(const std::string&) const;
	void setValueChangedPeriod(const std::string&, const Poco::Any& value);

private:
	int _range;
};


} } // namespace IoT::SensorTag


#endif // IoT_SensorTag_SensorTagAccelerometer_INCLUDED

