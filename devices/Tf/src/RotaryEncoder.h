//
// RotaryEncoder.h
//
// $Id: //iot/Main/Tf/src/RotaryEncoder.h#3 $
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Tf_RotaryEncoder_INCLUDED
#define IoT_Tf_RotaryEncoder_INCLUDED


#include "IoT/Tf/Tf.h"
#include "IoT/Devices/RotaryEncoder.h"
#include "BrickletImpl.h"
#include "IoT/Tf/MasterConnection.h"
extern "C"
{
#include "bricklet_rotary_encoder.h"
}

namespace IoT {
namespace Tf {


class IoTTf_API RotaryEncoder: public BrickletImpl<IoT::Devices::RotaryEncoder, RotaryEncoder>
{
public:
	enum
	{
		DEVICE_IDENTIFIER = ROTARY_ENCODER_DEVICE_IDENTIFIER
	};

	RotaryEncoder(MasterConnection::Ptr pMasterConn, const std::string& uid);
		/// Creates a RotaryEncoderImpl.
		
	~RotaryEncoder();
		/// Destroys the RotaryEncoderImpl.
	
	// RotaryEncoder
	Poco::Int32 count() const;
	Poco::Int32 reset();
	bool buttonState() const;
	
protected:
	Poco::Any getCountChangedPeriod(const std::string&) const;
	void setCountChangedPeriod(const std::string&, const Poco::Any& value);
	Poco::Any getDisplayValue(const std::string&) const;

	static void onCountChanged(Poco::Int32 count, void* userData);
	static void onButtonPressed(void* userData);
	static void onButtonReleased(void* userData);

private:
	mutable ::RotaryEncoder _rotaryEncoder;
};


} } // namespace IoT::Tf


#endif // IoT_Tf_RotaryEncoder_INCLUDED
