//
// ActiveRecordBundleActivator.cpp
//
// Copyright (c) 2020-2021, Applied Informatics Software Engineering GmbH.
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


class ActiveRecordBundleActivator: public BundleActivator
{
public:
	ActiveRecordBundleActivator()
	{
	}

	~ActiveRecordBundleActivator()
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
	POCO_EXPORT_CLASS(ActiveRecordBundleActivator)
POCO_END_MANIFEST
