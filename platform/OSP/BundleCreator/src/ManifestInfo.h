//
// ManifestInfo.h
//
// $Id: //poco/1.6/OSP/BundleCreator/src/ManifestInfo.h#1 $
//
// Declaration of the ManifestInfo class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/Version.h"
#include "Poco/OSP/VersionRange.h"
#include <vector>


class ManifestInfo
{
public:
	struct Dependency
	{
		std::string symbolicName;
		std::string versions;
	};
	typedef std::vector<Dependency> Dependencies;

	ManifestInfo(const std::string& name,
		const std::string& symbolicName,
		const Poco::OSP::Version& version,
		const std::string& vendor,
		const std::string& copyright,
		const std::string& activatorClass,
		const std::string& activatorLibrary,
		const Dependencies& requiredBundles,
		bool lazyStart,
		const std::string& runLevel,
		const std::string& extendsBundle);

	~ManifestInfo();

	const std::string& name() const;
	const std::string& symbolicName() const;
	Poco::OSP::Version version() const;
	const std::string& vendor() const;
	const std::string& copyright() const;
	const std::string& activatorClass() const;
	const std::string& activatorLibrary() const;
	const Dependencies& requiredBundles() const;
	bool lazyStart() const;
	const std::string& runLevel() const;
	const std::string& extendsBundle() const;

private:
	std::string  _name;
	std::string  _symbolicName;
	Poco::OSP::Version _version;
	std::string  _vendor;
	std::string  _copyright;
	std::string  _activatorClass;
	std::string  _activatorLibrary;
	Dependencies _requiredBundles;
	bool         _lazyStart;
	std::string  _runLevel;
	std::string  _extendsBundle;
};


//
// inlines
//
inline const std::string& ManifestInfo::name() const
{
	return _name;
}


inline const std::string& ManifestInfo::symbolicName() const
{
	return _symbolicName;
}


inline Poco::OSP::Version ManifestInfo::version() const
{
	return _version;
}


inline const std::string& ManifestInfo::vendor() const
{
	return _vendor;
}


inline const std::string& ManifestInfo::copyright() const
{
	return _copyright;
}


inline const std::string& ManifestInfo::activatorClass() const
{
	return _activatorClass;
}


inline const std::string& ManifestInfo::activatorLibrary() const
{
	return _activatorLibrary;
}


inline const ManifestInfo::Dependencies& ManifestInfo::requiredBundles() const
{
	return _requiredBundles;
}


inline bool ManifestInfo::lazyStart() const
{
	return _lazyStart;
}


inline const std::string& ManifestInfo::runLevel() const
{
	return _runLevel;
}


inline const std::string& ManifestInfo::extendsBundle() const
{
	return _extendsBundle;
}
