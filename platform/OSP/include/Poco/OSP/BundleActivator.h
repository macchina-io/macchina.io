//
// BundleActivator.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/BundleActivator.h#1 $
//
// Library: OSP
// Package: Bundle
// Module:  BundleActivator
//
// Definition of the BundleActivator class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_BundleActivator_INCLUDED
#define OSP_BundleActivator_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/BundleContext.h"


namespace Poco {
namespace OSP {


class BundleContext;


class OSP_API BundleActivator
	/// The BundleActivator is the entry point for
	/// every bundle contributing executable code and
	/// requiring special action upon startup or
	/// shutdown.
	///
	/// A bundle should provide its own BundleActivator
	/// class derived from this class. 
	///
	/// The BundleActivator (or, correctly speaking, a class
	/// derived from it) is the only class loaded from the
	/// bundle by the OSP framework.
	///
	/// To prevent lengthy startup and shutdown sequences,
	/// the start() and stop() method should do their 
	/// work in a timely fashion.
{
public:
	virtual void start(BundleContext::Ptr pContext) = 0;
		/// Called during the "starting" phase of a bundle,
		/// after all dependencies have been resolved.
		///
		/// Typical things to do in this member function are
		///   * registering services with the service registry
		///   * subscribing to events
		///   * preparing the environment so that the bundle
		///     can do its work
		///
		/// The BundleContext object passed as argument is valid
		/// through the entire lifetime of the bundle (until
		/// stop() returns) and can be stored for later reference.
		
	virtual void stop(BundleContext::Ptr pContext) = 0;
		/// Called during the "stopping" phase of the bundle.
		///
		/// Typical things to do in this member function are
		///   * unregistering services with the service registry
		///   * unsubscribing from events
		///   * cleaning up the mess left behind from the bundle

	virtual ~BundleActivator();
		/// Destroys the BundleActivator.

protected:
	BundleActivator();

private:
	BundleActivator(const BundleActivator&);
	BundleActivator& operator = (const BundleActivator&);
};


} } // namespace Poco::OSP


#endif // OSP_BundleActivator_INCLUDED
