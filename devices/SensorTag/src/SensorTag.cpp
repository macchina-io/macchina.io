//
// SensorTag.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "SensorTag.h"
#include "Poco/NumberFormatter.h"
#include "Poco/MemoryStream.h"
#include "Poco/BinaryReader.h"
#include <cmath>


namespace IoT {
namespace BtLE {
namespace SensorTag {


class PollTask: public Poco::Util::TimerTask
{
public:
	PollTask(SensorTagSensor& sensor):
		_sensor(sensor)
	{
	}
	
	void run()
	{
		_sensor.poll();
	}
	
private:
	SensorTagSensor& _sensor;
};


const std::string SensorTagSensor::NAME("SensorTag Sensor");
const std::string SensorTagSensor::SYMBOLIC_NAME("io.macchina.btle.sensortag");


SensorTagSensor::SensorTagSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	_params(params),
	_pPeripheral(pPeripheral),
	_pTimer(pTimer),
	_ready(false),
	_value(0),
	_valueChangedDelta(0.0),
	_pEventPolicy(new IoT::Devices::NoModerationPolicy<double>(valueChanged)),
	_deviceIdentifier(pPeripheral->address()),
	_symbolicName(SYMBOLIC_NAME),
	_name(NAME),
	_physicalQuantity(params.physicalQuantity),
	_physicalUnit(params.physicalUnit)
{
	addProperty("displayValue", &SensorTagSensor::getDisplayValue);
	addProperty("valueChangedDelta", &SensorTagSensor::getValueChangedDelta, &SensorTagSensor::setValueChangedDelta);
	addProperty("deviceIdentifier", &SensorTagSensor::getDeviceIdentifier);
	addProperty("symbolicName", &SensorTagSensor::getSymbolicName);
	addProperty("name", &SensorTagSensor::getName);
	addProperty("physicalQuantity", &SensorTagSensor::getPhysicalQuantity);
	addProperty("physicalUnit", &SensorTagSensor::getPhysicalUnit);
	
	_pEventPolicy = new IoT::Devices::NoModerationPolicy<double>(valueChanged);

	_pPeripheral->connect();
	_controlChar = _pPeripheral->characteristic(_params.serviceUUID, _params.controlUUID);
	_dataChar = _pPeripheral->characteristic(_params.serviceUUID, _params.dataUUID);

	if (_params.pollInterval > 0)
	{
		_pPollTask = new PollTask(*this);
		_pTimer->scheduleAtFixedRate(_pPollTask, 0, _params.pollInterval);
	}
}

	
SensorTagSensor::~SensorTagSensor()
{
	if (_pPollTask) _pPollTask->cancel();
	_pPeripheral->disconnect();
	_pPeripheral = 0;
}


double SensorTagSensor::value() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _value;
}


bool SensorTagSensor::ready() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _ready;	
}


Poco::Any SensorTagSensor::getValueChangedDelta(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valueChangedDelta;
}


void SensorTagSensor::setValueChangedDelta(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	double delta = Poco::AnyCast<double>(value);
	if (delta != _valueChangedDelta)
	{
		if (delta == 0)
		{
			_pEventPolicy = new IoT::Devices::NoModerationPolicy<double>(valueChanged);
		}
		else
		{
			_pEventPolicy = new IoT::Devices::MinimumDeltaModerationPolicy<double>(valueChanged, _value, delta);
		}
		_valueChangedDelta = delta;
	}
}


Poco::Any SensorTagSensor::getDisplayValue(const std::string&) const
{
	return Poco::NumberFormatter::format(value(), 0, 1);
}


Poco::Any SensorTagSensor::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
}


Poco::Any SensorTagSensor::getName(const std::string&) const
{
	return _name;
}


Poco::Any SensorTagSensor::getSymbolicName(const std::string&) const
{
	return _symbolicName;
}


Poco::Any SensorTagSensor::getPhysicalQuantity(const std::string&) const
{
	return _physicalQuantity;
}


Poco::Any SensorTagSensor::getPhysicalUnit(const std::string&) const
{
	return _physicalUnit;
}


void SensorTagSensor::update(double value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!_ready || _value != value)
	{
		_ready = true;
		_value = value;
		_pEventPolicy->valueChanged(value);
	}
}


//
// SensorTagTemperatureSensor
//
 

SensorTagTemperatureSensor::SensorTagTemperatureSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	SensorTagSensor(pPeripheral, params, pTimer)
{
}


SensorTagTemperatureSensor::~SensorTagTemperatureSensor()
{
}


void SensorTagTemperatureSensor::poll()
{
	if (!_ready)
	{
		_pPeripheral->writeUInt8(_controlChar.valueHandle, 1, true);
	}
	std::string data = _pPeripheral->read(_dataChar.valueHandle);
	Poco::MemoryInputStream istr(data.data(), data.size());
	Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	Poco::UInt16 rawT;
	Poco::UInt16 rawH;
	reader >> rawT >> rawH;
	double temp = -46.85 + 175.72 * (rawT / 65536.0);
	update(temp);
}


//
// SensorTagHumiditySensor
//


SensorTagHumiditySensor::SensorTagHumiditySensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	SensorTagSensor(pPeripheral, params, pTimer)
{
}


SensorTagHumiditySensor::~SensorTagHumiditySensor()
{
}


void SensorTagHumiditySensor::poll()
{
	if (!_ready)
	{
		_pPeripheral->writeUInt8(_controlChar.valueHandle, 1, true);
	}
	std::string data = _pPeripheral->read(_dataChar.valueHandle);
	Poco::MemoryInputStream istr(data.data(), data.size());
	Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	Poco::UInt16 rawT;
	Poco::UInt16 rawH;
	reader >> rawT >> rawH;
	double rh = -6.0 + 125.0 * ((rawH & 0xFFFC)/65536.0);
	update(rh);
}


//
// SensorTagLightSensor
//


SensorTagLightSensor::SensorTagLightSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	SensorTagSensor(pPeripheral, params, pTimer)
{
}


SensorTagLightSensor::~SensorTagLightSensor()
{
}


void SensorTagLightSensor::poll()
{
	if (!_ready)
	{
		_pPeripheral->writeUInt8(_controlChar.valueHandle, 1, true);
	}
	Poco::UInt16 raw = _pPeripheral->readUInt16(_dataChar.valueHandle);
	Poco::UInt16 m = raw & 0x0FFF;
	Poco::UInt16 e = (raw & 0xF000) >> 12;
 
	update(m*(0.01*std::pow(2.0, e)));
}


} } } // namespace IoT::BtLE::SensorTag
