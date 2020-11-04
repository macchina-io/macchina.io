//
// SQLiteBundleActivator.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;
using Poco::OSP::PreferencesService;
using Poco::OSP::ServiceFinder;


class SQLiteBundleActivator: public BundleActivator
{
public:
	SQLiteBundleActivator()
	{
	}
	
	~SQLiteBundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
		Poco::Data::SQLite::Connector::registerConnector();

		PreferencesService::Ptr pPrefs = ServiceFinder::find<PreferencesService>(pContext);
		if (pPrefs)
		{
			bool sharedCache = pPrefs->configuration()->getBool("data.sqlite.sharedCache", false);
			if (sharedCache)
			{
				Poco::Data::SQLite::Connector::enableSharedCache(sharedCache);
			}
		
			bool heapLimit = pPrefs->configuration()->getInt("data.sqlite.softHeapLimit", 0);
			if (heapLimit)
			{
				Poco::Data::SQLite::Connector::enableSoftHeapLimit(heapLimit);
			}
		}
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		Poco::Data::SQLite::Connector::unregisterConnector();
	}
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(SQLiteBundleActivator)
POCO_END_MANIFEST
