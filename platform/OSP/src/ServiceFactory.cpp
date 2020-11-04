//
// ServiceFactory.cpp
//
// Library: OSP
// Package: Service
// Module:  ServiceFactory
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/ServiceFactory.h"


namespace Poco {
namespace OSP {


ServiceFactory::ServiceFactory()
{
}


ServiceFactory::~ServiceFactory()
{
}


const std::type_info& ServiceFactory::type() const
{
	return typeid(ServiceFactory);
}


bool ServiceFactory::isA(const std::type_info& otherType) const
{
	std::string name(typeid(ServiceFactory).name());
	return name == otherType.name() || Service::isA(otherType);
}


} } // namespace Poco::OSP
