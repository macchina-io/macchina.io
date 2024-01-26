//
// ServiceRef.cpp
//
// Library: OSP
// Package: Service
// Module:  ServiceRef
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFactory.h"
#ifdef POCO_HAVE_CXXABI_H
#include <cxxabi.h>
#include <cstdlib>
#endif


using namespace std::string_literals;


namespace Poco {
namespace OSP {


ServiceRef::ServiceRef(const std::string& name, const Properties& props, Service::Ptr pService):
	_name(name),
	_props(props),
	_pService(pService)
{
}


ServiceRef::~ServiceRef()
{
}


Service::Ptr ServiceRef::instance() const
{
	Poco::AutoPtr<ServiceFactory> pFactory = _pService.cast<ServiceFactory>();
	if (pFactory)
	{	
		return pFactory->createService();
	}
	else
	{
		return _pService;
	}
}


std::string ServiceRef::demangle(const char* typeName)
{
	std::string result;
#ifdef POCO_HAVE_CXXABI_H
	int status;
	char* demangled = abi::__cxa_demangle(typeName, nullptr, nullptr, &status);
	if (demangled)
	{
		result = demangled;
		std::free(demangled);
	}
	else
	{
		result = typeName;
	}
#else
	result = typeName;
#endif	
	return result;
}


} } // namespace Poco::OSP
