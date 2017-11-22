//
// SensorTagAccelerometer.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "SensorTagAccelerometer.h"
#include "Poco/Format.h"
#include "Poco/MemoryStream.h"
#include "Poco/BinaryReader.h"
#include "Poco/Delegate.h"


namespace IoT {
namespace SensorTag {


//
// SensorTagAccelerometer
//


const std::string SensorTagAccelerometer::NAME("SensorTag Accelerometer");
const std::string SensorTagAccelerometer::TYPE("io.macchina.accelerometer");
const std::string SensorTagAccelerometer::SYMBOLIC_NAME("io.macchina.sensortag.accelerometer");


SensorTagAccelerometer::SensorTagAccelerometer(BtLE::Peripheral::Ptr pPeripheral, const Params& params):
	_params(params),
	_pPeripheral(pPeripheral),
	_ready(false),
	_enabled(false),
	_deviceIdentifier(pPeripheral->address()),
	_logger(Poco::Logger::get("IoT.SensorTagAccelerometer"))
{
	addProperty("displayValue", &SensorTagAccelerometer::getDisplayValue);
	addProperty("connected", &SensorTagAccelerometer::getConnected);
	addProperty("deviceIdentifier", &SensorTagAccelerometer::getDeviceIdentifier);
	addProperty("symbolicName", &SensorTagAccelerometer::getSymbolicName);
	addProperty("name", &SensorTagAccelerometer::getName);
	addProperty("type", &SensorTagAccelerometer::getType);
	addProperty("enabled", &SensorTagAccelerometer::getEnabled, &SensorTagAccelerometer::setEnabled);
	addProperty("wakeOnMotion", &SensorTagAccelerometer::getWakeOnMotion, &SensorTagAccelerometer::setWakeOnMotion);
	addProperty("valueChangedPeriod", &SensorTagAccelerometer::getValueChangedPeriod, &SensorTagAccelerometer::setValueChangedPeriod);
	addProperty("range", &SensorTagAccelerometer::getRange, &SensorTagAccelerometer::setRange);

	_pPeripheral->services();
	_controlChar = _pPeripheral->characteristic(_params.serviceUUID, _params.controlUUID);
	_dataChar = _pPeripheral->characteristic(_params.serviceUUID, _params.dataUUID);
	_periodChar = _pPeripheral->characteristic(_params.serviceUUID, _params.periodUUID);
	_notifHandle = _pPeripheral->handleForDescriptor(_params.serviceUUID, _params.notifUUID);

	_pPeripheral->connected += Poco::delegate(this, &SensorTagAccelerometer::onConnected);
	_pPeripheral->disconnected += Poco::delegate(this, &SensorTagAccelerometer::onDisconnected);
	_pPeripheral->notificationReceived += Poco::delegate(this, &SensorTagAccelerometer::onNotificationReceived);
}


SensorTagAccelerometer::~SensorTagAccelerometer()
{
	_pPeripheral->connected -= Poco::delegate(this, &SensorTagAccelerometer::onConnected);
	_pPeripheral->disconnected -= Poco::delegate(this, &SensorTagAccelerometer::onDisconnected);
	_pPeripheral->notificationReceived -= Poco::delegate(this, &SensorTagAccelerometer::onNotificationReceived);
	_pPeripheral = 0;
}


bool SensorTagAccelerometer::isConnected() const
{
	return _pPeripheral->isConnected();
}


IoT::Devices::Acceleration SensorTagAccelerometer::acceleration() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _acceleration;
}


Poco::Any SensorTagAccelerometer::getConnected(const std::string&) const
{
	return isConnected();
}


Poco::Any SensorTagAccelerometer::getDisplayValue(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_ready)
		return Poco::format("x=%.2f y=%.2f z=%.2f", _acceleration.x, _acceleration.y, _acceleration.z);
	else
		return std::string("n/a");
}


Poco::Any SensorTagAccelerometer::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
}


Poco::Any SensorTagAccelerometer::getName(const std::string&) const
{
	return NAME;
}


Poco::Any SensorTagAccelerometer::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any SensorTagAccelerometer::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


void SensorTagAccelerometer::onConnected()
{
	if (_enabled)
	{
		enable(true);
	}
}


void SensorTagAccelerometer::onDisconnected()
{
}


void SensorTagAccelerometer::onNotificationReceived(const BtLE::Notification& nf)
{
	if (nf.handle == _dataChar.valueHandle)
	{
		update(nf.data);
	}
}


//
// SensorTag1Accelerometer
//


SensorTag1Accelerometer::SensorTag1Accelerometer(BtLE::Peripheral::Ptr pPeripheral, const Params& params):
	SensorTagAccelerometer(pPeripheral, params)
{
	enable(true);
}


SensorTag1Accelerometer::~SensorTag1Accelerometer()
{
}


void SensorTag1Accelerometer::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_pPeripheral->writeUInt16(_notifHandle, enabled, true);
	_pPeripheral->writeUInt8(_controlChar.valueHandle, enabled, true);
}


Poco::Any SensorTag1Accelerometer::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return (_pPeripheral->readUInt8(_controlChar.valueHandle) != 0) ? true : false;
}


void SensorTag1Accelerometer::setEnabled(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	enable(Poco::AnyCast<bool>(value));
}


Poco::Any SensorTag1Accelerometer::getWakeOnMotion(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return false;
}


void SensorTag1Accelerometer::setWakeOnMotion(const std::string& name, const Poco::Any&)
{
	throw IoT::Devices::NotWritableException(name);
}


Poco::Any SensorTag1Accelerometer::getValueChangedPeriod(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt8 rawPeriod = _pPeripheral->readUInt8(_periodChar.valueHandle);
	return static_cast<int>(static_cast<unsigned>(rawPeriod)*10);
}


