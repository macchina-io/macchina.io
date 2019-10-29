//
// BundleActivator.cpp
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/RemotingNG/ORB.h"
#include "Poco/File.h"
#include "Poco/ClassLibrary.h"
#include "Poco/SharedPtr.h"
#include "IoT/Devices/SensorServerHelper.h"
#include "LinuxThermalSensor.h"


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace LinuxThermalSimple {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	Poco::OSP::ServiceRef::Ptr createSensor(const std::string& id, const std::string& path)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Sensor> ServerHelper;

		Poco::SharedPtr<LinuxThermalSensor> pSensor = new LinuxThermalSensor(path);
		ServerHelper::RemoteObjectPtr pSensorRemoteObject = ServerHelper::createRemoteObject(pSensor, id);

		Properties props;
		props.set("io.macchina.device", LinuxThermalSensor::SYMBOLIC_NAME);
		props.set("io.macchina.deviceType", LinuxThermalSensor::TYPE);
		props.set("io.macchina.physicalQuantity", LinuxThermalSensor::PHYSICAL_QUANTITY);

		return _pContext->registry().registerService(id, pSensorRemoteObject, props);
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;

		Poco::OSP::PreferencesService::Ptr pPrefs = ServiceFinder::find<PreferencesService>(pContext);

		std::string path = pPrefs->configuration()->getString("linux-thermal-simple.path", "/sys/class/thermal/thermal_zone0");
		Poco::File file(path);
		if (file.exists())
		{
			_pServiceRef = createSensor(LinuxThermalSensor::SYMBOLIC_NAME, path);
		}
		else
		{
			pContext->logger().warning("Thermal device file not found: %s", path);
		}
	}

	void stop(BundleContext::Ptr pContext)
	{
		pContext->registry().unregisterService(_pServiceRef);
		_pServiceRef.reset();
		_pContext.reset();
	}

private:
	Poco::OSP::BundleContext::Ptr _pContext;
	Poco::OSP::ServiceRef::Ptr _pServiceRef;
};


} } // namespace IoT::LinuxThermalSimple


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::LinuxThermalSimple::BundleActivator)
POCO_END_MANIFEST
