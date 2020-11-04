//
// DataBundleActivator.cpp
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


class DataBundleActivator: public BundleActivator
{
public:
	DataBundleActivator()
	{
	}
	
	~DataBundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
	}
		
	void stop(BundleContext::Ptr pContext)
	{
	}
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(DataBundleActivator)
POCO_END_MANIFEST
