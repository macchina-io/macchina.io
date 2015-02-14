//
// AuthService.cpp
//
// $Id: //poco/1.6/OSP/src/AuthService.cpp#1 $
//
// Library: OSP
// Package: Service
// Module:  AuthService
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
