//
// BundleEvent.h
//
// $Id: //poco/1.4/OSP/include/Poco/OSP/BundleEvent.h#2 $
//
// Library: OSP
// Package: Bundle
// Module:  BundleEvent
//
// Definition of the BundleEvent class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_BundleEvent_INCLUDED
#define OSP_BundleEvent_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Bundle.h"


namespace Poco {
namespace OSP {


class OSP_API BundleEvent
	/// The BundleEvent class holds information about
	/// an event caused by a change to a bundle's state.
{
public:
	enum EventKind
	{
		EV_BUNDLE_INSTALLED,
		EV_BUNDLE_LOADED,
		EV_BUNDLE_RESOLVING,
		EV_BUNDLE_RESOLVED,
		EV_BUNDLE_STARTING,
		EV_BUNDLE_STARTED,
		EV_BUNDLE_STOPPING,
		EV_BUNDLE_STOPPED,
		EV_BUNDLE_UNINSTALLING,
		EV_BUNDLE_UNINSTALLED,
		EV_BUNDLE_UNLOADED
	};
	
	BundleEvent(Bundle::Ptr pBundle, EventKind what);
		/// Creates the BundleEvent.

	BundleEvent(Bundle* pBundle, EventKind what);
		/// Creates the BundleEvent.

	BundleEvent(const BundleEvent& event);
		/// Creates a BundleEvent from another one.

	~BundleEvent();
		/// Destroys the BundleEvent.
		
	BundleEvent& operator = (const BundleEvent& event);
		/// Assigns a BundleEvent.
		
	Bundle::ConstPtr bundle() const;
		/// Returns the bundle that caused the event.
		
	EventKind what() const;
		/// Returns the reason of the event.

private:
	BundleEvent();
	
	Bundle::Ptr _pBundle;
	EventKind   _what;
};


//
// inlines
//
inline Bundle::ConstPtr BundleEvent::bundle() const
{
	return _pBundle;
}


inline BundleEvent::EventKind BundleEvent::what() const
{
	return _what;
}


} } // namespace Poco::OSP


#endif // OSP_BundleEvent_INCLUDED
