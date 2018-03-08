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
#include "Poco/OSP/ServiceListener.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"
#include "IoT/Devices/ISensor.h"


namespace HelloSensor2 {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	void start(Poco::OSP::BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pListener = pContext->registry().createListener(
			"io.macchina.physicalQuantity == \"temperature\"",
			Poco::delegate(this, &BundleActivator::onSensorRegistered),
			Poco::delegate(this, &BundleActivator::onSensorUnregistered));
	}

	void stop(Poco::OSP::BundleContext::Ptr pContext)
	{
		_pListener.reset();
		_pContext.reset();
	}

protected:
	void onSensorRegistered(const Poco::OSP::ServiceRef::Ptr& pSensorRef)
	{
		_pContext->logger().information("Sensor registered: %s", pSensorRef->name());
		const Poco::OSP::Properties& props = pSensorRef->properties();
		for (const auto& key: props.keys())
		{
			_pContext->logger().information("Property: %s = %s", key, props[key]);
		}
		IoT::Devices::ISensor::Ptr pSensor = pSensorRef->castedInstance<IoT::Devices::ISensor>();
		_pContext->logger().information("Sensor value: %.2f", pSensor->value());
	}

	void onSensorUnregistered(const Poco::OSP::ServiceRef::Ptr& pSensorRef)
	{
		_pContext->logger().information("Sensor unregistered: %s", pSensorRef->name());
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::ServiceListener::Ptr _pListener;
};


} // namespace HelloSensor2


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(HelloSensor2::BundleActivator)
POCO_END_MANIFEST
