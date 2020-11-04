//
// DCMotor.h
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef IoT_Tf_DCMotor_INCLUDED
#define IoT_Tf_DCMotor_INCLUDED


#include "IoT/Tf/Tf.h"
#include "IoT/Devices/Switch.h"
#include "IoT/Tf/MasterConnection.h"
#include "BrickletImpl.h"
#include "brick_dc.h"


namespace IoT {
namespace Tf {


class IoTTf_API DCMotor: public BrickletImpl<IoT::Devices::Switch, DCMotor>
{
public:
	enum
	{
		DEVICE_IDENTIFIER = DC_DEVICE_IDENTIFIER
	};

	DCMotor(MasterConnection::Ptr pMasterConn, const std::string& uid);
		/// Creates a DCMotorImpl.
		
	~DCMotor();
		/// Destroys the DCMotorImpl.
	
	// Trigger
	bool state() const;
	bool getTargetState() const;
	void setTargetState(bool newState);

protected:
	Poco::Any getDisplayState(const std::string&) const;
	Poco::Any getTargetVelocity(const std::string&) const;
	void setTargetVelocity(const std::string&, const Poco::Any& value);
	Poco::Any getVelocity(const std::string&) const;
	Poco::Any getAcceleration(const std::string&) const;
	void setAcceleration(const std::string&, const Poco::Any& value);
	Poco::Any getFrequency(const std::string&) const;
	void setFrequency(const std::string&, const Poco::Any& value);
	Poco::Any getDriveMode(const std::string&) const;
	void setDriveMode(const std::string&, const Poco::Any& value);
	Poco::Any getCurrent(const std::string&) const;
	Poco::Any getExternalVoltage(const std::string&) const;
	Poco::Any getInternalVoltage(const std::string&) const;

	static void onMotionDetected(void* userData);
	static void onDetectionCycleEnded(void* userData);

private:
	mutable ::DC _dc;
};


} } // namespace IoT::Tf


#endif // IoT_Tf_DCMotor_INCLUDED
