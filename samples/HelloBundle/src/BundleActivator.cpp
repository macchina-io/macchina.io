//
// BundleActivator.cpp
//
// Copyright (c) 2018, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/ClassLibrary.h"


namespace HelloBundle {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	void start(Poco::OSP::BundleContext::Ptr pContext)
	{
		pContext->logger().information("Hello, world!");
	}

	void stop(Poco::OSP::BundleContext::Ptr pContext)
	{
		pContext->logger().information("Goodbye!");
	}
};


} // namespace HelloBundle


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(HelloBundle::BundleActivator)
POCO_END_MANIFEST
