//
// Service.cpp
//
// $Id: //poco/1.7/OSP/src/Service.cpp#1 $
//
// Library: OSP
// Package: Service
// Module:  Service
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
