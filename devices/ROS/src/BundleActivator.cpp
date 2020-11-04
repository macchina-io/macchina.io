//
// BundleActivator.cpp
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/RemotingNG/ORB.h"
#include "IoT/Devices/SensorServerHelper.h"
#include "IoT/Devices/AccelerometerServerHelper.h"
#include "IoT/Devices/GyroscopeServerHelper.h"
#include "IoT/Devices/MagnetometerServerHelper.h"
#include "IoT/Devices/GNSSSensorServerHelper.h"
#include "IoT/ROS/BridgeClient.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Delegate.h"
#include "Accelerometer.h"
#include "Gyroscope.h"
#include "Magnetometer.h"
#include "GNSSSensor.h"
#include "Sensor.h"
#include <vector>
#include <set>
#include <map>
#include <cmath>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace ROS {
namespace Devices {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void registerSensor(Sensor::Ptr pSensor)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Sensor> ServerHelper;

		std::string symbolicName = pSensor->getPropertyString("symbolicName");
		std::string type = pSensor->getPropertyString("type");
		std::string physicalQuantity = pSensor->getPropertyString("physicalQuantity");

		std::string oid(Sensor::SYMBOLIC_NAME);
		oid += ".";
		oid += physicalQuantity;

		ServerHelper::RemoteObjectPtr pSensorRemoteObject = ServerHelper::createRemoteObject(pSensor, oid);

		Properties props;
		props.set("io.macchina.device", symbolicName);
		props.set("io.macchina.deviceType", type);
		props.set("io.macchina.physicalQuantity", physicalQuantity);

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pSensorRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void registerAccelerometer(Accelerometer::Ptr pAccelerometer)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Accelerometer> ServerHelper;

		std::string oid(Accelerometer::SYMBOLIC_NAME);

		ServerHelper::RemoteObjectPtr pAccelerometerRemoteObject = ServerHelper::createRemoteObject(pAccelerometer, oid);

		Properties props;
		props.set("io.macchina.device", Accelerometer::SYMBOLIC_NAME);
		props.set("io.macchina.deviceType", Accelerometer::TYPE);

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pAccelerometerRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void registerMagnetometer(Magnetometer::Ptr pMagnetometer)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Magnetometer> ServerHelper;

		std::string oid(Magnetometer::SYMBOLIC_NAME);

		ServerHelper::RemoteObjectPtr pMagnetometerRemoteObject = ServerHelper::createRemoteObject(pMagnetometer, oid);

		Properties props;
		props.set("io.macchina.device", Magnetometer::SYMBOLIC_NAME);
		props.set("io.macchina.deviceType", Magnetometer::TYPE);

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pMagnetometerRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void registerGyroscope(Gyroscope::Ptr pGyroscope)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::Gyroscope> ServerHelper;

		std::string oid(Gyroscope::SYMBOLIC_NAME);

		ServerHelper::RemoteObjectPtr pGyroscopeRemoteObject = ServerHelper::createRemoteObject(pGyroscope, oid);

		Properties props;
		props.set("io.macchina.device", Gyroscope::SYMBOLIC_NAME);
		props.set("io.macchina.deviceType", Gyroscope::TYPE);

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pGyroscopeRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void registerGNSSSensor(GNSSSensor::Ptr pGNSSSensor)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::GNSSSensor> ServerHelper;

		std::string oid(GNSSSensor::SYMBOLIC_NAME);

		ServerHelper::RemoteObjectPtr pGNSSSensorRemoteObject = ServerHelper::createRemoteObject(pGNSSSensor, oid);

		Properties props;
		props.set("io.macchina.device", GNSSSensor::SYMBOLIC_NAME);
		props.set("io.macchina.deviceType", GNSSSensor::TYPE);

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pGNSSSensorRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void updateIMU(const Poco::JSON::Object::Ptr& pMessage)
	{
		static const std::string ANGULAR("angular_velocity");
		static const std::string LINEAR("linear_acceleration");
		static const std::string ORIENT("orientation");
		static const std::string X("x");
		static const std::string Y("y");
		static const std::string Z("z");
		static const double G(9.81);

		Poco::JSON::Object::Ptr pAngular = pMessage->getObject(ANGULAR);
		Poco::JSON::Object::Ptr pLinear = pMessage->getObject(LINEAR);
		Poco::JSON::Object::Ptr pOrient = pMessage->getObject(ORIENT);

		IoT::Devices::Acceleration accel;
		accel.x = pLinear->optValue<double>(X, 0.0)/G;
		accel.y = pLinear->optValue<double>(Y, 0.0)/G;
		accel.z = pLinear->optValue<double>(Z, 0.0)/G;
		_pAccelerometer->update(accel);

		IoT::Devices::Rotation rot;
		rot.x = pAngular->optValue<double>(X, 0.0);
		rot.y = pAngular->optValue<double>(Y, 0.0);
		rot.z = pAngular->optValue<double>(Z, 0.0);
		_pGyroscope->update(rot);
	}

	void updateMag(const Poco::JSON::Object::Ptr& pMessage)
	{
		static const std::string VECTOR("vector");
		static const std::string X("x");
		static const std::string Y("y");
		static const std::string Z("z");

		Poco::JSON::Object::Ptr pVector = pMessage->getObject(VECTOR);

		IoT::Devices::MagneticFieldStrength mag;
		mag.x = pVector->optValue<double>(X, 0.0);
		mag.y = pVector->optValue<double>(Y, 0.0);
		mag.z = pVector->optValue<double>(Z, 0.0);
		_pMagnetometer->update(mag);
	}

