//
// AppRegistry.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "AppRegistry.h"


namespace IoT {
namespace Web {
namespace Launcher {


std::string AppRegistry::SERVICE_NAME("io.macchina.web.appregistry");


AppRegistry::AppRegistry()
{
}


AppRegistry::~AppRegistry()
{
}


void AppRegistry::add(const App& app)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	_appMap[app.id] = app;
}


void AppRegistry::remove(const std::string& bundle)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	for (AppMap::iterator it = _appMap.begin(); it != _appMap.end(); ++it)
	{
		if (it->second.pBundle->symbolicName() == bundle)
		{
			_appMap.erase(it);
			break;
		}
	}
}


void AppRegistry::list(AppVec& apps)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	for (AppMap::const_iterator it = _appMap.begin(); it != _appMap.end(); ++it)
	{
		apps.push_back(it->second);
	}
}


const std::type_info& AppRegistry::type() const
{
	return typeid(AppRegistry);
}


bool AppRegistry::isA(const std::type_info& otherType) const
{
	std::string name(typeid(AppRegistry).name());
	return name == otherType.name() || Poco::OSP::Service::isA(otherType);
}


} } } // namespace IoT::Web::Launcher
