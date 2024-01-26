//
// Wrapper.cpp
//
// Library: JS/Core
// Package: Wrappers
// Module:  Wrapper
//
// Copyright (c) 2013-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/JS/Core/Wrapper.h"
#include <iostream>


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
	try
	{
		cleanup();
	}
	catch (...)
	{
		poco_unexpected();
	}
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
	std::size_t n = _wrappers.erase(pWrapper);
	poco_assert (n == 1);
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

	// Note: a trivial _registry.erase(pIsolate) will not work here on all platforms.
	// We need to clean up the registry before it is removed from the map.
	// This is because deleting a Wrapper instance in cleanup()
	// will result in a call to forIsolate(), followed by unregisterWrapper().
	// Some implementations of erase(pIsolate) remove the registry from the map
	// first, before destroying it, resulting eventually in a crash (double delete).

	RegistryMap::iterator it = _registry.find(pIsolate);
	if (it != _registry.end())
	{
		it->second->cleanup();
		_registry.erase(it);
	}
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


std::string Wrapper::toString(v8::Isolate* pIsolate, v8::Local<v8::Value> value)
{
	v8::String::Utf8Value utf8(pIsolate, value);
	return std::string(*utf8, utf8.length());
}


std::string Wrapper::toString(v8::Isolate* pIsolate, v8::Local<v8::Name> value)
{
	v8::String::Utf8Value utf8(pIsolate, value);
	return std::string(*utf8, utf8.length());
}


std::string Wrapper::toString(v8::Isolate* pIsolate, v8::Local<v8::String> value)
{
	v8::String::Utf8Value utf8(pIsolate, value);
	return std::string(*utf8, utf8.length());
}


std::string Wrapper::toString(v8::Isolate* pIsolate, v8::MaybeLocal<v8::Value> maybeValue)
{
	v8::Local<v8::Value> value;
	if (maybeValue.ToLocal(&value))
	{
		v8::String::Utf8Value utf8(pIsolate, value);
		return std::string(*utf8, utf8.length());
	}
	else
	{
		return std::string();
	}
}


std::string Wrapper::toString(v8::Isolate* pIsolate, v8::MaybeLocal<v8::String> maybeValue)
{
	v8::Local<v8::String> value;
	if (maybeValue.ToLocal(&value))
	{
		v8::String::Utf8Value utf8(pIsolate, value);
		return std::string(*utf8, utf8.length());
	}
	else
	{
		return std::string();
	}
}

v8::Local<v8::String> Wrapper::toV8String(v8::Isolate* pIsolate, const std::string& value, v8::NewStringType type)
{
	v8::MaybeLocal<v8::String> maybeV8String = v8::String::NewFromUtf8(
		pIsolate,
		value.data(),
		type,
		static_cast<int>(value.length()));

	v8::Local<v8::String> v8String;
	if (maybeV8String.ToLocal(&v8String))
	{
		return v8String;
	}
	else
	{
		return v8::String::Empty(pIsolate);
	}
}


v8::Local<v8::String> Wrapper::toV8Internalized(v8::Isolate* pIsolate, const std::string& value)
{
	return toV8String(pIsolate, value, v8::NewStringType::kInternalized);
}


v8::Local<v8::String> Wrapper::toV8String(v8::Isolate* pIsolate, const char* value)
{
	v8::MaybeLocal<v8::String> maybeV8String = v8::String::NewFromUtf8(pIsolate, value);

	v8::Local<v8::String> v8String;
	if (maybeV8String.ToLocal(&v8String))
	{
		return v8String;
	}
	else
	{
		return v8::String::Empty(pIsolate);
	}
}


void Wrapper::reportEmptySetResult(const char* file, int line)
{
	std::cerr << "!!!\n!!! WARNING: Object/Array->Set() returned empty result in file '" << file << "', line " << line << ".\n!!!" << std::endl;
}


} } } // namespace Poco::JS::Core
