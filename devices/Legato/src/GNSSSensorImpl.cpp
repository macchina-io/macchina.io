//
// GNSSSensorImpl.cpp
//
// $Id$
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "GNSSSensorImpl.h"
#include "IoT/GNSS/NMEA/SentenceDecoder.h"
#include "Poco/Geo/LatLon.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Buffer.h"
#include "Poco/Delegate.h"
#include "Poco/Exception.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/select.h>


namespace IoT {
namespace Legato {


const std::string GNSSSensorImpl::NAME("Legato GNSS Sensor");
const std::string GNSSSensorImpl::TYPE("io.macchina.gnss");
const std::string GNSSSensorImpl::SYMBOLIC_NAME("io.macchina.legato.gnss");
const std::string GNSSSensorImpl::PATH("/dev/nmea");


GNSSSensorImpl::GNSSSensorImpl():
	_fd(-1),
	_buffer(4096),
	_lastValidPosition(0),
	_lastPositionUpdate(0),
	_positionAvailable(false),
	_course(-1),
	_speed(-1),
	_magneticVariation(-1),
	_altitude(-9999),
	_hdop(-9999),
	_period(0),
	_delta(0),
	_timeout(30000),
	_done(false),
	_logger(Poco::Logger::get("IoT.Legato.GNSSSensorImpl"))
{
	addProperty("symbolicName", &GNSSSensorImpl::getSymbolicName);
	addProperty("name", &GNSSSensorImpl::getName);
	addProperty("type", &GNSSSensorImpl::getType);
	addProperty("displayValue", &GNSSSensorImpl::getDisplayValue);
	addProperty("positionChangedPeriod", &GNSSSensorImpl::getPositionChangedPeriod, &GNSSSensorImpl::setPositionChangedPeriod);
	addProperty("positionChangedDelta", &GNSSSensorImpl::getPositionChangedDelta, &GNSSSensorImpl::setPositionChangedDelta);
	addProperty("positionTimeout", &GNSSSensorImpl::getPositionTimeout, &GNSSSensorImpl::setPositionTimeout);

	_fd = ::open(PATH.c_str(), O_RDONLY | O_NONBLOCK);
	if (_fd == -1) throw Poco::FileNotFoundException(PATH);

	_thread.start(*this);
}


GNSSSensorImpl::~GNSSSensorImpl()
{
	try
	{
		stop();
	}
	catch (Poco::Exception&)
	{
		poco_unexpected();
	}
	::close(_fd);
}


void GNSSSensorImpl::run()
{
	IoT::GNSS::NMEA::RMCProcessor rmcProcessor;
	IoT::GNSS::NMEA::GGAProcessor ggaProcessor;

	IoT::GNSS::NMEA::SentenceDecoder nmeaDecoder;
	nmeaDecoder.sentenceReceived += Poco::delegate(&rmcProcessor, &IoT::GNSS::NMEA::RMCProcessor::processSentence);
	nmeaDecoder.sentenceReceived += Poco::delegate(&ggaProcessor, &IoT::GNSS::NMEA::GGAProcessor::processSentence);

	rmcProcessor.rmcReceived += Poco::delegate(this, &GNSSSensorImpl::onRMCReceived);
	ggaProcessor.ggaReceived += Poco::delegate(this, &GNSSSensorImpl::onGGAReceived);

	::write(_fd, "$GPS_START\n", 11);

	while (!done())
	{
		try
		{
			if (poll(Poco::Timespan(1, 0)) > 0)
			{
				int n = ::read(_fd, _buffer.begin(), _buffer.size());
				if (n > 0)
				{
					nmeaDecoder.processBuffer(_buffer.begin(), n);
				}
			}
			bool fireLostPosition = false;
			{
				Poco::FastMutex::ScopedLock lock(_mutex);
				if (_positionAvailable && _lastPositionUpdate.elapsed() > Poco::Timestamp::TimeVal(_timeout)*1000)
				{
					_positionAvailable = false;
					fireLostPosition = true;
				}
			}
			if (fireLostPosition)
			{
				try
				{
					positionLost(this);
				}
				catch (Poco::Exception&)
				{
				}
			}
		}
		catch (Poco::Exception& exc)
		{
			_logger.log(exc);
			Poco::Thread::sleep(200);
		}
	}

	::write(_fd, "$GPS_STOP\n", 10);
}


void GNSSSensorImpl::stop()
{
	{
		Poco::FastMutex::ScopedLock lock(_mutex);
		_done = true;
	}
	_thread.join();
}


bool GNSSSensorImpl::done()
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _done;
}


bool GNSSSensorImpl::positionAvailable() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _positionAvailable;
}


IoT::Devices::LatLon GNSSSensorImpl::position() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _position;
}


double GNSSSensorImpl::course() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _course;
}


double GNSSSensorImpl::speed() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _speed;
}


double GNSSSensorImpl::magneticVariation() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _magneticVariation;
}


double GNSSSensorImpl::altitude() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _altitude;
}


