//
// SimpleAuthService.cpp
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// This is unpublished proprietary source code of Applied Informatics.
// The contents of this file may not be disclosed to third parties,
// copied or duplicated in any form, in whole or in part.
//


#include "Poco/OSP/Auth/AuthService.h"
#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/AutoPtr.h"
#include "Poco/StringTokenizer.h"
#include "Poco/ClassLibrary.h"
#include <set>


using Poco::OSP::BundleActivator;
using Poco::OSP::BundleContext;
using Poco::OSP::Bundle;
using Poco::OSP::Properties;
using Poco::OSP::Service;
using Poco::OSP::ServiceRef;
using Poco::OSP::PreferencesService;
using Poco::AutoPtr;
using Poco::StringTokenizer;


class SimpleAuthService: public Poco::OSP::Auth::AuthService
	/// A very simple implementation of AuthService.
	/// Only two users are known - "user" and "admin".
	/// Any password is valid for "user". The password for "admin"
	/// can be set in the global configuration file with the
	/// "adminPassword" property. If no password
	/// has been set in the global configuration file, a default
	/// password (stored in the bundle's properties) is used.
	/// The "admin" user has all permissions. The set of permissions
	/// for "user" can be set in the global configuration file,
	/// using the "userPermissions" property. The permissions are
	/// specified as a comma-separated list.
{
public:
	SimpleAuthService(const std::string& adminPassword, const std::set<std::string>& userPermissions):
		_adminPassword(adminPassword),
		_userPermissions(userPermissions)
	{
	}

	~SimpleAuthService()
	{
	}

	// AuthService
	bool authenticate(const std::string& userName, const std::string& credentials) const
	{
		return userName == "user" || (userName == "admin" && credentials == _adminPassword);
	}

	bool authorize(const std::string& userName, const std::string& permission) const
	{
		return userName == "admin" || (userName == "user" && _userPermissions.find(permission) != _userPermissions.end());
	}

	bool userExists(const std::string& userName) const
	{
		return userName == "admin" || userName == "user";
	}

	// Service
	const std::type_info& type() const
	{
		return typeid(SimpleAuthService);
	}

	bool isA(const std::type_info& otherType) const
	{
		std::string name(typeid(SimpleAuthService).name());
		return name == otherType.name() || Poco::OSP::Auth::AuthService::isA(otherType);
	}

private:
	std::string _adminPassword;
	std::set<std::string> _userPermissions;
};


class SimpleAuthServiceBundleActivator: public BundleActivator
	/// The BundleActivator for the SimpleAuthService.
	/// Registes the SimpleAuthService with the Service Registry.
{
public:
	SimpleAuthServiceBundleActivator()
	{
	}

	~SimpleAuthServiceBundleActivator()
	{
	}

	void start(BundleContext::Ptr pContext)
	{
		std::string adminPassword = pContext->thisBundle()->properties().getString("adminPassword", "admin");
		std::string perms = pContext->thisBundle()->properties().getString("userPermissions", "admin");
		std::set<std::string> userPermissions;

		// Find Preferences service
		ServiceRef::Ptr pPrefsRef = pContext->registry().findByName(PreferencesService::SERVICE_NAME);
		AutoPtr<PreferencesService> pPrefs = pPrefsRef->castedInstance<PreferencesService>();

		// Get admin password and user permissions from global config
		adminPassword = pPrefs->configuration()->getString("adminPassword", adminPassword);
		perms = pPrefs->configuration()->getString("userPermissions", perms);
		StringTokenizer tok(perms, ",;", StringTokenizer::TOK_TRIM | StringTokenizer::TOK_IGNORE_EMPTY);
		for (StringTokenizer::Iterator it = tok.begin(); it != tok.end(); ++it)
		{
			userPermissions.insert(*it);
		}

		// Create an instance of the SimpleAuthService
		AutoPtr<SimpleAuthService> pService = new SimpleAuthService(adminPassword, userPermissions);
		// Register the SimpleAuthService with the ServiceRegistry.
		_pService = pContext->registry().registerService("osp.auth", pService, Properties());
	}

	void stop(BundleContext::Ptr pContext)
	{
		// Unregister the GreetingService
		pContext->registry().unregisterService(_pService);
	}

private:
	ServiceRef::Ptr _pService;
};


POCO_BEGIN_MANIFEST(BundleActivator)
	POCO_EXPORT_CLASS(SimpleAuthServiceBundleActivator)
POCO_END_MANIFEST
