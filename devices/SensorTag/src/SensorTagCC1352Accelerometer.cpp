//
// SensorTagCC1352Accelerometer.cpp
//
// Copyright (c) 2024, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "SensorTagCC1352Accelerometer.h"
#include "Poco/Format.h"
#include "Poco/MemoryStream.h"
#include "Poco/BinaryReader.h"
#include "Poco/Delegate.h"


namespace IoT {
namespace SensorTag {


//
// SensorTagCC1352Accelerometer
//


const std::string SensorTagCC1352Accelerometer::NAME("SensorTag Accelerometer");
const std::string SensorTagCC1352Accelerometer::TYPE("io.macchina.accelerometer");
const std::string SensorTagCC1352Accelerometer::SYMBOLIC_NAME("io.macchina.sensortag.accelerometer");
const Poco::UUID SensorTagCC1352Accelerometer::SERVICE_UUID("f000ffa0-0451-4000-b000-000000000000");
const Poco::UUID SensorTagCC1352Accelerometer::CHAR_ACC_ENABLE_UUID("f000ffa1-0451-4000-b000-000000000000");
const Poco::UUID SensorTagCC1352Accelerometer::CHAR_ACC_X_UUID("f000ffa3-0451-4000-b000-000000000000");
const Poco::UUID SensorTagCC1352Accelerometer::CHAR_ACC_Y_UUID("f000ffa4-0451-4000-b000-000000000000");
const Poco::UUID SensorTagCC1352Accelerometer::CHAR_ACC_Z_UUID("f000ffa5-0451-4000-b000-000000000000");


SensorTagCC1352Accelerometer::SensorTagCC1352Accelerometer(BtLE::Peripheral::Ptr pPeripheral):
	_pPeripheral(pPeripheral),
	_ready(false),
	_deviceIdentifier(pPeripheral->address()),
	_logger(Poco::Logger::get("IoT.SensorTagCC1352Accelerometer"))
{
	addProperty("displayValue", &SensorTagCC1352Accelerometer::getDisplayValue);
	addProperty("connected", &SensorTagCC1352Accelerometer::getConnected);
	addProperty("deviceIdentifier", &SensorTagCC1352Accelerometer::getDeviceIdentifier);
	addProperty("symbolicName", &SensorTagCC1352Accelerometer::getSymbolicName);
	addProperty("name", &SensorTagCC1352Accelerometer::getName);
	addProperty("type", &SensorTagCC1352Accelerometer::getType);
	addProperty("enabled", &SensorTagCC1352Accelerometer::getEnabled, &SensorTagCC1352Accelerometer::setEnabled);

	_controlChar = _pPeripheral->characteristic(SERVICE_UUID, CHAR_ACC_ENABLE_UUID);
	_notifHandleX = _pPeripheral->characteristic(SERVICE_UUID, CHAR_ACC_X_UUID).valueHandle;
	_notifHandleY = _pPeripheral->characteristic(SERVICE_UUID, CHAR_ACC_Y_UUID).valueHandle;
	_notifHandleZ = _pPeripheral->characteristic(SERVICE_UUID, CHAR_ACC_Z_UUID).valueHandle;

	_pPeripheral->connected += Poco::delegate(this, &SensorTagCC1352Accelerometer::onConnected);
	_pPeripheral->disconnected += Poco::delegate(this, &SensorTagCC1352Accelerometer::onDisconnected);
	_pPeripheral->notificationReceived += Poco::delegate(this, &SensorTagCC1352Accelerometer::onNotificationReceived);

	enable(true);
}


SensorTagCC1352Accelerometer::~SensorTagCC1352Accelerometer()
{
	_pPeripheral->connected -= Poco::delegate(this, &SensorTagCC1352Accelerometer::onConnected);
	_pPeripheral->disconnected -= Poco::delegate(this, &SensorTagCC1352Accelerometer::onDisconnected);
	_pPeripheral->notificationReceived -= Poco::delegate(this, &SensorTagCC1352Accelerometer::onNotificationReceived);
	_pPeripheral.reset();
}


bool SensorTagCC1352Accelerometer::isConnected() const
{
	return _pPeripheral->isConnected();
}


IoT::Devices::Acceleration SensorTagCC1352Accelerometer::acceleration() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _acceleration;
}


Poco::Any SensorTagCC1352Accelerometer::getConnected(const std::string&) const
{
	return isConnected();
}


Poco::Any SensorTagCC1352Accelerometer::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_ready)
		return Poco::format("x=%.2f y=%.2f z=%.2f", _acceleration.x, _acceleration.y, _acceleration.z);
	else
		return std::string("n/a");
}


Poco::Any SensorTagCC1352Accelerometer::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
}


Poco::Any SensorTagCC1352Accelerometer::getName(const std::string&) const
{
	return NAME;
}


Poco::Any SensorTagCC1352Accelerometer::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any SensorTagCC1352Accelerometer::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


void SensorTagCC1352Accelerometer::enable(bool enabled)
{
	const Poco::UUID enableUUID = _pPeripheral->expandUUID(0x2902);
	Poco::UInt16 enableXHnd = _pPeripheral->handleForDescriptor(SERVICE_UUID, CHAR_ACC_X_UUID, enableUUID);
	Poco::UInt16 enableYHnd = _pPeripheral->handleForDescriptor(SERVICE_UUID, CHAR_ACC_Y_UUID, enableUUID);
	Poco::UInt16 enableZHnd = _pPeripheral->handleForDescriptor(SERVICE_UUID, CHAR_ACC_Z_UUID, enableUUID);

	if (enabled)
	{
		_pPeripheral->writeUInt16(enableXHnd, 1, false);
		_pPeripheral->writeUInt16(enableYHnd, 1, false);
		_pPeripheral->writeUInt16(enableZHnd, 1, false);
		_pPeripheral->writeUInt8(_controlChar.valueHandle, 1, true);
	}
	else
	{
		_pPeripheral->writeUInt8(_controlChar.valueHandle, 0, true);
		_pPeripheral->writeUInt16(enableXHnd, 0, false);
		_pPeripheral->writeUInt16(enableYHnd, 0, false);
		_pPeripheral->writeUInt16(enableZHnd, 0, false);
	}
}


Poco::Any SensorTagCC1352Accelerometer::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return (_pPeripheral->readUInt8(_controlChar.valueHandle) != 0) ? true : false;
}


void SensorTagCC1352Accelerometer::setEnabled(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	enable(Poco::AnyCast<bool>(value));
}


void SensorTagCC1352Accelerometer::onConnected()
{
	enable(true);
}


void SensorTagCC1352Accelerometer::onDisconnected()
{
}


void SensorTagCC1352Accelerometer::onNotificationReceived(const BtLE::Notification& nf)
{	
	if (nf.data.size() == 2)
	{
		Poco::MemoryInputStream istr(nf.data.data(), nf.data.size());
		Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
		Poco::Int16 acc;
		reader >> acc;

		{
			Poco::Mutex::ScopedLock lock(_mutex);

			if (nf.handle == _notifHandleX)
			{
				_acceleration.x = acc/16384.0;
			}
			else if (nf.handle == _notifHandleY)
			{
				_acceleration.y = acc/16384.0;
			}
			else if (nf.handle == _notifHandleZ)
			{
				_acceleration.z = acc/16384.0;
			}
			_ready = true;
			_logger.debug("Acceleration update: X=%.1f Y=%.1f Z=%.1f", _acceleration.x, _acceleration.y, _acceleration.z);
		}

		accelerationChanged(_acceleration);
	}
}


} } // namespace IoT::SensorTag
