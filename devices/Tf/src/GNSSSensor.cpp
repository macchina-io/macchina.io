//
// GNSSSensor.cpp
//
// $Id: //iot/Main/Tf/src/GNSSSensor.cpp#2 $
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "GNSSSensor.h"
#include "MasterConnectionImpl.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"


namespace IoT {
namespace Tf {


GNSSSensor::GNSSSensor(MasterConnection::Ptr pMasterConn, const std::string& uid):
	BrickletType("io.macchina.tf.gnss", "Tinkerforge GPS Bricklet", ""),
	_positionAvailable(false)
{
	addProperty("displayValue", &GNSSSensor::getDisplayValue);
	addProperty("positionChangedPeriod", &GNSSSensor::getPositionChangedPeriod, &GNSSSensor::setPositionChangedPeriod);
	addProperty("positionChangedDelta", &GNSSSensor::getPositionChangedDelta, &GNSSSensor::setPositionChangedDelta);

	IPConnection *ipcon = pMasterConn.cast<MasterConnectionImpl>()->ipcon();
	gps_create(&_gps, uid.c_str(), ipcon);
	
	char deviceUID[8];
	char masterUID[8];
	char position;
	Poco::UInt8 hardwareVersion[3];
	Poco::UInt8 firmwareVersion[3];
	Poco::UInt16 deviceType;
	if (gps_get_identity(&_gps, deviceUID, masterUID, &position, hardwareVersion, firmwareVersion, &deviceType) == E_OK)
	{
		setIdentity(deviceUID, masterUID, position, hardwareVersion, firmwareVersion, deviceType);
	}
	
	gps_register_callback(&_gps, GPS_CALLBACK_COORDINATES, reinterpret_cast<void*>(onPositionChanged), this);
	gps_set_coordinates_callback_period(&_gps, 1000);

	gps_register_callback(&_gps, GPS_CALLBACK_STATUS, reinterpret_cast<void*>(onStatusChanged), this);
	gps_set_status_callback_period(&_gps, 10000);
}

	
GNSSSensor::~GNSSSensor()
{
	gps_destroy(&_gps);
}


bool GNSSSensor::positionAvailable() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt8 fix;
	Poco::UInt8 nSatsInView;
	Poco::UInt8 nSatsUsed;
	int rc = gps_get_status(&_gps, &fix, &nSatsInView, &nSatsUsed);
	if (rc == E_OK)
	{
		return fix >= GPS_FIX_2D_FIX;
	}
	else return false;
}


IoT::Devices::LatLon GNSSSensor::position() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt32 lat;
	Poco::UInt32 lon;
	char ns;
	char ew;
	Poco::UInt16 pdop;
	Poco::UInt16 hdop;
	Poco::UInt16 vdop;
	Poco::UInt16 epe;
	
	int rc = gps_get_coordinates(&_gps, &lat, &ns, &lon, &ew, &pdop, &hdop, &vdop, &epe);
	if (rc == E_OK)
	{
		IoT::Devices::LatLon latLon;
		latLon.latitude = lat/1000000.0;
		latLon.longitude = lon/1000000.0;
		if (ns == 'S') latLon.latitude = -latLon.latitude;
		if (ew == 'W') latLon.longitude = -latLon.longitude;
		return latLon;
	}
	else throw Poco::IOException("Cannot obtain position");
}


double GNSSSensor::course() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt32 course;
	Poco::UInt32 speed;
	int rc = gps_get_motion(&_gps, &course, &speed);
	if (rc == E_OK)
	{
		return course/100.0;
	}
	else return -1;
}


double GNSSSensor::speed() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt32 course;
	Poco::UInt32 speed;
	int rc = gps_get_motion(&_gps, &course, &speed);
	if (rc == E_OK)
	{
		return 0.539956803*speed/100.0; // km/h/100 to kn
	}
	else return -1;
}


double GNSSSensor::magneticVariation() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	return -1; // n/a
}


