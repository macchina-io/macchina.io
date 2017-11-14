//
// SensorTag.cpp
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
#include "Poco/Delegate.h"
#include "Poco/Logger.h"
#include <cmath>


namespace IoT {
namespace BtLE {
namespace SensorTag {


class PollTask: public Poco::Util::TimerTask
{
public:
	PollTask(SensorTagSensor& sensor):
		_sensor(sensor),
		_logger(Poco::Logger::get("IoT.SensorTag"))
	{
	}
	
	void run()
	{
		try
		{
			if (_sensor.isConnected())
			{
				_sensor.poll();
			}
		}
		catch (Poco::Exception& exc)
		{
			_logger.log(exc);
		}
	}
	
private:
	SensorTagSensor& _sensor;
	Poco::Logger& _logger;
};


const std::string SensorTagSensor::NAME("SensorTag Sensor");
const std::string SensorTagSensor::TYPE("io.macchina.sensor");
const std::string SensorTagSensor::SYMBOLIC_NAME("io.macchina.btle.sensortag");


SensorTagSensor::SensorTagSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	_params(params),
	_pPeripheral(pPeripheral),
	_pTimer(pTimer),
	_ready(false),
	_enabled(false),
	_value(0),
	_valueChangedDelta(0.0),
	_pEventPolicy(new IoT::Devices::NoModerationPolicy<double>(valueChanged)),
	_deviceIdentifier(pPeripheral->address()),
	_physicalQuantity(params.physicalQuantity),
	_physicalUnit(params.physicalUnit)
{
	addProperty("displayValue", &SensorTagSensor::getDisplayValue);
	addProperty("enabled", &SensorTagSensor::getEnabled, &SensorTagSensor::setEnabled);
	addProperty("connected", &SensorTagSensor::getConnected);
	addProperty("valueChangedDelta", &SensorTagSensor::getValueChangedDelta, &SensorTagSensor::setValueChangedDelta);
	addProperty("deviceIdentifier", &SensorTagSensor::getDeviceIdentifier);
	addProperty("symbolicName", &SensorTagSensor::getSymbolicName);
	addProperty("name", &SensorTagSensor::getName);
	addProperty("type", &SensorTagSensor::getType);
	addProperty("physicalQuantity", &SensorTagSensor::getPhysicalQuantity);
	addProperty("physicalUnit", &SensorTagSensor::getPhysicalUnit);
	
	_pEventPolicy = new IoT::Devices::NoModerationPolicy<double>(valueChanged);

	_pPeripheral->services();
	_controlChar = _pPeripheral->characteristic(_params.serviceUUID, _params.controlUUID);
	_dataChar = _pPeripheral->characteristic(_params.serviceUUID, _params.dataUUID);

	_pPeripheral->connected += Poco::delegate(this, &SensorTagSensor::onConnected);
	_pPeripheral->disconnected += Poco::delegate(this, &SensorTagSensor::onDisconnected);
}

	
SensorTagSensor::~SensorTagSensor()
{
	_pPeripheral->connected -= Poco::delegate(this, &SensorTagSensor::onConnected);
	_pPeripheral->disconnected -= Poco::delegate(this, &SensorTagSensor::onDisconnected);

	if (_pPollTask) _pPollTask->cancel();
	_pPeripheral = 0;
}


bool SensorTagSensor::isConnected() const
{
	return _pPeripheral->isConnected();
}


double SensorTagSensor::value() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!_pPollTask && _pPeripheral->isConnected())
	{
		const_cast<SensorTagSensor*>(this)->poll();
	}

	return _value;
}


bool SensorTagSensor::ready() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _ready && _pPeripheral->isConnected();	
}


void SensorTagSensor::startPolling()
{
	if (_params.pollInterval > 0 && !_pPollTask)
	{
		_pPollTask = new PollTask(*this);
		_pTimer->scheduleAtFixedRate(_pPollTask, 250, _params.pollInterval);
	}
}


void SensorTagSensor::stopPolling()
{
	if (_pPollTask)
	{
		_pPollTask->cancel();
		_pPollTask = 0;
	}
}


void SensorTagSensor::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	_pPeripheral->writeUInt8(_controlChar.valueHandle, enabled, true);

	if (enabled)
	{
		startPolling();
	}
	else
	{
		stopPolling();
	}
	_enabled = enabled;
}


