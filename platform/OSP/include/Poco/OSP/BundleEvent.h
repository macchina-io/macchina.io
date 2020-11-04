//
// BundleEvent.h
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
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_BundleEvent_INCLUDED
#define OSP_BundleEvent_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/Exception.h"


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
		EV_BUNDLE_UNLOADED,
		EV_BUNDLE_FAILED
	};
	
	BundleEvent(Bundle::Ptr pBundle, EventKind what);
		/// Creates the BundleEvent.

	BundleEvent(Bundle* pBundle, const Poco::Exception& exception);
		/// Creates the BundleEvent with the given exception,
		/// and state EV_BUNDLE_FAILED.

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
		
	Poco::Exception* exception() const;
		/// Returns the exception if starting the bundle failed,
		/// or null if no exception is available.

private:
	BundleEvent();
	
	Bundle::Ptr      _pBundle;
	EventKind        _what;
	Poco::Exception* _pException;
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


inline Poco::Exception* BundleEvent::exception() const
{
	return _pException;
}


} } // namespace Poco::OSP


#endif // OSP_BundleEvent_INCLUDED
