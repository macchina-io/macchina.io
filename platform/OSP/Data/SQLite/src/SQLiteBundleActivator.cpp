//
// SQLiteBundleActivator.cpp
//
// $Id: //poco/1.6/OSP/Data/SQLite/src/SQLiteBundleActivator.cpp#1 $
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/Data/SQLite/Connector.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;


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
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		Poco::Data::SQLite::Connector::unregisterConnector();
	}
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(SQLiteBundleActivator)
POCO_END_MANIFEST
