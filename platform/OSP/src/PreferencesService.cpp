//
// PreferencesService.cpp
//
// Library: OSP
// Package: PreferencesService
// Module:  PreferencesService
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/PreferencesService.h"


namespace Poco {
namespace OSP {


const std::string PreferencesService::SERVICE_NAME("osp.core.preferences");


PreferencesService::PreferencesService(const Poco::Path& persistencyDir, Poco::Util::AbstractConfiguration* pGlobalConfig):
	_path(persistencyDir),
	_pConfig(new Configuration(pGlobalConfig))
{
	_path.makeDirectory();
	_path.pushDirectory(SERVICE_NAME);
}


PreferencesService::~PreferencesService()
{
}


Preferences::Ptr PreferencesService::preferences(const std::string& bundleOrServiceID)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	PrefsMap::iterator it = _prefsMap.find(bundleOrServiceID);
	if (it == _prefsMap.end())
	{
		Poco::Path prefsPath(_path);
		prefsPath.makeDirectory();
		prefsPath.setFileName(bundleOrServiceID + ".properties");
		Preferences::Ptr pPrefs = new Preferences(prefsPath.toString());
		_prefsMap[bundleOrServiceID] = pPrefs;
		return pPrefs;
	}
	else return it->second;
}


Configuration::Ptr PreferencesService::configuration()
{
	return _pConfig;
}


const std::type_info& PreferencesService::type() const
{
	return typeid(PreferencesService);
}


bool PreferencesService::isA(const std::type_info& otherType) const
{
	std::string name(typeid(PreferencesService).name());
	return name == otherType.name() || Service::isA(otherType);
}


} } // namespace Poco::OSP
