//
// CryptoBundleActivator.cpp
//
// Copyright (c) 2007-2014, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/Crypto/Crypto.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;


class CryptoBundleActivator: public BundleActivator
{
public:
	CryptoBundleActivator()
	{
	}
	
	~CryptoBundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{
		Poco::Crypto::initializeCrypto();
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		Poco::Crypto::uninitializeCrypto();
	}
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(CryptoBundleActivator)
POCO_END_MANIFEST
