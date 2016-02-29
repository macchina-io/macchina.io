//
// BundleStreamFactory.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/BundleStreamFactory.h#1 $
//
// Library: OSP
// Package: Util
// Module:  BundleStreamFactory
//
// Definition of the BundleStreamFactory class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_BundleStreamFactory_INCLUDED
#define OSP_BundleStreamFactory_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/URIStreamFactory.h"


namespace Poco {
namespace OSP {


class BundleLoader;


class OSP_API BundleStreamFactory: public Poco::URIStreamFactory
	/// An implementation of the URIStreamFactory interface
	/// that handles Bundle (bndl) URIs for accessing
	/// resources stored in bundles.
	///
	/// The format of a bndl URI is:
	///     bndl://<symbolic-name>/<resource-path>
	///
	/// Example: bndl://com.appinf.osp.sample-bundle/sample.txt
{
public:
	BundleStreamFactory(BundleLoader& loader);
		/// Creates the BundleStreamFactory, using
		/// the given bundle loader.

	~BundleStreamFactory();
		/// Destroys the BundleStreamFactory.

	virtual std::istream* open(const Poco::URI& uri);
		/// Creates and opens a stream for the given bndl URI.
		
	static void registerFactory(BundleLoader& loader);
		/// Registers the BundleStreamFactory with the
		/// default URIStreamOpener instance.	

	static void unregisterFactory();
		/// Registers the BundleStreamFactory with the
		/// default URIStreamOpener instance.	

private:
	BundleStreamFactory();

	BundleLoader& _loader;
};


} } // namespace Poco::OSP


#endif // OSP_BundleStreamFactory_INCLUDED
