//
// ExtensionPointService.h
//
// Library: OSP
// Package: ExtensionPointService
// Module:  ExtensionPointService
//
// Definition of the ExtensionPointService class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_ExtensionPointService_INCLUDED
#define OSP_ExtensionPointService_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/ExtensionPoint.h"
#include "Poco/OSP/Service.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/BundleEvent.h"
#include "Poco/Logger.h"
#include "Poco/Mutex.h"
#include <map>
#include <istream>


namespace Poco {
namespace OSP {


class BundleEvents;


class OSP_API ExtensionPointService: public Service
	/// The ExtensionPointService allows a bundle to define
	/// extension points (or "hooks") where other bundles
	/// can "hook in" functionality, thus extending the
	/// bundle.
	///
	/// The service listens for EV_BUNDLE_STARTED events.
	/// For every started bundle, the service tries to
	/// retrieve the bundle's "extensions.xml" file.
	/// If the file exists, the file is parsed using
	/// a DOM parser.
	///
	/// The ExtensionPointService then iterates over
	/// all "extension" elements in that document.
	/// Every "extension" element must specify an
	/// attribute named "point" that specifies the
	/// ExtensionPoint object to invoke for this
	/// element. The service then invokes the
	/// ExtensionPoint::handleExtension() member function
	/// with the bundle and the "extension" element as
	/// arguments.
	///
	/// The "extensions.xml" file basically looks as follows:
	///     <extensions>
	///         <extension point="<id>">
	///             <!-- extension point specific content -->
	///         </extension>
	///         <!-- more extension elements -->
	///     </extensions>
	///
	/// The service name of the ExtensionPointService
	/// is "osp.core.xp".
{
public:
	using Ptr = Poco::AutoPtr<ExtensionPointService>;
	using ConstPtr = const Ptr;

	ExtensionPointService(BundleEvents& events);
		/// Creates the ExtensionPointService.

	void registerExtensionPoint(Bundle::ConstPtr pBundle, const std::string& id, ExtensionPoint::Ptr pExtensionPoint);
		/// Registers the given extension point under the given ID.
		/// If the bundle registering the extension point is stopped,
		/// the extension point will be automatically unregistered.
		///
		/// Throws a Poco::ExistsException if an extension point with the
		/// given ID has already been registered.

	void unregisterExtensionPoint(const std::string& id);
		/// Unregisters the extension point with the given ID.
		///
		/// Throws a Poco::NotFoundException if the extension
		/// point with the given ID does not exist.

	static const std::string SERVICE_NAME;
	static const std::string EXTENSIONS_XML;
	static const std::string EXTENSIONS_ELEM;
	static const std::string EXTENSION_ELEM;
	static const std::string POINT_ATTR;

	// Service
	const std::type_info& type() const;
	bool isA(const std::type_info& otherType) const;

protected:
	typedef void (ExtensionPointService::*GenericHandler)(Bundle::ConstPtr pBundle, const std::string& id, Poco::XML::Element* pExtensionElement);

	enum Direction /// The direction in which to traverse the extension points
	{
		DIR_FORWARD,
		DIR_REVERSE
	};

	void onBundleStarted(const void* pSender, BundleEvent& event);
		/// Handles an EV_BUNDLE_STARTED event.

	void onBundleStopped(const void* pSender, BundleEvent& event);
		/// Handles an EV_BUNDLE_STOPPED event.

	void handleExtensions(Bundle::ConstPtr pBundle, GenericHandler handler, Direction dir = DIR_FORWARD);
		/// Handles the "extensions.xml" file, if it exists.

	void handleExtensions(Bundle::ConstPtr pBundle, std::istream& istr, GenericHandler handler, Direction dir = DIR_FORWARD);
		/// Handles the "extensions.xml" file.

	void handleExtension(Bundle::ConstPtr pBundle, const std::string& id, Poco::XML::Element* pExtensionElement);
		/// Handles a single "extension" element.

	void removeExtension(Bundle::ConstPtr pBundle, const std::string& id, Poco::XML::Element* pExtensionElement);
		/// Handles a single "extension" element for extension removal.

	ExtensionPoint::Ptr findExtensionPoint(const std::string& id);
		/// Returns the extension point with the given ID.

	~ExtensionPointService();
		/// Destroys the ExtensionPointService.

private:
	ExtensionPointService();

	using XPMap = std::map<std::string, ExtensionPoint::Ptr>;
	using BundleMap = std::multimap<Bundle::Ptr, std::string>;

	XPMap           _xpMap;
	BundleMap       _bundleMap;
	BundleEvents&   _events;
	Poco::Logger&   _logger;
	Poco::FastMutex _mutex;
};


} } // namespace Poco::OSP


#endif // OSP_ExtensionPointService_INCLUDED
