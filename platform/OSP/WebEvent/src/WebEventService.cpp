//
// WebEventService.cpp
//
// $Id: //poco/1.7/OSP/WebEvent/src/WebEventService.cpp#1 $
//
// Library: OSP/WebEvent
// Package: WebEvent
// Module:  WebEventService
//
// Copyright (c) 2013, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/WebEvent/WebEventService.h"


namespace Poco {
namespace OSP {
namespace WebEvent {


const std::string WebEventService::SERVICE_NAME("com.appinf.osp.webevent");


WebEventService::WebEventService()
{
}


WebEventService::~WebEventService()
{
}


const std::type_info& WebEventService::type() const
{
	return typeid(WebEventService);
}


bool WebEventService::isA(const std::type_info& otherType) const
{
	std::string name(typeid(WebEventService).name());
	return name == otherType.name() || Poco::OSP::Service::isA(otherType);
}


} } } // namespace Poco::OSP::WebEvent
