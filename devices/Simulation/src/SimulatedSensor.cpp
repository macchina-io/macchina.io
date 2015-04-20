//
// SimulatedSensor.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "SimulatedSensor.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/Random.h"


namespace IoT {
namespace Simulation {


class LinearUpdateTimerTask: public Poco::Util::TimerTask
{
public:
	LinearUpdateTimerTask(SimulatedSensor& sensor, double initialValue, double delta, int cycles):
		_sensor(sensor),
		_initialValue(initialValue),
		_delta(delta),
		_cycles(cycles),
		_count(0)
	{
	}
	
	void run()
	{
		if (++_count == _cycles)
		{
			_sensor.update(_initialValue);
			_count = 0;
		}
		else
		{
			double value = _sensor.value();
			value += _delta;
			_sensor.update(value);
		}
	}
	
private:
	SimulatedSensor& _sensor;
	double _initialValue;
	double _delta;
	int _cycles;
	int _count;
};


class RandomUpdateTimerTask: public Poco::Util::TimerTask
{
public:
	RandomUpdateTimerTask(SimulatedSensor& sensor, double initialValue, double delta, int cycles):
		_sensor(sensor),
		_initialValue(initialValue),
		_delta(delta),
		_cycles(cycles),
		_count(0)
	{
	}
	
	void run()
	{
		if (++_count == _cycles)
		{
			_sensor.update(_initialValue);
			_count = 0;
		}
		else
		{
			double value = _sensor.value();
			value += _delta*_random.nextDouble()*2 - _delta;
			_sensor.update(value);
		}
	}
	
private:
	SimulatedSensor& _sensor;
	double _initialValue;
	double _delta;
	int _cycles;
	int _count;
	Poco::Random _random;
};


const std::string SimulatedSensor::NAME("Simulated Sensor");
const std::string SimulatedSensor::SYMBOLIC_NAME("io.macchina.simulation.sensor");


SimulatedSensor::SimulatedSensor(const Params& params, Poco::Util::Timer& timer):
	_value(params.initialValue),
	_valueChangedPeriod(0.0),
	_valueChangedDelta(0.0),
	_pEventPolicy(new IoT::Devices::NoModerationPolicy<double>(valueChanged)),
	_deviceIdentifier(params.id),
	_symbolicName(SYMBOLIC_NAME),
	_name(NAME),
	_physicalQuantity(params.physicalQuantity),
	_physicalUnit(params.physicalUnit),
	_timer(timer)
{
	addProperty("displayValue", &SimulatedSensor::getDisplayValue);
	addProperty("valueChangedPeriod", &SimulatedSensor::getValueChangedPeriod, &SimulatedSensor::setValueChangedPeriod);
	addProperty("valueChangedDelta", &SimulatedSensor::getValueChangedDelta, &SimulatedSensor::setValueChangedDelta);
	addProperty("deviceIdentifier", &SimulatedSensor::getDeviceIdentifier);
	addProperty("symbolicName", &SimulatedSensor::getSymbolicName);
	addProperty("name", &SimulatedSensor::getName);
	addProperty("physicalQuantity", &SimulatedSensor::getPhysicalQuantity);
	addProperty("physicalUnit", &SimulatedSensor::getPhysicalUnit);
	
	if (params.updateRate > 0)
	{
		long interval = 1000/params.updateRate;
		if (params.mode == SIM_LINEAR)
		{
			_timer.scheduleAtFixedRate(new LinearUpdateTimerTask(*this, params.initialValue, params.delta, params.cycles), interval, interval);
		}
		else
		{
			_timer.scheduleAtFixedRate(new RandomUpdateTimerTask(*this, params.initialValue, params.delta, params.cycles), interval, interval);
		}
	}
}

	
SimulatedSensor::~SimulatedSensor()
{
}


double SimulatedSensor::value() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _value;
}


bool SimulatedSensor::ready() const
{
	return true;
}


Poco::Any SimulatedSensor::getValueChangedPeriod(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valueChangedPeriod;
}


void SimulatedSensor::setValueChangedPeriod(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	int period = Poco::AnyCast<int>(value);
	if (period != _valueChangedPeriod)
	{
		if (period == 0)
		{
			_pEventPolicy = new IoT::Devices::NoModerationPolicy<double>(valueChanged);
		}
		else
		{
			_pEventPolicy = new IoT::Devices::MaximumRateModerationPolicy<double>(valueChanged, _value, period, _timer);
		}
		_valueChangedPeriod = period;
	}
}


Poco::Any SimulatedSensor::getValueChangedDelta(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valueChangedDelta;
}


void SimulatedSensor::setValueChangedDelta(const std::string&, const Poco::Any& value)
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


Poco::Any SimulatedSensor::getDisplayValue(const std::string&) const
{
	return Poco::NumberFormatter::format(value(), 0, 1);
}


Poco::Any SimulatedSensor::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
}


Poco::Any SimulatedSensor::getName(const std::string&) const
{
	return _name;
}


Poco::Any SimulatedSensor::getSymbolicName(const std::string&) const
{
	return _symbolicName;
}


Poco::Any SimulatedSensor::getPhysicalQuantity(const std::string&) const
{
	return _physicalQuantity;
}


Poco::Any SimulatedSensor::getPhysicalUnit(const std::string&) const
{
	return _physicalUnit;
}


void SimulatedSensor::update(double value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	if (_value != value)
	{
		_value = value;
		_pEventPolicy->valueChanged(value);
	}
}


} } // namespace IoT::Simulation
