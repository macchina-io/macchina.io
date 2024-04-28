//
// SensorTagCC1352Accelerometer.h
//
// Copyright (c) 2024, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_SensorTag_SensorTagCC1352Accelerometer_INCLUDED
#define IoT_SensorTag_SensorTagCC1352Accelerometer_INCLUDED


#include "IoT/Devices/Accelerometer.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/BtLE/Peripheral.h"
#include "Poco/SharedPtr.h"
#include "Poco/Logger.h"


namespace IoT {
namespace SensorTag {


class SensorTagCC1352Accelerometer: public IoT::Devices::DeviceImpl<IoT::Devices::Accelerometer, SensorTagCC1352Accelerometer>
{
public:
	using Ptr = Poco::SharedPtr<SensorTagCC1352Accelerometer>;

	SensorTagCC1352Accelerometer(BtLE::Peripheral::Ptr pPeripheral);
		/// Creates a SensorTagCC1352Accelerometer.

	~SensorTagCC1352Accelerometer();
		/// Destroys the SensorTagCC1352Accelerometer.

	bool isConnected() const;
		/// Returns true if the sensor's peripheral is connected.

	// Accelerometer
	IoT::Devices::Acceleration acceleration() const;

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;
	static const Poco::UUID SERVICE_UUID;
	static const Poco::UUID CHAR_ACC_ENABLE_UUID;
	static const Poco::UUID CHAR_ACC_X_UUID;
	static const Poco::UUID CHAR_ACC_Y_UUID;
	static const Poco::UUID CHAR_ACC_Z_UUID;

protected:
	void enable(bool enabled);
	Poco::Any getConnected(const std::string&) const;
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	virtual Poco::Any getEnabled(const std::string&) const;
	virtual void setEnabled(const std::string&, const Poco::Any& value);
	void onConnected();
	void onDisconnected();
	void onNotificationReceived(const BtLE::Notification& nf);

protected:
	mutable BtLE::Peripheral::Ptr _pPeripheral;
	BtLE::Characteristic _controlChar;
	Poco::UInt16 _notifHandleX;
	Poco::UInt16 _notifHandleY;
	Poco::UInt16 _notifHandleZ;
	bool _ready;
	IoT::Devices::Acceleration _acceleration;
	Poco::Any _deviceIdentifier;
	Poco::Logger& _logger;
};


} } // namespace IoT::SensorTag


#endif // IoT_SensorTag_SensorTagCC1352Accelerometer_INCLUDED

