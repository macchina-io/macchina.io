//
// BundleStorage.h
//
// $Id: //poco/1.7/OSP/include/Poco/OSP/BundleStorage.h#1 $
//
// Library: OSP
// Package: Bundle
// Module:  BundleStorage
//
// Definition of the BundleStorage class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#ifndef OSP_BundleStorage_INCLUDED
#define OSP_BundleStorage_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/RefCountedObject.h"
#include "Poco/Timestamp.h"
#include "Poco/AutoPtr.h"
#include <vector>
#include <istream>


namespace Poco {
namespace OSP {


class OSP_API BundleStorage: public Poco::RefCountedObject
	/// BundleStorage manages provides access to all resources
	/// stored inside of a bundle.
	///
	/// BundleStorage itself is an abstract class; subclasses
	/// implement the BundleStorage interface for bundles stored
	/// in directories or Zip files.
	///
	/// Paths to resources within a bundle are always specified
	/// using Unix notation - directories are separated with
	/// a forward slash ('/').
{
public:
	typedef Poco::AutoPtr<BundleStorage> Ptr;
	typedef const Ptr ConstPtr;

	virtual std::istream* getResource(const std::string& path) const = 0;
		/// Returns an input stream for reading the resource with
		/// the given path, if the resource exists.
		/// Otherwise, returns NULL.
		///
		/// The caller receives ownership of, and is responsible for 
		/// deleting the input stream when it's no longer needed.
		
	virtual void list(const std::string& path, std::vector<std::string>& files) const = 0;
		/// List all files in the directory specified by path.
		/// If path is empty, all files in the bundle root directory
		/// are listed.

	virtual Poco::Timestamp lastModified(const std::string& path) const = 0;
		/// Returns the last modification timestamp for the specified file.

	virtual std::string path() const = 0;
		/// Returns the path to the bundle's directory or archive file.

protected:
	virtual ~BundleStorage();
		/// Destroys the BundleStorage.
};


} } // namespace Poco::OSP


#endif // OSP_BundleStorage_INCLUDED
