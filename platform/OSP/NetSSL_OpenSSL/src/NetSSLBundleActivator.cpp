//
// NetSSLBundleActivator.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/Net/HTTPSStreamFactory.h"
#include "Poco/Net/HTTPSSessionInstantiator.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;
using Poco::Net::HTTPSStreamFactory;
using Poco::Net::HTTPSSessionInstantiator;


class NetSSLBundleActivator: public BundleActivator
{
public:
	NetSSLBundleActivator()
	{
	}
	
	~NetSSLBundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
		Poco::Net::initializeSSL();
		HTTPSStreamFactory::registerFactory();
		HTTPSSessionInstantiator::registerInstantiator();
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		HTTPSSessionInstantiator::unregisterInstantiator();
		HTTPSStreamFactory::unregisterFactory();
		Poco::Net::uninitializeSSL();
	}
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(NetSSLBundleActivator)
POCO_END_MANIFEST
