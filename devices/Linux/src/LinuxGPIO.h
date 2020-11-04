//
// LinuxGPIO.h
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Linux_LinuxGPIO_INCLUDED
#define IoT_Linux_LinuxGPIO_INCLUDED


#include "Poco/Path.h"
#include "Poco/Activity.h"
#include "Poco/Mutex.h"
#include "Poco/Logger.h"
#include "Poco/AutoPtr.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/IO.h"


namespace IoT {
namespace Linux {


class LinuxGPIO: public IoT::Devices::DeviceImpl<IoT::Devices::IO, LinuxGPIO>
	/// Default implementation for LinuxGPIO using the macchina.io IO class.
{
public:
	using Ptr = Poco::AutoPtr<LinuxGPIO>;

	enum Direction
	{
		DIRECTION_IN,	/// GPIO pin as input
		DIRECTION_OUT	/// GPIO pin as output
	};

	LinuxGPIO(const int pin, Direction direction);
		/// Creates the LinuxGPIO using the given device name.

	~LinuxGPIO();
		/// Destroys the LinuxGPIO.

	// GPIO
	bool state() const;
	void set(bool state);
	bool toggle();

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

	static std::string toString(Direction direction);
		/// Convert direction enum to string for linux sys

	static Direction toDirection(const std::string& direction);
		/// Convert string friendly-name to Direction enum

protected:
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getDevice(const std::string&) const;
	Poco::Any getDirection(const std::string&) const;
	Poco::Any getState(const std::string&) const;
	void setState(const std::string&, const Poco::Any& value);

	static const std::string LOGGER_NAME;
		/// GPIO Logger name

private:
	int _pin;
		/// GPIO pin index
	Direction _direction;
		/// GPIO direction
	Poco::Path _gpioPath;
		/// GPIO prefix path
	Poco::Activity<LinuxGPIO> _eventActivity;
		/// Watch GPIO pin
	Poco::Logger& _logger;
		/// GPIO event logger
	mutable Poco::FastMutex _mutex;
		/// Mutex for GPIO value file

	void exportPin(int pin) const;
		/// Export control of a GPIO to userspace

	void unexportPin(int pin) const;
		/// Will remove a GPIO node exported

	void registerEvent(int pin) const;
		/// Set the signal edge(s) that will make poll

	void unregisterEvent(int pin) const;
		/// Disable event trigger

	void setDirection(int pin, Direction direction) const;
		/// Set direction of a GPIO as input or output

	template <typename T>
	void writeHelper(const std::string& path, const T& value) const;
		/// Help to write any value in a GPIO file

	std::string pathHelper(const std::string path) const;
		/// Help to solve GPIO file path

	void watchInputPin();
		/// Use pin interruption to set GPIO event

	bool canInterrupt();
		/// Check if is possible to trigger interruption
};


} } // namespace IoT::Linux


#endif // IoT_Linux_LinuxGPIO_INCLUDED