double GNSSSensorImpl::hdop() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _hdop;
}


Poco::Any GNSSSensorImpl::getName(const std::string&) const
{
	return NAME;
}


Poco::Any GNSSSensorImpl::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any GNSSSensorImpl::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any GNSSSensorImpl::getPositionChangedPeriod(const std::string&) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return Poco::Any(_period);
}


void GNSSSensorImpl::setPositionChangedPeriod(const std::string&, const Poco::Any& value)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_period = Poco::AnyCast<int>(value);
}


Poco::Any GNSSSensorImpl::getPositionChangedDelta(const std::string&) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return Poco::Any(_delta);
}


void GNSSSensorImpl::setPositionChangedDelta(const std::string&, const Poco::Any& value)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_delta = Poco::AnyCast<double>(value);
}


Poco::Any GNSSSensorImpl::getPositionTimeout(const std::string&) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return Poco::Any(_timeout);
}


void GNSSSensorImpl::setPositionTimeout(const std::string&, const Poco::Any& value)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_timeout = Poco::AnyCast<int>(value);
}


Poco::Any GNSSSensorImpl::getDisplayValue(const std::string&) const
{
	if (positionAvailable())
	{
		IoT::Devices::LatLon latLon = position();
		std::string value = Poco::format("%02.6f,%03.6f", latLon.latitude, latLon.longitude);
		double knots = speed();
		if (knots >= 0) Poco::format(value, " %.2f kn", knots);
		double degrees = course();
		if (degrees >= 0) Poco::format(value, " %.1f°", degrees);
		return value;
	}
	else return std::string("n/a");
}


void GNSSSensorImpl::onRMCReceived(const IoT::GNSS::NMEA::RMCProcessor::RMC& rmc)
{
	IoT::Devices::PositionUpdate event;
	IoT::Devices::LatLon lastPosition;
	double delta = 0;
	double period = 0;
	{
		Poco::FastMutex::ScopedLock lock(_mutex);

		delta = _delta;
		period = _period;

		_lastValidPosition.update();
		_positionAvailable = true;

		lastPosition = _position;
		_position.latitude = rmc.position.latitude().degrees();
		_position.longitude = rmc.position.longitude().degrees();
		_course   = rmc.heading.degrees();
		_speed    = rmc.speed;
		_magneticVariation = rmc.magneticVariation.degrees();
	}

	try
	{
		if (_lastPositionUpdate.isElapsed(1000*Poco::Timestamp::TimeVal(period)))
		{
			bool needUpdate = delta == 0;
			if (!needUpdate)
			{
				Poco::Geo::LatLon lastLatLon(
					Poco::Geo::Angle::fromDegrees(lastPosition.latitude),
					Poco::Geo::Angle::fromDegrees(lastPosition.longitude));
				Poco::Geo::LatLon curLatLon(
					Poco::Geo::Angle::fromDegrees(_position.latitude),
					Poco::Geo::Angle::fromDegrees(_position.longitude));
				Poco::Geo::Angle gcd = lastLatLon.greatCircleDistanceTo(curLatLon);
				needUpdate = gcd.radians()*Poco::Geo::LatLon::EARTH_MEAN_RADIUS >= delta;
			}
			if (needUpdate)
			{
				_lastPositionUpdate.update();

				event.position = _position;
				event.course   = _course;
				event.speed    = _speed;
				event.magneticVariation = _magneticVariation;
				event.timestamp = rmc.timestamp;

				positionUpdate(this, event);
			}
		}
	}
	catch (Poco::Exception& exc)
	{
		_logger.log(exc);
	}
}


void GNSSSensorImpl::onGGAReceived(const IoT::GNSS::NMEA::GGAProcessor::GGA& gga)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_altitude = gga.altitude;
	_hdop = gga.hdop;
}


int GNSSSensorImpl::poll(const Poco::Timespan& timeout)
{
	fd_set fdRead;
	fd_set fdWrite;
	fd_set fdExcept;
	FD_ZERO(&fdRead);
	FD_ZERO(&fdWrite);
	FD_ZERO(&fdExcept);
	FD_SET(_fd, &fdRead);
	Poco::Timespan remainingTime(timeout);
	int rc;
	do
	{
		struct timeval tv;
		tv.tv_sec  = static_cast<long>(remainingTime.totalSeconds());
		tv.tv_usec = static_cast<long>(remainingTime.useconds());
		Poco::Timestamp start;
		rc = ::select(_fd + 1, &fdRead, &fdWrite, &fdExcept, &tv);
		if (rc < 0 && errno == EINTR)
		{
			Poco::Timestamp end;
			Poco::Timespan waited = end - start;
			if (waited < remainingTime)
				remainingTime -= waited;
			else
				remainingTime = 0;
		}
	}
	while (rc < 0 && errno == EINTR);
	if (rc < 0) throw Poco::IOException("file poll error", strerror(errno));
	return rc;
}


} } // namespace IoT::Legato
