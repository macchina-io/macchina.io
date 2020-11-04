//
// XBeeSensor.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "XBeeSensor.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Delegate.h"


namespace IoT {
namespace XBee {
namespace Sensor {


const std::string XBeeSensor::NAME("XBee Sensor");
const std::string XBeeSensor::TYPE("io.macchina.sensor");
const std::string XBeeSensor::SYMBOLIC_NAME("io.macchina.xbee.sensor");


XBeeSensor::XBeeSensor(IXBeeNode::Ptr pXBeeNode, Params params):
	_pXBeeNode(pXBeeNode),
	_id(params.id),
	_analogChannel(params.analogChannel),
	_ready(false),
	_value(0),
	_valueChangedDelta(0.0),
	_pEventPolicy(new IoT::Devices::NoModerationPolicy<double>(valueChanged)),
	_deviceIdentifier(params.id),
	_physicalQuantity(params.physicalQuantity),
	_physicalUnit(params.physicalUnit)
{
	addProperty("displayValue", &XBeeSensor::getDisplayValue);
	addProperty("valueChangedDelta", &XBeeSensor::getValueChangedDelta, &XBeeSensor::setValueChangedDelta);
	addProperty("deviceIdentifier", &XBeeSensor::getDeviceIdentifier);
	addProperty("symbolicName", &XBeeSensor::getSymbolicName);
	addProperty("name", &XBeeSensor::getName);
	addProperty("type", &XBeeSensor::getType);
	addProperty("physicalQuantity", &XBeeSensor::getPhysicalQuantity);
	addProperty("physicalUnit", &XBeeSensor::getPhysicalUnit);

	_pXBeeNode->ioSampleReceived += Poco::delegate(this, &XBeeSensor::onIOSampleReceived);
}


XBeeSensor::~XBeeSensor()
{
	_pXBeeNode->ioSampleReceived -= Poco::delegate(this, &XBeeSensor::onIOSampleReceived);
}


double XBeeSensor::value() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _value;
}


bool XBeeSensor::ready() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _ready;
}


Poco::Any XBeeSensor::getValueChangedDelta(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return _valueChangedDelta;
}


void XBeeSensor::setValueChangedDelta(const std::string&, const Poco::Any& value)
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


Poco::Any XBeeSensor::getDisplayValue(const std::string&) const
{
	return Poco::NumberFormatter::format(value(), 0, 1);
}


Poco::Any XBeeSensor::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
}


Poco::Any XBeeSensor::getName(const std::string&) const
{
	return NAME;
}


Poco::Any XBeeSensor::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any XBeeSensor::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any XBeeSensor::getPhysicalQuantity(const std::string&) const
{
	return _physicalQuantity;
}


Poco::Any XBeeSensor::getPhysicalUnit(const std::string&) const
{
	return _physicalUnit;
}


void XBeeSensor::update(double value)
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
// XBeeTemperatureSensor
//


XBeeTemperatureSensor::XBeeTemperatureSensor(IXBeeNode::Ptr pXBeeNode, Params params):
	XBeeSensor(pXBeeNode, params)
{
}


XBeeTemperatureSensor::~XBeeTemperatureSensor()
{
}


void XBeeTemperatureSensor::onIOSampleReceived(const IOSample& ioSample)
{
	if (ioSample.deviceAddress == _id && ((ioSample.analogChannelMask >> _analogChannel) & 1))
	{
		double mV = 1200.0*(ioSample.analogSamples[_analogChannel - 1]/1023.0);
		update((mV - 500)/10);
	}
}


//
// XBeeHumiditySensor
//


XBeeHumiditySensor::XBeeHumiditySensor(IXBeeNode::Ptr pXBeeNode, Params params):
	XBeeSensor(pXBeeNode, params)
{
}


XBeeHumiditySensor::~XBeeHumiditySensor()
{
}


void XBeeHumiditySensor::onIOSampleReceived(const IOSample& ioSample)
{
	if (ioSample.deviceAddress == _id && ((ioSample.analogChannelMask >> _analogChannel) & 1))
	{
		double mV = 1200.0*(ioSample.analogSamples[_analogChannel - 1]/1023.0);
		update(((mV*108.2/33.2)/5000 - 0.16)/0.0062);
	}
}


//
// XBeeLightSensor
//


XBeeLightSensor::XBeeLightSensor(IXBeeNode::Ptr pXBeeNode, Params params):
	XBeeSensor(pXBeeNode, params)
{
}


XBeeLightSensor::~XBeeLightSensor()
{
}


void XBeeLightSensor::onIOSampleReceived(const IOSample& ioSample)
{
	if (ioSample.deviceAddress == _id && ((ioSample.analogChannelMask >> _analogChannel) & 1))
	{
		double mV = 1200.0*(ioSample.analogSamples[_analogChannel - 1]/1023.0);
		update(mV);
	}
}


} } } // namespace IoT::XBee::Sensor
