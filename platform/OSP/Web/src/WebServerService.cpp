//
// WebServerService.cpp
//
// $Id: //poco/1.4/OSP/Web/src/WebServerService.cpp#2 $
//
// Library: OSP/Web
// Package: Web
// Module:  WebServerService
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/Web/WebServerService.h"


namespace Poco {
namespace OSP {
namespace Web {


WebServerService::WebServerService()
{
}


WebServerService::~WebServerService()
{
}


const std::type_info& WebServerService::type() const
{
	return typeid(WebServerService);
}


bool WebServerService::isA(const std::type_info& otherType) const
{
	std::string name(typeid(WebServerService).name());
	return name == otherType.name() || Service::isA(otherType);
}


} } } // namespace Poco::OSP::Web
