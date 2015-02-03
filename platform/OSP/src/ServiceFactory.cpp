//
// ServiceFactory.cpp
//
// $Id: //poco/1.4/OSP/src/ServiceFactory.cpp#2 $
//
// Library: OSP
// Package: Service
// Module:  ServiceFactory
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
