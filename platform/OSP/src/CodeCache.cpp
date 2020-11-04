//
// CodeCache.cpp
//
// Library: OSP
// Package: Util
// Module:  CodeCache
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/CodeCache.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/SharedLibrary.h"
#include "Poco/StreamCopier.h"
#include "Poco/SHA1Engine.h"


using Poco::File;
using Poco::SharedLibrary;
using Poco::StreamCopier;
using Poco::Timestamp;


namespace Poco {
namespace OSP {


CodeCache::CodeCache(const std::string& path, bool shared):
	_path(path)
{
	if (shared) _pMutex = new Poco::NamedMutex(mutexName(path));
	_path.makeDirectory();
	File dir(path);
	dir.createDirectories();
}


CodeCache::~CodeCache()
{
}


bool CodeCache::hasLibrary(const std::string& name)
{
	Path p(_path, name);
	File f(p);
	return f.exists();
}


Poco::Timestamp CodeCache::libraryTimestamp(const std::string& name)
{
	Path p(_path, name);
	File f(p);
	return f.getLastModified();
}


void CodeCache::installLibrary(const std::string& name, std::istream& istr)
{
	Path p(_path, name);
	File f(p);
	Poco::FileOutputStream ostr(f.path());
	if (ostr.good())
	{
		StreamCopier::copyStream(istr, ostr);
		ostr.close();
		f.setExecutable();
	}
	else throw CreateFileException(f.path());
}


void CodeCache::uninstallLibrary(const std::string& name)
{
	Path p(_path, name);
	File f(p);
	f.remove();
}


std::string CodeCache::pathFor(const std::string& name, bool appendSuffix)
{
	Path p(_path);
	if (!name.empty())
	{
		if (appendSuffix)
			p.setFileName(name + SharedLibrary::suffix());
		else
			p.setFileName(name);
	}
	return p.toString();
}


void CodeCache::clear()
{
	File dir(_path);
	dir.remove(true);
	dir.createDirectories();
}


void CodeCache::lock()
{
	if (_pMutex) _pMutex->lock();
}


void CodeCache::unlock()
{
	if (_pMutex) _pMutex->unlock();
}


std::string CodeCache::mutexName(const std::string& path)
{
	std::string name("ospcc");
	Poco::Path p(path);
	p.makeAbsolute();
	p.makeDirectory();
	Poco::SHA1Engine sha1;
	sha1.update(p.toString());
	std::string hash = Poco::DigestEngine::digestToHex(sha1.digest());
	hash.resize(16);
	name += hash;
	return name;
}


} } // namespace Poco::OSP
