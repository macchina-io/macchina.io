//
// WebFilterFactory.cpp
//
// $Id: //poco/1.6/OSP/Web/src/WebFilterFactory.cpp#1 $
//
// Library: OSP/Web
// Package: Web
// Module:  WebFilterFactory
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/Web/WebFilterFactory.h"


namespace Poco {
namespace OSP {
namespace Web {


WebFilterFactory::WebFilterFactory()
{
}


WebFilterFactory::~WebFilterFactory()
{
}


void WebFilterFactory::init(BundleContext::Ptr pContext)
{
	_pContext = pContext;
	initImpl();
}


void WebFilterFactory::initImpl()
{
}


} } } // namespace Poco::OSP::Web
