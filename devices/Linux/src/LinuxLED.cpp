//
// LinuxLED.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "LinuxLED.h"
#include "Poco/NumberFormatter.h"
#include "Poco/FileStream.h"
#include "Poco/Path.h"


namespace IoT {
namespace Linux {


const std::string LinuxLED::NAME("Linux LED");
const std::string LinuxLED::TYPE("io.macchina.led");
const std::string LinuxLED::SYMBOLIC_NAME("io.macchina.linux.led");


class SwitchLEDTask: public Poco::Util::TimerTask
{
public:
	SwitchLEDTask(LinuxLED& led, double brightness):
		_led(led),
		_brightness(brightness)
	{
	}
	
	void run()
	{
		_led.setBrightnessImpl(_brightness);
	}
	
private:
	LinuxLED& _led;
	double _brightness;
};


LinuxLED::LinuxLED(const std::string& device, Poco::SharedPtr<Poco::Util::Timer> pTimer):
	_device(device),
	_pTimer(pTimer),
	_brightnessPath(device),
	_deviceIdentifier(Poco::Path(device).getFileName()),
	_maxBrightness(0),
	_onMilliseconds(0),
	_offMilliseconds(0)
{
	addProperty("displayValue", &LinuxLED::getDisplayValue);
	addProperty("deviceIdentifier", &LinuxLED::getDeviceIdentifier);
	addProperty("symbolicName", &LinuxLED::getSymbolicName);
	addProperty("name", &LinuxLED::getName);
	addProperty("type", &LinuxLED::getType);
	addProperty("blinkOn", &LinuxLED::getBlinkOn, &LinuxLED::setBlinkOn);
	addProperty("blinkOff", &LinuxLED::getBlinkOff, &LinuxLED::setBlinkOff);

	_brightnessPath += "/brightness";

	std::string maxBrightnessPath(_device);
	maxBrightnessPath += "/max_brightness";
	Poco::FileInputStream istr(maxBrightnessPath);
	istr >> _maxBrightness;
	if (_maxBrightness == 0) throw Poco::IOException("Invalid maximum brightness", device);
}

	
LinuxLED::~LinuxLED()
{
}


void LinuxLED::on()
{
	setBrightness(1.0);
}


void LinuxLED::off()
{
	setBrightness(0.0);
}


double LinuxLED::getBrightness() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Poco::FileInputStream istr(_brightnessPath);
	int brightness;
	istr >> brightness;
	return static_cast<double>(brightness)/_maxBrightness;
}


void LinuxLED::setBrightness(double brightness)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	if (_pOnTask) _pOnTask->cancel();
	if (_pOffTask) _pOffTask->cancel();
	_pOnTask = 0;
	_pOffTask = 0;
	_pTimer->schedule(new SwitchLEDTask(*this, brightness), Poco::Clock());	
}


void LinuxLED::blink(int onMilliseconds, int offMilliseconds)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_onMilliseconds  = onMilliseconds;
	_offMilliseconds = offMilliseconds;
	
	if (_onMilliseconds > 0 && _offMilliseconds > 0)
	{
		if (_pOnTask) _pOnTask->cancel();
		_pOnTask  = new SwitchLEDTask(*this, 1.0);
		if (_pOffTask) _pOffTask->cancel();
		_pOffTask = new SwitchLEDTask(*this, 0.0);
		_pTimer->scheduleAtFixedRate(_pOnTask, 0, _onMilliseconds + _offMilliseconds);
		_pTimer->scheduleAtFixedRate(_pOffTask, _onMilliseconds, _onMilliseconds + _offMilliseconds);
	}
	else
	{
		if (_pOnTask) _pOnTask->cancel();
		if (_pOffTask) _pOffTask->cancel();
		_pOnTask = 0;
		_pOffTask = 0;
		if (_onMilliseconds == 0 && _offMilliseconds == 0)
		{
			_pTimer->schedule(new SwitchLEDTask(*this, 0.0), Poco::Clock());
		}
	}
}


Poco::Any LinuxLED::getDisplayValue(const std::string&) const
{
	return Poco::NumberFormatter::format(getBrightness(), 0, 1);
}


Poco::Any LinuxLED::getDeviceIdentifier(const std::string&) const
{
	return _deviceIdentifier;
}


Poco::Any LinuxLED::getName(const std::string&) const
{
	return NAME;
}


Poco::Any LinuxLED::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any LinuxLED::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any LinuxLED::getBlinkOn(const std::string&) const
{
	return _onMilliseconds;
}


void LinuxLED::setBlinkOn(const std::string&, const Poco::Any& value)
{
	blink(Poco::AnyCast<int>(value), _offMilliseconds);
}


Poco::Any LinuxLED::getBlinkOff(const std::string&) const
{
	return _offMilliseconds;
}


void LinuxLED::setBlinkOff(const std::string&, const Poco::Any& value)
{
	blink(_onMilliseconds, Poco::AnyCast<int>(value));
}


void LinuxLED::setBrightnessImpl(double brightness)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	int newBrightness = static_cast<int>(_maxBrightness*brightness);
	Poco::FileOutputStream ostr(_brightnessPath);
	ostr << newBrightness << std::endl;
}


} } // namespace IoT::Linux
