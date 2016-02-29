//
// BundleInstallerService.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/BundleInstallerService.h#1 $
//
// Library: OSP
// Package: BundleInstallerService
// Module:  BundleInstallerService
//
// Definition of the BundleInstallerService class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_BundleInstallerService_INCLUDED
#define OSP_BundleInstallerService_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Service.h"
#include "Poco/OSP/Bundle.h"
#include <istream>


namespace Poco {
namespace OSP {


class BundleRepository;


class OSP_API BundleInstallerService: public Service
	/// The BundleInstallerService allows a bundle to install
	/// other bundles, either from a stream or from a
	/// URI.
	///
	/// The service name of the BundleInstallerService
	/// is "osp.core.installer".
{
public:
	typedef Poco::AutoPtr<BundleInstallerService> Ptr;
	typedef const Ptr ConstPtr;

	BundleInstallerService(BundleRepository& repository);
		/// Creates the BundleInstallerService, using
		/// the given BundleRepository.

	Bundle::Ptr installBundle(const std::string& uri);
		/// Installs a bundle from the given URI.
		/// The Poco::URIStreamOpener class is used to
		/// open a stream for the given URI.
		///
		/// Returns a pointer to the installed bundle.

	Bundle::Ptr installBundle(std::istream& istr);
		/// Installs a bundle from the given stream.
		///
		/// Returns a pointer to the installed bundle.

	Bundle::Ptr replaceBundle(const std::string& symbolicName, std::istream& istr);
		/// Upgrades or replaces a bundle from the given stream.
		///
		/// Returns a pointer to the installed bundle.

	Bundle::Ptr replaceBundle(const std::string& symbolicName, const std::string& uri);
		/// Upgrades or replaces a bundle from the given URI.
		/// The Poco::URIStreamOpener class is used to
		/// open a stream for the given URI.
		///
		/// Returns a pointer to the installed bundle.
		
	static const std::string SERVICE_NAME;

	// Service
	const std::type_info& type() const;
	bool isA(const std::type_info& otherType) const;

protected:
	~BundleInstallerService();
		/// Destroys the BundleInstallerService.

private:
	BundleInstallerService();
	
	BundleRepository& _bundleRepository;
};


} } // namespace Poco::OSP


#endif // OSP_BundleInstallerService_INCLUDED
