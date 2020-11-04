//
// BundleDirectory.h
//
// Library: OSP
// Package: Bundle
// Module:  BundleDirectory
//
// Definition of the BundleDirectory class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_BundleDirectory_INCLUDED
#define OSP_BundleDirectory_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/BundleStorage.h"
#include "Poco/Path.h"


namespace Poco {
namespace OSP {


class OSP_API BundleDirectory: public BundleStorage
	/// BundleDirectory implements the BundleStorage interface
	/// for bundles stored in directories.
{
public:
	BundleDirectory(const std::string& path);
		/// Creates the BundleDirectory, using the
		/// given path which must specify the root
		/// directory of the bundle.

	// BundleStorage
	std::istream* getResource(const std::string& path) const;
	void list(const std::string& path, std::vector<std::string>& files) const;	
	Poco::Timestamp lastModified(const std::string& path) const;	
	std::string path() const;

protected:
	Poco::Path buildPath(const std::string& path) const;
		/// Builds a path to a file or directory inside the
		/// bundle by concatenating the bundle's path with
		/// the given path, and doing various sanity checks
		/// along the way.

	~BundleDirectory();
		/// Destroys the BundleDirectory.

private:
	BundleDirectory();
	BundleDirectory(const BundleDirectory&);
	BundleDirectory& operator = (const BundleDirectory&);
	
	Poco::Path _path;
};


} } // namespace Poco::OSP


#endif // OSP_BundleDirectory_INCLUDED
