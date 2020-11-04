//
// SimulatedGNSSSensor.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "SimulatedGNSSSensor.h"
#include "Poco/Util/TimerTask.h"
#include "Poco/SAX/DefaultHandler.h"
#include "Poco/SAX/Attributes.h"
#include "Poco/SAX/SAXParser.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "Poco/NumberParser.h"
#include "Poco/DateTimeParser.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/String.h"


namespace IoT {
namespace Simulation {


const std::string SimulatedGNSSSensor::NAME("GNSS Sensor Simulation (GPX)");
const std::string SimulatedGNSSSensor::TYPE("io.macchina.gnss");
const std::string SimulatedGNSSSensor::SYMBOLIC_NAME("io.macchina.simulation.gnss");


class PositionUpdate: public Poco::Util::TimerTask
{
public:
	PositionUpdate(SimulatedGNSSSensor& sensor, const Poco::Geo::LatLon& latLon, double altitude):
		_sensor(sensor),
		_latLon(latLon),
		_altitude(altitude)
	{
	}
	
	void run()
	{
		_sensor.updatePosition(_latLon, _altitude);
	}
	
private:
	SimulatedGNSSSensor& _sensor;
	Poco::Geo::LatLon _latLon;
	double _altitude;
};


class LoadGPX: public Poco::Util::TimerTask
{
public:
	LoadGPX(SimulatedGNSSSensor& sensor, const std::string& gpxPath):
		_sensor(sensor),
		_gpxPath(gpxPath)
	{
	}
	
	void run()
	{
		_sensor.loadGPX(_gpxPath);
	}
	
private:
	SimulatedGNSSSensor& _sensor;
	std::string _gpxPath;
};


class GPXHandler: public Poco::XML::DefaultHandler
{
public:
	enum State
	{
		GPX_STATE_IDLE,
		GPX_STATE_TRKPT,
		GPX_STATE_ELE,
		GPX_STATE_TIME
	};
	
	GPXHandler(SimulatedGNSSSensor& sensor):
		_sensor(sensor),
		_startTime(0)
	{
	}
	
	void startElement(const std::string& uri, const std::string& localName, const std::string& qname, const Poco::XML::Attributes& attributes)
	{
		if (localName == "trkpt")
		{
			_state = GPX_STATE_TRKPT;
			_lat = attributes.getValue("lat");
			_lon = attributes.getValue("lon");	
		}
		else if (localName == "ele")
		{
			_state = GPX_STATE_ELE;
			_ele.clear();
		}
		else if (localName == "time")
		{
			_state = GPX_STATE_TIME;
			_time.clear();
		}
	}

	void endElement(const std::string& uri, const std::string& localName, const std::string& qname)
	{
		if (localName == "trkpt")
		{
			try
			{
				int tzd;
				Poco::Timestamp ts = Poco::DateTimeParser::parse(Poco::DateTimeFormat::ISO8601_FORMAT, _time, tzd).timestamp();
				Poco::Geo::LatLon latLon(
					Poco::Geo::Angle::fromDegrees(Poco::NumberParser::parseFloat(_lat)), 
					Poco::Geo::Angle::fromDegrees(Poco::NumberParser::parseFloat(_lon)));
				double altitude = Poco::NumberParser::parseFloat(_ele);
				
				if (_startTime == 0)
				{
					_startTime = ts;
				}
				Poco::Timestamp::TimeDiff diff = (ts - _startTime)/_sensor._speedUp; 
				_endClock = _startClock;
				_endClock += diff;
				_sensor._timer.schedule(new PositionUpdate(_sensor, latLon, altitude), _endClock);
			}
			catch (Poco::Exception& exc)
			{
				_sensor._logger.log(exc);
			}

			_state = GPX_STATE_IDLE;
		}
		else if (localName == "ele")
		{
			Poco::trimInPlace(_ele);
			_state = GPX_STATE_TRKPT;
		}
		else if (localName == "time")
		{
			Poco::trimInPlace(_time);
			_state = GPX_STATE_TRKPT;
		}
	}

	void characters(const char ch[], int start, int length)
	{
		if (_state == GPX_STATE_ELE)
		{
			_ele.append(ch + start, length);
		}
		else if (_state == GPX_STATE_TIME)
		{
			_time.append(ch + start, length);
		}
	}

	const Poco::Clock& endClock() const
	{
		return _endClock;
	}
	
private:
	SimulatedGNSSSensor& _sensor;
	State _state;
	Poco::Timestamp _startTime;
	std::string _lat;
	std::string _lon;
	std::string _ele;
	std::string _time;
	Poco::Clock _startClock;
	Poco::Clock _endClock;
};


SimulatedGNSSSensor::SimulatedGNSSSensor(const Params& params):
	_gpxPath(params.gpxPath),
	_loopReplay(params.loopReplay),
	_speedUp(params.speedUp),
	_lastValidPosition(0),
	_lastPositionUpdate(0),
	_positionAvailable(false),
	_course(-1),
	_speed(-1),
	_altitude(-9999),
	_period(0),
	_delta(0),
	_timeout(30000),
	_logger(Poco::Logger::get("IoT.Simulation.SimulatedGNSSSensor"))
{
	addProperty("symbolicName", &SimulatedGNSSSensor::getSymbolicName);
	addProperty("name", &SimulatedGNSSSensor::getName);
	addProperty("type", &SimulatedGNSSSensor::getType);
	addProperty("displayValue", &SimulatedGNSSSensor::getDisplayValue);
	addProperty("positionChangedPeriod", &SimulatedGNSSSensor::getPositionChangedPeriod, &SimulatedGNSSSensor::setPositionChangedPeriod);
	addProperty("positionChangedDelta", &SimulatedGNSSSensor::getPositionChangedDelta, &SimulatedGNSSSensor::setPositionChangedDelta);
	addProperty("positionTimeout", &SimulatedGNSSSensor::getPositionTimeout, &SimulatedGNSSSensor::setPositionTimeout);
	addProperty("gpxPath", &SimulatedGNSSSensor::getGPXPath);

	loadGPX(_gpxPath);
}

	
SimulatedGNSSSensor::~SimulatedGNSSSensor()
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


void SimulatedGNSSSensor::stop()
{
	_timer.cancel(true);
}


bool SimulatedGNSSSensor::positionAvailable() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _positionAvailable;
}


IoT::Devices::LatLon SimulatedGNSSSensor::position() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _position;
}