Poco::Any SensorTagSensor::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _pPeripheral->readUInt8(_controlChar.valueHandle) == 1 ? true : false;
}


void SensorTagSensor::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any SensorTagSensor::getConnected(const std::string&) const
{
	return isConnected();
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
	if (_ready)
		return Poco::NumberFormatter::format(value(), 0, 1);
	else
		return std::string("n/a");
}


Poco::Any SensorTagSensor::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
}


Poco::Any SensorTagSensor::getName(const std::string&) const
{
	return NAME;
}


Poco::Any SensorTagSensor::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any SensorTagSensor::getType(const std::string&) const
{
	return TYPE;
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


void SensorTagSensor::init()
{
	enable(true);
}


void SensorTagSensor::onConnected()
{
	if (_enabled)
	{
		enable(true);
	}
}


void SensorTagSensor::onDisconnected()
{
	stopPolling();
}


//
// SensorTag1IRAmbientTemperatureSensor
//
 

SensorTag1IRAmbientTemperatureSensor::SensorTag1IRAmbientTemperatureSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	SensorTagSensor(pPeripheral, params, pTimer)
{
	init();
}


SensorTag1IRAmbientTemperatureSensor::~SensorTag1IRAmbientTemperatureSensor()
{
}


void SensorTag1IRAmbientTemperatureSensor::poll()
{
	std::string data = _pPeripheral->readString(_dataChar.valueHandle);
	if (data.size() == 4)
	{
		Poco::MemoryInputStream istr(data.data(), data.size());
		Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
		Poco::Int16 rawObjT;
		Poco::Int16 rawAmbT;
		reader >> rawObjT >> rawAmbT;
		double tAmb = static_cast<double>(rawAmbT)/128.0;
		update(tAmb);
	}
}


//
// SensorTag1IRObjectTemperatureSensor
//
 

SensorTag1IRObjectTemperatureSensor::SensorTag1IRObjectTemperatureSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	SensorTagSensor(pPeripheral, params, pTimer)
{
	init();
}


SensorTag1IRObjectTemperatureSensor::~SensorTag1IRObjectTemperatureSensor()
{
}


void SensorTag1IRObjectTemperatureSensor::poll()
{
	std::string data = _pPeripheral->readString(_dataChar.valueHandle);
	if (data.size() == 4)
	{
		Poco::MemoryInputStream istr(data.data(), data.size());
		Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
		Poco::Int16 rawObjT;
		Poco::Int16 rawAmbT;
		reader >> rawObjT >> rawAmbT;

		double tAmb = static_cast<double>(rawAmbT)/128.0;
		double vObj2 = static_cast<double>(rawObjT)*0.00000015625;
		double tDie2 = tAmb + 273.15;
		const double s0 = 5.593E-14; // Calibration factor
		const double a1 = 1.75E-3;
		const double a2 = -1.678E-5;
		const double b0 = -2.94E-5;
		const double b1 = -5.7E-7;
		const double b2 = 4.63E-9;
		const double c2 = 13.4;
		const double tRef = 298.15;
		double s = s0*(1 + a1*(tDie2 - tRef) + a2*std::pow(tDie2 - tRef, 2));
		double vos = b0 + b1*(tDie2 - tRef) + b2*std::pow(tDie2 - tRef, 2);
		double fObj = (vObj2 - vos) + c2*std::pow(vObj2 - vos, 2);
		double tObj = std::pow(std::pow(tDie2, 4) + (fObj/s), .25) - 273.15;
		update(tObj);
	}
}


//
// SensorTag2IRAmbientTemperatureSensor
//
 

SensorTag2IRAmbientTemperatureSensor::SensorTag2IRAmbientTemperatureSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	SensorTagSensor(pPeripheral, params, pTimer)
{
	init();
}


SensorTag2IRAmbientTemperatureSensor::~SensorTag2IRAmbientTemperatureSensor()
{
}


void SensorTag2IRAmbientTemperatureSensor::poll()
{
	std::string data = _pPeripheral->readString(_dataChar.valueHandle);
	if (data.size() == 4)
	{
		Poco::MemoryInputStream istr(data.data(), data.size());
		Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
		Poco::Int16 rawObjT;
		Poco::Int16 rawAmbT;
		reader >> rawObjT >> rawAmbT;
		rawAmbT >>= 2;
		double tAmb = static_cast<double>(rawAmbT)*0.03125;
		update(tAmb);
	}
}


//
// SensorTag2IRObjectTemperatureSensor
//
 

SensorTag2IRObjectTemperatureSensor::SensorTag2IRObjectTemperatureSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	SensorTagSensor(pPeripheral, params, pTimer)
{
	init();
}


SensorTag2IRObjectTemperatureSensor::~SensorTag2IRObjectTemperatureSensor()
{
}


void SensorTag2IRObjectTemperatureSensor::poll()
{
	std::string data = _pPeripheral->readString(_dataChar.valueHandle);
	if (data.size() == 4)
	{
		Poco::MemoryInputStream istr(data.data(), data.size());
		Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
		Poco::Int16 rawObjT;
		Poco::Int16 rawAmbT;
		reader >> rawObjT >> rawAmbT;
		rawObjT >>= 2;
		double tObj = static_cast<double>(rawObjT)*0.03125;
		update(tObj);
	}
}


//
// SensorTagHumiditySensor
//


SensorTagHumiditySensor::SensorTagHumiditySensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	SensorTagSensor(pPeripheral, params, pTimer)
{
	init();
}


SensorTagHumiditySensor::~SensorTagHumiditySensor()
{
}


void SensorTagHumiditySensor::poll()
{
	std::string data = _pPeripheral->readString(_dataChar.valueHandle);
	Poco::MemoryInputStream istr(data.data(), data.size());
	Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	Poco::UInt16 rawT;
	Poco::UInt16 rawH;
	reader >> rawT >> rawH;
	double rh = -6.0 + 125.0 * ((rawH & 0xFFFC)/65536.0);
	update(rh);
}


//
// SensorTag2LightSensor
//


SensorTag2LightSensor::SensorTag2LightSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	SensorTagSensor(pPeripheral, params, pTimer)
{
	init();
}


SensorTag2LightSensor::~SensorTag2LightSensor()
{
}


void SensorTag2LightSensor::poll()
{
	Poco::UInt16 raw = _pPeripheral->readUInt16(_dataChar.valueHandle);
	Poco::UInt16 m = raw & 0x0FFF;
	Poco::UInt16 e = (raw & 0xF000) >> 12;
 
	update(m*(0.01*std::pow(2.0, e)));
}


//
// SensorTag1AirPressureSensor
//


SensorTag1AirPressureSensor::SensorTag1AirPressureSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	SensorTagSensor(pPeripheral, params, pTimer)
{
	init();
	_calCoeff[0] = 0;
	_calCoeff[1] = 0;
	_calCoeff[2] = 0;
	_calCoeff[3] = 0;
	_calCoeff[4] = 0;
	_calCoeff[5] = 0;
	_calCoeff[6] = 0;
	_calCoeff[7] = 0;
}


SensorTag1AirPressureSensor::~SensorTag1AirPressureSensor()
{
}


void SensorTag1AirPressureSensor::poll()
{
	std::string bytes = _pPeripheral->readString(_dataChar.valueHandle);
	if (bytes.size() == 6)
	{
		Poco::UInt32 raw = static_cast<unsigned char>(bytes[3]) 
						 + (static_cast<unsigned char>(bytes[4]) << 8) 
						 + (static_cast<unsigned char>(bytes[5]) << 16);
 
		update(raw/100.0);
	}
}


//
// SensorTag2AirPressureSensor
//


SensorTag2AirPressureSensor::SensorTag2AirPressureSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	SensorTagSensor(pPeripheral, params, pTimer)
{
	init();
}


SensorTag2AirPressureSensor::~SensorTag2AirPressureSensor()
{
}


void SensorTag2AirPressureSensor::poll()
{
	std::string bytes = _pPeripheral->readString(_dataChar.valueHandle);
	if (bytes.size() == 6)
	{
		Poco::UInt32 raw = static_cast<unsigned char>(bytes[3]) 
						 + (static_cast<unsigned char>(bytes[4]) << 8) 
						 + (static_cast<unsigned char>(bytes[5]) << 16);
 
		update(raw/100.0);
	}
}


} } } // namespace IoT::BtLE::SensorTag
