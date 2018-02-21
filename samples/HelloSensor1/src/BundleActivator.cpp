//
// BundleActivator.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/ClassLibrary.h"
#include "IoT/Devices/ISensor.h"


namespace HelloSensor1 {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	void start(Poco::OSP::BundleContext::Ptr pContext)
	{
		auto sensorRefs = pContext->registry().find("io.macchina.physicalQuantity == \"temperature\"");
		pContext->logger().information("Found %z temperature sensors.", sensorRefs.size());
		for (auto pSensorRef: sensorRefs)
		{
			pContext->logger().information("Sensor name: %s", pSensorRef->name());
			const Poco::OSP::Properties& props = pSensorRef->properties();
			for (const auto& key: props.keys())
			{
				pContext->logger().information("Property: %s = %s", key, props[key]);
			}
			IoT::Devices::ISensor::Ptr pSensor = pSensorRef->castedInstance<IoT::Devices::ISensor>();
			pContext->logger().information("Sensor value: %.2f", pSensor->value());
		}
	}

	void stop(Poco::OSP::BundleContext::Ptr pContext)
	{
	}
};


} // namespace HelloSensor1


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(HelloSensor1::BundleActivator)
POCO_END_MANIFEST
