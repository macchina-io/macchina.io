//
// TokenValidator.cpp
//
// Library: OSP/Web
// Package: Web
// Module:  TokenValidator
//
// Copyright (c) 2019, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/Web/TokenValidator.h"


namespace Poco {
namespace OSP {
namespace Web {


const std::type_info& TokenValidator::type() const
{
	return typeid(TokenValidator);
}


bool TokenValidator::isA(const std::type_info& otherType) const
{
	std::string name(typeid(TokenValidator).name());
	return name == otherType.name() || Service::isA(otherType);
}


} } } // namespace Poco::OSP::Web
