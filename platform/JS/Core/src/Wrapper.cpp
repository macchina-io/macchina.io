//
// Wrapper.cpp
//
// $Id: //poco/1.4/JS/Core/src/Wrapper.cpp#4 $
//
// Library: JSCore
// Package: JSCore
// Module:  Wrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/JS/Core/Wrapper.h"


namespace Poco {
namespace JS {
namespace Core {


//
// WeakPersistentWrapperRegistry
//


WeakPersistentWrapperRegistry::RegistryMap WeakPersistentWrapperRegistry::_registry;
Poco::Mutex WeakPersistentWrapperRegistry::_registryMutex;


WeakPersistentWrapperRegistry::WeakPersistentWrapperRegistry()
{
}

	
WeakPersistentWrapperRegistry::~WeakPersistentWrapperRegistry()
{
	cleanup();
}

	
void WeakPersistentWrapperRegistry::registerWrapper(WeakPersistentWrapperBase* pWrapper)
{
#ifdef _DEBUG
	WrapperSet::iterator it = _wrappers.find(pWrapper);
	poco_assert (it == _wrappers.end());
#endif

	_wrappers.insert(pWrapper);
}

	
void WeakPersistentWrapperRegistry::unregisterWrapper(WeakPersistentWrapperBase* pWrapper)
{
	_wrappers.erase(pWrapper);
}


void WeakPersistentWrapperRegistry::cleanup()
{
	WrapperSet::iterator it = _wrappers.begin();
	while (it != _wrappers.end())
	{
		delete *it; // will remove from map
		it = _wrappers.begin();
	}
	poco_assert (_wrappers.empty());
}

	
WeakPersistentWrapperRegistry& WeakPersistentWrapperRegistry::forIsolate(v8::Isolate* pIsolate)
{
	Poco::Mutex::ScopedLock lock(_registryMutex);

	RegistryMap::iterator it = _registry.find(pIsolate);
	if (it != _registry.end())
	{
		return *it->second;
	}
	else
	{
		WeakPersistentWrapperRegistry::Ptr pWrapper = new WeakPersistentWrapperRegistry;
		_registry[pIsolate] = pWrapper;
		return *pWrapper;
	}
}

	
void WeakPersistentWrapperRegistry::cleanupIsolate(v8::Isolate* pIsolate)
{
	Poco::Mutex::ScopedLock lock(_registryMutex);

	_registry.erase(pIsolate);
}


//
// WeakPersistentWrapperBase
//


WeakPersistentWrapperBase::~WeakPersistentWrapperBase()
{
}


//
// Wrapper
//


Wrapper::Wrapper()
{
}


Wrapper::~Wrapper()
{
}


std::string Wrapper::toString(v8::Local<v8::Value> value)
{
	v8::String::Utf8Value utf8(value);
	return std::string(*utf8);
}


} } } // namespace Poco::JS::Core
