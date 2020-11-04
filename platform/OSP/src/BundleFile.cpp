//
// BundleFile.cpp
//
// Library: OSP
// Package: Bundle
// Module:  BundleFile
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleFile.h"
#include "Poco/Zip/ZipArchive.h"
#include "Poco/Zip/ZipStream.h"
#include "Poco/Path.h"
#include "Poco/Exception.h"
#include "Poco/FileStream.h"
#include <set>
#include <iostream>


using Poco::Path;
using Poco::Zip::ZipArchive;
using Poco::Zip::ZipInputStream;
using Poco::Zip::ZipIOS;
using Poco::Zip::ZipLocalFileHeader;


namespace Poco {
namespace OSP {


namespace
{
	class BundleFileInputStream: public ZipIOS, public std::istream
	{
	public:
		BundleFileInputStream(const std::string& path, const ZipLocalFileHeader& fileEntry):
			ZipIOS(_istr, fileEntry, true), 
			std::istream(&_buf),
			_istr(path)
		{
		}
		
		~BundleFileInputStream()
		{
		}
		
	private:
		Poco::FileInputStream _istr;
	};
}


BundleFile::BundleFile(const std::string& path):
	_path(path),
	_pArchive(0)
{
	Poco::FileInputStream istr(path);
	if (istr.good())
		_pArchive = new ZipArchive(istr);
	else
		throw Poco::OpenFileException(path);
}


BundleFile::~BundleFile()
{
	delete _pArchive;
}


std::istream* BundleFile::getResource(const std::string& path) const
{
	poco_assert (_pArchive);
	
	ZipArchive::FileHeaders::const_iterator it = _pArchive->findHeader(path);
	if (it != _pArchive->headerEnd() && it->second.isFile())
		return new BundleFileInputStream(_path, it->second);
	else
		return 0;
}


void BundleFile::list(const std::string& path, std::vector<std::string>& files) const	
{
	poco_assert (_pArchive);
	
	files.clear();
	int depth = 0;
	std::string parent;
	if (!path.empty())
	{
		// ensure parent ends with a slash
		Path parentPath(path, Path::PATH_UNIX);
		parentPath.makeDirectory();
		parent = parentPath.toString(Path::PATH_UNIX);
	}
	ZipArchive::FileHeaders::const_iterator it;
	ZipArchive::FileHeaders::const_iterator end(_pArchive->headerEnd());
	if (path.empty())
	{
		it = _pArchive->headerBegin();
	}
	else
	{
		it = _pArchive->findHeader(parent);
		if (it != end) ++it;
		depth = Path(parent).depth();
	}
	
	std::set<std::string> fileSet;
	while (it != end && isSubdirectoryOf(it->first, parent))
	{
		Path p(it->first, Path::PATH_UNIX);
		p.makeFile();
		if (p.depth() == depth)
		{
			std::string name = p.getFileName();
			if (fileSet.find(name) == fileSet.end())
			{
				files.push_back(name);
				fileSet.insert(name);
			}
		}
		++it;
	}
}


Poco::Timestamp BundleFile::lastModified(const std::string& path) const
{
	poco_assert (_pArchive);

	ZipArchive::FileInfos::const_iterator it(_pArchive->fileInfoBegin());
	ZipArchive::FileInfos::const_iterator end(_pArchive->fileInfoEnd());
	while (it != end)
	{
		if (it->first == path)
		{
			return it->second.lastModifiedAt().timestamp();
		}
		++it;
	}

	throw Poco::NotFoundException(path);
}


std::string BundleFile::path() const
{
	return _path;
}


bool BundleFile::isSubdirectoryOf(const std::string& dir, const std::string& parent) const
{
	if (dir.size() > parent.size())
		return dir.compare(0, parent.size(), parent) == 0;
	else
		return false;
}


} } // namespace Poco::OSP
