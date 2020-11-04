//
// BundleDirectory.cpp
//
// Library: OSP
// Package: Bundle
// Module:  BundleDirectory
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleDirectory.h"
#include "Poco/File.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/Exception.h"
#include "Poco/FileStream.h"


using Poco::Path;
using Poco::File;
using Poco::DirectoryIterator;


namespace Poco {
namespace OSP {


BundleDirectory::BundleDirectory(const std::string& path):
	_path(path)
{
	_path.makeDirectory();
}


BundleDirectory::~BundleDirectory()
{
}


std::istream* BundleDirectory::getResource(const std::string& path) const
{
	Path p(buildPath(path));
	File f(p);
	if (f.exists() && f.isFile())
		return new Poco::FileInputStream(f.path());
	else
		return 0;
}


void BundleDirectory::list(const std::string& path, std::vector<std::string>& files) const	
{
	files.clear();
	Path p(buildPath(path));
	File f(p);
	if (f.exists() && f.isDirectory())
	{
		DirectoryIterator it(p);
		DirectoryIterator end;
		for (; it != end; ++it)
		{
			files.push_back(it.name());
		}
	}
}


Poco::Timestamp BundleDirectory::lastModified(const std::string& path) const
{
	Path p(buildPath(path));
	File f(p);
	return f.getLastModified();
}
 

std::string BundleDirectory::path() const
{
	return _path.toString();
}


Poco::Path BundleDirectory::buildPath(const std::string& path) const
{
	Path fullPath(_path);
	if (path.empty())
	{
		fullPath.makeFile();
	}
	else
	{
		if (path.find('\\') != std::string::npos)
			throw Poco::InvalidArgumentException("Resource path contains invalid characters", path);
		Path resPath(path, Path::PATH_UNIX);
		if (!resPath.isRelative()) 
			throw Poco::InvalidArgumentException("Resource path must be relative", path);
		resPath.makeFile();
		for (int i = 0; i < resPath.depth(); ++i)
		{
			const std::string& dir(resPath[i]);
			if (dir == "..") 
				throw Poco::InvalidArgumentException("Resource path must not contain references to a parent directory", path);
			if (dir != ".")
				fullPath.pushDirectory(dir);
		}
		fullPath.setFileName(resPath.getFileName());
	}
	return fullPath;
}


} } // namespace Poco::OSP
