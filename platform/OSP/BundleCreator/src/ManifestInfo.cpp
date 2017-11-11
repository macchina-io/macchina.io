//
// ManifestInfo.cpp
//
// This sample demonstrates the OSP framework.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "ManifestInfo.h"


ManifestInfo::ManifestInfo(const std::string& name,
	const std::string& symbolicName,
	const Poco::OSP::Version& version,
	const std::string& vendor,
	const std::string& copyright,
	const std::string& activatorClass,
	const std::string& activatorLibrary,
	const Dependencies& requiredBundles,
	bool lazyStart,
	const std::string& runLevel,
	const std::string& extendsBundle):
	_name(name),
	_symbolicName(symbolicName),
	_version(version),
	_vendor(vendor),
	_copyright(copyright),
	_activatorClass(activatorClass),
	_activatorLibrary(activatorLibrary),
	_requiredBundles(requiredBundles),
	_lazyStart(lazyStart),
	_runLevel(runLevel),
	_extendsBundle(extendsBundle)
{
}


ManifestInfo::~ManifestInfo()
{
}
