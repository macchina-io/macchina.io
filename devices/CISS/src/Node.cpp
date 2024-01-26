//
// Node.cpp
//
// Definition of the Node class.
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Node.h"
#include "NPIPort.h"
#include "NPIFrame.h"
#include "Poco/MemoryStream.h"
#include "Poco/BinaryWriter.h"
#include "Poco/BinaryReader.h"


using namespace std::string_literals;


namespace IoT {
namespace CISS {


Node::Node(const std::string& id, Poco::SharedPtr<NPIPort> pPort):
	_id(id),
	_pPort(pPort),
	_stopped(false),
	_environmentalEnabled(0),
	_lastCommandOK(false),
	_logger(Poco::Logger::get("IoT.CISS.Node"s))
{
	_pTemperature   = new Sensor(*this, CISS_SENSOR_ENVIRONMENTAL, CISS_STREAM_TEMPERATURE, "temperature"s, IoT::Devices::Sensor::PHYSICAL_UNIT_DEGREES_CELSIUS, "CISS Temperature Sensor"s);
	_pHumidity      = new Sensor(*this, CISS_SENSOR_ENVIRONMENTAL, CISS_STREAM_HUMIDITY, "humidity"s, "%"s, "CISS Humidity Sensor"s);
	_pPressure      = new Sensor(*this, CISS_SENSOR_ENVIRONMENTAL, CISS_STREAM_PRESSURE, "airPressure"s, "hPa"s, "CISS Air Pressure Sensor"s);
	_pLight         = new Sensor(*this, CISS_SENSOR_LIGHT, CISS_STREAM_LIGHT, "illuminance"s, IoT::Devices::Sensor::PHYSICAL_UNIT_LUX, "CISS Light Sensor"s);
	_pAccelerometer = new Accelerometer(*this);
	_pMagnetometer  = new Magnetometer(*this);
	_pGyroscope     = new Gyroscope(*this);

	start();

	try
	{
		resetStreams();
	}
	catch (Poco::Exception&)
	{
	}
}


Node::~Node()
{
	try
	{
		resetStreams();
	}
	catch (...)
	{
	}

	try
	{
		stop();
	}
	catch (...)
	{
	}
}


void Node::resetStreams()
{
	enableSensor(CISS_SENSOR_ACCELEROMETER, false);
	enableSensor(CISS_SENSOR_MAGNETOMETER, false);
	enableSensor(CISS_SENSOR_GYROSCOPE, false);
	enableSensor(CISS_SENSOR_ENVIRONMENTAL, false);
	enableSensor(CISS_SENSOR_LIGHT, false);
}


void Node::enableSensorImpl(Poco::UInt8 sensorId, bool enable)
{
	char payload[2] =
	{
		static_cast<char>(sensorId),
		static_cast<char>(enable)
	};
	NPIFrame frame(payload, 2);

	_pPort->sendFrame(frame);
	_responseReceived.wait(CISS_COMMAND_TIMEOUT);
	if (!_lastCommandOK) throw Poco::IOException("Failed to enable sensor"s);
}


void Node::enableSensor(Poco::UInt8 sensorId, bool enable)
{
	if (_logger.debug())
	{
		if (enable)
			_logger.debug("Enabling sensor 0x%02x."s, static_cast<unsigned>(sensorId));
		else
			_logger.debug("Disabling sensor 0x%02x."s, static_cast<unsigned>(sensorId));
	}

	Poco::FastMutex::ScopedLock lock(_mutex);
	enableSensorImpl(sensorId, enable);
}


void Node::enableEnvironmentalSensor(Poco::UInt8 sensorId, Poco::UInt8 streamId, bool enable)
{
	if (_logger.debug())
	{
		if (enable)
			_logger.debug("Enabling environmental sensor 0x%02x/0x%02x."s, static_cast<unsigned>(sensorId), static_cast<unsigned>(streamId));
		else
			_logger.debug("Disabling environmental sensor 0x%02x/0x%02x."s, static_cast<unsigned>(sensorId), static_cast<unsigned>(streamId));
	}

	Poco::FastMutex::ScopedLock lock(_mutex);

	if (sensorId == CISS_SENSOR_ENVIRONMENTAL)
	{
		bool isEnabled = _environmentalEnabled != 0;
		int bit = 1 << streamId;

		if (enable)
			_environmentalEnabled |= bit;
		else
			_environmentalEnabled &= ~bit;

		if (isEnabled != (_environmentalEnabled != 0))
		{
			enableSensorImpl(sensorId, !isEnabled);
		}
	}
	else
	{
		enableSensorImpl(sensorId, enable);
	}
}


void Node::setSamplingInterval(Poco::UInt8 sensorId, Poco::UInt32 interval)
{
	if (_logger.debug())
	{
		_logger.debug("Setting inertial sampling interval to %u ms."s, interval);
	}

	char payload[6];
	Poco::MemoryOutputStream ostr(payload, sizeof(payload));
	Poco::BinaryWriter writer(ostr, Poco::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);

	writer << sensorId << static_cast<Poco::UInt8>(0x02) << interval;
	NPIFrame frame(payload, sizeof(payload));

	Poco::FastMutex::ScopedLock lock(_mutex);
	_pPort->sendFrame(frame);
	_responseReceived.wait(CISS_COMMAND_TIMEOUT);
	if (!_lastCommandOK) throw Poco::IOException("Failed to set sampling interval"s);
}


void Node::setEnvironmentalSamplingInterval(Poco::UInt8 sensorId, Poco::UInt16 interval)
{
	if (_logger.debug())
	{
		_logger.debug("Setting environmental sampling interval to %hu ms."s, interval);
	}

	char payload[4];
	Poco::MemoryOutputStream ostr(payload, sizeof(payload));
	Poco::BinaryWriter writer(ostr, Poco::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);

	writer << sensorId << static_cast<Poco::UInt8>(0x02) << static_cast<Poco::UInt16>(interval/1000);
	NPIFrame frame(payload, sizeof(payload));

	Poco::FastMutex::ScopedLock lock(_mutex);
	_pPort->sendFrame(frame);
	_responseReceived.wait(CISS_COMMAND_TIMEOUT);
	if (!_lastCommandOK) throw Poco::IOException("Failed to set sampling interval"s);
}


void Node::setAccelerometerRange(Poco::UInt8 rangeInGs)
{
	if (_logger.debug())
	{
		_logger.debug("Setting accelerometer range to %u G."s, static_cast<unsigned>(rangeInGs));
	}

	if (rangeInGs != 2 && rangeInGs != 4 && rangeInGs != 8 && rangeInGs != 16)
		throw Poco::InvalidArgumentException("Accelerometer range must be 2,4,8 or 16"s);

	char payload[6];
	Poco::MemoryOutputStream ostr(payload, sizeof(payload));
	Poco::BinaryWriter writer(ostr, Poco::BinaryWriter::LITTLE_ENDIAN_BYTE_ORDER);

	writer << static_cast<Poco::UInt8>(CISS_SENSOR_ACCELEROMETER) << static_cast<Poco::UInt8>(0x04) << rangeInGs;
	NPIFrame frame(payload, sizeof(payload));

	Poco::FastMutex::ScopedLock lock(_mutex);
	_pPort->sendFrame(frame);
	_responseReceived.wait(CISS_COMMAND_TIMEOUT);
	if (!_lastCommandOK) throw Poco::IOException("Failed to set accelerometer range"s);
}


void Node::handleFrame(const NPIFrame& frame)
{
	Poco::MemoryInputStream istr(frame.payload(), frame.payloadSize());
	Poco::BinaryReader reader(istr, Poco::BinaryReader::LITTLE_ENDIAN_BYTE_ORDER);
	bool done = false;
	Poco::UInt8 type;
	reader >> type;
	while (!istr.eof() && !done)
	{
		switch (type)
		{
		case CISS_OK:
			_logger.debug("Last command OK."s);
			_lastCommandOK = true;
			_responseReceived.set();
			done = true;
			break;

		case CISS_NOK:
			_logger.error("Last command failed."s);
			_lastCommandOK = false;
			_responseReceived.set();
			done = true;
			break;

		case CISS_STREAM_ACCELEROMETER:
			{
				IoT::Devices::Acceleration acc;
				Poco::Int16 x, y, z;
				reader >> x >> y >> z;
				acc.x = x/1000.0;
				acc.y = y/1000.0;
				acc.z = z/1000.0;
				_pAccelerometer->update(acc);
			}
			break;

		case CISS_STREAM_MAGNETOMETER:
			{
				IoT::Devices::MagneticFieldStrength field;
				Poco::Int16 x, y, z;
				reader >> x >> y >> z;
				field.x = x/1000.0;
				field.y = y/1000.0;
				field.z = z/1000.0;
				field.r = 0;
				_pMagnetometer->update(field);
			}
			break;

		case CISS_STREAM_GYROSCOPE:
			{
				IoT::Devices::Rotation rot;
				Poco::Int16 x, y, z;
				reader >> x >> y >> z;
				rot.x = x;
				rot.y = y;
				rot.z = z;
				_pGyroscope->update(rot);
			}
			break;

		case CISS_STREAM_TEMPERATURE:
			{
				Poco::Int16 value;
				reader >> value;
				_pTemperature->update(value/10.0);
			}
			break;

		case CISS_STREAM_PRESSURE:
			{
				Poco::UInt32 value;
				reader >> value;
				_pPressure->update(value/100.0);
			}
			break;

		case CISS_STREAM_HUMIDITY:
			{
				Poco::UInt16 value;
				reader >> value;
				_pHumidity->update(value/100.0);
			}
			break;

		case CISS_STREAM_LIGHT:
			{
				Poco::UInt32 value;
				reader >> value;
				_pLight->update(value);
			}
			break;

		default:
			_logger.warning("Invalid payload received (type=0x%x, length=%z).",
				static_cast<unsigned>(frame.type()), frame.frameSize());
			break;
		}
		reader >> type;
	}
}


void Node::run()
{
	while (!_stopped)
	{
		try
		{
			if (_pPort->poll(200000))
			{
				NPIFrame frame;
				if (_pPort->receiveFrame(frame, Poco::Timespan(200000)))
				{
					if (_logger.debug())
					{
						_logger.debug("NPI frame received (type=0x%x, length=%z)"s,
							static_cast<unsigned>(frame.type()), frame.frameSize());
					}
					handleFrame(frame);
				}
			}
		}
		catch (Poco::Exception& exc)
		{
			_logger.log(exc);
		}
	}
}


void Node::start()
{
	_stopped = false;
	_thread.start(*this);
}


void Node::stop()
{
	if (!_stopped)
	{
		_stopped = true;
		_thread.join();
	}
}


} } // namespace IoT::CISS
