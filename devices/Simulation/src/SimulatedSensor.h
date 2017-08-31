//
// SimulatedSensor.h
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Simulation_SimulatedSensor_INCLUDED
#define IoT_Simulation_SimulatedSensor_INCLUDED


#include "IoT/Devices/Sensor.h"
#include "IoT/Devices/DeviceImpl.h"
#include "IoT/Devices/EventModerationPolicy.h"
#include "Poco/Util/Timer.h"


namespace IoT {
namespace Simulation {


class SimulatedSensor: public IoT::Devices::DeviceImpl<IoT::Devices::Sensor, SimulatedSensor>
{
public:
	enum Mode
	{
		SIM_LINEAR, /// linear function
		SIM_RANDOM  /// random function
	};
	
	struct Params
	{
		std::string id;
			/// The ID of the sensor.

		std::string physicalQuantity;
			/// The physical quantity the sensor measures.
		
		std::string physicalUnit;
			/// The physical unit used.

		double initialValue; 
			/// Initial sensor value.

		double delta;
			/// For linear mode, this value is added in each step.
			/// For random mode, a random number in this range will be
			/// generated and added to the current value.

		int cycles;
			/// The number of cycles after which the value is reset
			/// to the initial value.

		double updateRate;
			/// The rate at which the sensor value is updated (updates/sec.).
			
		Mode mode;
			/// Mode - linear or random.
	};
	
	SimulatedSensor(const Params& params, Poco::Util::Timer& timer);
		/// Creates a SimulatedSensor.
		
	~SimulatedSensor();
		/// Destroys the SimulatedSensor.
	
	// Sensor
	double value() const;
	bool ready() const;

	static const std::string NAME;
	static const std::string TYPE;
	static const std::string SYMBOLIC_NAME;

protected:
	Poco::Any getValueChangedPeriod(const std::string&) const;
	void setValueChangedPeriod(const std::string&, const Poco::Any& value);
	Poco::Any getValueChangedDelta(const std::string&) const;
	void setValueChangedDelta(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;
	Poco::Any getDeviceIdentifier(const std::string&) const;
	Poco::Any getName(const std::string&) const;
	Poco::Any getType(const std::string&) const;
	Poco::Any getSymbolicName(const std::string&) const;
	Poco::Any getPhysicalQuantity(const std::string&) const;
	Poco::Any getPhysicalUnit(const std::string&) const;
	void update(double value);

private:
	double _value;
	int _valueChangedPeriod;
	double _valueChangedDelta;
	Poco::SharedPtr<IoT::Devices::EventModerationPolicy<double> > _pEventPolicy;
	Poco::Any _deviceIdentifier;
	Poco::Any _symbolicName;
	Poco::Any _name;
	Poco::Any _physicalQuantity;
	Poco::Any _physicalUnit;
	Poco::Util::Timer& _timer;
	
	friend class LinearUpdateTimerTask;
	friend class RandomUpdateTimerTask;
};


} } // namespace IoT::Simulation


#endif // IoT_Simulation_SimulatedSensor_INCLUDED
