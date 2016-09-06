//
// DCMotor.cpp
//
// $Id$
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "DCMotor.h"
#include "MasterConnectionImpl.h"
#include "Poco/Format.h"


namespace IoT {
namespace Tf {


DCMotor::DCMotor(MasterConnection::Ptr pMasterConn, const std::string& uid):
	BrickletType("io.macchina.tf.dc", "Tinkerforge DC Brick")
{
	addProperty("displayState", &DCMotor::getDisplayState);
	addProperty("targetVelocity", &DCMotor::getTargetVelocity, &DCMotor::setTargetVelocity);
	addProperty("velocity", &DCMotor::getVelocity);
	addProperty("acceleration", &DCMotor::getAcceleration, &DCMotor::setAcceleration);
	addProperty("frequency", &DCMotor::getFrequency, &DCMotor::setFrequency);
	addProperty("driveMode", &DCMotor::getDriveMode, &DCMotor::setDriveMode);
	addProperty("current", &DCMotor::getCurrent);
	addProperty("externalVoltage", &DCMotor::getExternalVoltage);
	addProperty("internalVoltage", &DCMotor::getInternalVoltage);

	IPConnection *ipcon = pMasterConn.cast<MasterConnectionImpl>()->ipcon();
	dc_create(&_dc, uid.c_str(), ipcon);
	
	char deviceUID[8];
	char masterUID[8];
	char position;
	Poco::UInt8 hardwareVersion[3];
	Poco::UInt8 firmwareVersion[3];
	Poco::UInt16 deviceType;
	if (dc_get_identity(&_dc, deviceUID, masterUID, &position, hardwareVersion, firmwareVersion, &deviceType) == E_OK)
	{
		setIdentity(deviceUID, masterUID, position, hardwareVersion, firmwareVersion, deviceType);
	}
}

	
DCMotor::~DCMotor()
{
	dc_disable(&_dc);
	dc_destroy(&_dc);
}


bool DCMotor::state() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	bool value;
	int rc = dc_is_enabled(&_dc, &value);
	if (rc == E_OK)
	{
		return value;
	}
	else throw Poco::IOException();
}


bool DCMotor::getTargetState() const
{
	return state();
}


void DCMotor::setTargetState(bool newState)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	bool oldState = !newState;
	dc_is_enabled(&_dc, &oldState);

	if (newState)
		dc_enable(&_dc);
	else
		dc_disable(&_dc);
		
	if (oldState != newState)
	{
		try
		{
			stateChanged(newState);	
		}
		catch (...)
		{
		}
	}
}


Poco::Any DCMotor::getDisplayState(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	bool enabled;
	dc_is_enabled(&_dc, &enabled);

	Poco::Int16 velocity;
	dc_get_current_velocity(&_dc, &velocity);

	Poco::UInt16 current;
	dc_get_current_consumption(&_dc, &current);

	if (enabled)
		return Poco::format("on, velocity: %hd, current: %hu mA", velocity, current);
	else
		return std::string("off");
}


Poco::Any DCMotor::getTargetVelocity(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::Int16 velocity;
	dc_get_velocity(&_dc, &velocity);
	return Poco::Any(static_cast<int>(velocity));
}


void DCMotor::setTargetVelocity(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::Int16 velocity = static_cast<Poco::Int16>(Poco::AnyCast<int>(value));
	dc_set_velocity(&_dc, velocity);
}


Poco::Any DCMotor::getVelocity(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::Int16 velocity;
	dc_get_current_velocity(&_dc, &velocity);
	return Poco::Any(static_cast<int>(velocity));
}


Poco::Any DCMotor::getAcceleration(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt16 acceleration;
	dc_get_acceleration(&_dc, &acceleration);
	return Poco::Any(static_cast<int>(acceleration));
}


void DCMotor::setAcceleration(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt16 acceleration = static_cast<Poco::UInt16>(Poco::AnyCast<int>(value));
	dc_set_acceleration(&_dc, acceleration);
}


Poco::Any DCMotor::getFrequency(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt16 frequency;
	dc_get_pwm_frequency(&_dc, &frequency);
	return Poco::Any(static_cast<int>(frequency));
}


void DCMotor::setFrequency(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt16 frequency = static_cast<Poco::UInt16>(Poco::AnyCast<int>(value));
	dc_set_pwm_frequency(&_dc, frequency);
}


Poco::Any DCMotor::getDriveMode(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt8 mode;
	dc_get_drive_mode(&_dc, &mode);
	return Poco::Any(static_cast<int>(mode));
}


void DCMotor::setDriveMode(const std::string&, const Poco::Any& value)
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt8 mode = static_cast<Poco::UInt8>(Poco::AnyCast<int>(value));
	dc_set_drive_mode(&_dc, mode);
}


Poco::Any DCMotor::getCurrent(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt16 current;
	dc_get_current_consumption(&_dc, &current);
	return Poco::Any(static_cast<int>(current));
}


Poco::Any DCMotor::getExternalVoltage(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt16 voltage;
	dc_get_external_input_voltage(&_dc, &voltage);
	return Poco::Any(static_cast<int>(voltage));
}


Poco::Any DCMotor::getInternalVoltage(const std::string&) const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt16 voltage;
	dc_get_stack_input_voltage(&_dc, &voltage);
	return Poco::Any(static_cast<int>(voltage));
}


} } // namespace IoT::Tf
