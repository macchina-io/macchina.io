//
// MotionDetector.h
//
// $Id: //iot/Main/Tf/src/MotionDetector.h#3 $
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Tf_MotionDetector_INCLUDED
#define IoT_Tf_MotionDetector_INCLUDED


#include "IoT/Tf/Tf.h"
#include "IoT/Devices/Trigger.h"
#include "IoT/Tf/MasterConnection.h"
#include "BrickletImpl.h"
extern "C"
{
#include "bricklet_motion_detector.h"
}

namespace IoT {
namespace Tf {


class IoTTf_API MotionDetector: public BrickletImpl<IoT::Devices::Trigger, MotionDetector>
{
public:
	enum
	{
		DEVICE_IDENTIFIER = MOTION_DETECTOR_DEVICE_IDENTIFIER
	};

	MotionDetector(MasterConnection::Ptr pMasterConn, const std::string& uid);
		/// Creates a MotionDetectorImpl.
		
	~MotionDetector();
		/// Destroys the MotionDetectorImpl.
	
	// Trigger
	bool state() const;

protected:
	Poco::Any getDisplayState(const std::string&) const;

	static void onMotionDetected(void* userData);
	static void onDetectionCycleEnded(void* userData);

private:
	mutable ::MotionDetector _motionDetector;
};


} } // namespace IoT::Tf


#endif // IoT_Tf_MotionDetector_INCLUDED
