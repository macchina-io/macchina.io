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
#include "Poco/Mutex.h"
#include "Poco/ClassLibrary.h"
#include "IoT/Devices/ISensor.h"


namespace HelloSensor3 {


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
		Poco::FastMutex::ScopedLock lock(_sensorMutex);

		if (_pSensor)
		{
			unsubscribe();
		}
		_pSensor.reset();
		_pSensorRef.reset();
		_pListener.reset();
		_pContext.reset();
	}

protected:
	void subscribe()
	{
		_pSensor->valueChanged += Poco::delegate(this, &BundleActivator::onTemperatureChanged);
	}

	void unsubscribe()
	{
		_pSensor->valueChanged -= Poco::delegate(this, &BundleActivator::onTemperatureChanged);
	}

	void onSensorRegistered(const Poco::OSP::ServiceRef::Ptr& pSensorRef)
	{
		Poco::FastMutex::ScopedLock lock(_sensorMutex);

		if (!_pSensorRef)
		{
			_pContext->logger().information("Sensor registered: %s", pSensorRef->name());
			_pSensorRef = pSensorRef;
			_pSensor = pSensorRef->castedInstance<IoT::Devices::ISensor>();
			subscribe();
		}
	}

	void onSensorUnregistered(const Poco::OSP::ServiceRef::Ptr& pSensorRef)
	{
		Poco::FastMutex::ScopedLock lock(_sensorMutex);

		if (pSensorRef == _pSensorRef)
		{
			_pContext->logger().information("Sensor unregistered: %s", pSensorRef->name());
			unsubscribe();
			_pSensor.reset();
			_pSensorRef.reset();
		}
	}

	void onTemperatureChanged(const double& temp)
	{
		_pContext->logger().information("Temperature changed: %.2f", temp);
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::ServiceListener::Ptr _pListener;
	Poco::OSP::ServiceRef::Ptr _pSensorRef;
	IoT::Devices::ISensor::Ptr _pSensor;
	Poco::FastMutex _sensorMutex;
};


} // namespace HelloSensor3


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(HelloSensor3::BundleActivator)
POCO_END_MANIFEST
