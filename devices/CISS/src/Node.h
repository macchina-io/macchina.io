//
// Node.h
//
// Definition of the Node class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_CISS_Node_INCLUDED
#define IoT_CISS_Node_INCLUDED


#include "Sensor.h"
#include "Accelerometer.h"
#include "Magnetometer.h"
#include "Gyroscope.h"
#include "Poco/Serial/SerialPort.h"
#include "Poco/SharedPtr.h"
#include "Poco/Thread.h"
#include "Poco/Runnable.h"
#include "Poco/Event.h"


namespace IoT {
namespace CISS {


class NPIFrame;
class NPIPort;


class Node: public Poco::Runnable
	/// This class implements communication with a CISS node.
{
public:
	enum
	{
		CISS_INVALID               = 0x00,
		CISS_OK                    = 0x01,
		CISS_NOK                   = 0xFF,
		CISS_STREAM_ACCELEROMETER  = 0x02,
		CISS_STREAM_MAGNETOMETER   = 0x03,
		CISS_STREAM_GYROSCOPE      = 0x04,
		CISS_STREAM_TEMPERATURE    = 0x05,
		CISS_STREAM_PRESSURE       = 0x06,
		CISS_STREAM_HUMIDITY       = 0x07,
		CISS_STREAM_LIGHT          = 0x08,
		CISS_STREAM_NOISE          = 0x09,
		CISS_SENSOR_ACCELEROMETER  = 0x80,
		CISS_SENSOR_MAGNETOMETER   = 0x81,
		CISS_SENSOR_GYROSCOPE      = 0x82,
		CISS_SENSOR_ENVIRONMENTAL  = 0x83,
		CISS_SENSOR_LIGHT          = 0x84,
		CISS_SENSOR_NOISE          = 0x85
	};

	enum
	{
		CISS_COMMAND_TIMEOUT = 5000
	};

	Node(const std::string& id, Poco::SharedPtr<NPIPort> pPort);
		/// Creates a Node using the given ID and NPIPort.

	~Node();
		/// Destroys the Node.

	const std::string& id() const;
		/// Returns the node ID.

	void enableSensor(Poco::UInt8 sensorId, bool enable);
		/// Enables or disables the sensor with the given ID
		/// (0x80 = Accelerometer, 0x81 = Magnetometer, 0x82 = Gyroscope)

	void enableEnvironmentalSensor(Poco::UInt8 sensorId, Poco::UInt8 streamId, bool enable);
		/// Enables or disables the environmental sensor with the given ID.
		/// If at least one environmental sensor is enabled, powers-on the
		/// environmental sensor on the CISS. If all environmental sensors
		/// are disabled, powers off the environmental sensor on the CISS.
		///
		/// The given sensorId should be 0x83 or 0x84.
		/// If sensorId is 0x83, streamId should be 0x05 for temperature,
		/// 0x06 for pressure, or 0x07 for humidity. If sensorId is other
		/// than 0x83, streamId is ignored.

	void setSamplingInterval(Poco::UInt8 sensorId, Poco::UInt32 interval);
		/// Sets the sampling interval in milliseconds; an interval of 0
		/// disables sampling.

	void setEnvironmentalSamplingInterval(Poco::UInt8 sensorId, Poco::UInt16 interval);
		/// Sets the sampling interval in milliseconds for environmental sensors;
		/// an interval of 0 disables sampling.

	void setAccelerometerRange(Poco::UInt8 rangeInGs);
		/// Sets the accelerometer range in G's.

	Poco::SharedPtr<Sensor> temperature() const;
		/// Returns the temperature sensor.

	Poco::SharedPtr<Sensor> humidity() const;
		/// Returns the humidity sensor.

	Poco::SharedPtr<Sensor> pressure() const;
		/// Returns the pressure sensor.

	Poco::SharedPtr<Sensor> light() const;
		/// Returns the light sensor.

	Poco::SharedPtr<Accelerometer> accelerometer() const;
		/// Returns the Accelerometer.

	Poco::SharedPtr<Magnetometer> magnetometer() const;
		/// Returns the Magnetometer.

	Poco::SharedPtr<Gyroscope> gyroscope() const;
		/// Returns the Gyroscope.

protected:
	void enableSensorImpl(Poco::UInt8 sensorId, bool enable);
	void resetStreams();
	void handleFrame(const NPIFrame& frame);
	void run();
	void start();
	void stop();

private:
	std::string _id;
	Poco::SharedPtr<NPIPort> _pPort;
	Poco::Thread _thread;
	bool _stopped;
	int _environmentalEnabled;
	bool _lastCommandOK;
	Poco::Event _responseReceived;
	Poco::SharedPtr<Sensor> _pTemperature;
	Poco::SharedPtr<Sensor> _pHumidity;
	Poco::SharedPtr<Sensor> _pPressure;
	Poco::SharedPtr<Sensor> _pLight;
	Poco::SharedPtr<Sensor> _pNoise;
	Poco::SharedPtr<Accelerometer> _pAccelerometer;
	Poco::SharedPtr<Magnetometer> _pMagnetometer;
	Poco::SharedPtr<Gyroscope> _pGyroscope;
	Poco::Logger& _logger;
	mutable Poco::FastMutex _mutex;
};


//
// inlines
//


inline const std::string& Node::id() const
{
	return _id;
}


inline Poco::SharedPtr<Sensor> Node::temperature() const
{
	return _pTemperature;
}


inline Poco::SharedPtr<Sensor> Node::humidity() const
{
	return _pHumidity;
}


inline Poco::SharedPtr<Sensor> Node::pressure() const
{
	return _pPressure;
}


inline Poco::SharedPtr<Sensor> Node::light() const
{
	return _pLight;
}


inline Poco::SharedPtr<Accelerometer> Node::accelerometer() const
{
	return _pAccelerometer;
}


inline Poco::SharedPtr<Magnetometer> Node::magnetometer() const
{
	return _pMagnetometer;
}


inline Poco::SharedPtr<Gyroscope> Node::gyroscope() const
{
	return _pGyroscope;
}


} } // namespace IoT::CISS


#endif // IoT_CISS_Node_INCLUDED
