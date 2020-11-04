//
// ModuleRegistry.h
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


#ifndef JS_Core_ModuleRegistry_INCLUDED
#define JS_Core_ModuleRegistry_INCLUDED


#include "Poco/JS/Core/Core.h"
#include "Poco/JS/Core/Module.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Mutex.h"
#include <map>


namespace Poco {
namespace JS {
namespace Core {


class JSCore_API ModuleRegistry: public Poco::RefCountedObject
	/// A registry of native JavaScript modules.
{
public:
	using Ptr = Poco::AutoPtr<ModuleRegistry>;

	ModuleRegistry();
		/// Creates the ModuleRegistry.

	~ModuleRegistry();
		/// Destroys the ModuleRegistry.

	void registerModule(const std::string& name, Module::Ptr pModule);
		/// Registers the given Module under the given name.
		///
		/// Throws a Poco::ExistsException if another module with the same
		/// name has already been registered.

	void unregisterModule(const std::string& name);
		/// Unregisters the module with the given name.

	Module::Ptr findModule(const std::string& name) const;
		/// Searches for a Module with the given name.
		///
		/// Returns a pointer to the Module if found, otherwise
		/// returns a null pointer.

private:
	using ModuleMap = std::map<std::string, Module::Ptr>;

	ModuleMap _modules;
	mutable Poco::FastMutex _mutex;
};


} } } // namespace Poco::JS::Core


#endif // JS_Core_ModuleRegistry_INCLUDED
