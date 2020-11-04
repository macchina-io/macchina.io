//
// BundleRepository.h
//
// Library: OSP
// Package: Bundle
// Module:  BundleRepository
//
// Definition of the BundleRepository class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_BundleRepository_INCLUDED
#define OSP_BundleRepository_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/BundleFilter.h"
#include "Poco/Logger.h"
#include <vector>
#include <map>
#include <istream>


namespace Poco {
namespace OSP {


class BundleLoader;


class OSP_API BundleRepository
	/// The bundle repository manages one or more directories
	/// in the file system containing bundles.
	///
	/// The BundleRepository uses the Logger "osp.core.BundleRepository"
	/// to log non-fatal errors.
{
public:
	BundleRepository(const std::string& path, BundleLoader& loader, BundleFilter::Ptr pBundleFilter = 0);
		/// Creates the BundleRepository, using the given
		/// path and BundleLoader, and optional BundleFilter.
		///
		/// The path argument may contain a single path, or a list
		/// of paths, separated by the platform's path separator
		/// (':' on Unix platforms, ';' on Windows).
		///
		/// The first path given in a list is said to be the
		/// primary path. Other paths are secondary paths.
		///
		/// Paths may either reference a directory containing
		/// bundles, or a bundle file (or bundle directory with
		/// the extension ".bndl") directly.
		///
		/// Paths may contain Glob expressions (see Poco::Glob).

	BundleRepository(const std::vector<std::string>& paths, BundleLoader& loader, BundleFilter::Ptr pBundleFilter = 0);
		/// Creates the BundleRepository, using the given
		/// paths and BundleLoader, and optional BundleFilter.
		///
		/// The paths argument specifies a list of paths where
		/// bundles are searched.
		///
		/// The first path given in a list is said to be the
		/// primary path. Other paths are secondary paths.
		///
		/// Paths may either reference a directory containing
		/// bundles, or a bundle file (or bundle directory with
		/// the extension ".bndl") directly.
		///
		/// Paths may contain Glob expressions (see Poco::Glob).

	~BundleRepository();
		/// Destroys the BundleRepository.

	void loadBundles();
		/// Loads all available bundles, using the BundleLoader.
		///
		/// If two or more versions of a bundle are found,
		/// the latest version of the bundle is loaded
		/// and a warning message is logged.

	Bundle::Ptr installBundle(std::istream& istr);
		/// Reads a bundle archive file from the given stream
		/// and installs it in the primary path.
		///
		/// The bundle's file name in the bundle repository
		/// will be "<symbolicName>_<version>.bndl".
		///
		/// Returns the newly installed bundle, which will
		/// be in INSTALLED state.

	Bundle::Ptr installBundle(const std::string& repositoryPath, std::istream& istr);
		/// Reads a bundle archive file from the given stream
		/// and installs it in the specified repositoryPath.
		///
		/// The repositoryPath must be one of the bundle repository paths specified
		/// in the constructor, otherwise the bundle won't be found
		/// the next time the application starts.
		///
		/// The directory referenced by repositoryPath must exist and must
		/// be writable, otherwise installing the bundle will fail.
		///
		/// The bundle's file name in the bundle repository
		/// will be "<symbolicName>_<version>.bndl".
		///
		/// Returns the newly installed bundle, which will
		/// be in INSTALLED state.

	Bundle::Ptr installBundle(std::istream& istr, const std::string& replaceBundle);
		/// Reads a bundle archive file from the given stream
		/// and installs it in the primary path.
		///
		/// If a bundle with the symbolic name given in replaceBundle
		/// exists, the bundle is stopped and uninstalled before
		/// the new bundle is installed.
		///
		/// The bundle's file name in the bundle repository
		/// will be "<symbolicName>_<version>.bndl".
		///
		/// Returns the newly installed bundle, which will
		/// be in INSTALLED state.

	Bundle::Ptr installBundle(const std::string& repositoryPath, std::istream& istr, const std::string& replaceBundle);
		/// Reads a bundle archive file from the given stream
		/// and installs it in the primary repositoryPath.
		///
		/// The repositoryPath must be one of the bundle repository paths specified
		/// in the constructor, otherwise the bundle won't be found
		/// the next time the application starts.
		///
		/// The directory referenced by repositoryPath must exist and must
		/// be writable, otherwise installing the bundle will fail.
		///
		/// If a bundle with the symbolic name given in replaceBundle
		/// exists, the bundle is stopped and uninstalled before
		/// the new bundle is installed.
		///
		/// The bundle's file name in the bundle repository
		/// will be "<symbolicName>_<version>.bndl".
		///
		/// Returns the newly installed bundle, which will
		/// be in INSTALLED state.

	const std::vector<std::string>& paths() const;
		/// Returns a vector containing all configured repository paths.

protected:
	using BundleMap = std::map<std::string, Bundle::Ptr>;

	void loadBundles(const std::string& path, BundleMap& bundles);
		/// Loads all availble bundles from the given path.

	void loadBundle(const std::string& path, BundleMap& bundles);
		/// Loads a bundle from the given path.

	Bundle::Ptr installBundleImpl(std::istream& istr, const std::string& replaceBundle, const std::string& path);
		/// Reads a bundle archive file from the given stream
		/// and installs it in the given path.

	std::string tempBundleName() const;
		/// Returns a temporary bundle name in the
		/// form "tmp.bundle-nnnn".

	void removeBundle(const std::string& symbolicName);
		/// Removes the bundle, by first stopping (if necessary),
		/// and then uninstalling it.

private:
	BundleRepository();
	BundleRepository(const BundleRepository&);
	BundleRepository& operator = (const BundleRepository&);

	std::vector<std::string> _paths;
	BundleLoader&            _loader;
	BundleFilter::Ptr        _pFilter;
	Poco::Logger&            _logger;
};


//
// inlines
//
inline const std::vector<std::string>& BundleRepository::paths() const
{
	return _paths;
}


} } // namespace Poco::OSP


#endif // OSP_BundleRepository_INCLUDED
