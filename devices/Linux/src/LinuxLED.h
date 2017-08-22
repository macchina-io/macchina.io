//
// LinuxLED.h
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Linux_LinuxLED_INCLUDED
#define IoT_Linux_LinuxLED_INCLUDED


#include "IoT/Devices/LED.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/Util/Timer.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/SharedPtr.h"
#include "Poco/Mutex.h"


namespace IoT {
namespace Linux {


class LinuxLED: public IoT::Devices::DeviceImpl<IoT::Devices::LED, LinuxLED>
{
public:
	LinuxLED(const std::string& device, Poco::SharedPtr<Poco::Util::Timer> pTimer);
		/// Creates a LinuxLED.
		
	~LinuxLED();
		/// Destroys the LinuxLED.
	
	// LED
	void on();
	void off();
	double getBrightness() const;
	void setBrightness(double brightness);
	void blink(int onMilliseconds, int offMilliseconds);

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

protected:
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getBlinkOn(const std::string&) const;
	void setBlinkOn(const std::string&, const Poco::Any& value);
	Poco::Any getBlinkOff(const std::string&) const;
	void setBlinkOff(const std::string&, const Poco::Any& value);
	void setBrightnessImpl(double brightness);

private:
	std::string _device;
	Poco::SharedPtr<Poco::Util::Timer> _pTimer;
	std::string _brightnessPath;
	Poco::Any _deviceIdentifier;
	int _maxBrightness;
	int _onMilliseconds;
	int _offMilliseconds;
	Poco::Util::TimerTask::Ptr _pOnTask;
	Poco::Util::TimerTask::Ptr _pOffTask;
	mutable Poco::FastMutex _mutex;
	
	friend class SwitchLEDTask;
};


} } // namespace IoT::Linux


#endif // IoT_Linux_LinuxLED_INCLUDED
