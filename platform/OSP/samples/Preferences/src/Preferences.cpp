//
// Preferences.cpp
//
// Copyright (c) 2007-2016, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/OSP/Preferences.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/DateTime.h"
#include "Poco/DateTimeFormatter.h"
#include "Poco/DateTimeFormat.h"
#include "Poco/AutoPtr.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;
using Poco::OSP::PreferencesService;
using Poco::OSP::Preferences;
using Poco::OSP::ServiceRef;
using Poco::DateTime;
using Poco::DateTimeFormatter;
using Poco::DateTimeFormat;
using Poco::AutoPtr;


class PreferencesBundleActivator: public BundleActivator
	/// A very simple bundle that shows the usage
	/// of the PreferencesService.
{
public:
	PreferencesBundleActivator()
	{
	}
	
	~PreferencesBundleActivator()
	{
	}
	
	void start(BundleContext::Ptr pContext)
	{		
		// find PreferencesService using the Service Registry
		ServiceRef::Ptr pPrefsSvcRef = pContext->registry().findByName("osp.core.preferences");
		if (pPrefsSvcRef)
		{
			// PreferencesService is available
			AutoPtr<PreferencesService> pPrefsSvc = pPrefsSvcRef->castedInstance<PreferencesService>();
			
			// Get the preferences for our bundle
			_pPrefs = pPrefsSvc->preferences(pContext->thisBundle()->symbolicName());
			
			// Do something with the preferences
			std::string lastStartup = _pPrefs->getString("lastStartup", "never");
			std::string lastShutdown = _pPrefs->getString("lastShutdown", "never");
			pContext->logger().information(std::string("Last startup at: ") + lastStartup);
			pContext->logger().information(std::string("Last shutdown at: ") + lastShutdown);
			DateTime now;
			std::string dateStr = DateTimeFormatter::format(now, DateTimeFormat::SORTABLE_FORMAT);
			_pPrefs->setString("lastStartup", dateStr);
		}
		else
		{
			// The service is not available
			pContext->logger().error("The PreferencesService is not available.");
		}
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		if (_pPrefs)
		{
			DateTime now;
			std::string dateStr = DateTimeFormatter::format(now, DateTimeFormat::SORTABLE_FORMAT);
			_pPrefs->setString("lastShutdown", dateStr);
		}
	}
	
private:
	AutoPtr<Preferences> _pPrefs;
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(PreferencesBundleActivator)
POCO_END_MANIFEST
