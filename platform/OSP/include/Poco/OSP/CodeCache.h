//
// CodeCache.h
//
// Library: OSP
// Package: Util
// Module:  CodeCache
//
// Definition of the CodeCache class.
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#ifndef OSP_CodeCache_INCLUDED
#define OSP_CodeCache_INCLUDED


#include "Poco/OSP/OSP.h"
#include "Poco/Path.h"
#include "Poco/Timestamp.h"
#include "Poco/NamedMutex.h"
#include "Poco/ScopedLock.h"
#include "Poco/SharedPtr.h"


namespace Poco {
namespace OSP {


class OSP_API CodeCache
	/// CodeCache is a utility class that manages the
	/// code cache directory where the shared libraries
	/// of resolved bundles are kept.
	///
	/// Under certain circumstances, multiple OSP processes
	/// can shared the same code cache directory.
	/// This is not recommended, but may be done to optimize
	/// a system's resource usage. If the codeCache is shared
	/// between multiple processes, all processes must use
	/// the same versions of common bundles. In other words,
	/// while different processes can run different sets of
	/// bundles, all bundles used by multiple processes must
	/// be the same, in order to prevent conflicts caused by
	/// incompatible shared libraries in the common code cache.
	///
	/// See the CodeCache constructor for enabling support for
	/// a shared code cache.
{
public:
	using Lock = Poco::ScopedLock<CodeCache>;

	CodeCache(const std::string& path, bool isShared = false);
		/// Creates the CodeCache, using the
		/// given path.
		///
		/// If isShared is true, the codeCache is considered shared
		/// among multiple processes and a named mutex is used
		/// to guard access to it.
		///
		/// If the cache directory does not exist,
		/// it is created.

	~CodeCache();
		/// Destroys the CodeCache.

	bool hasLibrary(const std::string& name);
		/// Returns true if a library with the given name
		/// is stored in the code cache.
		///
		/// The name must not contain an filename extension.

	Poco::Timestamp libraryTimestamp(const std::string& name);
		/// Returns library last modification timestamp.
		///
		/// The name must not contain an filename extension.

	void installLibrary(const std::string& name, std::istream& istr);
		/// Installs the library with the given name, which
		/// must not contain an extension, into the code cache.

	void uninstallLibrary(const std::string& name);
		/// Removes the library with the given name from
		/// the cache directory.

	std::string pathFor(const std::string& name, bool appendSuffix = true);
		/// Returns the full path for the library with the given name.
		/// If appendSuffix is true (default), appends the appropriate suffix
		/// for debug version and OS dynamic library extension.

	void clear();
		/// Clears the cache by removing the entire
		/// cache directory.

	void lock();
		/// For a shared CodeCache, locks the code cache directory.
		///
		/// Does nothing if the codeCache is not shared.

	void unlock();
		/// For a shared CodeCache, unlocks the code cache directory.
		///
		/// Does nothing if the codeCache is not shared.

protected:
	static std::string mutexName(const std::string& path);

private:
	CodeCache();
	CodeCache(const CodeCache&);
	CodeCache& operator = (const CodeCache&);

	Poco::Path _path;
	Poco::SharedPtr<Poco::NamedMutex> _pMutex;
};


} } // namespace Poco::OSP


#endif // OSP_CodeCache_INCLUDED
