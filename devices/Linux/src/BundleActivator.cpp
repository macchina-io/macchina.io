//
// BundleActivator.cpp
//
// Copyright (c) 2015, Applied Informatics Software Engineering GmbH.
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
#include "Poco/RemotingNG/ORB.h"
#include "IoT/Devices/LEDServerHelper.h"
#include "IoT/Devices/IOServerHelper.h"
#include "Poco/ClassLibrary.h"
#include "Poco/Format.h"
#include "Poco/NumberFormatter.h"
#include "Poco/NumberParser.h"
#include "Poco/SharedPtr.h"
#include "Poco/File.h"
#include "Poco/Path.h"
#include "Poco/DirectoryIterator.h"
#include "Poco/Format.h"
#include "Poco/StringTokenizer.h"
#include "LinuxLED.h"
#include "LinuxGPIO.h"
#include <vector>
#include <set>
#include <map>


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
		props.set("io.macchina.deviceType", "io.macchina.led");

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pLEDRemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void createLEDs(const std::set<std::string>& deviceWhitelist)
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
						if (deviceWhitelist.empty() || deviceWhitelist.count(it.path().getFileName()) == 1)
						{
							createLED(it.path().toString());
						}
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

	void createGPIO(const std::string& pin, const std::string& direction)
	{
		typedef Poco::RemotingNG::ServerHelper<IoT::Devices::IO> ServerHelper;

		std::string oid(LinuxGPIO::SYMBOLIC_NAME);
		oid += '#';
		oid += pin;

		const int pinIndex = Poco::NumberParser::parse(pin);
		LinuxGPIO::Direction gpioDirection = LinuxGPIO::toDirection(direction);

		Poco::SharedPtr<LinuxGPIO> pGPIO = new LinuxGPIO(pinIndex, gpioDirection);
		ServerHelper::RemoteObjectPtr pGPIORemoteObject = ServerHelper::createRemoteObject(pGPIO, oid);

		Properties props;
		props.set("io.macchina.device", LinuxGPIO::SYMBOLIC_NAME);
		props.set("io.macchina.deviceType", LinuxGPIO::TYPE);

		ServiceRef::Ptr pServiceRef = _pContext->registry().registerService(oid, pGPIORemoteObject, props);
		_serviceRefs.push_back(pServiceRef);
	}

	void createGPIOs(const std::map<std::string, std::string>& deviceWhitelist)
	{
		Poco::File gpioDir("/sys/class/gpio");
		if (gpioDir.exists() && gpioDir.isDirectory())
		{
			std::map<std::string, std::string>::const_iterator it = deviceWhitelist.begin();
			std::map<std::string, std::string>::const_iterator end = deviceWhitelist.end();
			for (;it != end; ++it)
			{
				createGPIO(it->first, it->second);
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
			if (_pPrefs->configuration()->getBool("linux.leds.enable", true))
			{
				std::string devices = _pPrefs->configuration()->getString("linux.leds.whitelist", "");
				Poco::StringTokenizer tok(devices, ",;", Poco::StringTokenizer::TOK_TRIM | Poco::StringTokenizer::TOK_IGNORE_EMPTY);
				std::set<std::string> deviceWhitelist(tok.begin(), tok.end());
				createLEDs(deviceWhitelist);
			}

			if (_pPrefs->configuration()->getBool("linux.gpio.enable", true))
			{
				std::map<std::string, std::string> gpioMap;
				Poco::Util::AbstractConfiguration::Keys keys;
				_pPrefs->configuration()->keys("linux.gpio.pins", keys);

				for (std::vector<std::string>::const_iterator it = keys.begin(); it != keys.end(); ++it)
				{
					std::string baseKey = "linux.gpio.pins.";
					baseKey += *it;

					std::string direction = _pPrefs->configuration()->getString(baseKey + ".direction", "out");
					gpioMap[*it] = direction;
				}

				createGPIOs(gpioMap);
			}
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
