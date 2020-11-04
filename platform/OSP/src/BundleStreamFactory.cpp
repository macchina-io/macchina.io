//
// BundleStreamFactory.cpp
//
// Library: OSP
// Package: Util
// Module:  BundleStreamFactory
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleStreamFactory.h"
#include "Poco/OSP/BundleLoader.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/URI.h"
#include "Poco/URIStreamOpener.h"
#include "Poco/Exception.h"


namespace Poco {
namespace OSP {


BundleStreamFactory::BundleStreamFactory(BundleLoader& loader):
	_loader(loader)
{
}


BundleStreamFactory::~BundleStreamFactory()
{
}


std::istream* BundleStreamFactory::open(const Poco::URI& uri)
{
	poco_assert (uri.getScheme() == "bndl");

	std::string symbolicName(uri.getAuthority());
	std::string path(uri.getPath());
	
	if (path.empty()) throw Poco::InvalidArgumentException("Bundle (bndl) URI does not contain a path", uri.toString());
	
	if (path[0] == '/')
		path.erase(0, 1);
	
	Bundle::Ptr pBundle = _loader.findBundle(symbolicName);
	if (pBundle)
	{
		std::istream* pStream = pBundle->getResource(path);
		if (pStream)
			return pStream;
	}
	throw Poco::NotFoundException("Bundle resource", uri.toString());
}

	
void BundleStreamFactory::registerFactory(BundleLoader& loader)
{
	Poco::URIStreamOpener::defaultOpener().registerStreamFactory("bndl", new BundleStreamFactory(loader));
}


void BundleStreamFactory::unregisterFactory()
{
	Poco::URIStreamOpener::defaultOpener().unregisterStreamFactory("bndl");
}


} } // namespace Poco::OSP
