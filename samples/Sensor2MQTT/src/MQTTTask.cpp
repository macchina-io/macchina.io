//
// MQTTTask.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "MQTTTask.h"
#include "Poco/Format.h"


namespace Sensor2MQTT {


MQTTTask::MQTTTask(IoT::Devices::ISensor::Ptr pSensor, IoT::MQTT::IMQTTClient::Ptr pMQTTClient, const std::string& topic):
	_pSensor(pSensor),
	_pMQTTClient(pMQTTClient),
	_topic(topic),
	_logger(Poco::Logger::get("MQTTTask"))
{
}


void MQTTTask::run()
{
	try
	{
		if (_pSensor->ready())
		{
			const std::string payload(Poco::format("%.1f", _pSensor->value()));
			_pMQTTClient->publish(
				_topic,
				payload,
				0
			);
			_logger.information("Temperature sent: %s", payload);
		}
	}
	catch (Poco::Exception& exc)
	{
		_logger.log(exc);
	}
}


} // namespace Sensor2MQTT
