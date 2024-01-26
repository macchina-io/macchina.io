//
// ODBCBundleActivator.cpp
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties, 
// copied or duplicated in any form, in whole or in part.
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/Data/ODBC/Connector.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;
using Poco::OSP::PreferencesService;
using Poco::OSP::ServiceFinder;


class ODBCBundleActivator: public BundleActivator
{
public:
	ODBCBundleActivator()
	{
	}
	
	~ODBCBundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
		Poco::Data::ODBC::Connector::registerConnector();

		PreferencesService::Ptr pPrefs = ServiceFinder::find<PreferencesService>(pContext);
		if (pPrefs)
		{
			bool flag = pPrefs->configuration()->getBool("data.odbc.bindStringToLongVarChar", true);
			Poco::Data::ODBC::Connector::bindStringToLongVarChar(flag);
		}
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		Poco::Data::ODBC::Connector::unregisterConnector();
	}
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(ODBCBundleActivator)
POCO_END_MANIFEST
