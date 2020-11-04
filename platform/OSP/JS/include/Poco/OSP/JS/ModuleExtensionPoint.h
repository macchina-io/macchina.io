//
// ModuleExtensionPoint.h
//
// Library: OSP/JS
// Package: Module
// Module:  ModuleExtensionPoint
//
// Definition of the ModuleExtensionPoint class.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_JS_ModuleExtensionPoint_INCLUDED
#define OSP_JS_ModuleExtensionPoint_INCLUDED


#include "Poco/OSP/JS/JS.h"
#include "Poco/OSP/JS/ModuleFactory.h"
#include "Poco/OSP/ExtensionPoint.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/BundleEvent.h"
#include "Poco/JS/Core/ModuleRegistry.h"
#include "Poco/ClassLoader.h"
#include "Poco/Mutex.h"
#include "Poco/SharedPtr.h"
#include <map>


namespace Poco {
namespace OSP {
namespace JS {


class OSPJS_API ModuleExtensionPoint: public Poco::OSP::ExtensionPoint
	/// ModuleExtensionPoint is used to add native (C++) JavaScript Modules to the
	/// JavaScript environment.
	///
	/// To register a native JavaScript Module:
	///     <extension point="com.appinf.osp.js.module"
	///                module="<module>"
	///                class="<factory class>"
	///                library="<library name>"/>
	///
	/// Note that the extension points are automatically removed if a bundle is stopped.
	///
	/// The following attributes can be specified for the extension point:
	///    * module: the name of the module (e.g., "net"), as passed as argument to the
	///      JavaScript require() function.
	///    * class: the class name of the ModuleFactory (see the ModuleFactory and Poco::JS::Module classes).
	///    * library: the name of the shared library containing the ModuleFactory.
{
public:
	using Ptr = Poco::AutoPtr<ModuleExtensionPoint>;

	ModuleExtensionPoint(Poco::OSP::BundleContext::Ptr pContext);
		/// Creates the ModuleExtensionPoint, using the given bundle context.

	~ModuleExtensionPoint();
		/// Destroys the ModuleExtensionPoint.

	Poco::JS::Core::ModuleRegistry::Ptr moduleRegistry() const;
		/// Returns the ModuleRegistry.

	// ExtensionPoint
	void handleExtension(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);

	static const std::string EXTPOINT;

protected:
	void handleModule(Bundle::ConstPtr pBundle, Poco::XML::Element* pExtensionElem);
		/// Handle the Module extension point.

	void onBundleStopped(const void* pSender, Poco::OSP::BundleEvent& ev);
		/// When a bundle is stopped, all of its Modules are automatically disabled.

	static const std::string ATTR_MODULE;
	static const std::string ATTR_CLASS;
	static const std::string ATTR_LIBRARY;
	static const std::string MANIFEST_NAME;

private:
	ModuleExtensionPoint();

	using FactoryPtr = Poco::SharedPtr<ModuleFactory>;
	using Loader = Poco::ClassLoader<ModuleFactory>;
	using LibBundleMap = std::map<std::string, Poco::OSP::Bundle::Ptr>;
	using ModBundleMap = std::map<std::string, Poco::OSP::Bundle::Ptr>;

	BundleContext::Ptr _pContext;
	Poco::JS::Core::ModuleRegistry::Ptr _pModuleRegistry;
	Loader _loader;
	LibBundleMap _libBundleMap;
	ModBundleMap _modBundleMap;
	Poco::FastMutex _mutex;
};


//
// inlines
//
inline Poco::JS::Core::ModuleRegistry::Ptr ModuleExtensionPoint::moduleRegistry() const
{
	return _pModuleRegistry;
}


} } } // namespace Poco::OSP::JS


#endif // OSP_JS_ModuleExtensionPoint_INCLUDED
