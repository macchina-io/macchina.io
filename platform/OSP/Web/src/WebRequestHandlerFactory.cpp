//
// WebRequestHandlerFactory.cpp
//
// $Id: //poco/1.7/OSP/Web/src/WebRequestHandlerFactory.cpp#1 $
//
// Library: OSP/Web
// Package: Web
// Module:  WebRequestHandlerFactory
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
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
