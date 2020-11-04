//
// WebRequestHandlerFactory.cpp
//
// Library: OSP/Web
// Package: Web
// Module:  WebRequestHandlerFactory
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/Web/WebRequestHandlerFactory.h"


namespace Poco {
namespace OSP {
namespace Web {


WebRequestHandlerFactory::WebRequestHandlerFactory()
{
}


WebRequestHandlerFactory::~WebRequestHandlerFactory()
{
}


void WebRequestHandlerFactory::init(BundleContext::Ptr pContext)
{
	_pContext = pContext;
	initImpl();
}


void WebRequestHandlerFactory::initImpl()
{
}


} } } // namespace Poco::OSP::Web
