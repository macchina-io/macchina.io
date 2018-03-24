//
// DeviceRegistrar.h
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_CAN_DeviceRegistrar_INCLUDED
#define IoT_CAN_DeviceRegistrar_INCLUDED


#include "IoT/CAN/CANDevices.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/RemotingNG/ServerHelper.h"
#include <vector>


namespace IoT {
namespace CAN {


class IoTCANDevices_API DeviceRegistrar
	/// A helper class taking care of registering CAN sensors
	/// and devices with the service registry and the ORB.
{
public:
	DeviceRegistrar(Poco::OSP::ServiceRegistry& registry);
		/// Creates the DeviceRegistrar.

	~DeviceRegistrar();
		/// Destroys the DeviceRegistrar and unregisters all devices.

	template <class D>
	void registerDevice(const std::string& bus, Poco::AutoPtr<D> pDevice)
	{
		typedef Poco::RemotingNG::ServerHelper<typename D::SuperType> ServerHelper;

		std::string symbolicName = pDevice->getPropertyString("symbolicName");
		std::string type = pDevice->getPropertyString("type");
		std::string signal = pDevice->getPropertyString("signal");
		std::string physicalQuantity;
		if (pDevice->hasProperty("physicalQuantity"))
			physicalQuantity = pDevice->getPropertyString("physicalQuantity");
		Poco::RemotingNG::Identifiable::ObjectId oid = symbolicName;
		oid += '#';
		oid += bus;
		oid += '/';
		oid += signal;
		typename ServerHelper::RemoteObjectPtr pDeviceRemoteObject = ServerHelper::createRemoteObject(pDevice, oid);

		Poco::OSP::Properties props;
		props.set("io.macchina.device", symbolicName);
		props.set("io.macchina.deviceType", type);
		props.set("io.macchina.can.signal", signal);
		if (!physicalQuantity.empty())
		{
			props.set("io.macchina.physicalQuantity", physicalQuantity);
		}

		Poco::OSP::ServiceRef::Ptr pServiceRef = _registry.registerService(oid, pDeviceRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void unregisterDevices();
		/// Unregisters all devices.

private:
	Poco::OSP::ServiceRegistry& _registry;
	std::vector<Poco::OSP::ServiceRef::Ptr> _serviceRefs;
};


} } // namespace IoT::CAN


#endif // IoT_CAN_DeviceRegistrar_INCLUDED
