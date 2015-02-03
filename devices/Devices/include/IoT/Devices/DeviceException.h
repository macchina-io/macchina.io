//
// DeviceException.h
//
// $Id: //iot/Main/Devices/include/IoT/Devices/DeviceException.h#2 $
//
// Library: IoT/Devices
// Package: Devices
// Module:  DeviceException
//
// Definition of exceptions for Device library.
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef IoT_Devices_DeviceException_INCLUDED
#define IoT_Devices_DeviceException_INCLUDED


#include "IoT/Devices/Devices.h"
#include "Poco/Exception.h"


namespace IoT {
namespace Devices {


POCO_DECLARE_EXCEPTION(IoTDevices_API, DeviceException, Poco::IOException)
POCO_DECLARE_EXCEPTION(IoTDevices_API, NotSupportedException, Poco::Exception)
POCO_DECLARE_EXCEPTION(IoTDevices_API, NotReadableException, Poco::Exception)
POCO_DECLARE_EXCEPTION(IoTDevices_API, NotWritableException, Poco::Exception)


} } // namespace IoT::Devices


#endif // IoT_Devices_DeviceException_INCLUDED
