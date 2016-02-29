//
// BundleManifest.cpp
//
// $Id: //poco/1.7/OSP/src/BundleManifest.cpp#1 $
//
// Library: OSP
// Package: Bundle
// Module:  BundleManifest
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleManifest.h"
#include "Poco/OSP/OSPException.h"
#include <memory>
#include <algorithm>
#include <cctype>


namespace Poco {
namespace OSP {


const std::string BundleManifest::VERSION("1.0");
const std::string BundleManifest::MANIFEST_VERSION("Manifest-Version");
const std::string BundleManifest::BUNDLE_NAME("Bundle-Name");
const std::string BundleManifest::BUNDLE_VENDOR("Bundle-Vendor");
const std::string BundleManifest::BUNDLE_COPYRIGHT("Bundle-Copyright");
const std::string BundleManifest::BUNDLE_SYMBOLICNAME("Bundle-SymbolicName");
const std::string BundleManifest::BUNDLE_VERSION("Bundle-Version");
const std::string BundleManifest::BUNDLE_ACTIVATOR("Bundle-Activator");
const std::string BundleManifest::REQUIRE_BUNDLE("Require-Bundle");
const std::string BundleManifest::EXTENDS_BUNDLE("Extends-Bundle");
const std::string BundleManifest::BUNDLE_LAZYSTART("Bundle-LazyStart");
const std::string BundleManifest::BUNDLE_RUNLEVEL("Bundle-RunLevel");
const std::string BundleManifest::BUNDLE_CERTIFICATE("Bundle-Certificate");
const std::string BundleManifest::DEFAULT_RUNLEVEL("999-user");


BundleManifest::BundleManifest(std::istream& istr):
	_lazyStart(false),	
	_pManifest(new Poco::Util::PropertyFileConfiguration(istr))
{
	parseManifest();
}


BundleManifest::~BundleManifest()
{
}


void BundleManifest::parseManifest()
{
	std::string manifestVersion = _pManifest->getString(MANIFEST_VERSION);
	if (manifestVersion != VERSION)
		throw ManifestException("Unsupported manifest version", manifestVersion);
	
	_name           = _pManifest->getString(BUNDLE_NAME);
	_symbolicName   = _pManifest->getString(BUNDLE_SYMBOLICNAME);
	_version        = _pManifest->getString(BUNDLE_VERSION);
	_vendor         = _pManifest->getString(BUNDLE_VENDOR, "");
	_copyright      = _pManifest->getString(BUNDLE_COPYRIGHT, "");
	_lazyStart      = _pManifest->getBool(BUNDLE_LAZYSTART, false);
	_runLevel       = _pManifest->getString(BUNDLE_RUNLEVEL, DEFAULT_RUNLEVEL);
	_extendedBundle = _pManifest->getString(EXTENDS_BUNDLE, "");
	
	parseActivator(_pManifest->getString(BUNDLE_ACTIVATOR, ""));
	parseRequiredBundles(_pManifest->getString(REQUIRE_BUNDLE, ""));
}


void BundleManifest::parseActivator(const std::string& activator)
{
	std::string clazz;
	std::string library;
	
	std::string::const_iterator it(activator.begin());
	std::string::const_iterator end(activator.end());
	
	while (it != end && std::isspace(*it)) ++it;
	while (it != end && !std::isspace(*it) && *it != ';') clazz += *it++;
	while (it != end && std::isspace(*it)) ++it;
	if (it != end)
	{
		if (*it == ';')
		{
			++it;
			while (it != end && std::isspace(*it)) ++it;
			std::string keyword;
			while (it != end && !std::isspace(*it) && *it != '=') keyword += *it++;
			if (keyword != "library") throw ManifestException(BUNDLE_ACTIVATOR, "Unknown keyword following activator class name");
			while (it != end && std::isspace(*it)) ++it;
			if (it == end || *it != '=') throw ManifestException(BUNDLE_ACTIVATOR, "The library keyword must be followed by '='");
			++it;
			while (it != end && std::isspace(*it)) ++it;
			while (it != end && !std::isspace(*it)) library += *it++;
			while (it != end && std::isspace(*it)) ++it;
		}
		if (it != end) throw ManifestException(BUNDLE_ACTIVATOR, "Invalid characters after activator class name");
	}
	std::swap(clazz, _activatorClass);
	std::swap(library, _activatorLibrary);
}


void BundleManifest::parseRequiredBundles(const std::string& requiredBundles)
{
	std::string::const_iterator it(requiredBundles.begin());
	std::string::const_iterator end(requiredBundles.end());
	
	while (it != end)
	{
		while (it != end && std::isspace(*it)) ++it;
		std::string name;
		while (it != end && !std::isspace(*it) && *it != ',' && *it != ';') name += *it++;
		if (!name.empty())
		{
			Dependency dependency;
			dependency.symbolicName = name;
			while (it != end && std::isspace(*it)) ++it;
			if (it != end && *it == ';')
			{
				++it;
				while (it != end && std::isspace(*it)) ++it;
				std::string keyword;
				while (it != end && !std::isspace(*it) && *it != '=') keyword += *it++;
				if (keyword != "bundle-version") throw ManifestException(REQUIRE_BUNDLE, "Unknown keyword following bundle name");
				while (it != end && std::isspace(*it)) ++it;
				if (it == end || *it != '=') throw ManifestException(REQUIRE_BUNDLE, "The bundle-version keyword must be followed by '='");
				++it;
				while (it != end && std::isspace(*it)) ++it;	
				if (it != end)
				{
					if (*it == '(' || *it == '[')
					{
						bool includeLower = *it == '[';
						++it;
						while (it != end && std::isspace(*it)) ++it;
						std::string lowerStr;
						while (it != end && !std::isspace(*it) && *it != ',') lowerStr += *it++;
						while (it != end && std::isspace(*it)) ++it;
						if (it != end && *it == ',')
						{
							++it;
							while (it != end && std::isspace(*it)) ++it;
							std::string upperStr;
							while (it != end && !std::isspace(*it) && *it != ')' && *it != ']') upperStr += *it++;
							while (it != end && std::isspace(*it)) ++it;
							if (it != end && (*it == ')' || *it == ']'))
							{
								bool includeUpper = *it == ']';
								++it;
								Version lower(lowerStr);
								Version upper(upperStr);
								dependency.versions = VersionRange(lower, includeLower, upper, includeUpper);
							}
							else throw ManifestException(REQUIRE_BUNDLE, "Invalid version range specified");
						}
					}
					else
					{
						std::string versionStr;
						while (it != end && !std::isspace(*it) && *it != ',') versionStr += *it++;
						Version version(versionStr);
						dependency.versions = VersionRange(version, true, version, true);
					}
				}
				else throw ManifestException(REQUIRE_BUNDLE, "The bundle-version keyword must be followed by a version or version range");
			}
			_requiredBundles.push_back(dependency);
		}
		if (it != end && *it == ',') ++it;
	}
}


} } // namespace Poco::OSP
