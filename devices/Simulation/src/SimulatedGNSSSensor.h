//
// SimulatedGNSSSensor.h
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Simulation_SimulatedGNSSSensor_INCLUDED
#define IoT_Simulation_SimulatedGNSSSensor_INCLUDED


#include "IoT/Devices/GNSSSensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "Poco/Geo/LatLon.h"
#include "Poco/Util/Timer.h"
#include "Poco/Timestamp.h"
#include "Poco/Mutex.h"
#include "Poco/Logger.h"


namespace IoT {
namespace Simulation {


class SimulatedGNSSSensor: public IoT::Devices::DeviceImpl<IoT::Devices::GNSSSensor, SimulatedGNSSSensor>
{
public:
	struct Params
	{
		std::string id;
			/// The ID of the sensor.

		std::string gpxPath;
			/// Path to the GPX file containing replay data.
			
		double speedUp;
			/// Replay speed-up factor.

		bool loopReplay;
			/// Loop replay of GPX file.
	};
	
	SimulatedGNSSSensor(const Params& params);
		/// Creates a SimulatedGNSSSensor.
		
	~SimulatedGNSSSensor();
		/// Destroys the SimulatedGNSSSensor.
	
	// GNSSSensor
	bool positionAvailable() const;
	IoT::Devices::LatLon position() const;
	double course() const;
	double speed() const;
	double magneticVariation() const;
	double altitude() const;
	double hdop() const;
	
	static const std::string NAME;
	static const std::string SYMBOLIC_NAME;

protected:
	Poco::Any getName(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getGPXPath(const std::string&) const;
	Poco::Any getPositionChangedPeriod(const std::string&) const;
	void setPositionChangedPeriod(const std::string&, const Poco::Any& value);
	Poco::Any getPositionChangedDelta(const std::string&) const;
	void setPositionChangedDelta(const std::string&, const Poco::Any& value);
	Poco::Any getPositionTimeout(const std::string&) const;
	void setPositionTimeout(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;

	void stop();
	bool done();
	void updatePosition(const Poco::Geo::LatLon& latLon, double altitude);
	void loadGPX(const std::string& path);

private:
	std::string _gpxPath;
	bool _loopReplay;
	double _speedUp;
	Poco::Timestamp _lastValidPosition;
	Poco::Timestamp _lastPositionUpdate;
	bool _positionAvailable;
	IoT::Devices::LatLon _position;
	double _course;
	double _speed;
	double _altitude;
	int _period;
	double _delta;
	int _timeout;
	Poco::Util::Timer _timer;
	Poco::Logger& _logger;
	mutable Poco::FastMutex _mutex;
	
	friend class PositionUpdate;
	friend class LoadGPX;
	friend class GPXHandler;
};


} } // namespace IoT::Simulation


#endif // IoT_Simulation_SimulatedGNSSSensor_INCLUDED
