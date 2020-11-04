//
// Service.cpp
//
// Library: OSP
// Package: Service
// Module:  Service
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/Service.h"


namespace Poco {
namespace OSP {


Service::Service()
{
}


Service::~Service()
{
}


const std::type_info& Service::type() const
{
	return typeid(Service);
}


bool Service::isA(const std::type_info& otherType) const
{
	std::string name(typeid(Service).name());
	return name == otherType.name();
}


} } // namespace Poco::OSP
