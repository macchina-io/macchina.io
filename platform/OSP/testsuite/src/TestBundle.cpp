//
// TestBundle.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;


class MyBundleActivator: public BundleActivator
{
public:
	MyBundleActivator()
	{
	}
	
	~MyBundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
		std::string msg("MyBundleActivator::start() for ");
		msg.append(pContext->thisBundle()->name());
		pContext->logger().information(msg);
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		std::string msg("MyBundleActivator::stop() for ");
		msg.append(pContext->thisBundle()->name());
		pContext->logger().information(msg);
	}
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(MyBundleActivator)
POCO_END_MANIFEST
