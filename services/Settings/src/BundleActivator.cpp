//
// BundleActivator.cpp
//
// Copyright (c) 2023, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: GPL-3.0-only
//


#include "IoT/Settings/SettingsServiceImpl.h"
#include "IoT/Settings/SettingsServiceServerHelper.h"
#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/Util/LayeredConfiguration.h"
#include "Poco/Util/Application.h"
#include "Poco/ClassLibrary.h"


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::Properties;
using namespace std::string_literals;


namespace IoT {
namespace Settings {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	using ServerHelper = Poco::RemotingNG::ServerHelper<IoT::Settings::SettingsService>;
		
	BundleActivator()
	{
	}
	
	~BundleActivator()
	{
	}

	void start(BundleContext::Ptr pContext)
	{
		Poco::Util::Application& app = Poco::Util::Application::instance();
		Poco::AutoPtr<Poco::Util::LayeredConfiguration> pLayered = app.configPtr();
		const std::string settingsPath = pLayered->getString("macchina.settings.path"s, ""s);
		if (!settingsPath.empty())
		{
			Poco::AutoPtr<Poco::Util::AbstractConfiguration> pConf = pLayered->find("macchina.settings"s);
			if (pConf)
			{
				Poco::AutoPtr<Poco::Util::PropertyFileConfiguration> pSettings = pConf.cast<Poco::Util::PropertyFileConfiguration>();
				if (pSettings)
				{
					Poco::SharedPtr<IoT::Settings::SettingsService> pSettingsService = new SettingsServiceImpl(pLayered, pSettings, settingsPath);
					const std::string oid("io.macchina.services.settings");
					ServerHelper::RemoteObjectPtr pSettingsServiceRemoteObject = ServerHelper::createRemoteObject(pSettingsService, oid);		
					_pServiceRef = pContext->registry().registerService(oid, pSettingsServiceRemoteObject, Properties());
					pContext->logger().information("Settings configuration found. Settings will be saved to %s."s, settingsPath);
				}
				else
				{
					pContext->logger().warning("Settings configuration is not a PropertyFileConfiguration. SettingsService will not be available."s);
				}
			}
			else
			{
				pContext->logger().warning("No 'macchina.settings' in application configuration. SettingsService will not be available."s);
			}
		}
		else
		{
			pContext->logger().warning("No macchina.settings.path in application configuration. SettingsService will not be available."s);
		}
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		pContext->registry().unregisterService(_pServiceRef);
		_pServiceRef.reset();
		
		ServerHelper::shutdown();
	}

private:
	Poco::OSP::ServiceRef::Ptr _pServiceRef;
};


} } // namespace IoT::Settings


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Settings::BundleActivator)
POCO_END_MANIFEST
