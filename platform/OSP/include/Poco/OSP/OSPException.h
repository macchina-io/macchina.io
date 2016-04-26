//
// OSPException.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/OSPException.h#1 $
//
// Library: OSP
// Package: Core
// Module:  OSPException
//
// Definition of the OSPException class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_OSPException_INCLUDED
#define OSP_OSPException_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/Exception.h"


namespace Poco {
namespace OSP {


POCO_DECLARE_EXCEPTION(OSP_API, OSPException, Poco::RuntimeException)
POCO_DECLARE_EXCEPTION(OSP_API, BundleException, OSPException)
POCO_DECLARE_EXCEPTION(OSP_API, ManifestException, BundleException)
POCO_DECLARE_EXCEPTION(OSP_API, BundleStateException, BundleException)
POCO_DECLARE_EXCEPTION(OSP_API, BundleVersionConflictException, BundleException)
POCO_DECLARE_EXCEPTION(OSP_API, BundleLoadException, BundleException)
POCO_DECLARE_EXCEPTION(OSP_API, BundleResolveException, BundleException)
POCO_DECLARE_EXCEPTION(OSP_API, BundleInstallException, BundleException)


} } // namespace Poco::OSP


#endif // OSP_OSPException_INCLUDED