	void updateGPS(const Poco::JSON::Object::Ptr& pMessage)
	{
		static const std::string LATITUDE("latitude");
		static const std::string LONGITUDE("longitude");
		static const std::string ALTITUDE("altitude");
		static const std::string VEL_X("velocity_x");
		static const std::string VEL_Y("velocity_y");

		IoT::Devices::PositionUpdate pos;
		pos.position.latitude = pMessage->optValue<double>(LATITUDE, 0.0);
		pos.position.longitude = pMessage->optValue<double>(LONGITUDE, 0.0);

		double vx = pMessage->optValue<double>(VEL_X, 0.0);
		double vy = pMessage->optValue<double>(VEL_Y, 0.0);

		pos.speed = std::sqrt(vx*vx+vy*vy)*1.94384; // knots
		pos.magneticVariation = 0;
		pos.course = std::atan2(vy, vx)*180.0/M_PI;

		double alt = pMessage->optValue<double>(ALTITUDE, 0.0);

		_pGNSSSensor->update(pos, alt);
	}

	void updateStatus(const Poco::JSON::Object::Ptr& pMessage)
	{
		static const std::string BAT_V("battery_voltage");
		static const std::string CPU("cpu_load");

		double voltage = pMessage->optValue<double>(BAT_V, 0.0);
		_pVoltage->update(voltage);

		double cpuLoad = pMessage->optValue<double>(CPU, 0.0);
		_pCPULoad->update(cpuLoad);
	}

	void onMessageReceived(const Poco::JSON::Object::Ptr& pMessage)
	{
		static const std::string TOPIC("topic");
		static const std::string OP("op");
		static const std::string MSG("msg");
		static const std::string EMPTY;

		std::ostringstream ostr;
		pMessage->stringify(ostr, 4, 4);
		if (_pContext->logger().debug())
		{
			_pContext->logger().debug("Message received:\n%s", ostr.str());
		}

		std::string op = pMessage->optValue<std::string>(OP, EMPTY);
		std::string topic = pMessage->optValue<std::string>(TOPIC, EMPTY);
		if (op == "publish")
		{
			if (topic == "/fcu/imu")
			{
				updateIMU(pMessage->getObject(MSG));
			}
			if (topic == "/fcu/mag")
			{
				updateMag(pMessage->getObject(MSG));
			}
			else if (topic == "/fcu/gps_custom")
			{
				updateGPS(pMessage->getObject(MSG));
			}
			else if (topic == "/fcu/status")
			{
				updateStatus(pMessage->getObject(MSG));
			}
		}
	}

	void subscribe(const std::string& topic)
	{
		std::string id = _pBridgeClient->subscribe(topic);
		_subscriptions[id] = topic;
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);
		_pBridgeClient = ServiceFinder::find<BridgeClient>(pContext);

		_pAccelerometer = new Accelerometer;
		_pGyroscope = new Gyroscope;
		_pMagnetometer = new Magnetometer;
		_pGNSSSensor = new GNSSSensor;
		_pVoltage = new Sensor("batteryVoltage", IoT::Devices::Sensor::PHYSICAL_UNIT_VOLT);
		_pCPULoad = new Sensor("cpuLoad", "");

		registerAccelerometer(_pAccelerometer);
		registerMagnetometer(_pMagnetometer);
		registerGyroscope(_pGyroscope);
		registerGNSSSensor(_pGNSSSensor);
		registerSensor(_pVoltage);
		registerSensor(_pCPULoad);

		_pBridgeClient->messageReceived += Poco::delegate(this, &BundleActivator::onMessageReceived);

		subscribe("/fcu/imu");
		subscribe("/fcu/mag");
		subscribe("/fcu/gps_custom");
		subscribe("/fcu/status");

		_pAccelerometer->enable(true);
		_pMagnetometer->enable(true);
		_pGyroscope->enable(true);
		_pGNSSSensor->enable(true);
		_pVoltage->enable(true);
		_pCPULoad->enable(true);
	}

	void stop(BundleContext::Ptr pContext)
	{
		_pAccelerometer->enable(false);
		_pMagnetometer->enable(false);
		_pGyroscope->enable(false);
		_pGNSSSensor->enable(false);
		_pVoltage->enable(false);
		_pCPULoad->enable(false);

		if (_pBridgeClient)
		{
			_pBridgeClient->messageReceived -= Poco::delegate(this, &BundleActivator::onMessageReceived);
			for (std::map<std::string, std::string>::const_iterator it = _subscriptions.begin(); it != _subscriptions.end(); ++it)
			{
				_pBridgeClient->unsubscribe(it->second, it->first);
			}
		}

		for (std::vector<ServiceRef::Ptr>::iterator it = _serviceRefs.begin(); it != _serviceRefs.end(); ++it)
		{
			_pContext->registry().unregisterService(*it);
		}
		_serviceRefs.clear();

		_pAccelerometer.reset();
		_pMagnetometer.reset();
		_pGyroscope.reset();
		_pGNSSSensor.reset();
		_pVoltage.reset();
		_pCPULoad.reset();

		_pPrefs.reset();
		_pContext.reset();
	}

private:
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	std::vector<ServiceRef::Ptr> _serviceRefs;
	BridgeClient::Ptr _pBridgeClient;
	Accelerometer::Ptr _pAccelerometer;
	Gyroscope::Ptr _pGyroscope;
	Magnetometer::Ptr _pMagnetometer;
	GNSSSensor::Ptr _pGNSSSensor;
	Sensor::Ptr _pVoltage;
	Sensor::Ptr _pCPULoad;
	std::map<std::string, std::string> _subscriptions;
};


} } } // namespace IoT::ROS::Devices


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::ROS::Devices::BundleActivator)
POCO_END_MANIFEST
