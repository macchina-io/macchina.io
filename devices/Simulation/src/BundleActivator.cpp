//
// BundleActivator.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
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
#include "Poco/Util/Timer.h"
#include "IoT/Devices/SensorServerHelper.h"
#include "IoT/Devices/GNSSSensorServerHelper.h"
#include "Poco/Delegate.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "Poco/SharedPtr.h"
#include "SimulatedSensor.h"
#include "SimulatedGNSSSensor.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace Simulation {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void createSensor(const SimulatedSensor::Params& params)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Sensor> ServerHelper;

		Poco::SharedPtr<SimulatedSensor> pSensor = new SimulatedSensor(params, *_pTimer);
		ServerHelper::RemoteObjectPtr pSensorRemoteObject = ServerHelper::createRemoteObject(pSensor, params.id);

		Properties props;
		props.set("io.macchina.device", SimulatedSensor::SYMBOLIC_NAME);
		props.set("io.macchina.deviceType", SimulatedSensor::TYPE);
		if (!params.physicalQuantity.empty())
		{
			props.set("io.macchina.physicalQuantity", params.physicalQuantity);
		}

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(params.id, pSensorRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void createGNSSSensor(const SimulatedGNSSSensor::Params& params)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::GNSSSensor> ServerHelper;

		Poco::SharedPtr<SimulatedGNSSSensor> pGNSSSensor = new SimulatedGNSSSensor(params);
		ServerHelper::RemoteObjectPtr pGNSSSensorRemoteObject = ServerHelper::createRemoteObject(pGNSSSensor, params.id);

		Properties props;
		props.set("io.macchina.device", SimulatedGNSSSensor::SYMBOLIC_NAME);
		props.set("io.macchina.deviceType", SimulatedGNSSSensor::TYPE);

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(params.id, pGNSSSensorRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void start(BundleContext::Ptr pContext)
	{
		_pTimer = new Poco::Util::Timer;
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);

		Poco::Util::AbstractConfiguration::Keys keys;
		_pPrefs->configuration()->keys("simulation.sensors", keys);
		for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
		{
			std::string baseKey = "simulation.sensors.";
			baseKey += *it;

			SimulatedSensor::Params params;
			params.id = SimulatedSensor::SYMBOLIC_NAME;
			params.id += "#";
			params.id += Poco::NumberFormatter::format(_serviceRefs.size());

			params.physicalQuantity = _pPrefs->configuration()->getString(baseKey + ".physicalQuantity", "");
			params.physicalUnit     = _pPrefs->configuration()->getString(baseKey + ".physicalUnit", "");
			params.initialValue     = _pPrefs->configuration()->getDouble(baseKey + ".initialValue", 0.0);
			params.delta            = _pPrefs->configuration()->getDouble(baseKey + ".delta", 0.0);
			params.cycles           = _pPrefs->configuration()->getInt(baseKey + ".cycles", 0);
			params.updateRate       = _pPrefs->configuration()->getDouble(baseKey + ".updateRate", 0.0);

			std::string mode = _pPrefs->configuration()->getString(baseKey + ".mode", "linear");
			if (mode == "linear")
				params.mode = SimulatedSensor::SIM_LINEAR;
			else if (mode == "random")
				params.mode = SimulatedSensor::SIM_RANDOM;

			try
			{
				createSensor(params);
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().error(Poco::format("Cannot create simulated sensor: %s", exc.displayText()));
			}
		}

		std::string gpxPath = _pPrefs->configuration()->getString("simulation.gnss.gpxPath", "");
		if (!gpxPath.empty())
		{
			SimulatedGNSSSensor::Params params;
			params.id = SimulatedGNSSSensor::SYMBOLIC_NAME;
			params.gpxPath = gpxPath;
			params.loopReplay = _pPrefs->configuration()->getBool("simulation.gnss.loopReplay", true);
			params.speedUp = _pPrefs->configuration()->getDouble("simulation.gnss.speedUp", 1.0);

			try
			{
				createGNSSSensor(params);
			}
			catch (Poco::Exception& exc)
			{
				pContext->logger().error(Poco::format("Cannot create simulated GNSS sensor: %s", exc.displayText()));
			}
		}
	}

	void stop(BundleContext::Ptr pContext)
	{
		_pTimer->cancel(true);
		_pTimer = 0;

		for (std::vector<ServiceRef::Ptr>::iterator it = _serviceRefs.begin(); it != _serviceRefs.end(); ++it)
		{
			_pContext->registry().unregisterService(*it);
		}
		_serviceRefs.clear();

		_pPrefs = 0;
		_pContext = 0;
	}

private:
	Poco::SharedPtr<Poco::Util::Timer> _pTimer;
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	std::vector<ServiceRef::Ptr> _serviceRefs;
};


} } // namespace IoT::Simulation


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Simulation::BundleActivator)
POCO_END_MANIFEST
