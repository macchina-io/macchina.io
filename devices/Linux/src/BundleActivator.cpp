//
// BundleActivator.cpp
//
// $Id$
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
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
#include "IoT/Devices/LEDServerHelper.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "Poco/SharedPtr.h"
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/Format.h"
#include "LinuxLED.h"
#include <vector>


using Poco::OSP::BundleContext;
using Poco::OSP::ServiceRegistry;
using Poco::OSP::ServiceRef;
using Poco::OSP::ServiceFinder;
using Poco::OSP::Properties;
using Poco::OSP::PreferencesService;


namespace IoT {
namespace Linux {


class BundleActivator: public Poco::OSP::BundleActivator
{
public:
	BundleActivator()
	{
	}
	
	~BundleActivator()
	{
	}
	
	void createLED(const std::string& device)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::LED> ServerHelper;
		
		std::string oid(LinuxLED::SYMBOLIC_NAME);
		oid += '#';
		oid += Poco::Path(device).getFileName();
		
		Poco::SharedPtr<LinuxLED> pLED = new LinuxLED(device, _pTimer);
		ServerHelper::RemoteObjectPtr pLEDRemoteObject = ServerHelper::createRemoteObject(pLED, oid);
		
		Properties props;
		props.set("io.macchina.device", LinuxLED::SYMBOLIC_NAME);
		
		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pLEDRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}
	
	void createLEDs()
	{
		Poco::File ledsDir("/sys/class/leds");
		if (ledsDir.exists() && ledsDir.isDirectory())
		{
			Poco::DirectoryIterator it(ledsDir);
			Poco::DirectoryIterator end;
			while (it != end)
			{
				if (it->isDirectory())
				{
					try
					{
						createLED(it.path().toString());
					}
					catch (Poco::Exception& exc)
					{
						_pContext->logger().error(Poco::format("Cannot create LED for device '%s': %s", it.path().toString(), exc.displayText()));
					}
				}
				++it;
			}
		}
	}
	
	void start(BundleContext::Ptr pContext)
	{
		_pTimer = new Poco::Util::Timer;
		_pContext = pContext;
		_pPrefs = ServiceFinder::find<PreferencesService>(pContext);
		
		try
		{
			createLEDs();
		}
		catch (Poco::Exception& exc)
		{
			_pContext->logger().log(exc);
		}
	}
		
	void stop(BundleContext::Ptr pContext)
	{
		_pTimer->cancel(true);
		_pTimer = 0;

		for (std::vector<ServiceRef::Ptr>::iterator it = _serviceRefs.begin(); it != _serviceRefs.end(); ++it)
		{
			_pContext->registry().unregisterService(*it);
		}
		_serviceRefs.clear();

		_pPrefs = 0;
		_pContext = 0;
	}
	
private:
	Poco::SharedPtr<Poco::Util::Timer> _pTimer;
	BundleContext::Ptr _pContext;
	PreferencesService::Ptr _pPrefs;
	std::vector<ServiceRef::Ptr> _serviceRefs;
};


} } // namespace IoT::Linux


POCO_BEGIN_MANIFEST(Poco::OSP::BundleActivator)
	POCO_EXPORT_CLASS(IoT::Linux::BundleActivator)
POCO_END_MANIFEST
