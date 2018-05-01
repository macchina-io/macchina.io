//
// LinuxGPIO.cpp
//
// Copyright (c) 2009-2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "LinuxGPIO.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Format.h"
#include "Poco/FileStream.h"
#include "Poco/File.h"
#include "Poco/Exception.h"
#include <unistd.h>
#include <poll.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


namespace IoT {
namespace Linux {


const std::string LinuxGPIO::NAME("Linux GPIO");
const std::string LinuxGPIO::TYPE("io.macchina.gpio");
const std::string LinuxGPIO::SYMBOLIC_NAME("io.macchina.linux.gpio");
const std::string LinuxGPIO::LOGGER_NAME("IoT.LinuxGPIO");


LinuxGPIO::LinuxGPIO(const int pin, LinuxGPIO::Direction direction):
	_pin(pin),
	_direction(direction),
	_gpioPath("/sys/class/gpio"),
	_eventActivity(this, &LinuxGPIO::watchInputPin),
	_logger(Poco::Logger::get(LOGGER_NAME))
{
	addProperty("displayValue", &LinuxGPIO::getDisplayValue);
	addProperty("symbolicName", &LinuxGPIO::getSymbolicName);
	addProperty("name", &LinuxGPIO::getName);
	addProperty("type", &LinuxGPIO::getType);
	addProperty("device", &LinuxGPIO::getDevice);
	addProperty("direction", &LinuxGPIO::getDirection);
	addProperty("state", &LinuxGPIO::getState, &LinuxGPIO::setState);

	exportPin(_pin);
	setDirection(_pin, _direction);
	if ((direction == DIRECTION_IN) && canInterrupt())
	{
		_eventActivity.start();
	}
}


LinuxGPIO::~LinuxGPIO()
{
	if (!_eventActivity.isStopped())
	{
		_eventActivity.stop();
		_eventActivity.wait();
	}
	unexportPin(_pin);
}


Poco::Any LinuxGPIO::getDisplayValue(const std::string&) const
{
	std::string value(state() ? "1" : "0");
	value += " [";
	value += toString(_direction);
	value += "]";
	return value;
}


Poco::Any LinuxGPIO::getName(const std::string&) const
{
	return NAME;
}


Poco::Any LinuxGPIO::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any LinuxGPIO::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any LinuxGPIO::getDevice(const std::string&) const
{
	return Poco::NumberFormatter::format(_pin);
}


Poco::Any LinuxGPIO::getDirection(const std::string&) const
{
	return toString(_direction);
}


Poco::Any LinuxGPIO::getState(const std::string&) const
{
	return state();
}


void LinuxGPIO::setState(const std::string&, const Poco::Any& value)
{
	set(Poco::AnyCast<bool>(value));
}


std::string LinuxGPIO::toString(LinuxGPIO::Direction direction)
{
	return (direction == LinuxGPIO::DIRECTION_OUT) ? "out" : "in";
}


LinuxGPIO::Direction LinuxGPIO::toDirection(const std::string& direction)
{
	if (direction == "in")
	{
		return LinuxGPIO::DIRECTION_IN;
	}
	else if (direction == "out")
	{
		return LinuxGPIO::DIRECTION_OUT;
	}
	else
	{
		throw Poco::InvalidArgumentException("Invalid direction type", direction);
	}
}


template <typename T>
void LinuxGPIO::writeHelper(const std::string& path, const T& value) const
{
	std::string file_path = pathHelper(path);
	Poco::FileOutputStream ostr(file_path);
	ostr << value << std::endl;
}


std::string LinuxGPIO::pathHelper(const std::string path) const
{
	return _gpioPath.toString() + path;
}


void LinuxGPIO::exportPin(int pin) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	writeHelper("/export", pin);
}


void LinuxGPIO::unexportPin(int pin) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	writeHelper("/unexport", pin);
}


void LinuxGPIO::registerEvent(int pin) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	writeHelper(Poco::format("/gpio%d/edge", pin), "both");
}


void LinuxGPIO::unregisterEvent(int pin) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	writeHelper(Poco::format("/gpio%d/edge", pin), "none");
}


void LinuxGPIO::setDirection(int pin, LinuxGPIO::Direction direction) const
{
	std::string strDirection = toString(direction);
	_logger.debug(Poco::format("Set direction as '%s' on gpio %d", strDirection, _pin));

	Poco::FastMutex::ScopedLock lock(_mutex);
	writeHelper(Poco::format("/gpio%d/direction", pin), strDirection);
}


void LinuxGPIO::set(bool state)
{
	_logger.debug(Poco::format("Set state %d on gpio %s", state, _pin));

	Poco::FastMutex::ScopedLock lock(_mutex);
	writeHelper(Poco::format("/gpio%d/value", _pin), state);
}


bool LinuxGPIO::toggle()
{
	_logger.debug(Poco::format("Toggling state on gpio %s", _pin));

	Poco::FastMutex::ScopedLock lock(_mutex);

	std::string file_path = pathHelper(Poco::format("/gpio%d/value", _pin));
	Poco::FileInputStream istr(file_path);
	bool level = false;
	istr >> level;
	level = !level;

	writeHelper(Poco::format("/gpio%d/value", _pin), level);

	return level;
}


bool LinuxGPIO::state() const
{
	std::string file_path = pathHelper(Poco::format("/gpio%d/value", _pin));
	Poco::FastMutex::ScopedLock lock(_mutex);
	Poco::FileInputStream istr(file_path);
	bool level;
	istr >> level;
	_logger.debug(Poco::format("Received state %d on gpio %d", level, _pin));
	return level;
}


bool LinuxGPIO::canInterrupt()
{
	Poco::File event_file(pathHelper(Poco::format("/gpio%d/edge", _pin)));
	return event_file.exists();
}


void LinuxGPIO::watchInputPin()
{
	const std::string file_path = pathHelper(Poco::format("/gpio%d/value", _pin));
	const int fd = ::open(file_path.c_str(), O_RDONLY | O_NONBLOCK);

	if (fd == -1)
	{
		throw Poco::IOException("file open error", strerror(errno));
	}

	struct pollfd pollfdset = {fd, POLLIN, 0};
	const nfds_t nfds = 1;
	const int timeout_ms = 100;
	int last_level = INT_MAX;

	try
	{
		registerEvent(_pin);

		_logger.debug(Poco::format("Watching gpio %d", _pin));

		while (!_eventActivity.isStopped())
		{
			int result = ::poll(&pollfdset, nfds, timeout_ms);

			if (result < 0)
			{
				throw Poco::IOException("file poll error", strerror(errno));
			}
			else if (result == 0)
			{
				continue;
			}
			else if (pollfdset.revents & POLLIN)
			{
				const int level = state();
				if (last_level != level)
				{
					_logger.debug(Poco::format("Registered state %d on gpio %d", level, _pin));
					stateChanged.notify(this, level);
					last_level = level;
				}
			}
		}

		unregisterEvent(_pin);
	}
	catch (Poco::Exception&)
	{
		::close(fd);
		throw;
	}
	::close(fd);
}


} } // namespace IoT::Linux
