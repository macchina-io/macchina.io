//
// MQTTTask.h
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef MQTTTask_INCLUDED
#define MQTTTask_INCLUDED


#include "Poco/Util/TimerTask.h"
#include "Poco/AutoPtr.h"
#include "IoT/Devices/ISensor.h"
#include "IoT/MQTT/IMQTTClient.h"
#include "Poco/Format.h"
#include "Poco/Logger.h"


namespace Sensor2MQTT {


class MQTTTask: public Poco::Util::TimerTask
{
public:
	typedef Poco::AutoPtr<MQTTTask> Ptr;

	MQTTTask(IoT::Devices::ISensor::Ptr pSensor, IoT::MQTT::IMQTTClient::Ptr pMQTTClient, const std::string& topic);

	// Poco::Util::TimerTask
	void run();

private:
	IoT::Devices::ISensor::Ptr _pSensor;
	IoT::MQTT::IMQTTClient::Ptr _pMQTTClient;
	std::string _topic;
	Poco::Logger& _logger;
};


} // namespace Sensor2MQTT


#endif // MQTTTask_INCLUDED
