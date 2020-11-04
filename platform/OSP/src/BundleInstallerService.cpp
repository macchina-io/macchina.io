//
// BundleInstallerService.cpp
//
// Library: OSP
// Package: BundleInstallerService
// Module:  BundleInstallerService
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleInstallerService.h"
#include "Poco/OSP/BundleRepository.h"
#include "Poco/URIStreamOpener.h"
#include <memory>


using Poco::URIStreamOpener;


namespace Poco {
namespace OSP {


const std::string BundleInstallerService::SERVICE_NAME("osp.core.installer");


BundleInstallerService::BundleInstallerService(BundleRepository& repository):
	_bundleRepository(repository)
{
}


BundleInstallerService::~BundleInstallerService()
{
}


Bundle::Ptr BundleInstallerService::installBundle(const std::string& uri)
{
	std::unique_ptr<std::istream> pStream(URIStreamOpener::defaultOpener().open(uri));
	return _bundleRepository.installBundle(*pStream);
}


Bundle::Ptr BundleInstallerService::installBundle(std::istream& istr)
{
	return _bundleRepository.installBundle(istr);
}


Bundle::Ptr BundleInstallerService::replaceBundle(const std::string& symbolicName, const std::string& uri)
{
	std::unique_ptr<std::istream> pStream(URIStreamOpener::defaultOpener().open(uri));
	return _bundleRepository.installBundle(*pStream, symbolicName);
}


Bundle::Ptr BundleInstallerService::replaceBundle(const std::string& symbolicName, std::istream& istr)
{
	return _bundleRepository.installBundle(istr, symbolicName);
}


const std::type_info& BundleInstallerService::type() const
{
	return typeid(BundleInstallerService);
}


bool BundleInstallerService::isA(const std::type_info& otherType) const
{
	std::string name(typeid(BundleInstallerService).name());
	return name == otherType.name() || Service::isA(otherType);
}


} } // namespace Poco::OSP