double GNSSSensor::altitude() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt8 fix;
	Poco::UInt8 nSatsInView;
	Poco::UInt8 nSatsUsed;
	int rc = gps_get_status(&_gps, &fix, &nSatsInView, &nSatsUsed);
	if (rc == E_OK && fix == GPS_FIX_3D_FIX)
	{
		Poco::UInt32 altitude;
		Poco::UInt32 geoidalSeparation;
		rc = gps_get_altitude(&_gps, &altitude, &geoidalSeparation);
		if (rc == E_OK)
		{
			return altitude/100.0;
		}
	}
	return -9999;
}


double GNSSSensor::hdop() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt32 lat;
	Poco::UInt32 lon;
	char ns;
	char ew;
	Poco::UInt16 pdop;
	Poco::UInt16 hdop;
	Poco::UInt16 vdop;
	Poco::UInt16 epe;
	
	int rc = gps_get_coordinates(&_gps, &lat, &ns, &lon, &ew, &pdop, &hdop, &vdop, &epe);
	if (rc == E_OK)
	{
		return epe/100.0;
	}
	return -9999;

}


Poco::Any GNSSSensor::getPositionChangedPeriod(const std::string&) const
{
	Poco::UInt32 uperiod;
	gps_get_coordinates_callback_period(&_gps, &uperiod);
	return Poco::Any(static_cast<int>(uperiod));
}


void GNSSSensor::setPositionChangedPeriod(const std::string&, const Poco::Any& value)
{
	Poco::UInt32 period = static_cast<Poco::UInt32>(Poco::AnyCast<int>(value));
	gps_set_coordinates_callback_period(&_gps, period);
}


Poco::Any GNSSSensor::getPositionChangedDelta(const std::string&) const
{
	// TODO
	return Poco::Any(0.0);
}


void GNSSSensor::setPositionChangedDelta(const std::string&, const Poco::Any& value)
{
	// TODO
}


Poco::Any GNSSSensor::getDisplayValue(const std::string&) const
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


void GNSSSensor::onPositionChanged(Poco::UInt32 latitude, char ns, Poco::UInt32 longitude, char ew,
	Poco::UInt16 pdop, Poco::UInt16 hdop, Poco::UInt16 vdop, Poco::UInt16 epe, void* userData)
{
	try
	{
		GNSSSensor* pThis = reinterpret_cast<GNSSSensor*>(userData);

		IoT::Devices::PositionUpdate positionUpdate;
		positionUpdate.position.latitude = latitude/1000000.0;
		positionUpdate.position.longitude = longitude/1000000.0;
		if (ns == 'S') positionUpdate.position.latitude = -positionUpdate.position.latitude;
		if (ew == 'W') positionUpdate.position.longitude = -positionUpdate.position.longitude;
		
		Poco::UInt32 course;
		Poco::UInt32 speed;
		int rc = gps_get_motion(&pThis->_gps, &course, &speed);
		if (rc == E_OK)
		{
			positionUpdate.course = course/100.0;
			positionUpdate.speed = 0.539956803*speed/100.0; // km/h/100 to kn
		}
		else
		{
			positionUpdate.course = -1;
			positionUpdate.speed = -1;
		}
		positionUpdate.magneticVariation = -1;

		pThis->_positionAvailable = true;		
		pThis->positionUpdate(positionUpdate);
	}
	catch (...)
	{
	}
}


void GNSSSensor::onStatusChanged(Poco::UInt8 fix, Poco::UInt8 satsInView, Poco::UInt8 satsUsed, void* userData)
{
	GNSSSensor* pThis = reinterpret_cast<GNSSSensor*>(userData);

	if (pThis->_positionAvailable && fix < GPS_FIX_2D_FIX)
	{
		try
		{
			pThis->_positionAvailable = false;
			pThis->positionLost();
		}
		catch (...)
		{
		}
	}
}


} } // namespace IoT::Tf
