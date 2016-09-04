//
// GNSSSensorImpl.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "GNSSSensorImpl.h"
#include "IoT/GNSS/NMEA/SentenceDecoder.h"
#include "Poco/Geo/LatLon.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "Poco/Delegate.h"


namespace IoT {
namespace GNSS {


const std::string GNSSSensorImpl::NAME("GNSS Sensor (NMEA-0183)");
const std::string GNSSSensorImpl::SYMBOLIC_NAME("io.macchina.gnss.nmea");


GNSSSensorImpl::GNSSSensorImpl(Poco::SharedPtr<Poco::Serial::SerialPort> pSerialPort):
	_pSerialPort(pSerialPort),
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
	_logger(Poco::Logger::get("IoT.NMEA.GNSSSensorImpl"))
{
	addProperty("symbolicName", &GNSSSensorImpl::getSymbolicName);
	addProperty("name", &GNSSSensorImpl::getName);
	addProperty("displayValue", &GNSSSensorImpl::getDisplayValue);
	addProperty("positionChangedPeriod", &GNSSSensorImpl::getPositionChangedPeriod, &GNSSSensorImpl::setPositionChangedPeriod);
	addProperty("positionChangedDelta", &GNSSSensorImpl::getPositionChangedDelta, &GNSSSensorImpl::setPositionChangedDelta);
	addProperty("positionTimeout", &GNSSSensorImpl::getPositionTimeout, &GNSSSensorImpl::setPositionTimeout);

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
	
	while (!done())
	{
		try
		{
			if (_pSerialPort->poll(Poco::Timespan(1, 0)))
			{
				std::string data;
				_pSerialPort->read(data);
				nmeaDecoder.processBuffer(data.data(), data.size());
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


Poco::Any GNSSSensorImpl::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any GNSSSensorImpl::getDevice(const std::string&) const
{
	return _pSerialPort->device();
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


} } // namespace IoT::GNSS
