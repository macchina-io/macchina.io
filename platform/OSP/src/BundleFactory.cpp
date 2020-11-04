//
// BundleFactory.cpp
//
// Library: OSP
// Package: Bundle
// Module:  BundleFactory
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleFactory.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/BundleDirectory.h"
#include "Poco/OSP/BundleFile.h"
#include "Poco/OSP/BundleLoader.h"
#include "Poco/OSP/OSPException.h"
#include "Poco/File.h"


namespace Poco {
namespace OSP {


BundleFactory::BundleFactory(const LanguageTag& language):
	_language(language)
{
}


BundleFactory::~BundleFactory()
{
}


Bundle* BundleFactory::createBundle(BundleLoader& loader, const std::string& path)
{
	File f(path);
	BundleStorage::Ptr pStorage(0);
	if (f.isFile())
		pStorage = new BundleFile(path);
	else if (f.isDirectory())
		pStorage = new BundleDirectory(path);
	else
		throw BundleLoadException("Attempted to load a bundle from something that is neither a file nor a directory", path);
		
	return new Bundle(loader.nextBundleId(), loader, pStorage, _language);
}


} } // namespace Poco::OSP