void SensorTag1Accelerometer::setValueChangedPeriod(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	int period = Poco::AnyCast<int>(value);
	if (period >= 100 && period <= 2550)
	{
		Poco::UInt8 rawPeriod = static_cast<Poco::UInt8>(period/10);
		_pPeripheral->writeUInt8(_periodChar.valueHandle, rawPeriod, true);
	}
	else throw Poco::InvalidArgumentException("period out of range (100 - 2550)");
}


Poco::Any SensorTag1Accelerometer::getRange(const std::string&) const
{
	return 2;
}


void SensorTag1Accelerometer::setRange(const std::string& name, const Poco::Any&)
{
	throw IoT::Devices::NotWritableException(name);
}


void SensorTag1Accelerometer::update(const std::string& data)
{
	if (data.size() == 3)
	{
		Poco::MemoryInputStream istr(data.data(), data.size());
		Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
		Poco::Int8 accX;
		Poco::Int8 accY;
		Poco::Int8 accZ;
		reader >> accX >> accY >> accZ;

		{
			Poco::Mutex::ScopedLock lock(_mutex);

			_acceleration.x = static_cast<double>(accX)/16.0;
			_acceleration.y = static_cast<double>(accY)/16.0;
			_acceleration.z = static_cast<double>(accZ)/16.0;
			_ready = true;
		}
		accelerationChanged(_acceleration);
	}
}


//
// SensorTag2Accelerometer
//


SensorTag2Accelerometer::SensorTag2Accelerometer(BtLE::Peripheral::Ptr pPeripheral, const Params& params):
	SensorTagAccelerometer(pPeripheral, params),
	_range(8)
{
	enable(true);
}


SensorTag2Accelerometer::~SensorTag2Accelerometer()
{
}


void SensorTag2Accelerometer::configure(Poco::UInt16 bits, Poco::UInt16 mask)
{
	Poco::UInt16 config = _pPeripheral->readUInt16(_controlChar.valueHandle);
	config &= ~mask;
	config |= bits;
	_pPeripheral->writeUInt16(_controlChar.valueHandle, config, true);

	Poco::UInt16 rawRange = (config >> 8) & 0x03;
	switch (rawRange)
	{
	case 0:
		_range = 2;
		break;
	case 1:
		_range = 4;
		break;
	case 2:
		_range = 8;
		break;
	case 3:
		_range = 16;
		break;
	}

	_logger.debug(Poco::format("Accelerometer range: %dG", _range));
}


void SensorTag2Accelerometer::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_pPeripheral->writeUInt16(_notifHandle, enabled, true);
	configure(enabled ? 0x0038 : 0x0000, 0x0038);
}


Poco::Any SensorTag2Accelerometer::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return (_pPeripheral->readUInt16(_controlChar.valueHandle) & 0x0038) ? true : false;
}


void SensorTag2Accelerometer::setEnabled(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	enable(Poco::AnyCast<bool>(value));
}


Poco::Any SensorTag2Accelerometer::getWakeOnMotion(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return (_pPeripheral->readUInt16(_controlChar.valueHandle) & 0x0080) ? true : false;
}


void SensorTag2Accelerometer::setWakeOnMotion(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	bool wakeOnMove = Poco::AnyCast<bool>(value);
	configure(wakeOnMove ? 0x0080 : 0x0000, 0x0080);
}


Poco::Any SensorTag2Accelerometer::getValueChangedPeriod(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt8 rawPeriod = _pPeripheral->readUInt8(_periodChar.valueHandle);
	return static_cast<int>(static_cast<unsigned>(rawPeriod)*10);
}


void SensorTag2Accelerometer::setValueChangedPeriod(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	int period = Poco::AnyCast<int>(value);
	if (period >= 100 && period <= 2550)
	{
		Poco::UInt8 rawPeriod = static_cast<Poco::UInt8>(period/10);
		_pPeripheral->writeUInt8(_periodChar.valueHandle, rawPeriod, true);
	}
	else throw Poco::InvalidArgumentException("period out of range (100 - 2550)");
}


Poco::Any SensorTag2Accelerometer::getRange(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _range;
}


void SensorTag2Accelerometer::setRange(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	int range = Poco::AnyCast<int>(value);
	Poco::UInt16 rawRange = 0;
	switch (range)
	{
	case 2:
		rawRange = 0;
		break;
	case 4:
		rawRange = 1;
		break;
	case 8:
		rawRange = 2;
		break;
	case 16:
		rawRange = 3;
		break;
	default:
		throw Poco::InvalidArgumentException("invalid accelerometer range (2, 4, 8, 16)");
	}
	rawRange <<= 8;
	configure(rawRange, 0x0300);
}


void SensorTag2Accelerometer::update(const std::string& data)
{
	if (data.size() == 18)
	{
		Poco::MemoryInputStream istr(data.data(), data.size());
		Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
		Poco::Int16 gyrX;
		Poco::Int16 gyrY;
		Poco::Int16 gyrZ;
		Poco::Int16 accX;
		Poco::Int16 accY;
		Poco::Int16 accZ;
		reader >> gyrX >> gyrY >> gyrZ >> accX >> accY >> accZ;

		{
			Poco::Mutex::ScopedLock lock(_mutex);

			_acceleration.x = static_cast<double>(accX)/(32768.0/_range);
			_acceleration.y = static_cast<double>(accY)/(32768.0/_range);
			_acceleration.z = static_cast<double>(accZ)/(32768.0/_range);
			_ready = true;
		}
		accelerationChanged(_acceleration);
	}
}


} } // namespace IoT::SensorTag
