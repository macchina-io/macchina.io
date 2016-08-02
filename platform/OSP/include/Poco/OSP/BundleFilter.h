//
// BundleFilter.h
//
// $Id$
//
// Library: OSP
// Package: Bundle
// Module:  BundleFilter
//
// Definition of the BundleFilter class.
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_BundleFilter_INCLUDED
#define OSP_BundleFilter_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/RefCountedObject.h"
#include "Poco/AutoPtr.h"


namespace Poco {
namespace OSP {


class OSP_API BundleFilter: public Poco::RefCountedObject
	/// A BundleFilter is used by BundleRepository to determine
	/// which bundles found in a repository should be loaded.
	/// For each bundle found in a repository, the BundleFilter's
	/// accept() method will be called, passing the Bundle as
	/// argument. Only if accept() returns true, the bundle will be
	/// loaded.
{
public:
	typedef Poco::AutoPtr<BundleFilter> Ptr;

	virtual bool accept(Bundle::Ptr pBundle) = 0;
		/// Check whether the given Bundle should be
		/// loaded. Must be overridden by subclasses.
		///
		/// Returns true if given Bundle should be loaded,
		/// or false otherwise.
		
	virtual ~BundleFilter();
		/// Destroys the BundleFilter.
};


} } // namespace Poco::OSP


#endif // OSP_BundleFilter_INCLUDED
