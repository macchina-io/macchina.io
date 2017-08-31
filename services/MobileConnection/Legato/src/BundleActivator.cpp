//
// BundleActivator.cpp
//
// $Id$
//
// Copyright (c) 2017, Applied Informatics Software Engineering GmbH.
// All rights reserved.
//
// SPDX-License-Identifier: Apache-2.0
//


#include "Poco/OSP/BundleActivator.h"
#include "Poco/OSP/BundleContext.h"
#include "Poco/OSP/Bundle.h"
#include "Poco/OSP/ServiceRegistry.h"
#include "Poco/OSP/ServiceRef.h"
#include "Poco/OSP/ServiceFinder.h"
#include "Poco/OSP/PreferencesService.h"
#include "Poco/RemotingNG/ORB.h"
#include "MobileConnectionServiceImpl.h"
#include "IoT/MobileConnection/MobileConnectionServiceServerHelper.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace MobileConnection {
namespace Legato {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	typedef Poco::RemotingNG::ServerHelper<IoT::MobileConnection::MobileConnectionService> ServerHelper;

	BundleActivator()
	{
	}

	~BundleActivator()
	{
	}

	void createMobileConnectionService(const std::string& cmPath)
	{
		Poco::SharedPtr<MobileConnectionServiceImpl> pMCS = new MobileConnectionServiceImpl(cmPath);
		std::string symbolicName = "io.macchina.mobileconnection.legato";
		Poco::RemotingNG::Identifiable::ObjectId oid = symbolicName;
		ServerHelper::RemoteObjectPtr pMCSRemoteObject = ServerHelper::createRemoteObject(pMCS, oid);

		Properties props;
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pMCSRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void start(BundleContext::Ptr pContext)
	{
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);

		bool enable = _pPrefs->configuration()->getBool("legato.mobileconnection.enable", false);
		if (enable)
		{
			pContext->logger().information("Creating Legato MobileConnectionService.");
			std::string cmPath = _pPrefs->configuration()->getString("legato.mobileconnection.cm.path", MobileConnectionServiceImpl::DEFAULT_CM_PATH);
			createMobileConnectionService(cmPath);
		}
	}

	void stop(BundleContext::Ptr pContext)
	{
		for (std::vector<ServiceRef::Ptr>::iterator it = _serviceRefs.begin(); it != _serviceRefs.end(); ++it)
		{
			_pContext->registry().unregisterService(*it);
		}
		_serviceRefs.clear();
		_pPrefs = 0;
		_pContext = 0;

		ServerHelper::shutdown();
	}

private:
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	std::vector<ServiceRef::Ptr> _serviceRefs;
};


} } } // namespace IoT::MobileConnection::Legato


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::MobileConnection::Legato::BundleActivator)
POCO_END_MANIFEST
