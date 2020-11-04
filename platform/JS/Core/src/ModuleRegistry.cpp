//
// ModuleRegistry.cpp
//
// Library: JS/Core
// Package: Execution
// Module:  ModuleRegistry
//
// Definition of the ModuleRegistry interface.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/ModuleRegistry.h"


namespace Poco {
namespace JS {
namespace Core {


ModuleRegistry::ModuleRegistry()
{
}


ModuleRegistry::~ModuleRegistry()
{
}


void ModuleRegistry::registerModule(const std::string& name, Module::Ptr pModule)
{
	Poco::FastMutex::ScopedLock lock(_mutex);
	
	ModuleMap::iterator it = _modules.find(name);
	if (it == _modules.end())
	{
		_modules[name] = pModule;
	}
	else throw Poco::ExistsException(name);
}

	
void ModuleRegistry::unregisterModule(const std::string& name)
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	_modules.erase(name);
}


Module::Ptr ModuleRegistry::findModule(const std::string& name) const
{
	Poco::FastMutex::ScopedLock lock(_mutex);

	Module::Ptr pModule;	
	ModuleMap::const_iterator it = _modules.find(name);
	if (it != _modules.end())
	{
		pModule = it->second;
	}
	return pModule;
}


} } } // namespace Poco::JS::Core