double SimulatedGNSSSensor::course() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _course;
}


double SimulatedGNSSSensor::speed() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _speed;
}


double SimulatedGNSSSensor::magneticVariation() const
{
	return -1;
}


double SimulatedGNSSSensor::altitude() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return _altitude;
}


double SimulatedGNSSSensor::hdop() const
{
	return -9999;
}


Poco::Any SimulatedGNSSSensor::getName(const std::string&) const
{
	return NAME;
}


Poco::Any SimulatedGNSSSensor::getType(const std::string&) const
{
	return TYPE;
}


Poco::Any SimulatedGNSSSensor::getSymbolicName(const std::string&) const
{
	return SYMBOLIC_NAME;
}


Poco::Any SimulatedGNSSSensor::getGPXPath(const std::string&) const
{
	return _gpxPath;
}


Poco::Any SimulatedGNSSSensor::getPositionChangedPeriod(const std::string&) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return Poco::Any(_period);
}


void SimulatedGNSSSensor::setPositionChangedPeriod(const std::string&, const Poco::Any& value)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_period = Poco::AnyCast<int>(value);
}


Poco::Any SimulatedGNSSSensor::getPositionChangedDelta(const std::string&) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return Poco::Any(_delta);
}


void SimulatedGNSSSensor::setPositionChangedDelta(const std::string&, const Poco::Any& value)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_delta = Poco::AnyCast<double>(value);
}


Poco::Any SimulatedGNSSSensor::getPositionTimeout(const std::string&) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	return Poco::Any(_timeout);
}


void SimulatedGNSSSensor::setPositionTimeout(const std::string&, const Poco::Any& value)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_timeout = Poco::AnyCast<int>(value);
}


Poco::Any SimulatedGNSSSensor::getDisplayValue(const std::string&) const
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


void SimulatedGNSSSensor::updatePosition(const Poco::Geo::LatLon& latLon, double altitude)
{
	if (_logger.debug())
	{
		_logger.debug(Poco::format("Updating position to lat=%f, lon=%f, alt=%f",
			latLon.latitude().degrees(), 
			latLon.longitude().degrees(),
			altitude));
	}
	
	IoT::Devices::PositionUpdate event;
	IoT::Devices::LatLon lastPosition;
	double delta = 0;
	double period = 0;
	double distance = 0;
	Poco::Geo::LatLon lastLatLon;
	{
		Poco::FastMutex::ScopedLock lock(_mutex);
		
		delta = _delta;
		period = _period;
		
		double diffSecs = static_cast<double>(_lastValidPosition.elapsed())/Poco::Timestamp::resolution();

		_lastValidPosition.update();
		_positionAvailable = true;
		
		lastPosition = _position;

		lastLatLon.assign(
			Poco::Geo::Angle::fromDegrees(lastPosition.latitude), 
			Poco::Geo::Angle::fromDegrees(lastPosition.longitude));

		Poco::Geo::Angle gcd = lastLatLon.greatCircleDistanceTo(latLon);
		distance = gcd.radians()*Poco::Geo::LatLon::EARTH_MEAN_RADIUS;

		_position.latitude = latLon.latitude().degrees();
		_position.longitude = latLon.longitude().degrees();
		_altitude = altitude;
		_course = Poco::Geo::Angle::normalizedDegrees(lastLatLon.greatCircleAzimuthTo(latLon).degrees());
		_speed = diffSecs > 0 ? distance/diffSecs*1.943844 : _speed; // m/s to kt
	}
	
	try
	{
		if (_lastPositionUpdate.isElapsed(1000*Poco::Timestamp::TimeVal(period)))
		{
			bool needUpdate = delta == 0;
			if (!needUpdate)
			{
				needUpdate = distance >= delta;
			}
			if (needUpdate)
			{
				_lastPositionUpdate.update();
	
				event.position = _position;
				event.course   = _course;
				event.speed    = _speed;
				event.magneticVariation = -1;
				event.timestamp.update();

				positionUpdate(this, event);
			}
		}
	}
	catch (Poco::Exception& exc)
	{
		_logger.log(exc);
	}
}


void SimulatedGNSSSensor::loadGPX(const std::string& path)
{
	_logger.information("Loading GNSS track from GPX file: " + path);

	GPXHandler gpxHandler(*this);

	Poco::XML::SAXParser parser;
	parser.setFeature(Poco::XML::XMLReader::FEATURE_NAMESPACES, true);
	parser.setFeature(Poco::XML::XMLReader::FEATURE_NAMESPACE_PREFIXES, true);
	parser.setContentHandler(&gpxHandler);
	
	parser.parse(path);
	
	if (_loopReplay)
	{
		_timer.schedule(new LoadGPX(*this, path), gpxHandler.endClock());
	}
}


} } // namespace IoT::Simulation
