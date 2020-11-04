//
// OSPException.h
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
// SPDX-License-Identifier: GPL-3.0-only
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
POCO_DECLARE_EXCEPTION(OSP_API, BundleUninstallException, BundleException)
POCO_DECLARE_EXCEPTION(OSP_API, BundleSealedException, BundleException)


} } // namespace Poco::OSP


#endif // OSP_OSPException_INCLUDED
