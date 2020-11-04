//
// BundleManifest.h
//
// Library: OSP
// Package: Bundle
// Module:  BundleManifest
//
// Definition of the BundleManifest class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_BundleManifest_INCLUDED
#define OSP_BundleManifest_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Version.h"
#include "Poco/OSP/VersionRange.h"
#include "Poco/Util/PropertyFileConfiguration.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include <vector>
#include <istream>


namespace Poco {
namespace OSP {


class OSP_API BundleManifest: public Poco::RefCountedObject
	/// The BundleManifest class parses and stores the
	/// manifest of a bundle.
{
public:
	using Ptr = Poco::AutoPtr<BundleManifest>;
	using ConstPtr = const Ptr;

	struct Dependency
	{
		std::string  symbolicName;
		VersionRange versions;
	};
	using Dependencies = std::vector<Dependency>;

    struct Module
    {
    	std::string symbolicName;
    	Version version;
    };
    using Modules = std::vector<Module>;

	BundleManifest(std::istream& istr);
		/// Creates the BundleManifest by parsing the
		/// META-INF/manifest.mf file.

	const std::string& name() const;
		/// Returns the name of the bundle.

	const std::string& symbolicName() const;
		/// Returns the symbolic name of the bundle.

	const Version& version() const;
		/// Returns the version of the bundle.

	const std::string& vendor() const;
		/// Returns the bundle's vendor name, or
		/// an empty string if no vendor name
		/// has been specified in the pManifest->

	const std::string& copyright() const;
		/// Returns the bundle's copyright information,
		/// or an empty string if no copyright information
		/// has been specified in the pManifest->

	const std::string& activatorClass() const;
		/// Returns the class name of the bundle's activator,
		/// or an empty string if the manifest does not
		/// specify an activator.

	const std::string& activatorLibrary() const;
		/// Returns the name of the library containing
		/// the bundle's activator class, or an empty string
		/// if the manifest does not specify an activator library.

	const Dependencies& requiredBundles() const;
		/// Returns a vector containing information about
		/// all bundles required by this bundle.

	const Dependencies& requiredModules() const;
		/// Returns a vector containing information about
		/// all modules required by this bundle.

	const Modules& providedModules() const;
		/// Returns a vector containing information about
		/// all modules provided by this bundle.

	bool lazyStart() const;
		/// Returns true if lazy startup has been specified for
		/// the bundle.

	bool sealed() const;
		/// Returns true if the bundle is sealed and cannot be
		/// extended by an extension bundle.

	bool preventUninstall() const;
		/// Returns true if the bundle must not be uninstalled
		/// at run-time.
		///
		/// This is mostly useful for bundles that cannot be
		/// cleanly stopped. An example are bundles that
		/// contain third-party libraries that, once loaded,
		/// cannot be unloaded cleanly.

	const std::string& runLevel() const;
		/// Returns the bundle's run level.
		///
		/// If the bundle does not specify a run level,
		/// returns the default "999-user".

	const std::string& extendedBundle() const;
		/// Returns the name of the bundle this
		/// bundle extends, or an empty string
		/// if the bundle is not an extension bundle.

	Poco::Util::AbstractConfiguration& rawManifest() const;
		/// Returns a reference to the configuration containing
		/// the raw manifest data.

	static const std::string VERSION;
	static const std::string MANIFEST_VERSION;
	static const std::string BUNDLE_NAME;
	static const std::string BUNDLE_VENDOR;
	static const std::string BUNDLE_COPYRIGHT;
	static const std::string BUNDLE_SYMBOLICNAME;
	static const std::string BUNDLE_VERSION;
	static const std::string BUNDLE_ACTIVATOR;
	static const std::string REQUIRE_BUNDLE;
	static const std::string REQUIRE_MODULE;
	static const std::string PROVIDE_MODULE;
	static const std::string EXTENDS_BUNDLE;
	static const std::string BUNDLE_LAZYSTART;
	static const std::string BUNDLE_SEALED;
	static const std::string BUNDLE_PREVENTUNINSTALL;
	static const std::string BUNDLE_RUNLEVEL;
	static const std::string BUNDLE_CERTIFICATE;
	static const std::string DEFAULT_RUNLEVEL;

protected:
	void parseManifest();
		/// Parses the bundle's manifest file.

	void parseActivator(const std::string& activator);
		/// Parses the Bundle-Activator property.

	void parseRequiredBundles(const std::string& requiredBundles);
		/// Parses the Required-Bundles property.

	void parseRequiredModules(const std::string& requiredModules);
		/// Parses the Required-Modules property.

	void parseProvidedModules(const std::string& providedModules);
		/// Parses the Provided-Modules property.

	void parseRequiredItems(const std::string& requiredItems, const std::string& what, const std::string& versionKeyword, Dependencies& dependencies);
		/// Parses the Required-Bundles or Required-Modules property and stored
		/// result in dependencies.

	~BundleManifest();
		/// Destroys the BundleManifest.

private:
	BundleManifest();
	BundleManifest(const BundleManifest&);
	BundleManifest& operator = (const BundleManifest&);

	std::string  _name;
	std::string  _symbolicName;
	Version      _version;
	std::string  _vendor;
	std::string  _copyright;
	std::string  _activatorClass;
	std::string  _activatorLibrary;
	Dependencies _requiredBundles;
	Dependencies _requiredModules;
	Modules      _providedModules;
	std::string  _extendedBundle;
	bool         _lazyStart;
	bool         _sealed;
	bool         _preventUninstall;
	std::string  _runLevel;

	Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> _pManifest;
};


//
// inlines
//
inline const std::string& BundleManifest::name() const
{
	return _name;
}


inline const std::string& BundleManifest::symbolicName() const
{
	return _symbolicName;
}


inline const Version& BundleManifest::version() const
{
	return _version;
}


inline const std::string& BundleManifest::vendor() const
{
	return _vendor;
}


inline const std::string& BundleManifest::copyright() const
{
	return _copyright;
}


inline const std::string& BundleManifest::activatorClass() const
{
	return _activatorClass;
}


inline const std::string& BundleManifest::activatorLibrary() const
{
	return _activatorLibrary;
}


inline const BundleManifest::Dependencies& BundleManifest::requiredBundles() const
{
	return _requiredBundles;
}


inline const BundleManifest::Dependencies& BundleManifest::requiredModules() const
{
	return _requiredModules;
}


inline const BundleManifest::Modules& BundleManifest::providedModules() const
{
	return _providedModules;
}


inline bool BundleManifest::lazyStart() const
{
	return _lazyStart;
}


inline bool BundleManifest::sealed() const
{
	return _sealed;
}


inline bool BundleManifest::preventUninstall() const
{
	return _preventUninstall;
}


inline const std::string& BundleManifest::runLevel() const
{
	return _runLevel;
}


inline const std::string& BundleManifest::extendedBundle() const
{
	return _extendedBundle;
}


} } // namespace Poco::OSP


#endif // OSP_BundleManifest_INCLUDED
