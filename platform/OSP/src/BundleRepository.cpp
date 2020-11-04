//
// BundleRepository.cpp
//
// Library: OSP
// Package: Bundle
// Module:  BundleRepository
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleRepository.h"
#include "Poco/OSP/BundleLoader.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/OSPException.h"
#include "Poco/StringTokenizer.h"
#include "Poco/Glob.h"
#include "Poco/Path.h"
#include "Poco/File.h"
#include "Poco/FileStream.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/StreamCopier.h"
#include "Poco/Mutex.h"
#include "Poco/NumberFormatter.h"
#include "Poco/String.h"
#include "Poco/Exception.h"
#include <map>
#include <set>


using namespace std::string_literals;


using Poco::StringTokenizer;
using Poco::Path;
using Poco::File;
using Poco::DirectoryIterator;
using Poco::StreamCopier;
using Poco::Logger;
using Poco::FastMutex;
using Poco::NumberFormatter;


namespace Poco {
namespace OSP {


BundleRepository::BundleRepository(const std::string& path, BundleLoader& loader, BundleFilter::Ptr pFilter):
	_loader(loader),
	_pFilter(pFilter),
	_logger(Logger::get("com.osp.BundleRepository"s))
{
#ifdef POCO_OS_FAMILY_UNIX
	std::string pathSep(":;");
#else
	std::string pathSep(";");
#endif
	StringTokenizer tokenizer(path, pathSep, StringTokenizer::TOK_IGNORE_EMPTY | StringTokenizer::TOK_TRIM);
	_paths.insert(_paths.end(), tokenizer.begin(), tokenizer.end());

	if (_paths.empty())
		throw Poco::InvalidArgumentException("At least one path must be supplied to a BundleRepository");
}


BundleRepository::BundleRepository(const std::vector<std::string>& paths, BundleLoader& loader, BundleFilter::Ptr pFilter):
	_paths(paths),
	_loader(loader),
	_pFilter(pFilter),
	_logger(Logger::get("com.osp.BundleRepository"s))
{
	if (_paths.empty())
		throw Poco::InvalidArgumentException("At least one path must be supplied to a BundleRepository");
}


BundleRepository::~BundleRepository()
{
}


void BundleRepository::loadBundles()
{
	BundleMap bundles;
	for (std::vector<std::string>::const_iterator it = _paths.begin(); it != _paths.end(); ++it)
	{
		try
		{
			loadBundles(*it, bundles);
		}
		catch (Poco::Exception& exc)
		{
			std::string msg("Failed to load bundles from ");
			msg += "'";
			msg += *it;
			msg += "': ";
			msg += exc.displayText();
			_logger.error(msg);
		}
	}
	for (BundleMap::iterator it = bundles.begin(); it != bundles.end(); ++it)
	{
		_loader.loadBundle(it->second);
		if (_logger.information())
		{
			_logger.information("Loaded bundle %s/%s."s,
				it->second->symbolicName(),
				it->second->version().toString());
		}
	}
}


void BundleRepository::loadBundles(const std::string& path, BundleMap& bundles)
{
	std::set<std::string> paths;
#if defined(POCO_OS_FAMILY_WINDOWS)
	int options = Poco::Glob::GLOB_CASELESS;
#else
	int options = Poco::Glob::GLOB_DEFAULT;
#endif
	Poco::Glob::glob(path, paths, options);
	for (std::set<std::string>::const_iterator git(paths.begin()), end(paths.end()); git != end; ++git)
	{
		Poco::Path p(*git);
		Poco::File f(*git);
		if (f.exists())
		{
			if (f.isFile() || (f.isDirectory() && Poco::icompare(p.getExtension(), "bndl") == 0))
			{
				try
				{
					if (_logger.debug())
					{
						_logger.debug("Found bundle %s."s, *git);
					}
					loadBundle(*git, bundles);
				}
				catch (Poco::Exception& exc)
				{
					std::string msg("Failed to load bundle from ");
					msg += "'";
					msg += *git;
					msg += "': ";
					msg += exc.displayText();
					_logger.error(msg);
				}
			}
			else
			{
				DirectoryIterator it(*git);
				DirectoryIterator end;
				for (; it != end; ++it)
				{
					try
					{
						bool isBundle = !it->isHidden();
						if (it->isDirectory())
						{
							Poco::Path metaPath(it->path());
							metaPath.makeDirectory();
							metaPath.setFileName("META-INF");
							Poco::File metaDir(metaPath.toString());
							if (!metaDir.exists() || !metaDir.isDirectory())
							{
								isBundle = false;
							}
						}
						if (isBundle)
						{
							if (_logger.debug())
							{
								_logger.debug("Found bundle %s."s, it->path());
							}
							loadBundle(it->path(), bundles);
						}
					}
					catch (Poco::Exception& exc)
					{
						std::string msg("Failed to load bundle from ");
						msg += "'";
						msg += it->path();
						msg += "': ";
						msg += exc.displayText();
						_logger.error(msg);
					}
				}
			}
		}
	}
}


void BundleRepository::loadBundle(const std::string& path, BundleMap& bundles)
{
	Bundle::Ptr pBundle(_loader.createBundle(path));

	if (_pFilter && !_pFilter->accept(pBundle))
	{
		std::string msg("Bundle rejected by filter: ");
		msg += pBundle->symbolicName();
		msg += "/";
		msg += pBundle->version().toString();
		_logger.information(msg);
		return;
	}

	const std::string& id = pBundle->symbolicName();
	BundleMap::iterator it = bundles.find(id);
	if (it != bundles.end())
	{
		std::string msg("Conflicting versions detected for bundle ");
		msg += id;
		msg += "; ";
		if (it->second->version() <= pBundle->version())
		{
			msg += "chosing version ";
			msg += pBundle->version().toString();
			msg += " from '";
			msg += pBundle->path();
			msg += "' over version ";
			msg += it->second->version().toString();
			msg += " from '";
			msg += it->second->path();
			msg += "'";
			it->second = pBundle;
		}
		else
		{
			msg += "chosing version ";
			msg += it->second->version().toString();
			msg += " from '";
			msg += it->second->path();
			msg += "' over version ";
			msg += pBundle->version().toString();
			msg += " from '";
			msg += pBundle->path();
			msg += "'";
		}
		_logger.warning(msg);
	}
	else
	{
		bundles[id] = pBundle;
	}
}


Bundle::Ptr BundleRepository::installBundle(std::istream& istr)
{
	poco_assert (!_paths.empty());

	return installBundleImpl(istr, _paths[0], std::string());
}


Bundle::Ptr BundleRepository::installBundle(const std::string& repositoryPath, std::istream& istr)
{
	return installBundleImpl(istr, repositoryPath, std::string());
}


Bundle::Ptr BundleRepository::installBundle(std::istream& istr, const std::string& replaceBundle)
{
	poco_assert (!_paths.empty());

	return installBundleImpl(istr, _paths[0], replaceBundle);
}


Bundle::Ptr BundleRepository::installBundle(const std::string& repositoryPath, std::istream& istr, const std::string& replaceBundle)
{
	return installBundleImpl(istr, repositoryPath, replaceBundle);
}


Bundle::Ptr BundleRepository::installBundleImpl(std::istream& istr, const std::string& path, const std::string& replaceBundle)
{
	Path p(path);
	p.makeDirectory();
	p.setFileName(tempBundleName());

	File f(p);
	Poco::FileOutputStream ostr(f.path());
	if (ostr.good())
	{
		try
		{
			StreamCopier::copyStream(istr, ostr);
			ostr.close();

			Bundle::Ptr pBundle(_loader.createBundle(f.path()));
			std::string symbolicName = pBundle->symbolicName();
			std::string newName(symbolicName);
			newName += "_";
			newName += pBundle->version().toString();
			newName += ".bndl";
			pBundle = 0;

			if (replaceBundle != symbolicName)
			{
				Bundle::Ptr pExistingBundle = _loader.findBundle(symbolicName);
				if (pExistingBundle)
				{
					throw Poco::OSP::BundleInstallException("A bundle with the same symbolic name is already installed", symbolicName);
				}
			}

			if (!replaceBundle.empty())
			{
				removeBundle(replaceBundle);
			}

			Path np(p);
			np.setFileName(newName);
			f.renameTo(np.toString());

			pBundle = _loader.loadBundle(np.toString());
			if (_logger.information())
			{
				_logger.information("Installed bundle %s/%s to '%s'."s,
					pBundle->symbolicName(),
					pBundle->version().toString(),
					f.path());
			}
			return pBundle;
		}
		catch (Poco::Exception&)
		{
			try
			{
				f.remove();
			}
			catch (...)
			{
			}
			throw;
		}
	}
	else throw Poco::CreateFileException(p.toString());
}


std::string BundleRepository::tempBundleName() const
{
	static FastMutex serialMutex;
	static unsigned serial(0);

	serialMutex.lock();
	unsigned n = serial++;
	serialMutex.unlock();

	std::string name("tmp.bundle-");
	name += NumberFormatter::format(n);
	return name;
}


void BundleRepository::removeBundle(const std::string& symbolicName)
{
	Bundle::Ptr pBundle = _loader.findBundle(symbolicName);
	if (pBundle)
	{
		if (pBundle->state() == Bundle::BUNDLE_ACTIVE)
		{
			pBundle->stop();
		}
		if (pBundle->state() == Bundle::BUNDLE_RESOLVED
		 || pBundle->state() == Bundle::BUNDLE_INSTALLED)
		{
			pBundle->uninstall();
		}
		else throw BundleStateException("Cannot remove bundle in state" , pBundle->stateString());
	}
}


} } // namespace Poco::OSP
