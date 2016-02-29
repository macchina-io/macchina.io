//
// CodeCache.cpp
//
// $Id: //poco/1.7/OSP/src/CodeCache.cpp#1 $
//
// Library: OSP
// Package: Util
// Module:  CodeCache
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/CodeCache.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/SharedLibrary.h"
#include "Poco/StreamCopier.h"


using Poco::File;
using Poco::SharedLibrary;
using Poco::StreamCopier;
using Poco::Timestamp;


namespace Poco {
namespace OSP {


CodeCache::CodeCache(const std::string& path):
	_path(path)
{
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


} } // namespace Poco::OSP
