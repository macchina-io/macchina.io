//
// BundleManifest.h
//
// $Id: //poco/1.4/OSP/include/Poco/OSP/BundleManifest.h#2 $
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
// SPDX-License-Identifier: Apache-2.0
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
	typedef Poco::AutoPtr<BundleManifest> Ptr;
	typedef const Ptr ConstPtr;
	
	struct Dependency
	{
		std::string  symbolicName;
		VersionRange versions;
	};
	typedef std::vector<Dependency> Dependencies;
	
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
		
	bool lazyStart() const;
		/// Returns true if lazy startup has been specified for
		/// the bundle.
		
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
	static const std::string EXTENDS_BUNDLE;
	static const std::string BUNDLE_LAZYSTART;
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
	std::string  _extendedBundle;
	bool         _lazyStart;
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


inline bool BundleManifest::lazyStart() const
{
	return _lazyStart;
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
