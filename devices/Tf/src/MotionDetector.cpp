//
// MotionDetector.cpp
//
// $Id: //iot/Main/Tf/src/MotionDetector.cpp#3 $
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "MotionDetector.h"
#include "MasterConnectionImpl.h"


namespace IoT {
namespace Tf {


MotionDetector::MotionDetector(MasterConnection::Ptr pMasterConn, const std::string& uid):
	BrickletType("io.macchina.tf.motiondetector", "Tinkerforge Motion Detector Bricklet")
{
	addProperty("displayState", &MotionDetector::getDisplayState);

	IPConnection *ipcon = pMasterConn.cast<MasterConnectionImpl>()->ipcon();
	motion_detector_create(&_motionDetector, uid.c_str(), ipcon);
	
	char deviceUID[8];
	char masterUID[8];
	char position;
	Poco::UInt8 hardwareVersion[3];
	Poco::UInt8 firmwareVersion[3];
	Poco::UInt16 deviceType;
	if (motion_detector_get_identity(&_motionDetector, deviceUID, masterUID, &position, hardwareVersion, firmwareVersion, &deviceType) == E_OK)
	{
		setIdentity(deviceUID, masterUID, position, hardwareVersion, firmwareVersion, deviceType);
	}
	
	motion_detector_register_callback(&_motionDetector, MOTION_DETECTOR_CALLBACK_MOTION_DETECTED, reinterpret_cast<void*>(onMotionDetected), this);
	motion_detector_register_callback(&_motionDetector, MOTION_DETECTOR_CALLBACK_DETECTION_CYCLE_ENDED, reinterpret_cast<void*>(onDetectionCycleEnded), this);
}

	
MotionDetector::~MotionDetector()
{
	motion_detector_destroy(&_motionDetector);
}


bool MotionDetector::state() const
{
	Poco::Mutex::ScopedLock lock(_mutex);

	Poco::UInt8 value;
	int rc = motion_detector_get_motion_detected(&_motionDetector, &value);
	if (rc == E_OK)
	{
		return value != 0;
	}
	else throw Poco::IOException();
}


Poco::Any MotionDetector::getDisplayState(const std::string&) const
{
	return std::string(state() ? "triggered" : "not triggered");
}


void MotionDetector::onMotionDetected(void* userData)
{
	try
	{
		MotionDetector* pThis = reinterpret_cast<MotionDetector*>(userData);
		bool value = true;
		pThis->stateChanged(value);
	}
	catch (...)
	{
	}
}


void MotionDetector::onDetectionCycleEnded(void* userData)
{
	try
	{
		MotionDetector* pThis = reinterpret_cast<MotionDetector*>(userData);
		bool value = false;
		pThis->stateChanged(value);
	}
	catch (...)
	{
	}
}


} } // namespace IoT::Tf
