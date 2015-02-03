//
// RotaryEncoder.cpp
//
// $Id: //iot/Main/Tf/src/RotaryEncoder.cpp#3 $
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "RotaryEncoder.h"
#include "MasterConnectionImpl.h"


namespace IoT {
namespace Tf {


RotaryEncoder::RotaryEncoder(MasterConnection::Ptr pMasterConn, const std::string& uid):
	BrickletType("com.iotframework.tf.rotaryencoder", "Tinkerforge Rotary Encoder Bricklet")
{
	addProperty("countChangedPeriod", &RotaryEncoder::getCountChangedPeriod, &RotaryEncoder::setCountChangedPeriod);
	
	IPConnection *ipcon = pMasterConn.cast<MasterConnectionImpl>()->ipcon();
	rotary_encoder_create(&_rotaryEncoder, uid.c_str(), ipcon);

	char deviceUID[8];
	char masterUID[8];
	char position;
	Poco::UInt8 hardwareVersion[3];
	Poco::UInt8 firmwareVersion[3];
	Poco::UInt16 deviceType;
	if (rotary_encoder_get_identity(&_rotaryEncoder, deviceUID, masterUID, &position, hardwareVersion, firmwareVersion, &deviceType) == E_OK)
	{
		setIdentity(deviceUID, masterUID, position, hardwareVersion, firmwareVersion, deviceType);
	}

	rotary_encoder_register_callback(&_rotaryEncoder, ROTARY_ENCODER_CALLBACK_COUNT, reinterpret_cast<void*>(onCountChanged), this);
	rotary_encoder_register_callback(&_rotaryEncoder, ROTARY_ENCODER_CALLBACK_PRESSED, reinterpret_cast<void*>(onButtonPressed), this);
	rotary_encoder_register_callback(&_rotaryEncoder, ROTARY_ENCODER_CALLBACK_RELEASED, reinterpret_cast<void*>(onButtonReleased), this);
}

	
RotaryEncoder::~RotaryEncoder()
{
	rotary_encoder_destroy(&_rotaryEncoder);
}


Poco::Int32 RotaryEncoder::count() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Poco::Int32 value;
	int rc = rotary_encoder_get_count(&_rotaryEncoder, false, &value);
	if (rc == E_OK)
		return value;
	else
		throw Poco::IOException();
}


Poco::Int32 RotaryEncoder::reset()
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Poco::Int32 value;
	int rc = rotary_encoder_get_count(&_rotaryEncoder, true, &value);
	if (rc == E_OK)
		return value;
	else
		throw Poco::IOException();
}


Poco::Any RotaryEncoder::getCountChangedPeriod(const std::string&) const
{
	Poco::UInt32 uperiod;
	rotary_encoder_get_count_callback_period(&_rotaryEncoder, &uperiod);
	return Poco::Any(static_cast<int>(uperiod));
}


void RotaryEncoder::setCountChangedPeriod(const std::string&, const Poco::Any& value)
{
	Poco::UInt32 period = static_cast<Poco::UInt32>(Poco::AnyCast<int>(value));
	rotary_encoder_set_count_callback_period(&_rotaryEncoder, period);
}


bool RotaryEncoder::buttonState() const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	bool state;
	int rc = rotary_encoder_is_pressed(&_rotaryEncoder, &state);
	if (rc == E_OK)
		return state;
	else
		throw Poco::IOException();
}


void RotaryEncoder::onCountChanged(Poco::Int32 count, void* userData)
{
	try
	{
		RotaryEncoder* pThis = reinterpret_cast<RotaryEncoder*>(userData);
		pThis->countChanged(count);
	}
	catch (...)
	{
	}
}


void RotaryEncoder::onButtonPressed(void* userData)
{
	try
	{
		RotaryEncoder* pThis = reinterpret_cast<RotaryEncoder*>(userData);
		bool value = true;
		pThis->buttonStateChanged(value);
	}
	catch (...)
	{
	}
}


void RotaryEncoder::onButtonReleased(void* userData)
{
	try
	{
		RotaryEncoder* pThis = reinterpret_cast<RotaryEncoder*>(userData);
		bool value = false;
		pThis->buttonStateChanged(value);
	}
	catch (...)
	{
	}
}


} } // namespace IoT::Tf
