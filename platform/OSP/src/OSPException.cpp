//
// OSPException.cpp
//
// $Id: //poco/1.7/OSP/src/OSPException.cpp#1 $
//
// Library: OSP
// Package: Core
// Module:  OSPException
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/OSPException.h"
#include <typeinfo>


namespace Poco {
namespace OSP {


POCO_IMPLEMENT_EXCEPTION(OSPException, Poco::RuntimeException, "OSP Exception")
POCO_IMPLEMENT_EXCEPTION(BundleException, OSPException, "Bundle error")
POCO_IMPLEMENT_EXCEPTION(ManifestException, BundleException, "Manifest error")
POCO_IMPLEMENT_EXCEPTION(BundleStateException, BundleException, "Invalid bundle state")
POCO_IMPLEMENT_EXCEPTION(BundleVersionConflictException, BundleException, "Bundle version conflict")
POCO_IMPLEMENT_EXCEPTION(BundleLoadException, BundleException, "Cannot load bundle")
POCO_IMPLEMENT_EXCEPTION(BundleResolveException, BundleException, "Cannot resolve bundle")
POCO_IMPLEMENT_EXCEPTION(BundleInstallException, BundleException, "Cannot install bundle")


} } // namespace Poco::OSP
