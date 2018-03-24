//
// DeviceRegistrar.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//



#include "IoT/CAN/DeviceRegistrar.h"


namespace IoT {
namespace CAN {


DeviceRegistrar::DeviceRegistrar(Poco::OSP::ServiceRegistry& registry):
	_registry(registry)
{
}


DeviceRegistrar::~DeviceRegistrar()
{
	unregisterDevices();
}


void DeviceRegistrar::unregisterDevices()
{
	for (std::vector<Poco::OSP::ServiceRef::Ptr>::iterator it = _serviceRefs.begin(); it != _serviceRefs.end(); ++it)
	{
		_registry.unregisterService(*it);
	}
	_serviceRefs.clear();
}


} } // namespace IoT::CAN
