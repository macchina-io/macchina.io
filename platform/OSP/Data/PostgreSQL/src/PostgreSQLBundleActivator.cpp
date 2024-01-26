//
// PostgreSQLBundleActivator.cpp
//
// Copyright (c) 2020, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/Data/PostgreSQL/Connector.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;


class PostgreSQLBundleActivator: public BundleActivator
{
public:
	PostgreSQLBundleActivator()
	{
	}

	~PostgreSQLBundleActivator()
	{
	}

	void start(BundleContext::Ptr pContext)
	{
		Poco::Data::PostgreSQL::Connector::registerConnector();
	}

	void stop(BundleContext::Ptr pContext)
	{
		Poco::Data::PostgreSQL::Connector::unregisterConnector();
	}
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(PostgreSQLBundleActivator)
POCO_END_MANIFEST
