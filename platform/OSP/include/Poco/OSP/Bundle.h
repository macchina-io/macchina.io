//
// Bundle.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/Bundle.h#1 $
//
// Library: OSP
// Package: Bundle
// Module:  Bundle
//
// Definition of the Bundle class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_Bundle_INCLUDED
#define OSP_Bundle_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/BundleManifest.h"
#include "Poco/OSP/BundleStorage.h"
#include "Poco/OSP/BundleProperties.h"
#include "Poco/OSP/LanguageTag.h"
#include "Poco/Util/LayeredConfiguration.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"
#include "Poco/Mutex.h"
#include <set>


namespace Poco {
namespace OSP {


class BundleActivator;
class BundleLoader;
class BundleEvents;


class OSP_API Bundle: public Poco::RefCountedObject
	/// This class represents a Bundle in OSP.
	///
	/// For every bundle directory or file found in
	/// the OSP bundle repository, a Bundle object
	/// is created. The bundle class stores the state
	/// of the Bundle and gives access to the bundle's
	/// manifest, configuration properties and resources.
	///
	/// The Bundle class also manages localized resources.
{
public:
	typedef Poco::AutoPtr<Bundle> Ptr;
	typedef const Ptr ConstPtr;

	enum State
	{
		BUNDLE_INSTALLED,
		BUNDLE_UNINSTALLED,
		BUNDLE_RESOLVED,
		BUNDLE_STARTING,
		BUNDLE_ACTIVE,
		BUNDLE_STOPPING
	};
	
	int id() const;
		/// Returns the internal ID of the bundle.
		///
		/// Note that internal IDs are only valid during
		/// the runtime of an OSP-based application and may
		/// change between restarts.
		///
		/// Bundle IDs are guaranteed to be unique within
		/// the scope of a BundleLoader. No assumptions shall
		/// be made that bundle IDs are given out in a certain
		/// order or that they are strictly consecutive.

	State state() const;
		/// Returns the current state of the bundle.
		
	const std::string& stateString() const;
		/// Returns the current state of the bundle as a string.
		
	bool isResolved() const;
		/// Returns true iff the bundle has been successfully
		/// resolved.
		///
		/// In other words, the bundle's state must be one of
		/// BUNDLE_RESOLVED, BUNDLE_STARTING, BUNDLE_ACTIVE, BUNDLE_STOPPED.
		
	bool isActive() const;
		/// Returns true iff the bundle's state is BUNDLE_ACTIVE.
		
	bool isStarted() const;
		/// Returns true iff the bundle's state is BUNDLE_STARTING,
		/// BUNDLE_ACTIVE or BUNDLE_STOPPING.
	
	std::string path() const;
		/// Returns the path to the bundle's directory
		/// or archive file.
		
	const std::string& name() const;
		/// Returns the bundle's name.
		///
		/// If the name contains a reference to a property,
		/// (${<property>}) the reference is expanded first.
		
	const std::string& symbolicName() const;
		/// Returns the symbolic name of the bundle.
		
	const Version& version() const;
		/// Returns the bundle's version.
		
	const std::string& vendor() const;
		/// Returns the bundle's vendor name, or
		/// an empty string if no vendor name
		/// has been specified in the pManifest->
		///
		/// If the vendor string contains a reference to a property,
		/// (${<property>}) the reference is expanded first.
		
	const std::string& copyright() const;
		/// Returns the bundle's copyright information,
		/// or an empty string if no copyright information
		/// has been specified in the pManifest->
		///
		/// If the copyright string contains a reference to a property,
		/// (${<property>}) the reference is expanded first.
		
	const std::string& activatorClass() const;
		/// Returns the class name of the bundle's activator,
		/// or an empty string if the manifest does not
		/// specify an activator.
		
	const std::string& activatorLibrary() const;
		/// Returns the name of the library containing
		/// the bundle's activator class, or an empty string
		/// if the manifest does not specify an activator library.
		
	BundleActivator* activator() const;
		/// If the bundle is active and has an activator,
		/// returns a pointer to the bundle's activator.
		/// Otherwise, returns NULL.
	
	bool lazyStart() const;
		/// Returns true whether lazy start has been specified for
		/// the bundle.
		
	const std::string& runLevel() const;
		/// Returns the bundle's run level.
		/// 
		/// If the bundle does not specify a run level,
		/// returns the default "999-user".	
		
	bool isExtensionBundle() const;
		/// Returns true iff the bundle is an extension bundle.
		///
		/// An extension bundle will "donate" all of its
		/// resources to the bundle it extends. This means
		/// that all properties defined in the extension
		/// bundle will become properties of the extended
		/// bundle. Also, all resources of the extension
		/// bundle will become available through 
		/// getResource() and getLocalizedResource() on
		/// the extended bundle.
		
	Bundle::Ptr extendedBundle() const;
		/// If the bundle is an extension bundle, returns
		/// the extended bundle, or in other words,
		/// the bundle that this bundle extends.
		///
		/// Returns a null pointer if the bundle is not
		/// an extension bundle, or the extended bundle
		/// has not been loaded.
	
	const Poco::Util::AbstractConfiguration& properties() const;
		/// Returns the bundle's properties, which are
		/// obtained from the bundle's "bundle.properties"
		/// file (and its optional localizations).
		
	std::istream* getResource(const std::string& name) const;
		/// Creates and returns an input stream for reading
		/// the bundle's (non-localized) resource with the given
		/// name.
		///
		/// Resources are ordinary files stored within the
		/// bundle's directory or archive file.
		///
		/// Returns NULL if the resource does not exist.
		///
		/// The caller gets ownership of the input stream and
		/// must delete it when it's no longer needed.

	std::istream* getLocalizedResource(const std::string& name) const;
		/// Creates and returns an input stream for reading
		/// the bundle's localized resource with the given
		/// name.
		///
		/// Resources are ordinary files stored within the
		/// bundle's directory or archive file.
		///
		/// Returns NULL if the resource does not exist.
		///
		/// The caller gets ownership of the input stream and
		/// must delete it when it's no longer needed.

	std::istream* getLocalizedResource(const std::string& name, const LanguageTag& language) const;
		/// Creates and returns an input stream for reading
		/// the bundle's localized (for the given language)
		/// resource with the given name.
		///
		/// Resources are ordinary files stored within the
		/// bundle's directory or archive file.
		///
		/// Returns NULL if the resource does not exist.
		///
		/// The caller gets ownership of the input stream and
		/// must delete it when it's no longer needed.

	void resolve();
		/// Resolves the bundle by verifying the availability
		/// of all required bundles. The bundle must be in
		/// BUNDLE_INSTALLED state. A sucessful resolve()
		/// puts the bundle in BUNDLE_RESOLVED state.
		///
		/// Throws an exception if the bundle cannot be resolved.
		
	void start();
		/// Starts the bundle. The bundle's state must be
		/// BUNDLE_RESOLVED.
		///
		/// Puts the bundle in BUNDLE_STARTING state, loads
		/// the bundle's activator and invokes it, and
		/// finally puts the bundle in BUNDLE_RUNNING state.
		
	void stop();
		/// Stops the bundle. The bundle's state must be
		/// BUNDLE_ACTIVE. Puts the bundle into BUNDLE_STOPPING
		/// state, stops the bundle activator and finally puts
		/// the bundle into BUNDLE_RESOLVED state.
		
	void uninstall();
		/// Uninstalls the bundle. The bundle must be in
		/// BUNDLE_INSTALLED or BUNDLE_RESOLVED state. 
		/// The bundle is also removed from the bundle repository.

	const BundleManifest::Dependencies& requiredBundles() const;
		/// Returns a vector containing information about
		/// all bundles required by this bundle.
		
	const BundleManifest& manifest() const;
		/// Returns a reference to the BundleManifest object.
		
	const LanguageTag& language() const;
		/// Returns the language used for localization.
		
	static const std::string MANIFEST_FILE;
	static const std::string PROPERTIES_FILE;
	static const std::string BUNDLE_INSTALLED_STRING;
	static const std::string BUNDLE_UNINSTALLED_STRING;
	static const std::string BUNDLE_RESOLVED_STRING;
	static const std::string BUNDLE_STARTING_STRING;
	static const std::string BUNDLE_ACTIVE_STRING;
	static const std::string BUNDLE_STOPPING_STRING;
	static const std::string BUNDLE_INVALID_STRING;

protected:
	void loadManifest();
		/// Loads the bundle's manifest file.
		
	void loadProperties();
		/// Loads the bundle's properties.
	
	void addProperties(const std::string& path);
		/// Adds the properties from the property file
		/// specified by path to the bundle's properties.

	BundleEvents& events();
		/// Returns a reference to the BundleEvents object.
		
	BundleStorage& storage();
		/// Returns a reference to the BundleStorage object.

	void setActivator(BundleActivator* pActivator);
		/// Sets the BundleActivator.
		
	void addExtensionBundle(Bundle* pExtensionBundle);
		/// Adds an extension bundle.
		///
		/// An extension bundle will "donate" all of its
		/// resources to the bundle it extends. This means
		/// that all properties defined in the extension
		/// bundle will become properties of the extended
		/// bundle. Also, all resources of the extension
		/// bundle will become available through 
		/// getResource() and getLocalizedResource() on
		/// the extended bundle.
		
	void removeExtensionBundle(Bundle* pExtensionBundle);
		/// Removes an extension bundle.
		///
		/// The resources and properties of the extension bundle
		/// will no longer be available to the extended bundle.

	Bundle(int id, BundleLoader& loader, BundleStorage::Ptr pStorage, const LanguageTag& language);
		/// Creates the Bundle and reads the manifest
		/// using the given BundleStorage object.
		///
		/// The bundle takes ownership of the BundleStorage object.
		
	~Bundle();
		/// Destroys the Bundle.

private:
	Bundle();
	Bundle(const Bundle&);
	Bundle& operator = (const Bundle&);

	int                     _id;
	State                   _state;
	BundleLoader&           _loader;
	BundleStorage::Ptr      _pStorage;
	LanguageTag             _language;
	BundleManifest::Ptr     _pManifest;
	std::string             _name;
	std::string             _vendor;
	std::string             _copyright;
	BundleProperties::Ptr   _pProperties;
	BundleActivator*        _pActivator;
	std::set<Bundle::Ptr>   _extensionBundles;
	mutable Poco::FastMutex _extensionBundlesMutex;
	
	friend class BundleLoader;
	friend class BundleFactory;
};


//
// inlines
//
inline int Bundle::id() const
{
	return _id;
}


inline Bundle::State Bundle::state() const
{
	return _state;
}


inline bool Bundle::isResolved() const
{
	return _state == BUNDLE_RESOLVED
	    || _state == BUNDLE_STARTING
	    || _state == BUNDLE_ACTIVE
	    || _state == BUNDLE_STOPPING;
}


inline bool Bundle::isActive() const
{
	return _state == BUNDLE_ACTIVE;
}


inline bool Bundle::isStarted() const
{
	return _state == BUNDLE_STARTING
	    || _state == BUNDLE_ACTIVE
	    || _state == BUNDLE_STOPPING;
}


inline std::string Bundle::path() const
{
	return _pStorage->path();
}


inline const std::string& Bundle::name() const
{
	return _name;
}


inline const std::string& Bundle::symbolicName() const
{
	return _pManifest->symbolicName();
}


inline const Version& Bundle::version() const
{
	return _pManifest->version();
}


inline const std::string& Bundle::vendor() const
{
	return _vendor;
}


inline const std::string& Bundle::copyright() const
{
	return _copyright;
}


inline const std::string& Bundle::activatorClass() const
{
	return _pManifest->activatorClass();
}


inline const std::string& Bundle::activatorLibrary() const
{
	return _pManifest->activatorLibrary();
}


inline BundleActivator* Bundle::activator() const
{
	return _pActivator;
}


inline bool Bundle::lazyStart() const
{
	return _pManifest->lazyStart();
}


inline const std::string& Bundle::runLevel() const
{
	return _pManifest->runLevel();
}


inline const Poco::Util::AbstractConfiguration& Bundle::properties() const
{
	return *_pProperties;
}


inline const BundleManifest::Dependencies& Bundle::requiredBundles() const
{
	return _pManifest->requiredBundles();
}


inline const BundleManifest& Bundle::manifest() const
{
	return *_pManifest;
}


inline const LanguageTag& Bundle::language() const
{
	return _language;
}


inline BundleStorage& Bundle::storage()
{
	return *_pStorage;
}


} } // namespace Poco::OSP


#endif // OSP_Bundle_INCLUDED
