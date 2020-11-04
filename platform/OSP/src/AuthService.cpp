//
// AuthService.cpp
//
// Library: OSP
// Package: Service
// Module:  AuthService
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/Auth/AuthService.h"
#include "Poco/OSP/ServiceFactory.h"


namespace Poco {
namespace OSP {
namespace Auth {


AuthService::AuthService()
{
}


AuthService::~AuthService()
{
}


const std::type_info& AuthService::type() const
{
	return typeid(AuthService);
}

	
bool AuthService::isA(const std::type_info& otherType) const
{
	std::string name(typeid(AuthService).name());
	return name == otherType.name() || Service::isA(otherType);
}


} } } // namespace Poco::OSP::Auth
