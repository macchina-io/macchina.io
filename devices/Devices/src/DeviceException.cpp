//
// DeviceException.cpp
//
// Library: IoT/Devices
// Package: Devices
// Module:  DeviceException
//
// Copyright (c) 2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Devices/DeviceException.h"
#include <typeinfo>


namespace IoT {
namespace Devices {


POCO_IMPLEMENT_EXCEPTION(DeviceException, Poco::IOException, "Device Exception")
POCO_IMPLEMENT_EXCEPTION(NotSupportedException, Poco::Exception, "Not supported")
POCO_IMPLEMENT_EXCEPTION(NotReadableException, Poco::Exception, "Not readable")
POCO_IMPLEMENT_EXCEPTION(NotWritableException, Poco::Exception, "Not writable")


} } // namespace IoT::Devices
