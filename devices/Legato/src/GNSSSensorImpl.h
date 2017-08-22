//
// GNSSSensorImpl.h
//
// $Id$
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Legato_GNSSSensorImpl_INCLUDED
#define IoT_Legato_GNSSSensorImpl_INCLUDED


#include "IoT/Devices/GNSSSensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/Serial/SerialPort.h"
#include "IoT/GNSS/NMEA/RMCProcessor.h"
#include "IoT/GNSS/NMEA/GGAProcessor.h"
#include "Poco/Timestamp.h"
#include "Poco/Thread.h"
#include "Poco/Mutex.h"
#include "Poco/Logger.h"


namespace IoT {
namespace Legato {


class GNSSSensorImpl: public IoT::Devices::DeviceImpl<IoT::Devices::GNSSSensor, GNSSSensorImpl>, public Poco::Runnable
{
public:
	GNSSSensorImpl();
		/// Creates a GNSSSensorImpl.
		
	~GNSSSensorImpl();
		/// Destroys the GNSSSensorImpl.
	
	// GNSSSensor
	bool positionAvailable() const;
	IoT::Devices::LatLon position() const;
	double course() const;
	double speed() const;
	double magneticVariation() const;
	double altitude() const;
	double hdop() const;

protected:
	Poco::Any getName(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getPositionChangedPeriod(const std::string&) const;
	void setPositionChangedPeriod(const std::string&, const Poco::Any& value);
	Poco::Any getPositionChangedDelta(const std::string&) const;
	void setPositionChangedDelta(const std::string&, const Poco::Any& value);
	Poco::Any getPositionTimeout(const std::string&) const;
	void setPositionTimeout(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;

	void run();
	void stop();
	bool done();
	void onRMCReceived(const IoT::GNSS::NMEA::RMCProcessor::RMC& rmc);
	void onGGAReceived(const IoT::GNSS::NMEA::GGAProcessor::GGA& gga);
	
	int poll(const Poco::Timespan& timeout);

	static const std::string NAME;
	static const std::string SYMBOLIC_NAME;
	static const std::string PATH;

private:
	int _fd;
	Poco::Buffer<char> _buffer;
	Poco::Timestamp _lastValidPosition;
	Poco::Timestamp _lastPositionUpdate;
	bool _positionAvailable;
	IoT::Devices::LatLon _position;
	double _course;
	double _speed;
	double _magneticVariation;
	double _altitude;
	double _hdop;
	int _period;
	double _delta;
	int _timeout;
	bool _done;
	Poco::Thread _thread;
	Poco::Logger& _logger;
	mutable Poco::FastMutex _mutex;
};


} } // namespace IoT::Legato


#endif // IoT_Legato_GNSSSensorImpl_INCLUDED
