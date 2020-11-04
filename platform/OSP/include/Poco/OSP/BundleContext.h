//
// BundleContext.h
//
// Library: OSP
// Package: Bundle
// Module:  BundleContext
//
// Definition of the BundleContext class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_BundleContext_INCLUDED
#define OSP_BundleContext_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/BundleFilter.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Logger.h"
#include "Poco/Path.h"
#include <vector>


namespace Poco {
namespace OSP {


class Bundle;
class ServiceRegistry;
class BundleEvents;
class SystemEvents;
class BundleLoader;


class OSP_API BundleContext: public Poco::RefCountedObject
	/// A BundleContext gives a BundleActivator access to the
	/// bundle's runtime environment. Via the BundleContext,
	/// the BundleActivator can obtain a pointer to the Bundle
	/// object, to system-wide configuration properties and
	/// to the ServiceRegistry. The BundleContext can also be
	/// used to find other bundles in the system.
{
public:
	using Ptr = Poco::AutoPtr<BundleContext>;
	using ConstPtr = const Ptr;

	Bundle::ConstPtr thisBundle() const;
		/// Returns a pointer to the bundle's Bundle object.

	Bundle::ConstPtr findBundle(const std::string& name) const;
		/// Returns a pointer to the Bundle object for the
		/// bundle with the given name, if such a bundle
		/// exists. Otherwise, returns NULL.

	Bundle::ConstPtr findBundle(int id) const;
		/// Returns a pointer to the Bundle object for the
		/// bundle with the given ID, if such a bundle
		/// exists. Otherwise, returns NULL.

	void listBundles(std::vector<Bundle::Ptr>& bundles) const;
		/// Fills the given vector with all bundles
		/// known to the OSP framework.

	void listBundles(std::vector<Bundle::Ptr>& bundles, BundleFilter::Ptr pFilter) const;
		/// Fills the given vector with all bundles
		/// known to the OSP framework, filtered by the
		/// given BundleFilter.

	ServiceRegistry& registry() const;
		/// Returns a reference to the ServiceRegistry object, which
		/// can be used to find or register services.

	BundleEvents& events() const;
		/// Returns a reference to the global BundleEvents object
		/// which can be used to subscribe to events reporting
		/// state changes in installed bundles.

	SystemEvents& systemEvents() const;
		/// Returns a reference to the global SystemEvents object
		/// which can be used to subscribe to events reporting
		/// state changes in the OSP system.

	Poco::Logger& logger() const;
		/// Returns a reference to a Poco::Logger that the bundle
		/// can use to emit log messages.

	std::string pathForLibrary(const std::string& libraryName);
		/// Returns the full path for the library with the given
		/// libraryName. If libraryName is the empty string,
		/// return the path to the code cache directory.

	const Poco::Path& temporaryDirectory() const;
		/// Returns the path to the bundle's temporary (transient)
		/// data directory.
		///
		/// A bundle can use this directory to create temporary
		/// files that need not be preserved between different
		/// runs of the application.
		///
		/// If the directory does not exist, it is created.
		/// The directory is cleared whenever the bundle is
		/// unloaded.

	const Poco::Path& persistentDirectory() const;
		/// Returns the path to the bundle's persistent
		/// data directory.
		///
		/// A bundle can use this directory to create files
		/// that must be preserved between different runs
		/// of the application.
		///
		/// If the directory does not exist, it is created.
		/// The persistent data directory is never cleared.

	BundleContext::Ptr contextForBundle(Bundle::ConstPtr pBundle) const;
		/// Returns the BundleContext for the given bundle.

protected:
	BundleContext(BundleLoader& loader, Bundle::ConstPtr pBundle, BundleEvents& events, SystemEvents& systemEvents, ServiceRegistry& registry, const Path& persistencyDir);
		/// Creates the BundleContext.

	~BundleContext();
		/// Destroys the BundleContext.

	void initPersistency(const Poco::Path& persistencyPath);
		/// Sets up the temporary and persistent data paths.

	static std::string loggerName(const Bundle* pBundle);
		/// Returns a logger name for the bundle.
		///
		/// The logger's name is "osp.bundle.<symbolic-name>",
		/// where <symbolic-name> is the bundle's symbolic name.

private:
	BundleContext();
	BundleContext(const BundleContext&);
	BundleContext& operator = (const BundleContext&);

	BundleLoader&    _loader;
	Bundle::ConstPtr _pBundle;
	BundleEvents&    _events;
	SystemEvents&    _systemEvents;
	ServiceRegistry& _registry;
	Poco::Logger&    _logger;
	Poco::Path       _temporaryDir;
	Poco::Path       _persistentDir;

	friend class BundleContextFactory;
};


//
// inlines
//
inline Bundle::ConstPtr BundleContext::thisBundle() const
{
	return _pBundle;
}


inline ServiceRegistry& BundleContext::registry() const
{
	return _registry;
}


inline BundleEvents& BundleContext::events() const
{
	return _events;
}


inline SystemEvents& BundleContext::systemEvents() const
{
	return _systemEvents;
}


inline Poco::Logger& BundleContext::logger() const
{
	return _logger;
}


} } // namespace Poco::OSP


#endif // OSP_BundleContext_INCLUDED
