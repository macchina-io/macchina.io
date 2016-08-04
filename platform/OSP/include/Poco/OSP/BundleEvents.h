//
// BundleEvents.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/BundleEvents.h#1 $
//
// Library: OSP
// Package: Bundle
// Module:  BundleEvents
//
// Definition of the BundleEvents class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_BundleEvents_INCLUDED
#define OSP_BundleEvents_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/BundleEvent.h"
#include "Poco/BasicEvent.h"


namespace Poco {
namespace OSP {


class OSP_API BundleEvents
	/// This class provides various events that interested
	/// parties can subscribe to to become notified
	/// whenever the state of a bundle in the system
	/// changes.
{
public:
	Poco::BasicEvent<BundleEvent> bundleInstalled;
		/// Fired after a bundle has been successfully installed.

	Poco::BasicEvent<BundleEvent> bundleLoaded;
		/// Fired after a bundle has been successfully loaded.
		/// The bundle is still in "installed" state.
		
	Poco::BasicEvent<BundleEvent> bundleResolving;
		/// Fired when resolving a bundle starts.
		/// The bundle is still in "installed" state.
		
	Poco::BasicEvent<BundleEvent> bundleResolved;
		/// Fired when resolving a bundle is completed.
		/// and the bundle is in "resolved" state.
		
	Poco::BasicEvent<BundleEvent> bundleStarting;
		/// Fired when a bundle is starting and the
		/// bundle has entered "starting" state.
		
	Poco::BasicEvent<BundleEvent> bundleStarted;
		/// Fired when starting a bundle is completed
		/// and the bundle has entered "active" state.
		
	Poco::BasicEvent<BundleEvent> bundleStopping;
		/// Fired when a bundle is stopped and the
		/// bundle has entered "stopping" state.
		
	Poco::BasicEvent<BundleEvent> bundleStopped;
		/// Fired when a bundle has been stopped and
		/// the bundle has entered "resolved" state.
		
	Poco::BasicEvent<BundleEvent> bundleUninstalling;
		/// Fired when uninstalling a bundle has
		/// started. The bundle is still in "installed"
		/// state.
		
	Poco::BasicEvent<BundleEvent> bundleUninstalled;
		/// Fired when uninstalling a bundle has completed
		/// and the bundle is in "uninstalled" state.

	Poco::BasicEvent<BundleEvent> bundleUnloaded;
		/// Fired after a bundle has been successfully unloaded.
		/// The bundle is still in "installed" or "resolved" state.
		
	Poco::BasicEvent<BundleEvent> bundleFailed;
		/// Fired after a bundle has failed to start due to
		/// an exception being thrown by its BundleActivator.
		/// The bundle is still in "resolved" state.
		
	BundleEvents();
		/// Creates a BundleEvents object.
		
	~BundleEvents();
		/// Destroys the BundleEvents object.
		
private:
	BundleEvents(const BundleEvents&);
	BundleEvents& operator = (const BundleEvents&);
};


} } // namespace Poco::OSP


#endif // OSP_BundleEvents_INCLUDED
