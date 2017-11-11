//
// XDKSensor.cpp
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "XDKSensor.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Delegate.h"
#include "Poco/Logger.h"


namespace IoT {
namespace BtLE {
namespace XDK {


class PollTask: public Poco::Util::TimerTask
{
public:
	PollTask(XDKSensor& sensor):
		_sensor(sensor),
		_logger(Poco::Logger::get("IoT.XDK"))
	{
	}
	
	void run()
	{
		try
		{
			if (_sensor.isConnected())
			{
				_logger.debug("Polling...");
				_sensor.poll();
			}
			else
			{
				_logger.debug("Sensor is not connected.");
			}
		}
		catch (Poco::Exception& exc)
		{
			_logger.log(exc);
		}
	}
	
private:
	XDKSensor& _sensor;
	Poco::Logger& _logger;
};


const std::string XDKSensor::NAME("XDK Sensor");
const std::string XDKSensor::TYPE("io.macchina.sensor");
const std::string XDKSensor::SYMBOLIC_NAME("io.macchina.btle.xdk");


XDKSensor::XDKSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
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
	addProperty("displayValue", &XDKSensor::getDisplayValue);
	addProperty("enabled", &XDKSensor::getEnabled, &XDKSensor::setEnabled);
	addProperty("connected", &XDKSensor::getConnected);
	addProperty("valueChangedDelta", &XDKSensor::getValueChangedDelta, &XDKSensor::setValueChangedDelta);
	addProperty("deviceIdentifier", &XDKSensor::getDeviceIdentifier);
	addProperty("symbolicName", &XDKSensor::getSymbolicName);
	addProperty("name", &XDKSensor::getName);
	addProperty("type", &XDKSensor::getType);
	addProperty("physicalQuantity", &XDKSensor::getPhysicalQuantity);
	addProperty("physicalUnit", &XDKSensor::getPhysicalUnit);
	
	_pEventPolicy = new IoT::Devices::NoModerationPolicy<double>(valueChanged);

	_pPeripheral->services();
	_dataChar = _pPeripheral->characteristic(_params.serviceUUID, _params.dataUUID);

	_pPeripheral->connected += Poco::delegate(this, &XDKSensor::onConnected);
	_pPeripheral->disconnected += Poco::delegate(this, &XDKSensor::onDisconnected);
}

	
XDKSensor::~XDKSensor()
{
	_pPeripheral->connected -= Poco::delegate(this, &XDKSensor::onConnected);
	_pPeripheral->disconnected -= Poco::delegate(this, &XDKSensor::onDisconnected);

	if (_pPollTask) _pPollTask->cancel();
	_pPeripheral = 0;
}


bool XDKSensor::isConnected() const
{
	return _pPeripheral->isConnected();
}


double XDKSensor::value() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!_pPollTask && _pPeripheral->isConnected())
	{
		const_cast<XDKSensor*>(this)->poll();
	}

	return _value;
}


bool XDKSensor::ready() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _ready && _pPeripheral->isConnected();	
}


void XDKSensor::startPolling()
{
	if (_params.pollInterval > 0 && !_pPollTask)
	{
		_pPollTask = new PollTask(*this);
		_pTimer->scheduleAtFixedRate(_pPollTask, 250, _params.pollInterval);
	}
}


void XDKSensor::stopPolling()
{
	if (_pPollTask)
	{
		_pPollTask->cancel();
		_pPollTask = 0;
	}
}


void XDKSensor::enable(bool enabled)
{
	Poco::Mutex::ScopedLock lock(_mutex);

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


Poco::Any XDKSensor::getEnabled(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _enabled;
}


void XDKSensor::setEnabled(const std::string&, const Poco::Any& value)
{
	enable(Poco::AnyCast<bool>(value));
}


Poco::Any XDKSensor::getConnected(const std::string&) const
{
	return isConnected();
}


Poco::Any XDKSensor::getValueChangedDelta(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valueChangedDelta;
}


void XDKSensor::setValueChangedDelta(const std::string&, const Poco::Any& value)
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


Poco::Any XDKSensor::getDisplayValue(const std::string&) const
{
	if (_ready)
		return Poco::NumberFormatter::format(value(), 0, 1);
	else
		return std::string("n/a");
}


Poco::Any XDKSensor::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
}


Poco::Any XDKSensor::getName(const std::string&) const
{
	return NAME;
}


Poco::Any XDKSensor::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any XDKSensor::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any XDKSensor::getPhysicalQuantity(const std::string&) const
{
	return _physicalQuantity;
}


Poco::Any XDKSensor::getPhysicalUnit(const std::string&) const
{
	return _physicalUnit;
}


void XDKSensor::update(double value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (!_ready || _value != value)
	{
		_ready = true;
		_value = value;
		_pEventPolicy->valueChanged(value);
	}
}


void XDKSensor::init()
{
	enable(true);
}


void XDKSensor::onConnected()
{
	if (_enabled)
	{
		enable(true);
	}
}


void XDKSensor::onDisconnected()
{
	stopPolling();
}



//
// XDKTemperatureSensor
//
 

XDKTemperatureSensor::XDKTemperatureSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	XDKSensor(pPeripheral, params, pTimer)
{
	init();
}


XDKTemperatureSensor::~XDKTemperatureSensor()
{
}


void XDKTemperatureSensor::poll()
{
	Poco::Int32 rawTemp = _pPeripheral->readInt32(_dataChar.valueHandle);
	update(rawTemp/1000.0);
}


//
// XDKHumiditySensor
//


XDKHumiditySensor::XDKHumiditySensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	XDKSensor(pPeripheral, params, pTimer)
{
	init();
}


XDKHumiditySensor::~XDKHumiditySensor()
{
}


void XDKHumiditySensor::poll()
{
	Poco::UInt32 rawHumidity = _pPeripheral->readUInt32(_dataChar.valueHandle);
	update(rawHumidity*1.0);
}


//
// XDKLightSensor
//


XDKLightSensor::XDKLightSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	XDKSensor(pPeripheral, params, pTimer)
{
	init();
}


XDKLightSensor::~XDKLightSensor()
{
}


void XDKLightSensor::poll()
{
	Poco::UInt32 rawIlluminance = _pPeripheral->readUInt32(_dataChar.valueHandle);
	update(rawIlluminance/10000.0);
}


//
// XDKAirPressureSensor
//


XDKAirPressureSensor::XDKAirPressureSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	XDKSensor(pPeripheral, params, pTimer)
{
	init();
}


XDKAirPressureSensor::~XDKAirPressureSensor()
{
}


void XDKAirPressureSensor::poll()
{
	Poco::UInt32 rawPressure = _pPeripheral->readUInt32(_dataChar.valueHandle);
	update(rawPressure/100.0);
}


//
// XDKNoiseSensor
//


XDKNoiseSensor::XDKNoiseSensor(Peripheral::Ptr pPeripheral, const Params& params, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	XDKSensor(pPeripheral, params, pTimer)
{
	init();
}


XDKNoiseSensor::~XDKNoiseSensor()
{
}


void XDKNoiseSensor::poll()
{
	Poco::UInt8 noiseLevel = _pPeripheral->readUInt8(_dataChar.valueHandle);
	update(noiseLevel*1.0);
}


} } } // namespace IoT::BtLE::XDK
