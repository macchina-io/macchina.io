//
// ModuleFactory.cpp
//
// Library: OSP/JS
// Package: Module
// Module:  ModuleFactory
//
// Copyright (c) 2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/JS/ModuleFactory.h"


namespace Poco {
namespace OSP {
namespace JS {


ModuleFactory::ModuleFactory()
{
}

	
ModuleFactory::~ModuleFactory()
{
}


void ModuleFactory::init(Poco::OSP::BundleContext::Ptr pContext)
{
	_pContext = pContext;
	initImpl();
}


void ModuleFactory::initImpl()
{
}


} } } // namespace Poco::OSP::JS
